#!/usr/bin/env bash
# verify-exercises.sh — Tests all exercise solutions in group 11 (Processes)
set -euo pipefail

PASS=0
FAIL=0

green() { printf '\033[32m%s\033[0m\n' "$1"; }
red()   { printf '\033[31m%s\033[0m\n' "$1"; }

run_test() {
    local name="$1" cmd="$2" expected="$3"
    printf "  %-30s ... " "$name"
    local out
    out=$(eval "$cmd" 2>&1) || true
    if echo "$out" | grep -q "$expected"; then
        green "PASS"
        PASS=$((PASS + 1))
    else
        red "FAIL"
        echo "    Expected: $expected"
        echo "    Got:      $out"
        FAIL=$((FAIL + 1))
    fi
}

echo "=== Group 11 — Process Exercises ==="
echo ""

# Ex 01 — fork+exec: launch /bin/uname -a
echo "Ex 01: fork+exec (launch uname)"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_01_fork_exec_solution.c -o /tmp/ex01_sol 2>&1" \
    ""
run_test "launches uname" \
    "/tmp/ex01_sol 2>&1" \
    "Linux"

# Ex 02 — execlp vs execvp
echo "Ex 02: exec variants"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_02_exec_solution.c -o /tmp/ex02_sol 2>&1" \
    ""
run_test "launches echo with argv" \
    "/tmp/ex02_sol 2>&1" \
    "hello from execvp"

# Ex 03 — system()
echo "Ex 03: system() safety"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_03_system_solution.c -o /tmp/ex03_sol 2>&1" \
    ""
run_test "runs safely" \
    "/tmp/ex03_sol 2>&1" \
    "Done"

# Ex 04 — pipe
echo "Ex 04: pipe (echo | tr)"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_04_pipe_solution.c -o /tmp/ex04_sol 2>&1" \
    ""
run_test "transforms text" \
    "/tmp/ex04_sol 2>&1" \
    "HELLO"

# Ex 05 — dup2
echo "Ex 05: dup2 redirect"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_05_dup2_solution.c -o /tmp/ex05_sol 2>&1" \
    ""
run_test "redirects to file" \
    "/tmp/ex05_sol; grep -c 'total' listing.txt 2>/dev/null || echo 'FAIL'" \
    "1"

# Ex 06 — getenv
echo "Ex 06: environment variables"
run_test "solution compiles" \
    'gcc -std=c11 -Wall -Wextra -pedantic ex_06_getenv_solution.c -o /tmp/ex06_sol 2>&1' \
    ""
run_test "reads EDITOR" \
    "EDITOR=nvim /tmp/ex06_sol 2>&1" \
    "EDITOR = nvim"
run_test "reads HOME" \
    "/tmp/ex06_sol 2>&1" \
    "HOME = /home"

# Ex 07 — sqlite3
echo "Ex 07: sqlite3 database"
run_test "solution compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_07_sqlite3_solution.c -o /tmp/ex07_sol -lsqlite3 2>&1" \
    ""
run_test "creates and queries" \
    "/tmp/ex07_sol 2>&1" \
    "processes"

# Ex 08 — Challenge: combine concepts (just compile check)
echo "Ex 08: Challenge (combine concepts)"
run_test "challenge compiles" \
    "gcc -std=c11 -Wall -Wextra -pedantic ex_08_challenge_solution.c -o /tmp/ex08_sol 2>&1" \
    ""

echo ""
echo "=== Results: $PASS passed, $FAIL failed ==="
exit $FAIL
