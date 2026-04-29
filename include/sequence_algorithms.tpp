#ifndef LAB2_SEQUENCE_ALGORITHMS_TPP
#define LAB2_SEQUENCE_ALGORITHMS_TPP

#include "sequence_algorithms.h"

namespace lab2 {
namespace algorithms {

template <class T, class R>
Sequence<R>* Map(const Sequence<T>& source, R (*func)(const T&)) {
    if (func == nullptr) {
        throw InvalidArgument("map function is null");
    }
    MutableArraySequence<R>* result = new MutableArraySequence<R>();
    for (int i = 0; i < source.GetLength(); ++i) {
        result->Append(func(source.Get(i)));
    }
    return result;
}

template <class T>
Sequence<T>* Where(const Sequence<T>& source, bool (*predicate)(const T&)) {
    if (predicate == nullptr) {
        throw InvalidArgument("predicate is null");
    }
    MutableArraySequence<T>* result = new MutableArraySequence<T>();
    for (int i = 0; i < source.GetLength(); ++i) {
        const T& item = source.Get(i);
        if (predicate(item)) {
            result->Append(item);
        }
    }
    return result;
}

template <class T, class R>
R Reduce(const Sequence<T>& source, R (*func)(const T&, const R&), const R& initial) {
    if (func == nullptr) {
        throw InvalidArgument("reduce function is null");
    }
    R acc = initial;
    for (int i = 0; i < source.GetLength(); ++i) {
        acc = func(source.Get(i), acc);
    }
    return acc;
}

template <class T, class R>
Sequence<R>* FlatMap(const Sequence<T>& source, Sequence<R>* (*func)(const T&)) {
    if (func == nullptr) {
        throw InvalidArgument("flat-map function is null");
    }
    MutableArraySequence<R>* result = new MutableArraySequence<R>();
    for (int i = 0; i < source.GetLength(); ++i) {
        Sequence<R>* piece = func(source.Get(i));
        if (piece == nullptr) {
            delete result;
            throw InvalidArgument("flat-map function returned null");
        }
        for (int j = 0; j < piece->GetLength(); ++j) {
            result->Append(piece->Get(j));
        }
        delete piece;
    }
    return result;
}

template <class T1, class T2>
Sequence<Pair<T1, T2>>* Zip(const Sequence<T1>& first, const Sequence<T2>& second) {
    int n = first.GetLength() < second.GetLength() ? first.GetLength() : second.GetLength();
    MutableArraySequence<Pair<T1, T2>>* result = new MutableArraySequence<Pair<T1, T2>>();
    for (int i = 0; i < n; ++i) {
        result->Append(Pair<T1, T2>(first.Get(i), second.Get(i)));
    }
    return result;
}

template <class T1, class T2>
Pair<Sequence<T1>*, Sequence<T2>*> Unzip(const Sequence<Pair<T1, T2>>& source) {
    MutableArraySequence<T1>* a = new MutableArraySequence<T1>();
    MutableArraySequence<T2>* b = new MutableArraySequence<T2>();
    for (int i = 0; i < source.GetLength(); ++i) {
        const Pair<T1, T2>& p = source.Get(i);
        a->Append(p.first);
        b->Append(p.second);
    }
    return Pair<Sequence<T1>*, Sequence<T2>*>(a, b);
}

template <class T>
Sequence<Sequence<T>*>* Split(const Sequence<T>& source, bool (*predicate)(const T&)) {
    if (predicate == nullptr) {
        throw InvalidArgument("predicate is null");
    }
    MutableArraySequence<Sequence<T>*>* result = new MutableArraySequence<Sequence<T>*>();
    MutableArraySequence<T>* chunk = new MutableArraySequence<T>();
    for (int i = 0; i < source.GetLength(); ++i) {
        const T& item = source.Get(i);
        if (predicate(item)) {
            result->Append(chunk);
            chunk = new MutableArraySequence<T>();
        } else {
            chunk->Append(item);
        }
    }
    result->Append(chunk);
    return result;
}

template <class T>
Sequence<T>* Slice(const Sequence<T>& source, int index, int length, const Sequence<T>& insert) {
    if (length < 0) {
        throw InvalidArgument("slice length must be non-negative");
    }
    int n = source.GetLength();
    int real_index = index < 0 ? n + index : index;
    if (real_index < 0 || real_index > n) {
        throw IndexOutOfRange("slice index out of range");
    }
    int end = real_index + length;
    if (end > n) {
        end = n;
    }
    MutableArraySequence<T>* result = new MutableArraySequence<T>();
    for (int i = 0; i < real_index; ++i) {
        result->Append(source.Get(i));
    }
    for (int i = 0; i < insert.GetLength(); ++i) {
        result->Append(insert.Get(i));
    }
    for (int i = end; i < n; ++i) {
        result->Append(source.Get(i));
    }
    return result;
}

}  // namespace algorithms
}  // namespace lab2

#endif
