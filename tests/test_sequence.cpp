#include "../include/array_sequence.h"
#include "../include/errors.h"
#include "../include/list_sequence.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

template <class Seq>
static void TestMutableSequence(const char* label) {
    std::printf("\n[Mutable %s]\n", label);

    int values[] = {1, 2, 3};
    Seq seq(values, 3);

    T_ASSERT_EQ("length", seq.GetLength(), 3);
    T_ASSERT_EQ("get first", seq.GetFirst(), 1);
    T_ASSERT_EQ("get last", seq.GetLast(), 3);
    T_ASSERT_EQ("operator[]", seq[1], 2);

    Sequence<int>* same = seq.Append(4);
    T_ASSERT_EQ("mutable append same instance", same, &seq);
    T_ASSERT_EQ("after append length", seq.GetLength(), 4);
    T_ASSERT_EQ("after append last", seq.GetLast(), 4);

    seq.Prepend(0);
    T_ASSERT_EQ("after prepend first", seq.GetFirst(), 0);
    T_ASSERT_EQ("after prepend length", seq.GetLength(), 5);

    seq.InsertAt(99, 2);
    T_ASSERT_EQ("after insert", seq.Get(2), 99);

    seq.Set(0, 7);
    T_ASSERT_EQ("after set", seq.Get(0), 7);

    int extra[] = {10, 20};
    Seq other(extra, 2);
    seq.Concat(&other);
    T_ASSERT_EQ("after concat last", seq.GetLast(), 20);

    Sequence<int>* sub = seq.GetSubsequence(0, 1);
    T_ASSERT_EQ("subseq length", sub->GetLength(), 2);
    delete sub;

    Sequence<int>* clone = seq.Clone();
    T_ASSERT_EQ("clone length", clone->GetLength(), seq.GetLength());
    delete clone;
}

template <class Seq>
static void TestImmutableSequence(const char* label) {
    std::printf("\n[Immutable %s]\n", label);

    int values[] = {1, 2, 3};
    Seq seq(values, 3);

    Sequence<int>* appended = seq.Append(4);
    T_ASSERT_NE("immutable append new instance", appended, &seq);
    T_ASSERT_EQ("original length unchanged", seq.GetLength(), 3);
    T_ASSERT_EQ("appended length", appended->GetLength(), 4);
    T_ASSERT_EQ("appended last", appended->GetLast(), 4);
    delete appended;

    Sequence<int>* prepended = seq.Prepend(0);
    T_ASSERT_EQ("prepended first", prepended->GetFirst(), 0);
    T_ASSERT_EQ("original first unchanged", seq.GetFirst(), 1);
    delete prepended;

    Sequence<int>* set_result = seq.Set(0, 100);
    T_ASSERT_EQ("set result first", set_result->GetFirst(), 100);
    T_ASSERT_EQ("original after set", seq.GetFirst(), 1);
    delete set_result;
}

void TestSequences() {
    TestMutableSequence<MutableArraySequence<int>>("ArraySequence");
    TestMutableSequence<MutableListSequence<int>>("ListSequence");
    TestImmutableSequence<ImmutableArraySequence<int>>("ArraySequence");
    TestImmutableSequence<ImmutableListSequence<int>>("ListSequence");
}

}  // namespace tests
}  // namespace lab2
