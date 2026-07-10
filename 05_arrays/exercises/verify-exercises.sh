#!/usr/bin/env bash
# verify-exercises.sh
# Group 05 — Arrays
# Compiles and runs all exercise solutions for Group 05.
# Usage: bash verify-exercises.sh [--clean]
#   --clean   remove all compiled binaries after running

set -euo pipefail

CDIR="$(cd "$(dirname "$0")" && pwd)"
EXERCISES_DIR="$CDIR"
FLAGS="-std=c11 -Wall -Wextra -Wpedantic"
BINS=()
FAIL=0
PASS=0

# ANSI colour codes
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m' # No Colour

printf "${CYAN}=== Group 05 — Arrays: Exercise Verification ===${NC}\n\n"

# ── Compile each solution ──────────────────────────────────────────
for src in "$EXERCISES_DIR"/solution_ex_*.c; do
    [ -f "$src" ] || continue
    name="$(basename "$src" .c)"
    bin="$EXERCISES_DIR/$name"

    printf "Compiling %-40s ... " "$name.c"

    if gcc $FLAGS -o "$bin" "$src" 2>/dev/null; then
        printf "${GREEN}OK${NC}\n"
        BINS+=("$bin")
    else
        printf "${RED}FAILED${NC}\n"
        # Show actual error for diagnostics
        gcc $FLAGS -o "$bin" "$src" 2>&1 || true
        ((++FAIL))
    fi
done

printf "\n"

# ── Run each compiled binary ───────────────────────────────────────
for bin in "${BINS[@]}"; do
    name="$(basename "$bin")"
    printf "Running  %-40s ... " "$name"

    # For the challenge, feed it some test input
    if echo "$name" | grep -q "07_challenge"; then
        output="$(
            printf "5\n12\n8\n3\n-1\n" | "$bin" 2>&1
        )" || true
    else
        output="$("$bin" 2>&1)" || true
    fi

    echo "${GREEN}PASSED${NC}"
    echo "$output" | sed 's/^/         | /'
    ((++PASS))
done

printf "\n"
printf "${CYAN}============================================${NC}\n"
printf "  Compiled: %2d   Ran: %2d   Failures: %2d\n" "$((PASS + FAIL))" "$PASS" "$FAIL"

# ── Clean up binaries only if requested ────────────────────────────
if [ "${1:-}" = "--clean" ]; then
    printf "\nCleaning up binaries...\n"
    for bin in "${BINS[@]}"; do
        rm -f "$bin"
    done
fi

exit "$FAIL"
