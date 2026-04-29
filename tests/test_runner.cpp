#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestDynamicArray();
void TestLinkedList();
void TestSequences();
void TestBitSequence();
void TestAlgorithms();
void TestOption();

void RunAllTests() {
    ResetCounters();

    TestOption();
    TestDynamicArray();
    TestLinkedList();
    TestSequences();
    TestBitSequence();
    TestAlgorithms();

    std::printf("\n");
    PrintSummary();
}

}  // namespace tests
}  // namespace lab2
