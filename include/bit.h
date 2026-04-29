#ifndef LAB2_BIT_H
#define LAB2_BIT_H

#include <ostream>

namespace lab2 {

// thin wrapper around a single bit value
class Bit {
public:
    Bit() : value_(false) {}
    Bit(bool value) : value_(value) {}

    bool Value() const { return value_; }

    Bit operator&(const Bit& other) const { return Bit(value_ && other.value_); }
    Bit operator|(const Bit& other) const { return Bit(value_ || other.value_); }
    Bit operator^(const Bit& other) const { return Bit(value_ != other.value_); }
    Bit operator~() const { return Bit(!value_); }

    bool operator==(const Bit& other) const { return value_ == other.value_; }
    bool operator!=(const Bit& other) const { return value_ != other.value_; }

private:
    bool value_;
};

inline std::ostream& operator<<(std::ostream& out, const Bit& bit) {
    out << (bit.Value() ? '1' : '0');
    return out;
}

}  // namespace lab2

#endif
