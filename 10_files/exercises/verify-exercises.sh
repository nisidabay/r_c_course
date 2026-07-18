#!/usr/bin/env bash
#
# verify-exercises.sh
# Group 09 — Files
#
# Compiles every exercise solution with -std=c11 -Wall -Wextra -pedantic.
# Runs each solution and checks output / exit code.
# Reports PASS/FAIL for each.
#
# Exit status: 0 if everything passes, 1 if any test fails.
#

set -u

GROUP="09_files"
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
    local bin; bin="$(mktemp /tmp/file_test_XXXXXX)"

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
echo "  Group 09 — Files — Exercise Verifier"
echo "============================================"
echo ""

# ============================================================
# Exercise 01 — fopen Modes
# ============================================================
echo "--- ex_01_fopen_modes ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_01_fopen_modes_solution.c" "ex_01_fopen_modes_solution")
if [ $? -eq 0 ]; then
    # Run from exercises dir so relative paths work
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    out=$("$bin" 2>&1; echo "EXIT:$?")
    popd > /dev/null 2>&1 || true
    if echo "$out" | grep -q "NULL as expected" && \
       echo "$out" | grep -q "Created test_data.txt" && \
       echo "$out" | grep -q "Cleaned up" && \
       echo "$out" | grep -q "EXIT:0"; then
        pass "ex_01_fopen_modes_solution"
    else
        fail "ex_01_fopen_modes_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 02 — Text I/O
# ============================================================
echo "--- ex_02_text_io ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_02_text_io_solution.c" "ex_02_text_io_solution")
if [ $? -eq 0 ]; then
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    out=$("$bin" 2>&1; echo "EXIT:$?")
    popd > /dev/null 2>&1 || true
    if echo "$out" | grep -q "Wrote 3 names" && \
       echo "$out" | grep -q "Read 3 names" && \
       echo "$out" | grep -q "Alice" && \
       echo "$out" | grep -q "Bob" && \
       echo "$out" | grep -q "Charlie" && \
       echo "$out" | grep -q "EXIT:0"; then
        pass "ex_02_text_io_solution"
    else
        fail "ex_02_text_io_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 03 — fclose Cleanup
# ============================================================
echo "--- ex_03_fclose_cleanup ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_03_fclose_cleanup_solution.c" "ex_03_fclose_cleanup_solution")
if [ $? -eq 0 ]; then
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    out=$("$bin" 2>&1; echo "EXIT:$?")
    popd > /dev/null 2>&1 || true
    if echo "$out" | grep -q "log.txt written and closed" && \
       echo "$out" | grep -q "log.txt opened for reading" && \
       echo "$out" | grep -q "Cleaned up" && \
       echo "$out" | grep -q "EXIT:0"; then
        pass "ex_03_fclose_cleanup_solution"
    else
        fail "ex_03_fclose_cleanup_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 04 — perror / errno
# ============================================================
echo "--- ex_04_perror ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_04_perror_solution.c" "ex_04_perror_solution")
if [ $? -eq 0 ]; then
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    out=$("$bin" 2>&1; echo "EXIT:$?")
    popd > /dev/null 2>&1 || true
    # perror on /root/secret.txt will produce an error message — that's expected
    if echo "$out" | grep -q "Reached EOF with no errors" && \
       echo "$out" | grep -q "EXIT:0"; then
        pass "ex_04_perror_solution"
    else
        fail "ex_04_perror_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Exercise 05 — File Operations (remove, rename)
# ============================================================
echo "--- ex_05_file_ops ---"
total
bin=$(check_compile "${EXERCISES_DIR}/ex_05_file_ops_solution.c" "ex_05_file_ops_solution")
if [ $? -eq 0 ]; then
    pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
    out=$("$bin" 2>&1; echo "EXIT:$?")
    popd > /dev/null 2>&1 || true
    if echo "$out" | grep -q "Created original.txt" && \
       echo "$out" | grep -q "original.txt exists" && \
       echo "$out" | grep -q "Renamed original.txt -> renamed.txt" && \
       echo "$out" | grep -q "original.txt no longer exists" && \
       echo "$out" | grep -q "Deleted renamed.txt" && \
       echo "$out" | grep -q "All file operations completed" && \
       echo "$out" | grep -q "EXIT:0"; then
        pass "ex_05_file_ops_solution"
    else
        fail "ex_05_file_ops_solution (output mismatch)"
        echo "    Got: $out"
    fi
    rm -f "$bin"
fi
echo ""

# ============================================================
# Challenge 06 — Line Count + Longest Line
# ============================================================
echo "--- ex_06_challenge ---"
total
if [ ! -f "$EXERCISES_DIR/sample.txt" ]; then
    echo "  [SKIP] sample.txt not found — challenge cannot run"
else
    bin=$(check_compile "${EXERCISES_DIR}/ex_06_challenge_solution.c" "ex_06_challenge_solution")
    if [ $? -eq 0 ]; then
        pushd "$EXERCISES_DIR" > /dev/null 2>&1 || true
        out=$("$bin" 2>&1; echo "EXIT:$?")
        popd > /dev/null 2>&1 || true
        if echo "$out" | grep -q "Total lines: 5" && \
           echo "$out" | grep -q "Longest line: Charlie" && \
           echo "$out" | grep -q "EXIT:0"; then
            pass "ex_06_challenge_solution"
        else
            fail "ex_06_challenge_solution (output mismatch)"
            echo "    Got: $out"
        fi
        rm -f "$bin"
    fi
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
