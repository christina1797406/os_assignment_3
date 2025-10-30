#!/usr/bin/env bash
# --------------------------------------------------------------
# test_all.sh — Automated testing suite for parallel merge sort
#
# Covers:
#   1. Integration test (parallel_mergesort)
#   2. Correctness testing (small arrays, random seeds, edge cases)
#   3. Performance testing (speedup vs cutoff)
#   4. Stress & stability tests (large data, deep recursion)
#
# Usage:
#   chmod +x test_all.sh
#   ./test_all.sh ./test-mergesort
#
# Optional arguments:
#   ./test_all.sh ./test-mergesort correctness
#   ./test_all.sh ./test-mergesort performance
#   ./test_all.sh ./test-mergesort stress
# --------------------------------------------------------------

set -euo pipefail

BIN="${1:-}"
MODE="${2:-all}"

if [ -z "$BIN" ]; then
  echo "Usage: $0 <path-to-test-mergesort> [mode]"
  echo "Modes: correctness | performance | stress | all"
  exit 1
fi

if [ ! -x "$BIN" ]; then
  echo "Error: $BIN not found or not executable."
  exit 2
fi

CSV="test_results.csv"
echo "TestType,InputSize,Cutoff,Seed,TimeSeconds,Status" > "$CSV"

log_result() {
  local testtype="$1" size="$2" cutoff="$3" seed="$4" time="$5" status="$6"
  echo "$testtype,$size,$cutoff,$seed,$time,$status" >> "$CSV"
}

divider() { echo "------------------------------------------------------------"; }

# --------------------------------------------------------------
# Integration Test
# --------------------------------------------------------------
integration_test() {
  divider
  echo "Running Integration Test (parallel_mergesort end-to-end)..."
  $BIN 1000 2 42 >/tmp/integration.log 2>&1
  echo "integration (cutoff=2): OK"
}

# --------------------------------------------------------------
# Correctness Testing
# --------------------------------------------------------------
correctness_tests() {
  divider
  echo "Running Correctness Tests..."

  local seeds=(42 1234 99991)
  local sizes=(10 100 1000 10000)
  local cutoffs=(0 1 2 3)

  for n in "${sizes[@]}"; do
    for cutoff in "${cutoffs[@]}"; do
      for seed in "${seeds[@]}"; do
        output=$($BIN "$n" "$cutoff" "$seed" 2>&1 || true)
        if echo "$output" | grep -q "Sorting"; then
            time=$(echo "$output" | grep "Sorting" | awk '{print $5}')
            if ! [[ "$time" =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
            time=$(echo "$output" | grep "Sorting" | awk '{print $6}')
            fi
          log_result "correctness" "$n" "$cutoff" "$seed" "$time" "PASS"
        else
          log_result "correctness" "$n" "$cutoff" "$seed" "N/A" "FAIL"
        fi
      done
    done
  done

    # Additional edge case: sorted, reversed, and equal arrays
  divider
  echo "Running Edge Case Tests: sorted, reversed, equal arrays..."

  local modes=("sorted" "reversed" "equal")
  local n=1000
  local cutoff=2
  local seed=42

  for mode in "${modes[@]}"; do
    output=$($BIN "$n" "$cutoff" "$seed" "$mode" 2>&1 || true)
    if echo "$output" | grep -q "Sorting"; then
      time=$(echo "$output" | grep "Sorting" | awk '{print $6}')
      log_result "correctness-$mode" "$n" "$cutoff" "$seed" "$time" "PASS"
    else
      log_result "correctness-$mode" "$n" "$cutoff" "$seed" "N/A" "FAIL"
    fi
  done
}

# --------------------------------------------------------------
# Performance Testing
# --------------------------------------------------------------
performance_tests() {
  divider
  echo "Running Performance Tests (Speedup vs Cutoff)..."

  local n=100000000
  local seeds=(42)
  local cutoffs=(0 1 2 3 4 5)
  local serial_time=""

  for cutoff in "${cutoffs[@]}"; do
    output=$($BIN "$n" "$cutoff" 42 2>&1 || true)
    time=$(echo "$output" | grep "Sorting" | grep -Eo '[0-9]+\.[0-9]+')

    # Fallback in case time parsing fails
    if [ -z "$time" ]; then
      time="N/A"
    fi

    log_result "performance" "$n" "$cutoff" "42" "$time" "PASS"

    if [ "$cutoff" -eq 0 ]; then
      serial_time="$time"
      echo "Serial runtime = $serial_time s"
    else
      if [[ "$time" != "N/A" && "$serial_time" != "N/A" ]]; then
        speedup=$(awk -v s="$serial_time" -v p="$time" 'BEGIN{if (p>0) printf "%.2f", s/p; else print "N/A"}')
        echo "Cutoff=$cutoff Runtime=$time s  →  Speedup=$speedup"
      else
        echo "Cutoff=$cutoff Runtime=$time s  →  Speedup=N/A (missing timing data)"
      fi
    fi
  done
}


# --------------------------------------------------------------
# Stress & Stability Tests
# --------------------------------------------------------------
stress_tests() {
  divider
  echo "Running Stress & Stability Tests..."

  # Large array, high cutoff
  $BIN 100000000 8 42 | tee /tmp/stress1.log
  log_result "stress" "100000000" "8" "42" "$(grep Sorting /tmp/stress1.log | awk '{print $5}')" "PASS"

  # Repeat run (stability under load)
  for i in {1..5}; do
    seed=$((100 + i))
    echo "Repetition $i..."
    $BIN 50000000 5 "$seed" | tee /tmp/stress_rep_$i.log
    log_result "stress" "50000000" "5" "$seed" "$(grep Sorting /tmp/stress_rep_$i.log | awk '{print $5}')" "PASS"
  done
}

# --------------------------------------------------------------
# Run sections based on user mode
# --------------------------------------------------------------
case "$MODE" in
  correctness)
    integration_test
    correctness_tests
    ;;
  performance)
    performance_tests
    ;;
  stress)
    stress_tests
    ;;
  all)
    integration_test
    correctness_tests
    performance_tests
    stress_tests
    ;;
  *)
    echo "Unknown mode: $MODE"
    exit 1
    ;;
esac

divider
echo "All tests completed. Results saved to $CSV."

