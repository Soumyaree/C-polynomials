#!/bin/bash
set -o pipefail
MAKE_CMD="make"
EXECUTABLES=(
    "./main.exe"
    "./bench_karatsuba.exe"
    "./bench_toom_cook.exe"
    "./bench_toom4.exe"
)
LOG_DIR="logs"
BUILD_LOG="$LOG_DIR/build.log"
mkdir -p "$LOG_DIR"
rm -f "$LOG_DIR"/*.log

echo "========================================"
echo " Polynomial Multiplication – Full Run"
echo "========================================"
echo

echo "[1/3] Building project using Makefile..."
echo "----------------------------------------"

if ! $MAKE_CMD 2>&1 | tee "$BUILD_LOG"; then
    echo
    echo "BUILD FAILED"
    echo "See $BUILD_LOG for details"
    exit 1
fi

echo "Build successful"
echo
echo "[2/3] Running benchmarks..."
echo "----------------------------------------"

RESULTS_SUMMARY=""

for exe in "${EXECUTABLES[@]}"; do
    if [[ ! -x "$exe" ]]; then
        echo "Missing executable: $exe"
        exit 1
    fi

    LOG_FILE="$LOG_DIR/$(basename "$exe").log"

    echo
    echo ">>> Running $exe"
    echo "----------------------------------------"

    if ! "$exe" 2>&1 | tee "$LOG_FILE"; then
        echo
        echo "Runtime error in $exe"
        echo "See $LOG_FILE for details"
        exit 1
    fi

    RESULTS_SUMMARY+=$'\n'
    RESULTS_SUMMARY+="===== $(basename "$exe") ====="$'\n'
    RESULTS_SUMMARY+="$(cat "$LOG_FILE")"$'\n'
done

echo
echo "[3/3] Final report"
echo "----------------------------------------"

echo
echo "ALL TESTS AND BENCHMARKS COMPLETED SUCCESSFULLY 🎉"
echo
echo "============= FULL RESULTS ============="
echo
echo "$RESULTS_SUMMARY"

echo
echo "Logs saved in: $LOG_DIR/"
echo "========================================"
