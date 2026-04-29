# Lab 2 — Polymorphic ADT in C++

`DynamicArray<T>`, `LinkedList<T>`, `Sequence<T>` (mutable / immutable
variants over array or list storage), `BitSequence`, plus generic
algorithms (Map / Where / Reduce / FlatMap / Zip / Unzip / Split / Slice).

## Layout

```
lab2/
  include/   public headers; templates split into .h + .tpp,
             non-template code split into .h + .cpp
  src/       console UI + main
  tests/     unit tests
```

Key design notes:

- mutable and immutable sequences share one base: every mutating method
  (`Append`, `Prepend`, `InsertAt`, `Set`, `Concat`) is implemented once
  in `ArraySequence` / `ListSequence` and dispatches through a virtual
  `Instance()` hook — `MutableX::Instance()` returns `this`, `ImmutableX::Instance()`
  returns a fresh clone.
- getters return references (`const T&`) instead of pointers / by-value.
- `BitSequence` stores bits as a `DynamicArray<unsigned int>` of 32-bit
  words; AND / OR / XOR / NOT operate word-by-word.

## Build

The project builds with `g++` (C++17).

## Run tests

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
  tests/test_main.cpp \
  tests/test_runner.cpp \
  tests/test_framework.cpp \
  tests/test_dynamic_array.cpp \
  tests/test_linked_list.cpp \
  tests/test_sequence.cpp \
  tests/test_algorithms.cpp \
  tests/test_option.cpp \
  tests/test_bit_sequence.cpp \
  include/bit_sequence.cpp \
  -o build/lab2_tests

./build/lab2_tests
```

Output is in lab 1 style — `[+]` per passing assertion, `[-]` per failing,
followed by a summary block (`All / Done / Fall / Coverage`).

## Run console app

```bash

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
  src/main.cpp \
  src/console_ui.cpp \
  tests/test_runner.cpp \
  tests/test_framework.cpp \
  tests/test_dynamic_array.cpp \
  tests/test_linked_list.cpp \
  tests/test_sequence.cpp \
  tests/test_algorithms.cpp \
  tests/test_option.cpp \
  tests/test_bit_sequence.cpp \
  include/bit_sequence.cpp \
  -o build/lab2

./build/lab2
```

Numeric menu. Available actions:

```
 1. Run tests              7. Insert into A
 2. Make sequence A        8. Get subsequence of A
 3. Make sequence B        9. Concat A + B
 4. Show sequences        10. Map A (x*2)
 5. Append to A           11. Where A (x > 0)
 6. Prepend to A          12. Reduce A (sum)
                          13. Bit sequence menu
                           0. Exit
```

When asked for sequence kind: `1` = mutable array, `2` = mutable list,
`3` = immutable array, `4` = immutable list.

The Bit sequence submenu lets you enter binary strings (`10110`) into
two registers and computes AND / OR / XOR / NOT.
