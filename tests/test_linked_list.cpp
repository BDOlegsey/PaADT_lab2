#include "../include/errors.h"
#include "../include/linked_list.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestLinkedList() {
    std::printf("\n[LinkedList]\n");

    LinkedList<int> empty;
    T_ASSERT_EQ("empty length", empty.GetLength(), 0);

    int values[] = {10, 20, 30};
    LinkedList<int> list(values, 3);
    T_ASSERT_EQ("from array length", list.GetLength(), 3);
    T_ASSERT_EQ("first", list.GetFirst(), 10);
    T_ASSERT_EQ("last", list.GetLast(), 30);
    T_ASSERT_EQ("middle", list.Get(1), 20);

    list.Append(40);
    T_ASSERT_EQ("after append last", list.GetLast(), 40);
    T_ASSERT_EQ("after append size", list.GetLength(), 4);

    list.Prepend(0);
    T_ASSERT_EQ("after prepend first", list.GetFirst(), 0);
    T_ASSERT_EQ("after prepend size", list.GetLength(), 5);

    list.InsertAt(99, 2);
    T_ASSERT_EQ("after insert", list.Get(2), 99);

    list.Set(0, 7);
    T_ASSERT_EQ("after set", list.GetFirst(), 7);

    LinkedList<int>* sub = list.GetSubList(1, 3);
    T_ASSERT_EQ("sublist size", sub->GetLength(), 3);
    T_ASSERT_EQ("sublist first", sub->GetFirst(), 10);
    delete sub;

    int more[] = {100, 200};
    LinkedList<int> tail(more, 2);
    LinkedList<int>* concat = list.Concat(&tail);
    T_ASSERT_EQ("concat size", concat->GetLength(), list.GetLength() + 2);
    T_ASSERT_EQ("concat last", concat->GetLast(), 200);
    delete concat;

    LinkedList<int> copy(list);
    T_ASSERT_EQ("copy size", copy.GetLength(), list.GetLength());
    T_ASSERT_EQ("copy first", copy.GetFirst(), list.GetFirst());

    T_ASSERT_THROWS("get out of range", IndexOutOfRange, list.Get(100));
    LinkedList<int> empty2;
    T_ASSERT_THROWS("first on empty", IndexOutOfRange, empty2.GetFirst());
}

}  // namespace tests
}  // namespace lab2
