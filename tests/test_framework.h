#ifndef LAB2_TEST_FRAMEWORK_H
#define LAB2_TEST_FRAMEWORK_H

#include <cmath>
#include <cstdio>

namespace lab2 {
namespace tests {

extern int t_passed;
extern int t_failed;
extern int t_total;

void ResetCounters();
void PrintSummary();

}  // namespace tests
}  // namespace lab2

#define T_ASSERT(name, cond)                                           \
    do {                                                               \
        ::lab2::tests::t_total++;                                      \
        if (cond) {                                                    \
            std::printf("  [+] %s\n", name);                           \
            ::lab2::tests::t_passed++;                                 \
        } else {                                                       \
            std::printf("  [-] %s\n", name);                           \
            ::lab2::tests::t_failed++;                                 \
        }                                                              \
    } while (0)

#define T_ASSERT_EQ(name, a, b) T_ASSERT(name, (a) == (b))
#define T_ASSERT_NE(name, a, b) T_ASSERT(name, (a) != (b))
#define T_ASSERT_NEAR(name, a, b, eps) T_ASSERT(name, std::fabs((a) - (b)) < (eps))
#define T_ASSERT_NULL(name, p) T_ASSERT(name, (p) == nullptr)
#define T_ASSERT_NOT_NULL(name, p) T_ASSERT(name, (p) != nullptr)

#define T_ASSERT_THROWS(name, ExceptionType, expr)                     \
    do {                                                               \
        bool t_caught = false;                                         \
        try {                                                          \
            expr;                                                      \
        } catch (const ExceptionType&) {                               \
            t_caught = true;                                           \
        } catch (...) {                                                \
        }                                                              \
        T_ASSERT(name, t_caught);                                      \
    } while (0)

#endif
