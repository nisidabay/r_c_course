#!/usr/bin/env bash
set -euo pipefail

# verify-exercises.sh — Compiles and runs ALL solutions, checks output.
# Learner can run this to verify their own work.

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
PASS=0
FAIL=0

echo "=== Group 07: 07_dynamic_mem — Verifying Exercises ==="
echo ""

run_solution() {
    local src="$1"
    local expected="$2"
    local input="${3:-}"
    local name
    name="$(basename "$src" .c)"
    local bin="/tmp/test_${name}"

    echo -n "[$name] Compiling... "
    if ! "$CC" $CFLAGS -o "$bin" "$src" 2>/dev/null; then
        echo "FAIL (compile error)"
        "$CC" $CFLAGS -o "$bin" "$src" 2>&1 || true
        FAIL=$((FAIL + 1))
        return
    fi
    echo "OK"

    echo -n "[$name] Running... "
    local actual
    if [ -n "$input" ]; then
        actual="$(printf "%b" "$input" | "$bin" 2>&1 || true)"
    else
        actual="$("$bin" 2>&1 || true)"
    fi

    if [ "$actual" = "$expected" ]; then
        echo "PASS"
        PASS=$((PASS + 1))
    else
        echo "FAIL"
        echo "  Expected: [${expected}]"
        echo "  Got:      [${actual}]"
        FAIL=$((FAIL + 1))
    fi
    echo ""
}

# ex_01_heap_stack_solution
run_solution \
    "$EXERCISES_DIR/ex_01_heap_stack_solution.c" \
    "Stack array size: 5 elements (fixed at compile time)
Heap array size: 10 elements (set at runtime)
Heap arrays can be much larger than stack arrays.
Stack arrays cannot be resized; heap arrays can (via realloc).
heap_arr[0] = 0, heap_arr[9] = 9"

# ex_02_malloc_solution
run_solution \
    "$EXERCISES_DIR/ex_02_malloc_solution.c" \
    "Allocated 8 doubles on the heap (sizeof(double) = 8 bytes):
  values[0] = 0.0
  values[1] = 1.5
  values[2] = 3.0
  values[3] = 4.5
  values[4] = 6.0
  values[5] = 7.5
  values[6] = 9.0
  values[7] = 10.5

Total bytes allocated: 64
Memory freed successfully."

# ex_03_null_check_solution
run_solution \
    "$EXERCISES_DIR/ex_03_null_check_solution.c" \
    "First array (12 floats):
  arr[0] = 0.0
  arr[1] = 0.5
  arr[2] = 1.0
  arr[3] = 1.5
  arr[4] = 2.0
  arr[5] = 2.5
  arr[6] = 3.0
  arr[7] = 3.5
  arr[8] = 4.0
  arr[9] = 4.5
  arr[10] = 5.0
  arr[11] = 5.5

Second array (6 floats): 100.0 90.0 80.0 70.0 60.0 50.0
All memory freed. Every allocation was checked."

# ex_04_calloc_realloc_solution
run_solution \
    "$EXERCISES_DIR/ex_04_calloc_realloc_solution.c" \
    "After calloc (all zeroed): 0 0 0 0
After filling: 10 20 30 40
After realloc to 7: 10 20 30 40 50 60 70

calloc gave us clean zeroes automatically.
realloc preserved the first 4 elements.
The TEMP pointer pattern kept data safe on failure."

# ex_05_growable_array_solution
run_solution \
    "$EXERCISES_DIR/ex_05_growable_array_solution.c" \
    "Dynamic array: len=5  cap=8
  arr[0] = 5
  arr[1] = 10
  arr[2] = 15
  arr[3] = 20
  arr[4] = 25

Appended 5 elements — capacity grew to 8.
The array can keep growing with no fixed limit."

# ex_06_free_valgrind_solution
run_solution \
    "$EXERCISES_DIR/ex_06_free_valgrind_solution.c" \
    "Before free: a[2]=20  b[2]=21  c[2]=22

All three arrays freed cleanly.
All pointers NULLed after free.
Check with: valgrind --leak-check=full ./ex_06_free_valgrind"

# ex_07_challenge_solution
run_solution \
    "$EXERCISES_DIR/ex_07_challenge_solution.c" \
    "Push: 10 20 30 40 50
Pop: got 50
Get[0]=10  Get[1]=20  Get[2]=30  Get[3]=40
After push 60: 10 20 30 40 60
Pop error: array is empty
Final array freed."

echo "=============================="
echo "Results: $PASS passed, $FAIL failed"
if [ "$FAIL" -eq 0 ]; then
    echo "All exercises verified successfully!"
else
    echo "Some exercises failed — review the output above."
    exit 1
fi
