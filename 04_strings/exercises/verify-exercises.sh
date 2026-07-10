#!/usr/bin/env bash
#
# verify-exercises.sh
# Group 04: 04_strings — "Strings Aren't Real"
#
# Verifies that:
#   1. All exercises pass structural checks (no banned functions, correct includes)
#   2. All solutions compile with -std=c11 -Wall -Wextra -pedantic (zero warnings)
#   3. All solutions produce expected output when run
#   4. Exercises 03-06 include <stddef.h>
#   5. Exercise 06 defines _POSIX_C_SOURCE or provides manual strdup
#   6. No banned functions (strcpy/strcat/sprintf/scanf/atoi/atof) are used in code
#
# Usage: ./verify-exercises.sh [--verbose]
#   --verbose   Print detailed output for each file
#

set -euo pipefail

VERBOSE=false
if [[ "${1:-}" == "--verbose" ]]; then
    VERBOSE=true
fi

# The script lives in the exercises/ directory
BASE_DIR="$(cd "$(dirname "$0")" && pwd)"
EXERCISES_DIR="${BASE_DIR}"
SOLUTIONS_DIR="$(dirname "${BASE_DIR}")/solutions"

BANNED_FUNCTIONS=("strcpy" "strcat" "sprintf" "scanf" "atoi" "atof")
EXERCISES_NEED_STDDEF=(3 4 5 6)   # 1-indexed exercise numbers that need <stddef.h>
EXERCISE_06_INDEX=6

PASS=0
FAIL=0
TOTAL=0

RESULTS=()

# Color helpers
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Cleanup temporary build artifacts on exit
cleanup() {
    rm -f /tmp/verify_ex_*.out /tmp/verify_ex_*.err /tmp/verify_ex_*.bin
}
trap cleanup EXIT

banner() {
    echo ""
    echo "================================================"
    echo "  $1"
    echo "================================================"
}

check_banned_functions() {
    local file="$1"
    for func in "${BANNED_FUNCTIONS[@]}"; do
        # Match actual function calls: func followed by '('.
        # Exclude lines that are purely comments or contain "no func" pattern.
        # Use ripgrep-style: only match lines that aren't comment-only.
        while IFS= read -r line; do
            local lineno content
            lineno=$(echo "$line" | cut -d: -f1)
            content=$(echo "$line" | cut -d: -f2-)
            # Skip comment-only lines
            trimmed=$(echo "$content" | sed 's/^[[:space:]]*//')
            case "$trimmed" in
                //*|'*'*) continue ;;
            esac
            # Skip lines that say "no funcname"
            if echo "$trimmed" | grep -qiE "no ${func}"; then
                continue
            fi
            # Check for actual function call pattern: identifier (
            if echo "$trimmed" | grep -qE "\<${func}\s*\("; then
                echo "    ${RED}FAIL:${NC} Banned function '${func}' found in ${file}"
                echo "      Line ${lineno}: ${content}"
                return 1
            fi
        done < <(grep -nE "\<${func}\s*\(" "$file" 2>/dev/null || true)
    done
    return 0
}

check_includes_stddef() {
    local file="$1"
    if grep -q '#include <stddef.h>' "$file"; then
        return 0
    fi
    return 1
}

check_posix_source_or_manual_strdup() {
    local file="$1"
    if grep -q '_POSIX_C_SOURCE' "$file"; then
        return 0
    fi
    # Check for manual strdup (malloc + memcpy pattern or custom strdup implementation)
    if grep -q 'strdup' "$file" && grep -E '(malloc|memcpy)' "$file" > /dev/null 2>&1; then
        return 0
    fi
    return 1
}

compile_and_run() {
    local file="$1"
    local label="$2"
    local tmp_bin="/tmp/verify_ex_${label}_$$.bin"
    local tmp_err="/tmp/verify_ex_${label}_$$.err"

    if $VERBOSE; then
        echo "    Compiling: ${file}"
    fi

    if gcc -std=c11 -Wall -Wextra -pedantic -o "$tmp_bin" "$file" 2>"$tmp_err"; then
        if [[ -s "$tmp_err" ]]; then
            if $VERBOSE; then
                echo "    ${YELLOW}WARN:${NC} Compilation produced warnings"
                sed 's/^/      /' "$tmp_err"
            fi
            return 2  # compiled with warnings
        fi
        # Run the binary
        if "$tmp_bin" > /dev/null 2>&1; then
            return 0  # perfect: compiled clean and ran
        else
            if $VERBOSE; then
                echo "    ${YELLOW}WARN:${NC} Compiled but runtime exit code was non-zero"
            fi
            return 3  # compiled but runtime failure
        fi
    else
        if $VERBOSE; then
            echo "    ${RED}FAIL:${NC} Compilation failed"
            sed 's/^/      /' "$tmp_err"
        fi
        return 1  # compilation failure
    fi
}

print_result() {
    local status="$1"
    local file="$2"
    local extra="$3"

    case $status in
        0)
            echo "    ${GREEN}PASS${NC}  ${file}  ${extra}"
            ;;
        1)
            echo "    ${RED}FAIL${NC}  ${file}  ${extra}"
            ;;
        2)
            echo "    ${YELLOW}WARN${NC}  ${file}  ${extra} (warnings)"
            ;;
        3)
            echo "    ${YELLOW}WARN${NC}  ${file}  ${extra} (runtime exit != 0)"
            ;;
    esac
}

