/*
 * This program was written on linux Manjaro 5.15.1,
 * compiler: g++(GCC) 12.2.1 20230201,
 * architecture: x86_64.
 *
 * NO WARRANTIES that this program will work at any other machines.
 */

#include <iostream>
#include <malloc.h>

/*
 * In memory, this value leans at [-1] position from pointer.
 * For some reason, actual size is always greater than actual one
 * by this magic number 9. So that it is used when we sub this number
 * from allocated bytes to get correct one.
 */
constexpr int MAGIC_NUMBER = 9;

/*
 * Base structure
 */
template<typename T>
struct S {
    ~S() = default;

    /*
     * This field is a just payload that is used to test program.
     * Using different values with alignment is a good allocator test =)
     */
    [[maybe_unused]] T payload[7];
};

/*
 * S specialisation for convenience.
 * At any time, type can be replaced by any other.
 */
using Struct = S<size_t>;

size_t arraySize(Struct *array) {
    static_assert(sizeof(size_t) == 8);

    return *reinterpret_cast<size_t *>(
            reinterpret_cast<unsigned char *>(array) - sizeof(size_t)
    ) - MAGIC_NUMBER;
}

int main() {
    auto *s = new/*(std::align_val_t{16})*/ Struct[1];

    // Using standard libc function
    auto mallocUsableSizeResult = malloc_usable_size(s);
    // Using self-written function
    auto arraySizeResult = arraySize(s);

    auto mallocUsableSizeElements = mallocUsableSizeResult / sizeof(Struct);
    auto arraySizeElements = arraySizeResult / sizeof(Struct);

    std::cout << "malloc_usable_size: " << mallocUsableSizeResult << "\n";
    std::cout << "arraySize: " << arraySizeResult << "\n";
    std::cout << "elements using 'malloc_usable_size': " << mallocUsableSizeElements << "\n";
    std::cout << "elements using 'arraySize': " << arraySizeElements << "\n";

    if (mallocUsableSizeElements != arraySizeElements) {
        std::cout << "Assertion is not passed.\n";
    } else {
        std::cout << "Assertion passed.\n";
    }

    delete[] s;
    return 0;
}