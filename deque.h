#include <cstring>

template <typename T>
class Deque {
private:
	size_t max_size = 2;

	T*data = new T[2];
	size_t begin_position = 1, end_position = 1;

	void realloc_(size_t new_size, size_t start = 0);

	size_t capacity() const { return max_size; }

public:
	Deque() = default;
	Deque(size_t size, T default_val = T());
	Deque(const Deque<T>& value) : begin_position(value.begin_position), end_position(value.end_position) {
		realloc_(value.max_size);
		memcpy(data, value.data, end_position * sizeof(T));
	}

	Deque<T>& resize(size_t new_size, T default_val = T());

	Deque<T>& clear() {
		realloc_(2);
		begin_position = end_position = 1;
		return *this;
	}

	Deque<T>& operator=(const Deque<T>& c);

	Deque<T>(const std::initializer_list<T>& lst);

	size_t size() const { return end_position - begin_position; }

	T& operator[](size_t index) {
		return data[index + begin_position];
	}

	T operator[](size_t index) const {
		return data[index + begin_position];
	}

	T& at(size_t index) {
		if (index >= size()) throw std::out_of_range("index out of range");
		return data[index + begin_position];
	}

	T at(size_t index) const {
		if (index >= size()) throw std::out_of_range("index out of range");
		return data[index + begin_position];
	}

	Deque<T>& push_back(const T& value);

	Deque<T>& pop_back() {
		--end_position;
		return *this;
	}

	Deque<T>& push_front(const T& value);

	Deque<T>& pop_front() {
		++begin_position;
		return *this;
	}

	bool empty() const {
		return begin_position == end_position;
	}

	Deque<T>& reverse() {
		int count = static_cast<int>(size()) / 2;
		for (int i = 0; i < count; ++i) {
			std::swap(data[i + begin_position], data[(static_cast<int>(size()) - i - 1) + begin_position]);
		}
		return *this;
	}

	class const_iterator;
	class iterator;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	Deque<T>& insert(iterator iter, T value);
	Deque<T>& erase(iterator iter);

	~Deque() {
		delete[] data;
	}
};

template <typename T>
Deque<T>& Deque<T>::resize(size_t new_size, T default_val) {
	realloc_(new_size);
	for (size_t i = size(); i < new_size; ++i) {
		data[i] = default_val;
	}
	end_position = new_size;
	begin_position = 0;
	return *this;
}

template <typename T>
bool operator== (const Deque<T>& left, const Deque<T>& right) {
	if (left.size() != right.size())return 0;
	for (int i = 0; i < static_cast<int>(left.size()); ++i) if (left[i] != right[i]) return false;
	return true;
}

template <typename T>
bool operator!= (const Deque<T>& left, const Deque<T>& right) {
	return !(left == right);
}

template <typename T>
Deque<T>::Deque(size_t size, T default_val) {
	resize(size);
	for (size_t i = 0; i < size; ++i) {
		data[i] = default_val;
	}
}

template <typename T>
Deque<T>& Deque<T>::operator= (const Deque<T>& value) {
	if (&value == this) return *this;
	realloc_(value.max_size);
	begin_position = value.begin_position;
	end_position = value.end_position;
	memcpy(data, value.data, end_position * sizeof(T));
	return *this;
}

template <typename T>
void Deque<T>::realloc_(size_t new_size, size_t start) {
	max_size = new_size;
	T* pt = data;
	data = new T[max_size];
	size_t last_size = size();
	//memcpy(data + start, pt + begin_position, std::min(new_size - start, last_size) * sizeof(T));
	for (size_t i = 0; i < std::min(new_size - start, last_size); ++i) {
		data[start + i] = pt[begin_position + i];
	}
	begin_position = start;
	end_position = std::min(new_size, begin_position + last_size);
	delete[] pt;
}

template <typename T>
Deque<T>::Deque(const std::initializer_list<T>& lst) {
	resize(lst.size());
	std::copy(lst.begin(), lst.end(), data);
}

template <typename T>
Deque<T>& Deque<T>::push_back(const T& value) {
	if (end_position == max_size) {
		realloc_(max_size * 3, max_size + begin_position);
	}
	data[end_position++] = value;
	return *this;
}

template <typename T>
Deque<T>& Deque<T>::push_front(const T& value) {
	if (begin_position == 0) {
		realloc_(max_size * 3, max_size + begin_position);
	}
	data[--begin_position] = value;
	return *this;
}

