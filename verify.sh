#!/usr/bin/env bash
# verify.sh — Top-level author verification for Modern C course
# Compiles all concept files, exercise solutions, and projects.
# Runs verify-exercises.sh scripts, checks BUILD.md existence.
# Checks no forward references (group N doesn't depend on group N+1 APIs).
set -u
# Manual error handling instead of set -e to safely run sub-scripts

COURSE_DIR="$(cd "$(dirname "$0")" && pwd)"
CC="gcc"
CFLAGS="-std=c11 -Wall -Wextra -pedantic"
FAIL=0
PASS=0
TOTAL=0

# Colour helpers
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

pass() {
    echo -e "  ${GREEN}PASS${NC} $1"
    PASS=$((PASS + 1))
}
fail() {
    echo -e "  ${RED}FAIL${NC} $1"
    FAIL=$((FAIL + 1))
}
total() { TOTAL=$((TOTAL + 1)); }
test_group() {
    echo ""
    echo "--- $1 ---"
}

compile_test() {
    local src="$1"
    local label="$2"
    total
    if "$CC" $CFLAGS -o /tmp/verify_test "$src" 2>/dev/null; then
        pass "$label"
    else
        echo "  ${RED}COMPILE ERROR${NC} $label"
        "$CC" $CFLAGS -o /tmp/verify_test "$src" 2>&1 | sed 's/^/    /' || true
        fail "$label"
    fi
    rm -f /tmp/verify_test
}

intro() {
    echo ""
    echo "============================================"
    echo "  Modern C Course — Author Verification"
    echo "============================================"
    echo "  Course root: $COURSE_DIR"
    echo "  Compiler:    $CC $CFLAGS"
    echo "============================================"
    echo ""
}

summary() {
    echo ""
    echo "============================================"
    echo -e "  Results: ${GREEN}$PASS passed${NC}, ${RED}$FAIL failed${NC}, $TOTAL total"
    echo "============================================"
    if [ "$FAIL" -eq 0 ]; then
        echo "  All checks passed! 🎉"
    fi
}

intro

# =============================================================
# 1. Compile ALL concept files
# =============================================================
echo "============================================"
echo "  Compiling Concept Files"
echo "============================================"

for concept_file in $(find "$COURSE_DIR" -path '*/concept/*.c' | sort); do
    group_name=$(echo "$concept_file" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)
    base_name=$(basename "$concept_file" .c)
    compile_test "$concept_file" "[concept] $group_name/$base_name"
done

# =============================================================
# 2. Compile ALL exercise solution files
# =============================================================
echo ""
echo "============================================"
echo "  Compiling Exercise Solutions"
echo "============================================"

# Find solution files — they follow various naming patterns.
# 04_strings solutions are now flat in exercises/ (ex_NN_*_solution.c).
# 03_functions, 06_pointers_101, 09_files use exercises/solutions/.
# Catch any future */solutions/*.c too.
for solution_file in $(find "$COURSE_DIR" -path '*/exercises/*solution*' -name '*.c' -o \
                        -path '*/exercises/*solved*' -name '*.c' -o \
                        -path '*/exercises/solutions/*.c' -o \
                        -path '*/solutions/*.c' | sort | uniq); do
    group_name=$(echo "$solution_file" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)
    base_name=$(basename "$solution_file" .c)
    compile_test "$solution_file" "[solution] $group_name/$base_name"
done

# =============================================================
# 2b. Cross-check: every exercise stub has a matching solution
# =============================================================
echo ""
echo "============================================"
echo "  Checking Exercise Stub ↔ Solution Match"
echo "============================================"
echo ""

