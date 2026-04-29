#include "../include/bit_sequence.h"
#include "../include/errors.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestBitSequence() {
    std::printf("\n[BitSequence]\n");

    BitSequence empty;
    T_ASSERT_EQ("empty length", empty.GetLength(), 0);

    BitSequence a("10110");
    T_ASSERT_EQ("from string length", a.GetLength(), 5);
    T_ASSERT_EQ("bit 0", a.GetBit(0), true);
    T_ASSERT_EQ("bit 1", a.GetBit(1), false);
    T_ASSERT_EQ("bit 2", a.GetBit(2), true);
    T_ASSERT(("to string"), a.ToString() == "10110");

    BitSequence b("11000");
    BitSequence c = a.And(b);
    T_ASSERT(("and"), c.ToString() == "10000");

    BitSequence d = a.Or(b);
    T_ASSERT(("or"), d.ToString() == "11110");

    BitSequence e = a.Xor(b);
    T_ASSERT(("xor"), e.ToString() == "01110");

    BitSequence f = a.Not();
    T_ASSERT(("not"), f.ToString() == "01001");

    a.SetBit(1, true);
    T_ASSERT_EQ("set bit", a.GetBit(1), true);

    BitSequence small("101");
    Sequence<Bit>* appended = small.Append(Bit(true));
    T_ASSERT_EQ("after append length", appended->GetLength(), 4);

    Sequence<Bit>* prepended = small.Prepend(Bit(false));
    T_ASSERT_EQ("after prepend length", prepended->GetLength(), 5);
    T_ASSERT_EQ("after prepend first", prepended->GetFirst().Value(), false);

    BitSequence wide_a(64);
    BitSequence wide_b(64);
    for (int i = 0; i < 64; ++i) {
        wide_a.SetBit(i, i % 2 == 0);
        wide_b.SetBit(i, i % 3 == 0);
    }
    BitSequence wide_xor = wide_a.Xor(wide_b);
    T_ASSERT_EQ("wide xor length", wide_xor.GetLength(), 64);
    bool ok = true;
    for (int i = 0; i < 64; ++i) {
        bool expected = (i % 2 == 0) != (i % 3 == 0);
        if (wide_xor.GetBit(i) != expected) {
            ok = false;
            break;
        }
    }
    T_ASSERT("wide xor correct", ok);

    BitSequence not_full = wide_a.Not();
    T_ASSERT_EQ("not preserves length", not_full.GetLength(), 64);

    T_ASSERT_THROWS("size mismatch and", SizeMismatch, a.And(BitSequence(10)));
    T_ASSERT_THROWS("invalid string", InvalidArgument, BitSequence("01x"));
}

}  // namespace tests
}  // namespace lab2
