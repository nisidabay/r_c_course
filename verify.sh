#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
errors=0

echo "=== Verifying all .c files compile ==="
while IFS= read -r f; do
    # Skip unity-build helper files (compiled via main.c)
    case "$f" in */project/todo.c|*/project/storage.c) continue ;; esac
    echo -n "  $f ... "
    if gcc -std=c11 -Wall -Wextra -pedantic -Werror -o /tmp/c_test "$f" 2>/dev/null; then
        echo "OK"
    else
        echo "FAIL"
        errors=$((errors + 1))
    fi
done < <(find "$ROOT" -name "*.c" | sort)

echo ""
echo "=== Building all projects ==="
while IFS= read -r d; do
    echo -n "  $d ... "
    if make -C "$d" 2>/dev/null 1>&2; then
        echo "OK"
    else
        echo "FAIL"
        errors=$((errors + 1))
    fi
done < <(find "$ROOT" -maxdepth 3 -name "Makefile" -exec dirname {} \; | sort)

echo ""
echo "=== Running project smoke tests ==="
echo -n "  01_hello_world/sysinfo ... "
"$ROOT/01_hello_world/project/sysinfo" > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  02_control_flow/divider ... "
"$ROOT/02_control_flow/project/divider" 10 + 3 > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  03_arrays_strings/grep-lite ... "
"$ROOT/03_arrays_strings/project/grep-lite" test <<< "test line" > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  04_numbers/calc ... "
"$ROOT/04_numbers/project/calc" 42 + 8 > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  05_dynamic_memory/uniq ... "
echo -e "a\na\nb" | "$ROOT/05_dynamic_memory/project/uniq" > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  06_files_io/wc-lite ... "
"$ROOT/06_files_io/project/wc-lite" "$ROOT/06_files_io/concept/string_slice.c" > /dev/null && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  07_processes/runit ... "
"$ROOT/07_processes/project/runit" echo hi > /dev/null 2>&1 && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo -n "  08_organization/todo ... "
"$ROOT/08_organization/project/todo" list > /dev/null 2>&1 && echo "OK" || { echo "FAIL"; errors=$((errors + 1)); }

echo ""
if [ "$errors" -eq 0 ]; then
    echo "✓ All checks passed"
else
    echo "✗ $errors failure(s)"
fi
exit "$errors"
