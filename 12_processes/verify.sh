#!/usr/bin/env bash
# verify.sh — Compile-check all concept files, exercises, solutions, and project
set -euo pipefail

FAIL=0

green() { printf '\033[32m%s\033[0m\n' "$1"; }
red()   { printf '\033[31m%s\033[0m\n' "$1"; }
check() {
    local label="$1" cmd="$2"
    printf "  %-40s ... " "$label"
    if eval "$cmd" 2>/dev/null; then
        green "OK"
    else
        red "FAIL"
        FAIL=$((FAIL + 1))
    fi
}

echo "=== 11_processes — Full Verify ==="
echo ""

cd "$(dirname "$0")"

echo "--- Concept files ---"
for f in concept/*.c; do
    base=$(basename "$f")
    extra=""
    [ "$base" = "07_sqlite3.c" ] && extra="-lsqlite3"
    check "$base" "gcc -std=c11 -Wall -Wextra -pedantic '$f' -o /tmp/v_${base%.c} $extra"
done

echo ""
echo "--- Exercise stubs ---"
for f in exercises/ex_*.c; do
    # Skip solution files
    case "$f" in *_solution.c) continue;; esac
    base=$(basename "$f")
    extra=""
    [ "$base" = "ex_07_sqlite3.c" ] && extra="-lsqlite3"
    check "$base" "gcc -std=c11 -Wall -Wextra -pedantic '$f' -o /tmp/v_${base%.c} $extra"
done

echo ""
echo "--- Exercise solutions ---"
for f in exercises/ex_*_solution.c; do
    base=$(basename "$f")
    extra=""
    [ "$base" = "ex_07_sqlite3_solution.c" ] && extra="-lsqlite3"
    check "$base" "gcc -std=c11 -Wall -Wextra -pedantic '$f' -o /tmp/v_${base%.c} $extra"
done

echo ""
echo "--- Project ---"
check "journal.c" "gcc -std=c11 -Wall -Wextra -pedantic project/journal.c -o /tmp/v_journal -lsqlite3"

echo ""
echo "=== Result: $FAIL failures ==="
exit $FAIL
