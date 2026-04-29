#include "test_framework.h"

namespace lab2 {
namespace tests {

int t_passed = 0;
int t_failed = 0;
int t_total = 0;

void ResetCounters() {
    t_passed = 0;
    t_failed = 0;
    t_total = 0;
}

void PrintSummary() {
    std::printf("All:  %3d\n", t_total);
    std::printf("Done: %3d\n", t_passed);
    std::printf("Fall: %3d\n", t_failed);
    std::printf("Coverage: %3d%%\n", t_total ? (t_passed * 100 / t_total) : 0);
}

}  // namespace tests
}  // namespace lab2
