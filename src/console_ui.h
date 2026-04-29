#ifndef LAB2_CONSOLE_UI_H
#define LAB2_CONSOLE_UI_H

#include "../include/bit_sequence.h"
#include "../include/sequence.h"

namespace lab2 {

class ConsoleUi {
public:
    ConsoleUi();
    ~ConsoleUi();

    void Run();

private:
    enum SequenceKind {
        kMutableArray = 1,
        kMutableList = 2,
        kImmutableArray = 3,
        kImmutableList = 4
    };

    void PrintMenu() const;

    void RunTests();
    void MakeSequence(int slot);
    void ShowSequences() const;
    void AppendItem();
    void PrependItem();
    void InsertItem();
    void GetSubsequence();
    void ConcatSequences();
    void RunMap();
    void RunWhere();
    void RunReduce();
    void BitSequenceMenu();

    Sequence<int>* CreateSequence(SequenceKind kind, const int* values, int count);
    void ReplaceSlot(int slot, Sequence<int>* value);
    void PrintSequence(const char* label, const Sequence<int>* seq) const;
    bool ReadIntList(const char* prompt, int* values, int max_count, int* out_count);
    int ReadInt(const char* prompt) const;
    int ReadMenuChoice() const;

    Sequence<int>* slot_a_;
    Sequence<int>* slot_b_;
    BitSequence bit_a_;
    BitSequence bit_b_;
};

}  // namespace lab2

#endif
