#include "../include/array_sequence.h"
#include "../include/sequence_algorithms.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

static int Square(const int& x) { return x * x; }
static bool IsEven(const int& x) { return x % 2 == 0; }
static int Sum(const int& x, const int& acc) { return acc + x; }
static bool IsZero(const int& x) { return x == 0; }
static Sequence<int>* Repeat(const int& x) {
    int values[] = {x, x};
    return new MutableArraySequence<int>(values, 2);
}

void TestAlgorithms() {
    std::printf("\n[Algorithms]\n");
    using namespace algorithms;

    int values[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> source(values, 5);

    Sequence<int>* squared = Map<int, int>(source, Square);
    T_ASSERT_EQ("map length", squared->GetLength(), 5);
    T_ASSERT_EQ("map element 2", squared->Get(2), 9);
    delete squared;

    Sequence<int>* evens = Where<int>(source, IsEven);
    T_ASSERT_EQ("where length", evens->GetLength(), 2);
    T_ASSERT_EQ("where first", evens->GetFirst(), 2);
    delete evens;

    int total = Reduce<int, int>(source, Sum, 0);
    T_ASSERT_EQ("reduce sum", total, 15);

    int b_values[] = {10, 20, 30};
    MutableArraySequence<int> b(b_values, 3);
    Sequence<Pair<int, int>>* zipped = Zip<int, int>(source, b);
    T_ASSERT_EQ("zip length", zipped->GetLength(), 3);
    T_ASSERT_EQ("zip first", zipped->Get(0).first, 1);
    T_ASSERT_EQ("zip second", zipped->Get(0).second, 10);

    Pair<Sequence<int>*, Sequence<int>*> unzipped = Unzip<int, int>(*zipped);
    T_ASSERT_EQ("unzip first length", unzipped.first->GetLength(), 3);
    T_ASSERT_EQ("unzip first 0", unzipped.first->Get(0), 1);
    T_ASSERT_EQ("unzip second 0", unzipped.second->Get(0), 10);
    delete unzipped.first;
    delete unzipped.second;
    delete zipped;

    int split_values[] = {1, 2, 0, 3, 4, 0, 5};
    MutableArraySequence<int> split_src(split_values, 7);
    Sequence<Sequence<int>*>* parts = Split<int>(split_src, IsZero);
    T_ASSERT_EQ("split parts", parts->GetLength(), 3);
    T_ASSERT_EQ("split first part length", parts->Get(0)->GetLength(), 2);
    T_ASSERT_EQ("split second part first", parts->Get(1)->GetFirst(), 3);
    for (int i = 0; i < parts->GetLength(); ++i) {
        delete parts->Get(i);
    }
    delete parts;

    int insert_values[] = {9, 10};
    MutableArraySequence<int> insert(insert_values, 2);
    Sequence<int>* sliced = Slice<int>(source, 1, 2, insert);
    // {1,2,3,4,5} replace seq[1..2] with {9,10} -> {1,9,10,4,5}
    T_ASSERT_EQ("slice length", sliced->GetLength(), 5);
    T_ASSERT_EQ("slice 0", sliced->Get(0), 1);
    T_ASSERT_EQ("slice 1", sliced->Get(1), 9);
    T_ASSERT_EQ("slice 2", sliced->Get(2), 10);
    T_ASSERT_EQ("slice 3", sliced->Get(3), 4);
    delete sliced;

    Sequence<int>* sliced_neg = Slice<int>(source, -2, 1, insert);
    // index -2 -> 3, replace 1 element -> {1,2,3,9,10,5}
    T_ASSERT_EQ("slice negative length", sliced_neg->GetLength(), 6);
    T_ASSERT_EQ("slice negative element", sliced_neg->Get(3), 9);
    delete sliced_neg;

    Sequence<int>* flat = FlatMap<int, int>(source, Repeat);
    T_ASSERT_EQ("flat map length", flat->GetLength(), 10);
    T_ASSERT_EQ("flat map 0", flat->Get(0), 1);
    T_ASSERT_EQ("flat map 1", flat->Get(1), 1);
    delete flat;
}

}  // namespace tests
}  // namespace lab2
