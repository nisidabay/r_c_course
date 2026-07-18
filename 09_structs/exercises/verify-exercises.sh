#!/usr/bin/env bash
set -euo pipefail

# verify-exercises.sh — Compiles and runs ALL solutions for Group 08 (structs).
# Learner can run this to verify their own work.

EXERCISES_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
PASS=0
FAIL=0

echo "=== Group 08: 08_structs — Verifying Exercises ==="
echo ""

run_solution() {
    local src="$1"
    local expected="$2"
    local input="${3:-}"
    local name
    name="$(basename "$src" .c)"

    echo -n "[$name] Compiling... "
    if ! "$CC" $CFLAGS -o /tmp/test_ex "$src" -lm 2>/dev/null; then
        echo "FAIL (compile error)"
        "$CC" $CFLAGS -o /tmp/test_ex "$src" -lm 2>&1 || true
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

# ex_01_struct_def_solution
run_solution \
    "$EXERCISES_DIR/ex_01_struct_def_solution.c" \
    "Book 1: The C Programming Language by Kernighan & Ritchie (1978)
Book 2: C: A Modern Approach by K. N. King (2008)"

# ex_02_typedef_solution
run_solution \
    "$EXERCISES_DIR/ex_02_typedef_solution.c" \
    "\"The Matrix\" (1999) — 8.7/10
\"Inception\" (2010) — 8.8/10"

# ex_03_member_access_solution
run_solution \
    "$EXERCISES_DIR/ex_03_member_access_solution.c" \
    "Employee: Jane Smith (ID: 1001)
Address:  456 Pine Rd
City:     Seattle
ZIP:      98101"

# ex_04_arrow_operator_solution
run_solution \
    "$EXERCISES_DIR/ex_04_arrow_operator_solution.c" \
    "Arrow:     Model 3 (2024) — \$44990.00
Deref+dot: Model 3 (2024) — \$44990.00
Updated year (arrow): 2025
Updated year ((*ptr)): 2026
Updated model: Model Y"

# ex_05_structs_functions_solution
run_solution \
    "$EXERCISES_DIR/ex_05_structs_functions_solution.c" \
    "p1 = (3.0, 4.0)
p2 = (1.0, 2.0)
sum = (4.0, 6.0)

Scaling p1 by 2.0...
p1 after scale = (6.0, 8.0)"

# ex_06_struct_arrays_solution
run_solution \
    "$EXERCISES_DIR/ex_06_struct_arrays_solution.c" \
    "Product Catalogue:
  1. Laptop     \$ 999.99  (qty: 10)
  2. Mouse      \$  29.99  (qty: 50)
  3. Keyboard   \$  89.99  (qty: 30)
  4. Monitor    \$ 349.99  (qty: 15)

After updates:
  1. Laptop     \$ 899.99  (qty: 10)
  2. Mouse      \$  29.99  (qty: 50)
  3. Keyboard   \$  89.99  (qty: 45)
  4. Monitor    \$ 349.99  (qty: 15)"

# ex_07_challenge_solution
run_solution \
    "$EXERCISES_DIR/ex_07_challenge_solution.c" \
    "How many students? 
Student 1:
Name: ID: Scores (3): 
Student 2:
Name: ID: Scores (3): 
--- Grade Report ---
#   Name         ID     Score1  Score2  Score3  Average
1   Alice        101    85      90      92      89.0
2   Bob          102    78      82      88      82.7" \
    "2
Alice
101
85 90 92
Bob
102
78 82 88"

echo "================================"
echo "Results: $PASS passed, $FAIL failed"
if [ "$FAIL" -eq 0 ]; then
    echo "All exercises verified successfully!"
else
    echo "Some exercises failed — review the output above."
    exit 1
fi
