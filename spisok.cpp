#define CATCH_CONFIG_MAIN
#include "catch.hpp"


struct Node {
    int data = 0;
    Node *prev = nullptr;
    Node *next = nullptr;
};
struct List {
    Node *head = nullptr;
    Node *tail = nullptr;
    void plus_end(Node *x){
        x->prev = tail;
        if (tail != nullptr) {
            tail->next = x;
        }
        else{
            head = x;
        }
        tail = x;
    }
    void plus_begin(Node *x){
        x->next = head;
        if (head != nullptr){
            head->prev = x;}
        else{
            tail = x;
        }
        head = x;

    }
    void plus_middle(Node *x, Node *y){
        x->prev = y;
        x->next = y->next;
        y->next->prev = x;
        y->next = x;
    }
    void minus_middle(Node *x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    void minus_end(){
        if (tail->prev != nullptr) {
            tail->prev->next = nullptr;
        }
        tail = tail->prev;
    }
    void minus_begin(){
        if (head->next != nullptr) {
            head->next->prev = nullptr;
        }
        head = head->next;
    }


};

TEST_CASE("ahayo"){
    List a;
    Node b,c,d;
    b.data = 10;
    a.plus_begin(&b);
    REQUIRE(a.head->data == 10);
    c.data = 15;
    a.plus_end(&c);
    REQUIRE(a.tail->data == 15);
    d.data = 17;
    REQUIRE(b.next->data == 15);
    a.plus_middle(&d, &b);
    REQUIRE(b.next->data == 17);
    REQUIRE(c.prev->data == 17);
    a.minus_middle(&d);
    REQUIRE(b.next->data == 15);
    REQUIRE(c.prev->data == 10);
    a.minus_begin();
    REQUIRE(a.head->data == 15);
    a.plus_end(&b);
    a.minus_end();
    REQUIRE(a.head->data == 15 );

}