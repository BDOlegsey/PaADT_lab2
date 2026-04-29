#ifndef LAB2_SEQUENCE_ALGORITHMS_H
#define LAB2_SEQUENCE_ALGORITHMS_H

#include "array_sequence.h"
#include "list_sequence.h"
#include "sequence.h"

namespace lab2 {

template <class T1, class T2>
struct Pair {
    T1 first;
    T2 second;

    Pair() : first(), second() {}
    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    bool operator==(const Pair<T1, T2>& other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const Pair<T1, T2>& other) const { return !(*this == other); }
};

namespace algorithms {

// Map: applies function to every element and returns a new ArraySequence.
template <class T, class R>
Sequence<R>* Map(const Sequence<T>& source, R (*func)(const T&));

// Where: keeps elements satisfying predicate.
template <class T>
Sequence<T>* Where(const Sequence<T>& source, bool (*predicate)(const T&));

// Reduce: left fold over the sequence.
template <class T, class R>
R Reduce(const Sequence<T>& source, R (*func)(const T&, const R&), const R& initial);

// FlatMap: maps each element to a sequence and concatenates results.
template <class T, class R>
Sequence<R>* FlatMap(const Sequence<T>& source, Sequence<R>* (*func)(const T&));

// Zip: pairs elements from two sequences (length = min of two).
template <class T1, class T2>
Sequence<Pair<T1, T2>>* Zip(const Sequence<T1>& first, const Sequence<T2>& second);

// Unzip: splits a sequence of pairs into two sequences.
template <class T1, class T2>
Pair<Sequence<T1>*, Sequence<T2>*> Unzip(const Sequence<Pair<T1, T2>>& source);

// Split: cuts the sequence at every position where predicate is true (separator dropped).
template <class T>
Sequence<Sequence<T>*>* Split(const Sequence<T>& source, bool (*predicate)(const T&));

// Slice (JS-style): replaces source[index .. index + length - 1] with insert.
// Negative index counts from the end. Returns a new Sequence<T>.
template <class T>
Sequence<T>* Slice(const Sequence<T>& source, int index, int length, const Sequence<T>& insert);

}  // namespace algorithms
}  // namespace lab2

#include "sequence_algorithms.tpp"

#endif
