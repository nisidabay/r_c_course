#!/usr/bin/env bash
# verify-exercises.sh — Exercise verifier for Group 02: Bitwise
set -u

COURSE_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
FAIL=0
PASS=0
TOTAL=0

red()   { echo -e "\033[0;31m$1\033[0m"; }
green() { echo -e "\033[0;32m$1\033[0m"; }

pass() { echo -e "  ${GREEN}PASS${NC} $1"; PASS=$((PASS + 1)); }
fail() { echo -e "  ${RED}FAIL${NC} $1"; FAIL=$((FAIL + 1)); }
total() { TOTAL=$((TOTAL + 1)); }

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "=== Group 02 — Bitwise Operations — Verifying Exercises ==="
echo ""

EXERCISES_DIR="$(dirname "$0")"
CONCEPT_DIR="$(dirname "$0")/../concept"

# Helper: compile and run a solution with optional input
verify_solution() {
    local exe_name="$1"
    local src="$2"
    local label="$3"
    local input="$4"

    total
    if $CC $CFLAGS -o "/tmp/${exe_name}" "$src" 2>/dev/null; then
        if echo -e "$input" | "/tmp/${exe_name}" > /dev/null 2>&1; then
            pass "$label"
        else
            fail "$label (runtime)"
        fi
    else
        fail "$label (compile)"
    fi
}

# ---- Exercise 01: Popcount ----
verify_solution "ex01" "${EXERCISES_DIR}/ex_01_popcount_solution.c" \
    "ex_01_popcount_solution" "42"

# ---- Exercise 02: Power of 2 ----
verify_solution "ex02a" "${EXERCISES_DIR}/ex_02_power_of_two_solution.c" \
    "ex_02_power_of_two (power of 2)" "64"
verify_solution "ex02b" "${EXERCISES_DIR}/ex_02_power_of_two_solution.c" \
    "ex_02_power_of_two (not power of 2)" "42"
verify_solution "ex02c" "${EXERCISES_DIR}/ex_02_power_of_two_solution.c" \
    "ex_02_power_of_two (zero)" "0"

# ---- Exercise 03: Bit check ----
verify_solution "ex03a" "${EXERCISES_DIR}/ex_03_bit_check_solution.c" \
    "ex_03_bit_check (bit 3 set)" "42\n3"
verify_solution "ex03b" "${EXERCISES_DIR}/ex_03_bit_check_solution.c" \
    "ex_03_bit_check (bit 4 not set)" "42\n4"

# ---- Exercise 04: Toggle bit ----
verify_solution "ex04" "${EXERCISES_DIR}/ex_04_toggle_bit_solution.c" \
    "ex_04_toggle_bit_solution" "42\n1"

# ---- Exercise 05: XOR swap ----
verify_solution "ex05" "${EXERCISES_DIR}/ex_05_xor_swap_solution.c" \
    "ex_05_xor_swap_solution" "42\n99"

# ---- Exercise 06: Challenge (bitwise calculator) ----
verify_solution "ex06a" "${EXERCISES_DIR}/ex_06_challenge_solution.c" \
    "ex_06_challenge (AND)" "42 & 25\nq"
verify_solution "ex06b" "${EXERCISES_DIR}/ex_06_challenge_solution.c" \
    "ex_06_challenge (shift)" "1 << 10\nq"

echo ""
echo "=== Results: ${PASS} passed, ${FAIL} failed ==="
exit $FAIL
