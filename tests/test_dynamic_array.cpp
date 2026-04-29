#include "../include/dynamic_array.h"
#include "../include/errors.h"
#include "test_framework.h"

namespace lab2 {
namespace tests {

void TestDynamicArray() {
    std::printf("\n[DynamicArray]\n");

    DynamicArray<int> empty;
    T_ASSERT_EQ("empty size", empty.GetSize(), 0);

    DynamicArray<int> sized(3);
    T_ASSERT_EQ("sized size", sized.GetSize(), 3);

    int values[] = {1, 2, 3, 4};
    DynamicArray<int> arr(values, 4);
    T_ASSERT_EQ("from array size", arr.GetSize(), 4);
    T_ASSERT_EQ("element 0", arr.Get(0), 1);
    T_ASSERT_EQ("element 3", arr.Get(3), 4);

    arr.Set(1, 20);
    T_ASSERT_EQ("after set", arr.Get(1), 20);

    arr[2] = 30;
    T_ASSERT_EQ("operator[] write", arr[2], 30);

    arr.Resize(6);
    T_ASSERT_EQ("resize grow", arr.GetSize(), 6);
    T_ASSERT_EQ("resize keeps data", arr.Get(0), 1);

    arr.Resize(2);
    T_ASSERT_EQ("resize shrink", arr.GetSize(), 2);

    DynamicArray<int> copy(arr);
    T_ASSERT_EQ("copy size", copy.GetSize(), 2);
    T_ASSERT_EQ("copy data", copy.Get(0), 1);

    DynamicArray<int> assigned;
    assigned = arr;
    T_ASSERT_EQ("assigned size", assigned.GetSize(), 2);

    T_ASSERT_THROWS("get out of range", IndexOutOfRange, arr.Get(10));
    T_ASSERT_THROWS("negative size", InvalidArgument, DynamicArray<int> bad(-1));
}

}  // namespace tests
}  // namespace lab2
