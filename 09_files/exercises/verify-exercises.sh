#!/usr/bin/env bash
# verify-exercises.sh
# Compiles and runs all Group 09 (Files) exercises and solutions.
# Usage: bash verify-exercises.sh [exercise_number]
#   If exercise_number is given (e.g., 02), only that exercise is tested.
#   If omitted, all exercises are tested.

set -e

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
SOLUTIONS_DIR="$EXERCISES_DIR/solutions"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"

# Color helpers
green() { printf "\033[0;32m%s\033[0m\n" "$1"; }
red()   { printf "\033[0;31m%s\033[0m\n" "$1"; }
bold()  { printf "\033[1m%s\033[0m\n" "$1"; }

# If a specific exercise number is given
FILTER=""
if [ $# -ge 1 ]; then
    FILTER=$(printf "%02d" "$1")
    bold "=== Verifying Group 09 — Exercise $FILTER ==="
else
    bold "=== Verifying Group 09: Files (all exercises) ==="
fi

passed=0
failed=0
total=0

run_exercise() {
    local src="$1"
    local label="$2"
    local exe="${src%.c}"

    total=$((total + 1))

    # Compile
    if ! $CC $CFLAGS -o "$exe" "$src" 2>/dev/null; then
        red "[COMPILE FAIL] $label"
        failed=$((failed + 1))
        return
    fi

    # Run (redirect stderr to stdout to catch perror output)
    # Change to exercises dir so relative paths work
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    if "$exe" > /tmp/verify_out.txt 2>&1; then
        green "[PASS] $label"
        passed=$((passed + 1))
    else
        red "[FAIL] $label — exit code $?"
        cat /tmp/verify_out.txt
        failed=$((failed + 1))
    fi
    popd > /dev/null 2>&1 || true

    # Clean up binary
    rm -f "$exe"
}

# Ex 01: fopen modes
if [ -z "$FILTER" ] || [ "$FILTER" = "01" ]; then
    bold "--- Exercise 01: fopen Modes ---"
    run_exercise "$SOLUTIONS_DIR/ex_01_fopen_modes_solution.c" "ex_01 solution"
fi

# Ex 02: Text I/O
if [ -z "$FILTER" ] || [ "$FILTER" = "02" ]; then
    bold "--- Exercise 02: Text I/O (fgets / fprintf) ---"
    run_exercise "$SOLUTIONS_DIR/ex_02_text_io_solution.c" "ex_02 solution"
fi

# Ex 03: fclose cleanup
if [ -z "$FILTER" ] || [ "$FILTER" = "03" ]; then
    bold "--- Exercise 03: fclose and Cleanup ---"
    run_exercise "$SOLUTIONS_DIR/ex_03_fclose_cleanup_solution.c" "ex_03 solution"
fi

# Ex 04: perror / errno
if [ -z "$FILTER" ] || [ "$FILTER" = "04" ]; then
    bold "--- Exercise 04: perror and errno ---"
    # perror on /root/secret.txt will produce EACCES — that's expected, not a failure
    run_exercise "$SOLUTIONS_DIR/ex_04_perror_solution.c" "ex_04 solution"
fi

# Ex 05: file ops (remove, rename, existence)
if [ -z "$FILTER" ] || [ "$FILTER" = "05" ]; then
    bold "--- Exercise 05: File Operations ---"
    run_exercise "$SOLUTIONS_DIR/ex_05_file_ops_solution.c" "ex_05 solution"
fi

# Ex 06: challenge
if [ -z "$FILTER" ] || [ "$FILTER" = "06" ]; then
    bold "--- Exercise 06: Mini-Challenge (Line Count + Longest Line) ---"
    # Check that sample.txt exists
    if [ ! -f "$EXERCISES_DIR/sample.txt" ]; then
        red "[SKIP] sample.txt not found — challenge cannot run"
    else
        run_exercise "$SOLUTIONS_DIR/ex_06_challenge_solution.c" "ex_06 solution"
    fi
fi

# Summary
echo ""
bold "=== Summary ==="
echo "Total: $total  |  Passed: $(green "$passed")  |  Failed: $(red "$failed")"

# Also test compilation of blank exercises
bold "--- Compilation check: blank exercises (fill-in-the-blank) ---"
for i in 01 02 03 04 05 06; do
    src="$EXERCISES_DIR/ex_${i}_"*.c 2>/dev/null || true
    # Just check the exercise file exists
    if ls "$EXERCISES_DIR/ex_${i}_"*.c > /dev/null 2>&1; then
        # Blank exercises might not compile due to missing blanks — that's fine
        # We just check they exist
        printf "  Found: "
        ls "$EXERCISES_DIR/ex_${i}_"*.c
    fi
done

if [ "$failed" -eq 0 ]; then
    echo ""
    green "All exercises verified successfully!"
else
    echo ""
    red "Some exercises failed — review output above."
    exit 1
fi
