#!/usr/bin/env bash
# verify-exercises.sh
# Group 10 — Advanced: Exercise verifier
#
# Compiles each exercise and solution file with strict flags,
# runs them, and reports pass/fail.
#
# Usage:
#   ./verify-exercises.sh            # verify all exercises
#   ./verify-exercises.sh -v         # verbose: show program output
#   ./verify-exercises.sh <pattern>  # verify matching exercises only

set -euo pipefail

CDIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
VERBOSE=false

# Parse options
ARGS=()
for arg in "$@"; do
    case "$arg" in
        -v|--verbose) VERBOSE=true ;;
        *) ARGS+=("$arg") ;;
    esac
done

# Determine which solution files to process
if [ ${#ARGS[@]} -gt 0 ]; then
    pattern="${ARGS[0]}"
    # If pattern doesn't end with _solution.c, add wildcard
    [[ "$pattern" != *_solution.c ]] && pattern="${pattern}_solution.c"
    SOLUTIONS=( "$CDIR"/$pattern )
else
    SOLUTIONS=( "$CDIR"/ex_*_solution.c )
fi

if [ ${#SOLUTIONS[@]} -eq 0 ] || [ ! -f "${SOLUTIONS[0]}" ]; then
    echo "ERROR: no matching solution files found"
    exit 1
fi

PASS=0
FAIL=0
SKIP=0

echo "========================================="
echo "  Group 10 — Advanced Exercise Verifier"
echo "========================================="
echo ""

for sol in "${SOLUTIONS[@]}"; do
    base="$(basename "$sol" .c)"
    exname="${base%_solution}"
    bin="$CDIR/.bin_${base}"

    # Derive exercise file (fill-in-blank) from solution name
    ex_file="$CDIR/${exname}.c"

    # Build header
    printf "  %-30s " "[${exname}]"

    # Compile
    if ! "$CC" $CFLAGS "$sol" -o "$bin" 2>/dev/null; then
        echo "COMPILE FAIL"
        FAIL=$((FAIL + 1))
        continue
    fi

    # Run
    set +e
    output="$("$bin" 2>&1)"
    rc=$?
    set -e

    if [ $rc -ne 0 ]; then
        echo "RUNTIME FAIL (exit=$rc)"
        FAIL=$((FAIL + 1))
        [ "$VERBOSE" = true ] && echo "$output" | sed 's/^/       | /'
        continue
    fi

    # Check that output is non-empty
    if [ -z "$output" ]; then
        echo "NO OUTPUT"
        FAIL=$((FAIL + 1))
        continue
    fi

    echo "PASS"
    PASS=$((PASS + 1))

    [ "$VERBOSE" = true ] && echo "$output" | sed 's/^/       | /'

    # Cleanup binary
    rm -f "$bin"
done

echo ""
echo "========================================="
echo "  Results: $PASS passed, $FAIL failed, $SKIP skipped"
echo "========================================="

# Also check that exercise files (fill-in-blanks) exist
echo ""
echo "  Checking exercise files exist..."
for sol in "${SOLUTIONS[@]}"; do
    base="$(basename "$sol" .c)"
    exname="${base%_solution}"
    ex_file="$CDIR/${exname}.c"
    if [ -f "$ex_file" ]; then
        printf "  %-30s FOUND\n" "[${exname}]"
    else
        printf "  %-30s MISSING\n" "[${exname}]"
    fi
done

exit $([ "$FAIL" -eq 0 ] && echo 0 || echo 1)
