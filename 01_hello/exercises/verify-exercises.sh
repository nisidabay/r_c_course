#!/usr/bin/env bash
set -euo pipefail

# verify-exercises.sh — Compiles and runs ALL solutions, checks output.
# Learner can run this to verify their own work.

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
PASS=0
FAIL=0

echo "=== Group 01: 01_hello — Verifying Exercises ==="
echo ""

run_solution() {
    local src="$1"
    local expected="$2"
    local input="${3:-}"
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
    if [ -n "$input" ]; then
        actual="$(echo -e "$input" | /tmp/test_ex 2>&1 || true)"
    else
        actual="$(/tmp/test_ex 2>&1 || true)"
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

# ex_01_hello_world_solution
run_solution \
    "$EXERCISES_DIR/ex_01_hello_world_solution.c" \
    "Hello, World!"

# ex_02_data_types_solution
run_solution \
    "$EXERCISES_DIR/ex_02_data_types_solution.c" \
    "Age: 25
Price: 9.99
Letter: Z"

# ex_03_arithmetic_solution
run_solution \
    "$EXERCISES_DIR/ex_03_arithmetic_solution.c" \
    "a = 20, b = 6
a + b = 26
a - b = 14
a * b = 120
a / b = 3
a % b = 2"

# ex_04_comments_solution
run_solution \
    "$EXERCISES_DIR/ex_04_comments_solution.c" \
    "In 7 years you will be 22."

# ex_05_input_solution
run_solution \
    "$EXERCISES_DIR/ex_05_input_solution.c" \
    "Enter your name: Enter your favorite number: Hello, Alice! Your favorite number is 42." \
    "Alice\n42"

# ex_06_challenge_solution
run_solution \
    "$EXERCISES_DIR/ex_06_challenge_solution.c" \
    "Enter your birth year: Enter current year: You are approximately 36 years old.
That is about 432 months!" \
    "1990\n2026"

echo "=============================="
echo "Results: $PASS passed, $FAIL failed"
if [ "$FAIL" -eq 0 ]; then
    echo "All exercises verified successfully!"
else
    echo "Some exercises failed — review the output above."
    exit 1
fi
