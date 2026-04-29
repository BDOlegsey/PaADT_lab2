#ifndef LAB2_LIST_SEQUENCE_TPP
#define LAB2_LIST_SEQUENCE_TPP

namespace lab2 {

template <class T>
class ListSequence<T>::ListEnumerator : public IEnumerator<T> {
public:
    explicit ListEnumerator(const LinkedList<T>* data)
        : data_(data), position_(-1) {}

    bool MoveNext() override {
        if (position_ + 1 >= data_->GetLength()) return false;
        ++position_;
        return true;
    }

    const T& Current() const override {
        if (position_ < 0) throw InvalidArgument("Enumerator: MoveNext not called");
        return data_->Get(position_);
    }

    void Reset() override { position_ = -1; }

private:
    const LinkedList<T>* data_;
    int position_;
};

template <class T>
ListSequence<T>::ListSequence() : items_() {}

template <class T>
ListSequence<T>::ListSequence(const T* items, int count) : items_(items, count) {}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& source) : items_(source) {}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : items_(other.items_) {}

template <class T>
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T>& other) {
    if (this == &other) return *this;
    items_ = other.items_;
    return *this;
}

template <class T>
ListSequence<T>::~ListSequence() = default;

template <class T>
int ListSequence<T>::GetLength() const { return items_.GetLength(); }

template <class T>
const T& ListSequence<T>::GetFirst() const { return items_.GetFirst(); }

template <class T>
const T& ListSequence<T>::GetLast() const { return items_.GetLast(); }

template <class T>
const T& ListSequence<T>::Get(int index) const { return items_.Get(index); }

template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int start_index, int end_index) const {
    LinkedList<T>* sub = items_.GetSubList(start_index, end_index);
    ListSequence<T>* result = MakeEmpty();
    for (int i = 0; i < sub->GetLength(); ++i) result->items_.Append(sub->Get(i));
    delete sub;
    return result;
}

template <class T>
Sequence<T>* ListSequence<T>::Append(const T& item) {
    ListSequence<T>* target = Instance();
    target->items_.Append(item);
    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::Prepend(const T& item) {
    ListSequence<T>* target = Instance();
    target->items_.Prepend(item);
    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::InsertAt(const T& item, int index) {
    ListSequence<T>* target = Instance();
    target->items_.InsertAt(item, index);
    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::Set(int index, const T& value) {
    ListSequence<T>* target = Instance();
    target->items_.Set(index, value);
    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::Concat(const Sequence<T>* other) {
    if (other == nullptr) throw InvalidArgument("Concat: other sequence is null");
    ListSequence<T>* target = Instance();
    const int n = other->GetLength();
    for (int i = 0; i < n; ++i) target->items_.Append(other->Get(i));
    return target;
}

template <class T>
IEnumerator<T>* ListSequence<T>::GetEnumerator() const {
    return new ListEnumerator(&items_);
}

// MutableListSequence
template <class T>
MutableListSequence<T>::MutableListSequence() : ListSequence<T>() {}

template <class T>
MutableListSequence<T>::MutableListSequence(const T* items, int count)
    : ListSequence<T>(items, count) {}

template <class T>
MutableListSequence<T>::MutableListSequence(const LinkedList<T>& source)
    : ListSequence<T>(source) {}

template <class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T>& other)
    : ListSequence<T>(other) {}

template <class T>
Sequence<T>* MutableListSequence<T>::Clone() const {
    return new MutableListSequence<T>(*this);
}

template <class T>
ListSequence<T>* MutableListSequence<T>::Instance() { return this; }

template <class T>
ListSequence<T>* MutableListSequence<T>::MakeEmpty() const {
    return new MutableListSequence<T>();
}

// ImmutableListSequence
template <class T>
ImmutableListSequence<T>::ImmutableListSequence() : ListSequence<T>() {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const T* items, int count)
    : ListSequence<T>(items, count) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const LinkedList<T>& source)
    : ListSequence<T>(source) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other)
    : ListSequence<T>(other) {}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Clone() const {
    return new ImmutableListSequence<T>(*this);
}

template <class T>
ListSequence<T>* ImmutableListSequence<T>::Instance() {
    return new ImmutableListSequence<T>(*this);
}

template <class T>
ListSequence<T>* ImmutableListSequence<T>::MakeEmpty() const {
    return new ImmutableListSequence<T>();
}

}  // namespace lab2

#endif