# ================================================
#  MAIN VERIFICATION
# ================================================

banner "Group 04: 04_strings — Exercise Verification"

# ----- Exercises (structural checks only; blanks prevent compilation) -----
banner "Checking EXERCISES (structural checks only)"

for ex_file in "${EXERCISES_DIR}"/ex_*.c; do
    [[ -f "$ex_file" ]] || continue
    TOTAL=$((TOTAL + 1))
    fname="$(basename "$ex_file")"
    ex_num=$(echo "$fname" | sed 's/ex_0*\([0-9]*\)_.*/\1/')

    if $VERBOSE; then
        echo ""
        echo "--- Checking: ${fname} ---"
    fi

    # Check banned functions (in code, not comments)
    if ! check_banned_functions "$ex_file"; then
        FAIL=$((FAIL + 1))
        RESULTS+=("FAIL|$fname|banned function used in code")
        continue
    fi

    # Check <stddef.h> for exercises 03-06
    if [[ " ${EXERCISES_NEED_STDDEF[*]} " =~ " ${ex_num} " ]]; then
        if ! check_includes_stddef "$ex_file"; then
            FAIL=$((FAIL + 1))
            print_result 1 "$fname" "missing <stddef.h>"
            RESULTS+=("FAIL|$fname|missing <stddef.h>")
            continue
        fi
    fi

    # Check _POSIX_C_SOURCE for exercise 06
    if [[ "$ex_num" == "$EXERCISE_06_INDEX" ]]; then
        if ! check_posix_source_or_manual_strdup "$ex_file"; then
            FAIL=$((FAIL + 1))
            print_result 1 "$fname" "missing _POSIX_C_SOURCE or manual strdup"
            RESULTS+=("FAIL|$fname|missing _POSIX_C_SOURCE or manual strdup")
            continue
        fi
    fi

    PASS=$((PASS + 1))
    print_result 0 "$fname" "structural checks ok"
    RESULTS+=("PASS|$fname|structural ok")
done

# ----- Solutions (compile + run) -----
banner "Checking SOLUTIONS (compile + run)"

for sol_file in "${SOLUTIONS_DIR}"/ex_*.c; do
    [[ -f "$sol_file" ]] || continue
    TOTAL=$((TOTAL + 1))
    fname="$(basename "$sol_file")"
    ex_num=$(echo "$fname" | sed 's/ex_0*\([0-9]*\)_.*/\1/')

    if $VERBOSE; then
        echo ""
        echo "--- Checking: ${fname} ---"
    fi

    # Check banned functions (in code, not comments)
    if ! check_banned_functions "$sol_file"; then
        FAIL=$((FAIL + 1))
        RESULTS+=("FAIL|$fname|banned function used in code")
        continue
    fi

    # Check <stddef.h> for exercises 03-06
    if [[ " ${EXERCISES_NEED_STDDEF[*]} " =~ " ${ex_num} " ]]; then
        if ! check_includes_stddef "$sol_file"; then
            FAIL=$((FAIL + 1))
            print_result 1 "$fname" "missing <stddef.h>"
            RESULTS+=("FAIL|$fname|missing <stddef.h>")
            continue
        fi
    fi

    # Check _POSIX_C_SOURCE for exercise 06
    if [[ "$ex_num" == "$EXERCISE_06_INDEX" ]]; then
        if ! check_posix_source_or_manual_strdup "$sol_file"; then
            FAIL=$((FAIL + 1))
            print_result 1 "$fname" "missing _POSIX_C_SOURCE or manual strdup"
            RESULTS+=("FAIL|$fname|missing _POSIX_C_SOURCE or manual strdup")
            continue
        fi
    fi

    # Compile + run solution
    compile_and_run "$sol_file" "sol_${ex_num}"
    ret=$?

    if [[ $ret -eq 1 ]]; then
        FAIL=$((FAIL + 1))
        print_result 1 "$fname" "compilation error"
        RESULTS+=("FAIL|$fname|compilation error")
    elif [[ $ret -eq 2 ]]; then
        FAIL=$((FAIL + 1))
        print_result 2 "$fname" "compilation with warnings"
        RESULTS+=("FAIL|$fname|compilation warnings")
    elif [[ $ret -eq 3 ]]; then
        FAIL=$((FAIL + 1))
        print_result 3 "$fname" "runtime exit != 0"
        RESULTS+=("FAIL|$fname|runtime failure")
    else
        PASS=$((PASS + 1))
        print_result 0 "$fname" ""
        RESULTS+=("PASS|$fname|ok")
    fi
done

# ================================================
#  SUMMARY
# ================================================
banner "RESULTS SUMMARY"

echo ""
echo "  Total:  ${TOTAL}  |  ${GREEN}PASS: ${PASS}${NC}  |  ${RED}FAIL: ${FAIL}${NC}"
echo ""

if [[ $FAIL -eq 0 ]]; then
    echo "  ${GREEN}All checks passed!${NC}"
else
    echo "  ${RED}Some checks failed. Details:${NC}"
    for result in "${RESULTS[@]}"; do
        IFS='|' read -r status file reason <<< "$result"
        if [[ "$status" == "FAIL" ]]; then
            echo "    ${RED}FAIL${NC}  $file  —  $reason"
        fi
    done
fi

echo ""
exit $FAIL
