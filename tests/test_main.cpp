#include "../include/bit_sequence.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {
void RunAllTests();
}
}  // namespace lab2

int main() {
    lab2::tests::RunAllTests();
    
    // с защиты
    std::printf("\n[BitSequence append + Get]\n");
    lab2::BitSequence test_bit;
    test_bit.Append(lab2::Bit(true));
    test_bit.Append(lab2::Bit(false));

    T_ASSERT_EQ("bit length after append", test_bit.GetLength(), 2);

    lab2::Bit b0 = test_bit.Get(0);
    lab2::Bit b1 = test_bit.Get(1);

    T_ASSERT_EQ("check1", b0.Value(), true);
    T_ASSERT_EQ("check2", b1.Value(), false);
    return 0;
}