template <typename T>
class Deque<T>::const_iterator {
protected:
	const Deque<T>* deque = nullptr;
	int v_index = 0;
	size_t max_size;

	int get_index() const {
		return (deque->capacity() - max_size) / 2 + v_index;
	}

public:
	const_iterator() = default;
	const_iterator(const Deque<T>* deque, int v_index) : deque(deque), v_index(v_index), max_size(deque->max_size) {}
	const_iterator(const const_iterator&) = default;
	const_iterator& operator=(const const_iterator&) = default;

	const_iterator& operator++() {
		++v_index;
		return *this;
	}

	const_iterator& operator--() {
		--v_index;
		return *this;
	}

	const_iterator operator++(int) {
		const_iterator answer = *this;
		++(*this);
		return answer;
	}

	const_iterator operator--(int) {
		const_iterator answer = *this;
		--(*this);
		return answer;
	}

	const_iterator& operator+=(int value) {
		v_index += value;
		return *this;
	}

	const_iterator& operator-=(int value) {
		v_index -= value;
		return *this;
	}

	int operator-(const const_iterator& iter) const {
		return get_index() - iter.get_index();
	}

	const T& operator*() const {
		return deque->data[get_index()];
	}

	const T* operator->() const {
		return &deque->data[get_index()];
	}

	const_iterator operator+(int value) const {
		const_iterator iter = *this;
		iter += value;
		return iter;
	}

	friend const_iterator operator+(int value, const_iterator iter) {
		iter += value;
		return iter;
	}

	const_iterator operator-(int value) const {
		const_iterator iter = *this;
		iter -= value;
		return iter;
	}

	bool operator==(const const_iterator& other) const {
		return *this - other == 0;
	}

	bool operator!=(const const_iterator& other) const {
		return !(*this == other);
	}

	bool operator<(const const_iterator& other) const {
		return *this - other < 0;
	}

	bool operator>(const const_iterator& other) const {
		return other < *this;
	}

	bool operator<=(const const_iterator& other) const {
		return !(other < *this);
	}

	bool operator>=(const const_iterator& other) const {
		return !(*this < other);
	}
};

template <typename T>
class Deque<T>::iterator : public Deque<T>::const_iterator {
public:
	using const_iterator::operator++;
	using const_iterator::operator--;
	using const_iterator::operator-;

	iterator() = default;
	iterator(const Deque<T>* deque, size_t v_index) : const_iterator(deque, v_index) {}
	iterator(const iterator&) = default;
	iterator& operator=(const iterator&) = default;

	T& operator*() const {
		return const_iterator::deque->data[const_iterator::get_index()];
	}

	T* operator->() const {
		return &const_iterator::deque->data[const_iterator::get_index()];
	}

	iterator operator++(int) {
		iterator answer = *this;
		++(*this);
		return answer;
	}

	iterator operator--(int) {
		iterator answer = *this;
		--(*this);
		return answer;
	}

	iterator operator+(int value) const {
		iterator iter = *this;
		iter += value;
		return iter;
	}

	friend iterator operator+(int value, iterator iter) {
		iter += value;
		return iter;
	}

	iterator operator-(int value) const {
		iterator iter = *this;
		iter -= value;
		return iter;
	}
};

template <typename T>
typename Deque<T>::iterator Deque<T>::begin() {
	return iterator(this, begin_position);
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::begin() const {
	return const_iterator(this, begin_position);
}

template <typename T>
typename Deque<T>::iterator Deque<T>::end() {
	return iterator(this, end_position);
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::end() const {
	return const_iterator(this, end_position);
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const {
	return const_iterator(this, begin_position);
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cend() const {
	return const_iterator(this, end_position);
}

template <typename T>
Deque<T>& Deque<T>::insert(typename Deque<T>::iterator iter, T value) {
	push_back(T());
	T cur_value = *iter;
	*iter = value;
	++iter;
	while (iter != end()) {
		std::swap(*iter, cur_value);
		++iter;
	}
	return *this;
}

template <typename T>
Deque<T>& Deque<T>::erase(typename Deque<T>::iterator iter) {
	++iter;
	while (iter != end()) {
		*(iter - 1) = *iter;
		++iter;
	}
	pop_back();
	return *this;
}