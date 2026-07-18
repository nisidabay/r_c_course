#!/usr/bin/env bash
#
# verify-exercises.sh
# Group 06 — Pointers 101
#
# Compiles every exercise solution with -std=c11 -Wall -Wextra -pedantic.
# Runs each solution and checks output with grep for expected strings.
# Reports PASS/FAIL for each.
#
# Exit status: 0 if everything passes, 1 if any test fails.
#

set -u

GROUP="06_pointers_101"
EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="${CC:-gcc}"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
TOTAL=0
PASSED=0
FAILED=0

# ---- colours ----
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

pass() { echo -e "  ${GREEN}PASS${NC} $1"; PASSED=$((PASSED + 1)); }
fail() { echo -e "  ${RED}FAIL${NC} $1"; FAILED=$((FAILED + 1)); }
total() { TOTAL=$((TOTAL + 1)); }

check_compile() {
    local src="$1"
    local label="$2"
    local bin; bin="$(mktemp /tmp/ptr_test_XXXXXX)"

    if ! $CC $CFLAGS -o "$bin" "$src" 2>/dev/null; then
        echo -e "  ${RED}COMPILE ERROR${NC} $label"
        $CC $CFLAGS -o "$bin" "$src" 2>&1 | sed 's/^/    /'
        rm -f "$bin"
        return 1
    fi
    echo "$bin"
}

# ---- header ----
echo "============================================"
echo "  Group 06 — Pointers 101 — Exercise Verifier"
echo "============================================"
echo ""

# ============================================================
# Exercise 01 — address-of
# ============================================================
echo "--- ex_01_address_of ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_01_address_of_solution.c" "ex_01_address_of_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "&a = 0x"   || { echo "  FAIL: missing &a address";   ex_pass=false; }
    echo "$actual" | grep -q "&b = 0x"   || { echo "  FAIL: missing &b address";   ex_pass=false; }
    echo "$actual" | grep -q "&c = 0x"   || { echo "  FAIL: missing &c address";   ex_pass=false; }
    echo "$actual" | grep -q "unique"    || { echo "  FAIL: missing uniqueness message"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_01_address_of_solution"
    else
        fail "ex_01_address_of_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -5)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 02 — dereference
# ============================================================
echo "--- ex_02_dereference ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_02_dereference_solution.c" "ex_02_dereference_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "x  = 42"                   || { echo "  FAIL: expected x=42"; ex_pass=false; }
    echo "$actual" | grep -q "\*p = 42"                  || { echo "  FAIL: expected *p=42"; ex_pass=false; }
    echo "$actual" | grep -q "x  = 99"                   || { echo "  FAIL: expected x=99 after write"; ex_pass=false; }
    echo "$actual" | grep -q "x  = 7"                    || { echo "  FAIL: expected x=7 after direct change"; ex_pass=false; }
    echo "$actual" | grep -q "\*p = 7"                   || { echo "  FAIL: expected *p=7 reflects x"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_02_dereference_solution"
    else
        fail "ex_02_dereference_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -10)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 03 — NULL pointer
# ============================================================
echo "--- ex_03_null_pointer ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_03_null_pointer_solution.c" "ex_03_null_pointer_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "p is valid, \*p = 100"     || { echo "  FAIL: expected valid dereference"; ex_pass=false; }
    echo "$actual" | grep -qi "nowhere is NULL"           || { echo "  FAIL: expected NULL skip message"; ex_pass=false; }
    echo "$actual" | grep -qi "segmentation fault"        || { echo "  FAIL: expected segfault mention"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_03_null_pointer_solution"
    else
        fail "ex_03_null_pointer_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -10)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 04 — pointer params (swap)
# ============================================================
echo "--- ex_04_pointers_params ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_04_pointers_params_solution.c" "ex_04_pointers_params_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "FAILS"                      || { echo "  FAIL: missing FAILS section"; ex_pass=false; }
    echo "$actual" | grep -q "Inside swap_fails: a=20, b=10" || { echo "  FAIL: expected local swap in swap_fails"; ex_pass=false; }
    echo "$actual" | grep -q "After  swap_fails:  x=10, y=20" || { echo "  FAIL: expected x=10,y=20 after fail swap"; ex_pass=false; }
    echo "$actual" | grep -q "After  swap_works: x=20, y=10" || { echo "  FAIL: expected x=20,y=10 after working swap"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_04_pointers_params_solution"
    else
        fail "ex_04_pointers_params_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -10)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 05 — arrays and pointers
# ============================================================
echo "--- ex_05_arrays_pointers ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_05_arrays_pointers_solution.c" "ex_05_arrays_pointers_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "sizeof(int) = 4"            || { echo "  FAIL: expected sizeof(int)=4"; ex_pass=false; }
    echo "$actual" | grep -q "arr\[0\] = 10"              || { echo "  FAIL: expected arr[0]=10"; ex_pass=false; }
    echo "$actual" | grep -q "equal"                      || { echo "  FAIL: expected equality checks"; ex_pass=false; }
    echo "$actual" | grep -q "arr\[2\] = 300"             || { echo "  FAIL: expected arr[2]=300 after pointer arithmetic write"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_05_arrays_pointers_solution"
    else
        fail "ex_05_arrays_pointers_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -10)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Challenge 06 — array reverse via pointers
# ============================================================
echo "--- ex_06_challenge ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_06_challenge_solution.c" "ex_06_challenge_solution")
if [ $? -eq 0 ]; then
    actual=$("$bin" 2>&1)
    ex_pass=true
    echo "$actual" | grep -q "Original array:  \[1, 2, 3, 4, 5, 6, 7, 8\]" || { echo "  FAIL: expected original array"; ex_pass=false; }
    echo "$actual" | grep -q "Sum.*36"                    || { echo "  FAIL: expected sum=36"; ex_pass=false; }
    echo "$actual" | grep -q "Reversed array:  \[8, 7, 6, 5, 4, 3, 2, 1\]" || { echo "  FAIL: expected reversed array"; ex_pass=false; }
    echo "$actual" | grep -q "Back to original: \[1, 2, 3, 4, 5, 6, 7, 8\]" || { echo "  FAIL: expected back to original"; ex_pass=false; }
    if $ex_pass; then
        pass "ex_06_challenge_solution"
    else
        fail "ex_06_challenge_solution (output mismatch)"
        echo "    Got: $(echo "$actual" | head -10)"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Summary
# ============================================================
echo "============================================"
echo -e "  Results: ${GREEN}${PASSED} passed${NC}, ${RED}${FAILED} failed${NC}, $TOTAL total"
echo "============================================"

if [ $FAILED -gt 0 ]; then
    exit 1
fi
exit 0
