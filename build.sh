#!/bin/bash

# TradeSim Pro Build Script
set -e

echo "🔨 Building TradeSim Pro..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "📋 Configuring with CMake..."
cmake ../cpp

# Build
echo "🏗️ Building C++ core..."
make -j$(nproc)

echo "✅ Build completed successfully!"
echo "📁 Build artifacts are in: $(pwd)"

# Optional: Run tests if they exist
if [ -f "bin/tradesim_tests" ]; then
    echo "🧪 Running tests..."
    ./bin/tradesim_tests
fi 