for stub_file in $(find "$COURSE_DIR" -path '*/exercises/*' -name 'ex_*.c' ! -name '*solution*' ! -name '*solved*' | sort); do
    total
    stub_base=$(basename "$stub_file" .c)
    stub_dir=$(dirname "$stub_file")
    group_name=$(echo "$stub_file" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)

    # Look for matching solution: same dir with _solution or _solved suffix, or in solutions/ subdir
    solution_found=false
    for suffix in "_solution" "_solved"; do
        if [ -f "${stub_dir}/${stub_base}${suffix}.c" ] || \
           [ -f "${stub_dir}/solutions/${stub_base}${suffix}.c" ] || \
           [ -f "$(dirname "$stub_dir")/solutions/${stub_base}${suffix}.c" ]; then
            solution_found=true
            break
        fi
    done
    # Also check solutions/ dir with same filename
    for alt_dir in "$(dirname "$stub_dir")/solutions" "${stub_dir}/solutions"; do
        if [ -f "${alt_dir}/${stub_base}.c" ]; then
            solution_found=true
            break
        fi
    done
    # Also check solution_ prefix (e.g. stub=ex_01, solution=solution_ex_01)
    if [ "$solution_found" = false ] && [ -f "${stub_dir}/solution_${stub_base}.c" ]; then
        solution_found=true
    fi

    if [ "$solution_found" = true ]; then
        pass "stub↔solution $group_name/$stub_base"
    else
        fail "stub↔solution $group_name/$stub_base (MISSING SOLUTION)"
    fi
done

# =============================================================
# 3. Compile ALL project source files
# =============================================================
echo ""
echo "============================================"
echo "  Compiling Project Files"
echo "============================================"

for project_file in $(find "$COURSE_DIR" -path '*/project/*.c' | sort); do
    group_name=$(echo "$project_file" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)
    base_name=$(basename "$project_file" .c)
    compile_test "$project_file" "[project] $group_name/$base_name"
done

# =============================================================
# 4. Run ALL verify-exercises.sh scripts
# =============================================================
echo ""
echo "============================================"
echo "  Running verify-exercises.sh Scripts"
echo "============================================"

# Check dynamic_mem verify first since it may have issues
for verify_script in $(find "$COURSE_DIR" -name 'verify-exercises.sh' | sort); do
    group_name=$(echo "$verify_script" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)
    total
    echo ""
    echo "--- Running $group_name verify-exercises.sh ---"
    if bash "$verify_script"; then
        pass "$group_name/verify-exercises.sh"
    else
        fail "$group_name/verify-exercises.sh"
    fi
done

# =============================================================
# 5. Check all projects have BUILD.md
# =============================================================
echo ""
echo "============================================"
echo "  Checking BUILD.md Existence"
echo "============================================"

for project_dir in $(find "$COURSE_DIR" -path '*/project' -type d | sort); do
    group_name=$(echo "$project_dir" | sed "s|$COURSE_DIR/||" | cut -d'/' -f1)
    total
    if [ -f "$project_dir/BUILD.md" ]; then
        pass "$group_name/project/BUILD.md"
    else
        fail "$group_name/project/BUILD.md (missing)"
    fi
done

# =============================================================
# 6. Check no forward references
# =============================================================
echo ""
echo "============================================"
echo "  Checking No Forward References"
echo "============================================"
echo "  (group N files don't depend on group N+1 APIs)"
echo ""

# Define groups in order
GROUPS=(
    "01_hello"
    "02_control"
    "03_functions"
    "04_strings"
    "05_arrays"
    "06_pointers_101"
    "07_dynamic_mem"
    "08_structs"
    "09_files"
    "10_advanced"
)

# Get all source files in order
all_source_files=""
for g in "${GROUPS[@]}"; do
    all_source_files="$all_source_files $(find "$COURSE_DIR/$g" -name '*.c' 2>/dev/null | sort)"
done

# Build a map from function name to group number of first definition
# We check #include directives — does a file from group N include
# a header or reference a path from group N+1 or later?
for g_idx in "${!GROUPS[@]}"; do
    group="${GROUPS[$g_idx]}"
    src_files=$(find "$COURSE_DIR/$group" -name '*.c' 2>/dev/null | sort)
    
    for src_file in $src_files; do
        base_name=$(basename "$src_file" .c)
        
        # Check for #include of later groups
        for later_idx in $(seq $((g_idx + 1)) $(( ${#GROUPS[@]} - 1 ))); do
            later_group="${GROUPS[$later_idx]}"
            later_dir=$(echo "$later_group" | sed 's/^[0-9]*_//')
            
            if grep -q "#include.*${later_group}" "$src_file" 2>/dev/null || \
               grep -q "#include.*${later_dir}" "$src_file" 2>/dev/null; then
                total
                fail "[forward-ref] $group/$base_name includes $later_group"
            fi
        done
    done
done

# If no forward refs detected, report success
if [ "$FAIL" -eq 0 ]; then
    # Add a pass for forward reference check
    total
    pass "No forward references detected"
fi

summary

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi
exit 0
