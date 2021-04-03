#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <memory>
#include <type_traits>


template <class T>
class vector {
private:
    std::size_t cp = 0;
    T *arr = nullptr;
    std::size_t sz = 0;


    void new_mem() {
        if (cp != 0) {
            T *new_arr = new T[2 * cp];
            for (int i = 0; i < sz; i++) {
                new_arr[i] = arr[i];
            }
            arr = new_arr;
            cp=cp*2;
        }
        else{
            cp++;
            T *new_arr = new T[cp];
            arr=new_arr;
        }
    }
public:
    vector()=default;
    T &operator[](std::size_t n) &{
        return arr[n];
    }
    T &&operator[](std::size_t n) &&{
        return std::move(arr[n]);
    }

    std::size_t size(){
        return sz;
    }

    bool empty(){
        return sz==0;
    }

    void push_back(T t){
        if (sz == cp){
            new_mem();
        }
        arr[sz] = t;
        sz++;
    }

    void pop_back(){
        if (sz!=0){
            sz--;
        }
    }

    vector(vector &&other): cp(std::exchange(other.cp, 0)),
                            arr(std::exchange(other.arr, nullptr)),
                            sz(std::exchange(other.sz, 0)) {
    }

    vector(const vector& other): cp(other.cp), sz(other.sz) {
        if (sz != 0) delete[] arr;
        arr = new T[cp];
        for (int i = 0; i < sz; ++i) {
            arr[i] = std::move(other.arr[i]);
        }
    }

    vector& operator=(vector&& outer) {
        sz=std::move(outer.sz);
        cp=std::move(outer.cp);
        if (sz != 0) delete[] arr;
        arr = new T[cp];
        for (int i = 0; i < sz; ++i) {
            arr[i] = std::move(outer.arr[i]);
        }
        return *this;
    }

    vector& operator=(const vector& outer) {
        sz=outer.sz;
        cp=outer.cp;
        if (sz != 0) delete[] arr;
        arr = new T[cp];
        for (int i = 0; i < sz; ++i) {
            arr[i] = outer.arr[i];
        }
        return *this;
    }

};






TEST_CASE() {
    vector<int> tested;

    for (int i = 0; i < 5; i++) {
        tested.push_back(i);
    }

    vector<int32_t> one_more_tested;
    one_more_tested = tested;

    REQUIRE(one_more_tested[0] == 0);
    REQUIRE(one_more_tested[1] == 1);
    REQUIRE(one_more_tested[2] == 2);
    REQUIRE(one_more_tested[3] == 3);
    REQUIRE(one_more_tested[4] == 4);
    REQUIRE(one_more_tested.size() == 5);

    tested.pop_back();

    REQUIRE(tested[0] == 0);
    REQUIRE(tested[1] == 1);
    REQUIRE(tested[2] == 2);
    REQUIRE(tested[3] == 3);
    REQUIRE(tested.size() == 4);
}


TEST_CASE() {
    vector<int> tested;


    for (int i = 0; i < 5; i++) {
        tested.push_back(i);
    }

    vector<int32_t> moved_tested(std::move(tested));
    REQUIRE(moved_tested[0] == 0);
    REQUIRE(moved_tested[1] == 1);
    REQUIRE(moved_tested[2] == 2);
    REQUIRE(moved_tested[3] == 3);
    REQUIRE(moved_tested[4] == 4);
    REQUIRE(moved_tested.size() == 5);

    vector<int32_t> asgn_mv_tested;
    asgn_mv_tested = std::move(moved_tested);
    REQUIRE(asgn_mv_tested[0] == 0);
    REQUIRE(asgn_mv_tested[1] == 1);
    REQUIRE(asgn_mv_tested[2] == 2);
    REQUIRE(asgn_mv_tested[3] == 3);
    REQUIRE(asgn_mv_tested[4] == 4);
    REQUIRE(asgn_mv_tested.size() == 5);
}


