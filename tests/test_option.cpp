#include "../include/errors.h"
#include "../include/option.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestOption() {
    std::printf("\n[Option]\n");

    Option<int> none = Option<int>::None();
    T_ASSERT_EQ("none has value", none.HasValue(), false);
    T_ASSERT_EQ("none value or", none.ValueOr(42), 42);

    Option<int> some = Option<int>::Some(7);
    T_ASSERT_EQ("some has value", some.HasValue(), true);
    T_ASSERT_EQ("some value", some.Value(), 7);
    T_ASSERT_EQ("some value or", some.ValueOr(42), 7);

    T_ASSERT_THROWS("none value throws", NoneValueAccess, none.Value());
}

}  // namespace tests
}  // namespace lab2
