#!/usr/bin/env bash
# regenerate_crons.sh — show Fibonacci study schedule
# Idempotent: safe to run multiple times.

set -euo pipefail

SCHEDULE="$(cd "$(dirname "$0")" && pwd)/learning_schedule.md"

echo "=== Study Schedule ==="
grep '^| [0-9]' "$SCHEDULE" | while IFS='|' read -r _ day num unit activity _; do
    day=$(echo "$day" | xargs)
    unit=$(echo "$unit" | xargs)
    activity=$(echo "$activity" | xargs)
    printf "Day %3d | %s | %s\n" "$day" "$unit" "$activity"
done

echo ""
echo "Schedule has $(grep -c '^| [0-9]' "$SCHEDULE") sessions across 8 modules."
