#!/usr/bin/env bash
#
# verify-exercises.sh
# Group 05 — Arrays
#
# Compiles every exercise solution with -std=c11 -Wall -Wextra -pedantic.
# Runs each solution and checks output with grep for expected strings.
# Reports PASS/FAIL for each.
#
# Exit status: 0 if everything passes, 1 if any test fails.
#

set -u

GROUP="05_arrays"
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
NC='\033[0m' # No Color

pass() { echo -e "  ${GREEN}PASS${NC} $1"; PASSED=$((PASSED + 1)); }
fail() { echo -e "  ${RED}FAIL${NC} $1"; FAILED=$((FAILED + 1)); }
total() { TOTAL=$((TOTAL + 1)); }

check_compile() {
    local src="$1"
    local label="$2"
    local bin; bin="$(mktemp /tmp/arr_test_XXXXXX)"

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
echo "  Group 05 — Arrays — Exercise Verifier"
echo "============================================"
echo ""

# ============================================================
# Exercise 01 — Array Declaration
# ============================================================
echo "--- ex_01_array_declaration ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_01_array_declaration_solution.c" "ex_01_array_declaration_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "numbers\[0\] = 10" && \
       echo "$out" | grep -q "numbers\[5\] = 60" && \
       echo "$out" | grep -q "partial\[3\] = 0" && \
       echo "$out" | grep -q "flags\[4\]   = 1"; then
        pass "ex_01_array_declaration_solution"
    else
        fail "ex_01_array_declaration_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 02 — Indexing
# ============================================================
echo "--- ex_02_indexing ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_02_indexing_solution.c" "ex_02_indexing_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "First: 5" && \
       echo "$out" | grep -q "Third: 25" && \
       echo "$out" | grep -q "Last:  65" && \
       echo "$out" | grep -q "data\[2\] = 99" && \
       echo "$out" | grep -q "data\[0\] = 65" && \
       echo "$out" | grep -q "data\[6\] = 5"; then
        pass "ex_02_indexing_solution"
    else
        fail "ex_02_indexing_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 03 — Iteration
# ============================================================
echo "--- ex_03_iteration ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_03_iteration_solution.c" "ex_03_iteration_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "Sum = 45" && \
       echo "$out" | grep -q "Count > 5 = 4" && \
       echo "$out" | grep -q "Even values: 2 4 8 6 0"; then
        pass "ex_03_iteration_solution"
    else
        fail "ex_03_iteration_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 04 — Multidimensional
# ============================================================
echo "--- ex_04_multidimensional ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_04_multidimensional_solution.c" "ex_04_multidimensional_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "Total sum = 78" && \
       echo "$out" | grep -q "Row 0 sum = 10" && \
       echo "$out" | grep -q "Row 1 sum = 26" && \
       echo "$out" | grep -q "Row 2 sum = 42"; then
        pass "ex_04_multidimensional_solution"
    else
        fail "ex_04_multidimensional_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 05 — Sizeof Trick
# ============================================================
echo "--- ex_05_sizeof_trick ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_05_sizeof_trick_solution.c" "ex_05_sizeof_trick_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "Array has 12 elements" && \
       echo "$out" | grep -q "sizeof(measurements) = 48 bytes" && \
       echo "$out" | grep -q "sizeof(measurements\[0\]) = 4 bytes"; then
        pass "ex_05_sizeof_trick_solution"
    else
        fail "ex_05_sizeof_trick_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 06 — Sorting
# ============================================================
echo "--- ex_06_sorting ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_06_sorting_solution.c" "ex_06_sorting_solution")
if [ $? -eq 0 ]; then
    out=$("$bin" 2>&1)
    if echo "$out" | grep -q "Before: 42 17 55 8 31 99 63 24" && \
       echo "$out" | grep -q "After:  8 17 24 31 42 55 63 99"; then
        pass "ex_06_sorting_solution"
    else
        fail "ex_06_sorting_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Challenge 07 — Arrays + Sorting + Median
# ============================================================
echo "--- ex_07_challenge ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_07_challenge_solution.c" "ex_07_challenge_solution")
if [ $? -eq 0 ]; then
    out=$(printf "5\n12\n8\n3\n-1\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "Sorted: 3 5 8 12" && \
       echo "$out" | grep -q "Median: 6.5"; then
        pass "ex_07_challenge_solution / 4 numbers (even count)"
    else
        fail "ex_07_challenge_solution / 4 numbers (even count)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi

total
bin=$(check_compile "${EXERCISES_DIR}/ex_07_challenge_solution.c" "ex_07_challenge_solution")
if [ $? -eq 0 ]; then
    out=$(printf "10\n20\n30\n-1\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "Sorted: 10 20 30" && \
       echo "$out" | grep -q "Median: 20.0"; then
        pass "ex_07_challenge_solution / 3 numbers (odd count)"
    else
        fail "ex_07_challenge_solution / 3 numbers (odd count)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi

total
bin=$(check_compile "${EXERCISES_DIR}/ex_07_challenge_solution.c" "ex_07_challenge_solution")
if [ $? -eq 0 ]; then
    out=$(printf "42\n-1\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "Sorted: 42" && \
       echo "$out" | grep -q "Median: 42.0"; then
        pass "ex_07_challenge_solution / single number"
    else
        fail "ex_07_challenge_solution / single number"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi

total
bin=$(check_compile "${EXERCISES_DIR}/ex_07_challenge_solution.c" "ex_07_challenge_solution")
if [ $? -eq 0 ]; then
    out=$(printf -- "-1\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "No numbers entered"; then
        pass "ex_07_challenge_solution / no numbers"
    else
        fail "ex_07_challenge_solution / no numbers"
        echo "    Got: $out"
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
