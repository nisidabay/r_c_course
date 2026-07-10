#!/usr/bin/env bash
#
# verify-exercises.sh
# Group 03 — Functions
#
# Compiles every exercise and solution with -std=c11 -Wall -Wextra -pedantic.
# Runs each exercise with canned input and checks output / exit code.
# Reports PASS/FAIL for each.
#
# Exit status: 0 if everything passes, 1 if any test fails.
#

set -u

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
SOLUTIONS_DIR="${EXERCISES_DIR}/solutions"
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

cleanup() {
    rm -f "${BIN:-}" 2>/dev/null
}
check_compile() {
    local src="$1"
    local label="$2"
    local bin; bin="$(mktemp /tmp/func_test_XXXXXX)"

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
echo "  Group 03 — Functions — Exercise Verifier"
echo "============================================"
echo ""

# ============================================================
# Exercise 01 — Defining Functions
# ============================================================
echo "--- ex_01_defining (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_01_defining_solved.c" "ex_01_defining_solved")
if [ $? -eq 0 ]; then
    out=$(printf "7\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "Hello from say_hello!" && echo "$out" | grep -q "double_it(7) = 14"; then
        pass "ex_01_defining_solved"
    else
        fail "ex_01_defining_solved (output mismatch)"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Exercise 02 — Return Values
# ============================================================
echo "--- ex_02_return_values (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_02_return_values_solved.c" "ex_02_return_values_solved")
if [ $? -eq 0 ]; then
    out=$(printf "42\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "42 is even"; then
        pass "ex_02_return_values_solved / even"
    else
        fail "ex_02_return_values_solved / even"
        echo "    Got: $out"
    fi
    cleanup
fi

total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_02_return_values_solved.c" "ex_02_return_values_solved")
if [ $? -eq 0 ]; then
    out=$(printf "7\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "7 is odd"; then
        pass "ex_02_return_values_solved / odd"
    else
        fail "ex_02_return_values_solved / odd"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Exercise 03 — Pass by Value
# ============================================================
echo "--- ex_03_pass_by_value (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_03_pass_by_value_solved.c" "ex_03_pass_by_value_solved")
if [ $? -eq 0 ]; then
    out=$(printf "10 20\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "unchanged" && echo "$out" | grep -q "add_them(10, 20) = 30"; then
        pass "ex_03_pass_by_value_solved"
    else
        fail "ex_03_pass_by_value_solved (output mismatch)"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Exercise 04 — Scope
# ============================================================
echo "--- ex_04_scope (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_04_scope_solved.c" "ex_04_scope_solved")
if [ $? -eq 0 ]; then
    out=$(printf "42\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "counter = 2" && echo "$out" | grep -q "Inside block: local_val = 999" && echo "$out" | grep -q "Outside block: local_val = 42"; then
        pass "ex_04_scope_solved"
    else
        fail "ex_04_scope_solved (output mismatch)"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Exercise 05 — Prototypes
# ============================================================
echo "--- ex_05_prototypes (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_05_prototypes_solved.c" "ex_05_prototypes_solved")
if [ $? -eq 0 ]; then
    out=$(printf "7 -3\n" | "$bin" 2>&1)
    if echo "$out" | grep -q "7 is positive" && echo "$out" | grep -q "7 \* -3 = -21"; then
        pass "ex_05_prototypes_solved"
    else
        fail "ex_05_prototypes_solved (output mismatch)"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Exercise 06 — Exit Codes
# ============================================================
echo "--- ex_06_exit_codes (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_06_exit_codes_solved.c" "ex_06_exit_codes_solved")
if [ $? -eq 0 ]; then
    out=$(printf "10 2\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "10 / 2 = 5" && echo "$out" | grep -q "EXIT:0"; then
        pass "ex_06_exit_codes_solved / success path"
    else
        fail "ex_06_exit_codes_solved / success path"
        echo "    Got: $out"
    fi
    cleanup
fi

total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_06_exit_codes_solved.c" "ex_06_exit_codes_solved")
if [ $? -eq 0 ]; then
    out=$(printf "5 0\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "division by zero" && echo "$out" | grep -q "EXIT:1"; then
        pass "ex_06_exit_codes_solved / error path"
    else
        fail "ex_06_exit_codes_solved / error path"
        echo "    Got: $out"
    fi
    cleanup
fi
echo ""

# ============================================================
# Challenge 07 — Function Composition
# ============================================================
echo "--- ex_07_challenge (solutions) ---"
total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_07_challenge_solved.c" "ex_07_challenge_solved")
if [ $? -eq 0 ]; then
    out=$(printf "5\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "5! = 120" && echo "$out" | grep -q "120 is NOT prime" && echo "$out" | grep -q "120 has 16 divisor" && echo "$out" | grep -q "EXIT:0"; then
        pass "ex_07_challenge_solved / 5! = 120"
    else
        fail "ex_07_challenge_solved / 5! = 120"
        echo "    Got: $out"
    fi
    cleanup
fi

total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_07_challenge_solved.c" "ex_07_challenge_solved")
if [ $? -eq 0 ]; then
    out=$(printf "0\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "0! = 1" && echo "$out" | grep -q "1 has 1 divisor" && echo "$out" | grep -q "EXIT:0"; then
        pass "ex_07_challenge_solved / 0! = 1"
    else
        fail "ex_07_challenge_solved / 0! = 1"
        echo "    Got: $out"
    fi
    cleanup
fi

total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_07_challenge_solved.c" "ex_07_challenge_solved")
if [ $? -eq 0 ]; then
    out=$(printf "13\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "out of range" && echo "$out" | grep -q "EXIT:1"; then
        pass "ex_07_challenge_solved / out of range"
    else
        fail "ex_07_challenge_solved / out of range"
        echo "    Got: $out"
    fi
    cleanup
fi

total
bin=$(check_compile "${SOLUTIONS_DIR}/ex_07_challenge_solved.c" "ex_07_challenge_solved")
if [ $? -eq 0 ]; then
    out=$(printf "3\n" | "$bin" 2>&1; echo "EXIT:$?")
    if echo "$out" | grep -q "3! = 6" && echo "$out" | grep -q "6 is NOT prime" && echo "$out" | grep -q "EXIT:0"; then
        pass "ex_07_challenge_solved / 3! = 6"
    else
        fail "ex_07_challenge_solved / 3! = 6"
        echo "    Got: $out"
    fi
    cleanup
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
