#include "../include/dynamic_array.h"
#include "../include/errors.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestDynamicArray() {
    std::printf("\n[DynamicArray]\n");

    DynamicArray<int> empty;
    T_ASSERT_EQ("empty size", empty.GetSize(), 0);
    T_ASSERT_EQ("empty capacity", empty.GetCapacity(), 0);

    DynamicArray<int> sized(3);
    T_ASSERT_EQ("sized size", sized.GetSize(), 3);
    T_ASSERT_EQ("sized capacity", sized.GetCapacity(), 3);

    int values[] = {1, 2, 3, 4};
    DynamicArray<int> arr(values, 4);
    T_ASSERT_EQ("from array size", arr.GetSize(), 4);
    T_ASSERT_EQ("from array capacity", arr.GetCapacity(), 4);
    T_ASSERT_EQ("element 0", arr.Get(0), 1);
    T_ASSERT_EQ("element 3", arr.Get(3), 4);

    arr.Set(1, 20);
    T_ASSERT_EQ("after set", arr.Get(1), 20);

    arr[2] = 30;
    T_ASSERT_EQ("operator[] write", arr[2], 30);

    arr.Resize(6);
    T_ASSERT_EQ("resize grow", arr.GetSize(), 6);
    T_ASSERT("capacity after grow >= size", arr.GetCapacity() >= arr.GetSize());
    T_ASSERT_EQ("resize keeps data", arr.Get(0), 1);
    const int cap_after_grow = arr.GetCapacity();

    arr.Resize(2);
    T_ASSERT_EQ("resize shrink", arr.GetSize(), 2);
    T_ASSERT_EQ("capacity does not shrink on resize down", arr.GetCapacity(), cap_after_grow);

    DynamicArray<int> growth;
    int prev_capacity = growth.GetCapacity();
    bool growth_capacity_ge_size = true;
    bool growth_capacity_monotonic = true;
    for (int i = 0; i < 1000; ++i) {
        growth.Resize(growth.GetSize() + 1);
        if (growth.GetCapacity() < growth.GetSize()) {
            growth_capacity_ge_size = false;
            break;
        }
        if (growth.GetCapacity() < prev_capacity) {
            growth_capacity_monotonic = false;
            break;
        }
        prev_capacity = growth.GetCapacity();
    }
    T_ASSERT("growth capacity >= size", growth_capacity_ge_size);
    T_ASSERT("growth capacity monotonic", growth_capacity_monotonic);
    T_ASSERT("capacity grows in reserve style", growth.GetCapacity() < growth.GetSize() * 4);

    DynamicArray<int> copy(arr);
    T_ASSERT_EQ("copy size", copy.GetSize(), 2);
    T_ASSERT_EQ("copy data", copy.Get(0), 1);
    T_ASSERT_EQ("copy capacity", copy.GetCapacity(), arr.GetCapacity());

    DynamicArray<int> assigned;
    assigned = arr;
    T_ASSERT_EQ("assigned size", assigned.GetSize(), 2);
    T_ASSERT_EQ("assigned capacity", assigned.GetCapacity(), arr.GetCapacity());

    T_ASSERT_THROWS("get out of range", IndexOutOfRange, arr.Get(10));
    T_ASSERT_THROWS("negative size", InvalidArgument, DynamicArray<int> bad(-1));
}

}  // namespace tests
}  // namespace lab2
