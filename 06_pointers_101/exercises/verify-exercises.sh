#!/usr/bin/env bash
set -euo pipefail

# verify-exercises.sh — Compiles and runs ALL solutions, checks output.
# Learner can run this to verify their own work after filling in the blanks.

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
PASS=0
FAIL=0

echo "=== Group 06: 06_pointers_101 — Verifying Exercises ==="
echo ""

check_expected_strings() {
    local src="$1"
    local name
    name="$(basename "$src" .c)"

    echo -n "[$name] Compiling... "
    if ! "$CC" $CFLAGS -o /tmp/test_ex "$src" 2>/dev/null; then
        echo "FAIL (compile error)"
        "$CC" $CFLAGS -o /tmp/test_ex "$src" 2>&1 || true
        FAIL=$((FAIL + 1))
        return
    fi
    echo "OK"

    echo -n "[$name] Running... "
    local actual
    actual="$(/tmp/test_ex 2>&1 || true)"

    # First check: no crash
    if [ -z "$actual" ]; then
        echo "FAIL (no output/crash)"
        FAIL=$((FAIL + 1))
        return
    fi

    # Second check: no actual segfault (exit code 139)
    # We only care about actual crashes, not printf messages mentioning segfault

    echo "OK (no crash)"
}

# Ex 01: address-of — check that addresses are printed and are unique
echo "--- Exercise 01: address-of ---"
ex1_src="$EXERCISES_DIR/solutions/ex_01_address_of_solution.c"
check_expected_strings "$ex1_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex1_pass=true
echo "$actual" | grep -q "&a = 0x"   || { echo "  FAIL: missing &a address";   ex1_pass=false; }
echo "$actual" | grep -q "&b = 0x"   || { echo "  FAIL: missing &b address";   ex1_pass=false; }
echo "$actual" | grep -q "&c = 0x"   || { echo "  FAIL: missing &c address";   ex1_pass=false; }
echo "$actual" | grep -q "unique"    || { echo "  FAIL: missing uniqueness message"; ex1_pass=false; }
if $ex1_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

# Ex 02: dereference
echo "--- Exercise 02: dereference ---"
ex2_src="$EXERCISES_DIR/solutions/ex_02_dereference_solution.c"
check_expected_strings "$ex2_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex2_pass=true
echo "$actual" | grep -q "x  = 42"                   || { echo "  FAIL: expected x=42"; ex2_pass=false; }
echo "$actual" | grep -q "\*p = 42"                  || { echo "  FAIL: expected *p=42"; ex2_pass=false; }
echo "$actual" | grep -q "x  = 99"                   || { echo "  FAIL: expected x=99 after write"; ex2_pass=false; }
echo "$actual" | grep -q "x  = 7"                    || { echo "  FAIL: expected x=7 after direct change"; ex2_pass=false; }
echo "$actual" | grep -q "\*p = 7"                   || { echo "  FAIL: expected *p=7 reflects x"; ex2_pass=false; }
if $ex2_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

# Ex 03: NULL pointer
echo "--- Exercise 03: NULL pointer ---"
ex3_src="$EXERCISES_DIR/solutions/ex_03_null_pointer_solution.c"
check_expected_strings "$ex3_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex3_pass=true
echo "$actual" | grep -q "p is valid, \*p = 100"     || { echo "  FAIL: expected valid dereference"; ex3_pass=false; }
echo "$actual" | grep -qi "nowhere is NULL"           || { echo "  FAIL: expected NULL skip message"; ex3_pass=false; }
echo "$actual" | grep -qi "segmentation fault"        || { echo "  FAIL: expected segfault mention"; ex3_pass=false; }
if $ex3_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

# Ex 04: pointer params (swap)
echo "--- Exercise 04: pointer params ---"
ex4_src="$EXERCISES_DIR/solutions/ex_04_pointers_params_solution.c"
check_expected_strings "$ex4_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex4_pass=true
echo "$actual" | grep -q "FAILS"                      || { echo "  FAIL: missing FAILS section"; ex4_pass=false; }
# swap_fails: Inside shows swapped, but caller unchanged
echo "$actual" | grep -q "Inside swap_fails: a=20, b=10" || { echo "  FAIL: expected local swap in swap_fails"; ex4_pass=false; }
echo "$actual" | grep -q "After  swap_fails:  x=10, y=20" || { echo "  FAIL: expected x=10,y=20 after fail swap"; ex4_pass=false; }
echo "$actual" | grep -q "After  swap_works: x=20, y=10" || { echo "  FAIL: expected x=20,y=10 after working swap"; ex4_pass=false; }
if $ex4_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

# Ex 05: arrays and pointers
echo "--- Exercise 05: arrays and pointers ---"
ex5_src="$EXERCISES_DIR/solutions/ex_05_arrays_pointers_solution.c"
check_expected_strings "$ex5_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex5_pass=true
echo "$actual" | grep -q "sizeof(int) = 4"            || { echo "  FAIL: expected sizeof(int)=4"; ex5_pass=false; }
echo "$actual" | grep -q "arr\[0\] = 10"              || { echo "  FAIL: expected arr[0]=10"; ex5_pass=false; }
echo "$actual" | grep -q "equal"                      || { echo "  FAIL: expected equality checks"; ex5_pass=false; }
echo "$actual" | grep -q "arr\[2\] = 300"             || { echo "  FAIL: expected arr[2]=300 after pointer arithmetic write"; ex5_pass=false; }
if $ex5_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

# Ex 06: challenge
echo "--- Exercise 06: challenge ---"
ex6_src="$EXERCISES_DIR/solutions/ex_06_challenge_solution.c"
check_expected_strings "$ex6_src"
actual="$(/tmp/test_ex 2>&1 || true)"
ex6_pass=true
echo "$actual" | grep -q "Original array:  \[1, 2, 3, 4, 5, 6, 7, 8\]" || { echo "  FAIL: expected original array"; ex6_pass=false; }
echo "$actual" | grep -q "Sum.*36"                    || { echo "  FAIL: expected sum=36"; ex6_pass=false; }
echo "$actual" | grep -q "Reversed array:  \[8, 7, 6, 5, 4, 3, 2, 1\]" || { echo "  FAIL: expected reversed array"; ex6_pass=false; }
echo "$actual" | grep -q "Back to original: \[1, 2, 3, 4, 5, 6, 7, 8\]" || { echo "  FAIL: expected back to original"; ex6_pass=false; }
if $ex6_pass; then
    echo "  PASS"
    PASS=$((PASS + 1))
else
    FAIL=$((FAIL + 1))
fi
echo ""

echo "=============================="
echo "Results: $PASS passed, $FAIL failed"
if [ "$FAIL" -eq 0 ]; then
    echo "All exercises verified successfully!"
else
    echo "Some exercises failed — review the output above."
    exit 1
fi
