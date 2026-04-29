#include "console_ui.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/array_sequence.h"
#include "../include/errors.h"
#include "../include/list_sequence.h"
#include "../include/sequence_algorithms.h"

namespace lab2 {
namespace tests {
void RunAllTests();
}
}  // namespace lab2

namespace lab2 {

namespace {

int DoubleValue(const int& x) { return x * 2; }
bool IsPositive(const int& x) { return x > 0; }
int SumOp(const int& x, const int& acc) { return acc + x; }

}  // namespace

ConsoleUi::ConsoleUi() : slot_a_(nullptr), slot_b_(nullptr) {}

ConsoleUi::~ConsoleUi() {
    delete slot_a_;
    delete slot_b_;
}

void ConsoleUi::PrintMenu() const {
    std::printf("\n");
    std::printf("=== Lab 2 menu ===\n");
    std::printf(" 1. Run tests\n");
    std::printf(" 2. Make sequence A\n");
    std::printf(" 3. Make sequence B\n");
    std::printf(" 4. Show sequences\n");
    std::printf(" 5. Append to A\n");
    std::printf(" 6. Prepend to A\n");
    std::printf(" 7. Insert into A\n");
    std::printf(" 8. Get subsequence of A\n");
    std::printf(" 9. Concat A + B\n");
    std::printf("10. Map A (x*2)\n");
    std::printf("11. Where A (x > 0)\n");
    std::printf("12. Reduce A (sum)\n");
    std::printf("13. Bit sequence menu\n");
    std::printf(" 0. Exit\n");
}

void ConsoleUi::Run() {
    while (true) {
        PrintMenu();
        int choice = ReadMenuChoice();
        try {
            switch (choice) {
                case 0:
                    return;
                case 1:
                    RunTests();
                    break;
                case 2:
                    MakeSequence(0);
                    break;
                case 3:
                    MakeSequence(1);
                    break;
                case 4:
                    ShowSequences();
                    break;
                case 5:
                    AppendItem();
                    break;
                case 6:
                    PrependItem();
                    break;
                case 7:
                    InsertItem();
                    break;
                case 8:
                    GetSubsequence();
                    break;
                case 9:
                    ConcatSequences();
                    break;
                case 10:
                    RunMap();
                    break;
                case 11:
                    RunWhere();
                    break;
                case 12:
                    RunReduce();
                    break;
                case 13:
                    BitSequenceMenu();
                    break;
                default:
                    std::printf("unknown choice\n");
            }
        } catch (const std::exception& ex) {
            std::printf("error: %s\n", ex.what());
        }
    }
}

void ConsoleUi::RunTests() { tests::RunAllTests(); }

int ConsoleUi::ReadMenuChoice() const {
    std::string line;
    std::printf("> ");
    if (!std::getline(std::cin, line)) {
        return 0;
    }
    std::stringstream ss(line);
    int value = -1;
    ss >> value;
    return value;
}

int ConsoleUi::ReadInt(const char* prompt) const {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) {
        throw InvalidArgument("input ended");
    }
    std::stringstream ss(line);
    int value = 0;
    if (!(ss >> value)) {
        throw InvalidArgument("not an integer");
    }
    return value;
}

bool ConsoleUi::ReadIntList(const char* prompt, int* values, int max_count, int* out_count) {
    std::printf("%s", prompt);
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::stringstream ss(line);
    int n = 0;
    int x;
    while (ss >> x) {
        if (n >= max_count) {
            break;
        }
        values[n++] = x;
    }
    *out_count = n;
    return true;
}

Sequence<int>* ConsoleUi::CreateSequence(SequenceKind kind, const int* values, int count) {
    switch (kind) {
        case kMutableArray:
            return new MutableArraySequence<int>(values, count);
        case kMutableList:
            return new MutableListSequence<int>(values, count);
        case kImmutableArray:
            return new ImmutableArraySequence<int>(values, count);
        case kImmutableList:
            return new ImmutableListSequence<int>(values, count);
    }
    throw InvalidArgument("unknown sequence kind");
}

void ConsoleUi::ReplaceSlot(int slot, Sequence<int>* value) {
    Sequence<int>*& target = (slot == 0) ? slot_a_ : slot_b_;
    if (target != value) {
        delete target;
        target = value;
    }
}

void ConsoleUi::MakeSequence(int slot) {
    std::printf("kind: 1=mut-array  2=mut-list  3=imm-array  4=imm-list\n");
    int kind = ReadInt("kind: ");
    int values[256];
    int count = 0;
    ReadIntList("values (space-separated): ", values, 256, &count);
    SequenceKind k = static_cast<SequenceKind>(kind);
    ReplaceSlot(slot, CreateSequence(k, values, count));
    std::printf("ok\n");
}

