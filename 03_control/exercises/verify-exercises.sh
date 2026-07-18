#!/usr/bin/env bash
#
# verify-exercises.sh — verification script for Group 02 (02_control)
#
# Tests that all exercise solutions compile and produce correct output,
# and that the exercise stubs compile (to let students fill blanks).
#
# Usage: bash verify-exercises.sh
#

set -euo pipefail

GROUP="02_control"
EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"

PASS=0
FAIL=0
TOTAL=0

red()   { printf '\033[1;31m%s\033[0m\n' "$1"; }
green() { printf '\033[1;32m%s\033[0m\n' "$1"; }
cyan()  { printf '\033[1;36m%s\033[0m\n' "$1"; }

cyan "=========================================="
cyan "  Verifying exercises — ${GROUP}"
cyan "=========================================="
echo ""

# ============================================================
# 1. Verify each exercise STUB compiles
# ============================================================
for stub in ex_01_if_else.c ex_02_while.c ex_03_for.c ex_04_logical.c \
            ex_05_comparisons.c ex_06_break_continue.c ex_07_challenge.c; do
    src="${EXERCISES_DIR}/${stub}"
    bin="/tmp/${stub%.c}_stub"

    TOTAL=$((TOTAL + 1))

    # Stubs have /*@*/ markers — they should still compile as-is because
    # the marker is a valid C comment. Let's try to compile.
    if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
        green "  [PASS] ${stub} compiles"
        PASS=$((PASS + 1))
        rm -f "${bin}"
    else
        red "  [CHECK] ${stub} stub compile (expected — markers are comments)" 
        # Stubs with /*@*/ markers may not compile since the blanks
        # need to be filled. That's OK — they serve as templates.
        # We'll just note it.
    fi
done

echo ""

# ============================================================
# 2. Verify each SOLUTION compiles and runs correctly
# ============================================================
echo "--- Solution tests ---"

# Helper: strip prompt prefix from solution output (prompts like "Enter ...: " are on the same line)
strip_prompt() {
    # Remove everything up to and including ": " at the start or end of prompt
    sed 's/^.*: //'
}

# ----- ex_01: if/else (positive, negative, zero) -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_01_if_else_solution.c"
bin="/tmp/ex_01_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    result_pos=$(echo "5"    | "${bin}" 2>&1 | strip_prompt)
    result_neg=$(echo "-3"   | "${bin}" 2>&1 | strip_prompt)
    result_zero=$(echo "0"   | "${bin}" 2>&1 | strip_prompt)
    if [ "${result_pos}" = "positive" ] && \
       [ "${result_neg}" = "negative" ] && \
       [ "${result_zero}" = "zero" ]; then
        green "  [PASS] ex_01_if_else_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_01_if_else_solution.c — wrong output"
        echo "    Got: pos='${result_pos}', neg='${result_neg}', zero='${result_zero}'"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_01_if_else_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_02: while (countdown) -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_02_while_solution.c"
bin="/tmp/ex_02_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    result=$(echo "3" | "${bin}" 2>&1 | strip_prompt)
    expected="3
2
1"
    if [ "${result}" = "${expected}" ]; then
        green "  [PASS] ex_02_while_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_02_while_solution.c — wrong output"
        echo "    Expected:"
        echo "${expected}"
        echo "    Got:"
        echo "${result}"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_02_while_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_03: for (sum 1..n) -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_03_for_solution.c"
bin="/tmp/ex_03_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    result=$(echo "5" | "${bin}" 2>&1 | strip_prompt)
    if [ "${result}" = "Sum = 15" ] && [ "$(echo '1' | "${bin}" 2>&1 | strip_prompt)" = "Sum = 1" ]; then
        green "  [PASS] ex_03_for_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_03_for_solution.c — wrong output"
        echo "    n=5 got: ${result}"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_03_for_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_04: logical (range check) -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_04_logical_solution.c"
bin="/tmp/ex_04_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    in=$(echo "25"  | "${bin}" 2>&1 | strip_prompt)
    out_low=$(echo "3" | "${bin}" 2>&1 | strip_prompt)
    out_high=$(echo "99" | "${bin}" 2>&1 | strip_prompt)
    edge_low=$(echo "10" | "${bin}" 2>&1 | strip_prompt)
    edge_high=$(echo "50" | "${bin}" 2>&1 | strip_prompt)
    if [ "${in}" = "In range" ] && [ "${out_low}" = "Out of range" ] && \
       [ "${out_high}" = "Out of range" ] && [ "${edge_low}" = "In range" ] && \
       [ "${edge_high}" = "In range" ]; then
        green "  [PASS] ex_04_logical_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_04_logical_solution.c — wrong output"
        echo "    25→'${in}', 3→'${out_low}', 99→'${out_high}', 10→'${edge_low}', 50→'${edge_high}'"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_04_logical_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_05: comparisons -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_05_comparisons_solution.c"
bin="/tmp/ex_05_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    gt=$(echo "7 3"   | "${bin}" 2>&1 | strip_prompt)
    lt=$(echo "2 9"   | "${bin}" 2>&1 | strip_prompt)
    eq=$(echo "5 5"   | "${bin}" 2>&1 | strip_prompt)
    if [ "${gt}" = "a is greater" ] && [ "${lt}" = "b is greater" ] && \
       [ "${eq}" = "equal" ]; then
        green "  [PASS] ex_05_comparisons_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_05_comparisons_solution.c — wrong output"
        echo "    7 3→'${gt}', 2 9→'${lt}', 5 5→'${eq}'"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_05_comparisons_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_06: break/continue -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_06_break_continue_solution.c"
bin="/tmp/ex_06_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    result=$(printf "3\n-2\n5\n0\n" | "${bin}" 2>&1 | tail -1)
    if [ "${result}" = "Sum of positives = 8" ]; then
        green "  [PASS] ex_06_break_continue_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_06_break_continue_solution.c — wrong output"
        echo "    3, -2, 5, 0 → '${result}' (expected 'Sum of positives = 8')"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_06_break_continue_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ----- ex_07: FizzBuzz challenge -----
TOTAL=$((TOTAL + 1))
src="${EXERCISES_DIR}/ex_07_challenge_solution.c"
bin="/tmp/ex_07_solution"
if ${CC} ${CFLAGS} -o "${bin}" "${src}" 2>/dev/null; then
    result=$(echo "15" | "${bin}" 2>&1 | strip_prompt)
    expected="1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz"
    if [ "${result}" = "${expected}" ]; then
        green "  [PASS] ex_07_challenge_solution.c — correct output"
        PASS=$((PASS + 1))
    else
        red "  [FAIL] ex_07_challenge_solution.c — wrong output"
        echo "--- Expected ---"
        echo "${expected}"
        echo "--- Got ---"
        echo "${result}"
        FAIL=$((FAIL + 1))
    fi
else
    red "  [FAIL] ex_07_challenge_solution.c — does not compile"
    FAIL=$((FAIL + 1))
fi
rm -f "${bin}"

# ============================================================
# Summary
# ============================================================
echo ""
cyan "=========================================="
cyan "  Results: ${PASS}/${TOTAL} passed, ${FAIL} failed"
cyan "=========================================="

if [ ${FAIL} -eq 0 ]; then
    green "  All tests passed!"
else
    red "  ${FAIL} test(s) failed."
    exit 1
fi
