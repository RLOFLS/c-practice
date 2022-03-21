#include "linked_list_test.h"
#include "linked_list.h"

void test_all() {
    test_empty();
    test_push_front();
    test_value_at();
    test_pop_front();
    test_push_back();
    test_pop_back();
    test_front_and_back();
    test_insert();
    test_earse();
    test_vale_n_from_end();
    test_reverse();
    test_remove_value();


    //test_value_at_out_range();
    //test_pop_front_empty();
    
}

void test_empty() {
    LinkedList *l = list_new();
    assert(empty(l));

    free_list(l);
}

void test_push_front() {
    LinkedList *l = list_new();
    push_front(l, 1);
    push_front(l, 2);
    push_front(l, 3);
    print_debug(l);
    // /list:3 -> 2 -> 1 ->

    free_list(l);
}

void test_value_at() {
    LinkedList *l = list_new();
    push_front(l, 1);
    push_front(l, 2);
    push_front(l, 3);

    assert(value_at(l, 0) == 3);
    assert(value_at(l, 1) == 2);
    assert(value_at(l, 2) == 1);

    free_list(l);
}

void test_value_at_out_range() {
   LinkedList *l = list_new();
   value_at(l, 1);
   free_list(l);
}

void test_pop_front() {
    LinkedList *l = list_new();
    push_front(l, 1);
    push_front(l, 2);
    assert(2 == pop_front(l));
    assert(1 == pop_front(l));

    assert(empty(l));

    free_list(l);
}

void test_pop_front_empty() {
    LinkedList *l = list_new();
    pop_front(l);
}

void test_push_back() {
    LinkedList *l = list_new();
    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    print_debug(l); //list:1 -> 2 -> 3 -> 
    free_list(l);
}

void test_pop_back() {
    LinkedList *l = list_new();
    push_front(l, 1);
    push_back(l,2);
    push_back(l, 3);

    assert(3 == pop_back(l));
    assert(2 == pop_back(l));
    assert(1 == pop_back(l));

    assert(empty(l));

    free_list(l);
}

void test_front_and_back() {
    LinkedList *l = list_new();

    push_back(l, 1);
    assert(1 == front(l));
    assert(1 == back(l));

    push_front(l, 2);
    assert(2 == front(l));
    assert(1 == back(l));

    print_debug(l); //list:2 -> 1 ->

    free_list(l);
}

void test_insert() {
    LinkedList *l = list_new();

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);

    print_debug(l); //list:1 -> 2 -> 3 ->

    insert(l, 0, 11);
    insert(l, 1, 22);
    insert(l, 1, 222); //list:11 -> 222 -> 3 ->

    print_debug(l);

    free_list(l);
}

void test_earse() {
    LinkedList *l = list_new();

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);

    erase(l, 1);
    print_debug(l); //list:1 -> 3 -> 

    erase(l, 0);
    erase(l, 0);
    assert(empty(l));

    free_list(l);
}

void test_vale_n_from_end() {
    LinkedList *l = list_new();

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    push_back(l, 4);
    assert(vale_n_from_end(l, 1) == 4);
    assert(vale_n_from_end(l, 2) == 3);
    assert(vale_n_from_end(l, 3) == 2);
    assert(vale_n_from_end(l, 4) == 1);

    free_list(l);
}

void test_reverse() {
    LinkedList *l = list_new();

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    push_back(l, 4);

    reverse(l);

    print_debug(l); //list:4 -> 3 -> 2 -> 1 -> 

    pop_back(l);
    pop_back(l);

    reverse(l);
    print_debug(l); //list:3 -> 4 -> 
    free_list(l);
}

void test_remove_value() {
    LinkedList *l = list_new();

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    push_back(l, 4);

    remove_value(l, 2); 

    print_debug(l); //list:1 -> 3 -> 4 -> 

    remove_value(l, 1); 
    remove_value(l, 4); 
    remove_value(l, 3); 
    assert(empty(l));

    free_list(l);
}