void ConsoleUi::PrintSequence(const char* label, const Sequence<int>* seq) const {
    std::printf("%s = ", label);
    if (seq == nullptr) {
        std::printf("(empty)\n");
        return;
    }
    std::printf("[");
    for (int i = 0; i < seq->GetLength(); ++i) {
        if (i > 0) {
            std::printf(", ");
        }
        std::printf("%d", seq->Get(i));
    }
    std::printf("]  (length %d)\n", seq->GetLength());
}

void ConsoleUi::ShowSequences() const {
    PrintSequence("A", slot_a_);
    PrintSequence("B", slot_b_);
}

void ConsoleUi::AppendItem() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    int value = ReadInt("value: ");
    Sequence<int>* result = slot_a_->Append(value);
    if (result != slot_a_) {
        delete slot_a_;
        slot_a_ = result;
    }
    PrintSequence("A", slot_a_);
}

void ConsoleUi::PrependItem() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    int value = ReadInt("value: ");
    Sequence<int>* result = slot_a_->Prepend(value);
    if (result != slot_a_) {
        delete slot_a_;
        slot_a_ = result;
    }
    PrintSequence("A", slot_a_);
}

void ConsoleUi::InsertItem() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    int value = ReadInt("value: ");
    int index = ReadInt("index: ");
    Sequence<int>* result = slot_a_->InsertAt(value, index);
    if (result != slot_a_) {
        delete slot_a_;
        slot_a_ = result;
    }
    PrintSequence("A", slot_a_);
}

void ConsoleUi::GetSubsequence() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    int start = ReadInt("start: ");
    int end = ReadInt("end: ");
    Sequence<int>* sub = slot_a_->GetSubsequence(start, end);
    PrintSequence("subseq", sub);
    delete sub;
}

void ConsoleUi::ConcatSequences() {
    if (slot_a_ == nullptr || slot_b_ == nullptr) {
        throw InvalidArgument("A or B is not initialized");
    }
    Sequence<int>* result = slot_a_->Concat(slot_b_);
    if (result != slot_a_) {
        delete slot_a_;
        slot_a_ = result;
    }
    PrintSequence("A", slot_a_);
}

void ConsoleUi::RunMap() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    Sequence<int>* mapped = algorithms::Map<int, int>(*slot_a_, DoubleValue);
    PrintSequence("map", mapped);
    delete mapped;
}

void ConsoleUi::RunWhere() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    Sequence<int>* filtered = algorithms::Where<int>(*slot_a_, IsPositive);
    PrintSequence("where", filtered);
    delete filtered;
}

void ConsoleUi::RunReduce() {
    if (slot_a_ == nullptr) {
        throw InvalidArgument("A is not initialized");
    }
    int total = algorithms::Reduce<int, int>(*slot_a_, SumOp, 0);
    std::printf("sum = %d\n", total);
}

void ConsoleUi::BitSequenceMenu() {
    while (true) {
        std::printf("\n--- BitSequence ---\n");
        std::printf("a = %s\n", bit_a_.ToString().c_str());
        std::printf("b = %s\n", bit_b_.ToString().c_str());
        std::printf(" 1. Set a from string\n");
        std::printf(" 2. Set b from string\n");
        std::printf(" 3. a AND b\n");
        std::printf(" 4. a OR  b\n");
        std::printf(" 5. a XOR b\n");
        std::printf(" 6. NOT a\n");
        std::printf(" 0. Back\n");
        int choice = ReadMenuChoice();
        try {
            switch (choice) {
                case 0:
                    return;
                case 1: {
                    std::printf("binary: ");
                    std::string line;
                    std::getline(std::cin, line);
                    bit_a_ = BitSequence(line);
                    break;
                }
                case 2: {
                    std::printf("binary: ");
                    std::string line;
                    std::getline(std::cin, line);
                    bit_b_ = BitSequence(line);
                    break;
                }
                case 3:
                    std::printf("=> %s\n", bit_a_.And(bit_b_).ToString().c_str());
                    break;
                case 4:
                    std::printf("=> %s\n", bit_a_.Or(bit_b_).ToString().c_str());
                    break;
                case 5:
                    std::printf("=> %s\n", bit_a_.Xor(bit_b_).ToString().c_str());
                    break;
                case 6:
                    std::printf("=> %s\n", bit_a_.Not().ToString().c_str());
                    break;
                default:
                    std::printf("unknown choice\n");
            }
        } catch (const std::exception& ex) {
            std::printf("error: %s\n", ex.what());
        }
    }
}

}  // namespace lab2
