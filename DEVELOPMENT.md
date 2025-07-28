# Development Guide

## Quick Start

### Prerequisites

- Docker and Docker Compose
- Git
- (Optional) CMake, Python 3.8+, Node.js for local development

### Using Docker (Recommended)

1. **Start development environment:**

   ```bash
   docker-compose up -d tradesim-dev
   docker-compose exec tradesim-dev bash
   ```

2. **Build the project:**

   ```bash
   ./build.sh
   ```

3. **Run tests:**

   ```bash
   # C++ tests
   cd build && make test

   # Python tests
   cd py && python -m pytest
   ```

### Local Development

1. **Install dependencies:**

   ```bash
   # Python
   cd py && pip install -r requirements.txt

   # Node.js (for GUI)
   cd gui && npm install
   ```

2. **Build C++ core:**

   ```bash
   ./build.sh
   ```

3. **Install Python package:**
   ```bash
   cd py && pip install -e .
   ```

## Project Structure

```
TradeSim-Pro/
├── cpp/                    # C++ core engine
│   ├── CMakeLists.txt     # Main build configuration
│   ├── src/               # Source files
│   ├── include/           # Header files
│   └── tests/             # C++ unit tests
├── py/                    # Python analytics
│   ├── setup.py          # Package configuration
│   ├── requirements.txt  # Python dependencies
│   └── tradesim/         # Python package
├── gui/                   # Desktop GUI
│   ├── package.json      # Node.js dependencies
│   └── src/              # React/TypeScript source
├── tests/                 # Integration tests
├── .devcontainer/         # VS Code dev container
├── Dockerfile            # Multi-stage Docker build
├── docker-compose.yml    # Local development setup
└── build.sh              # Build script
```

## Development Workflow

### 1. C++ Development

- Use CMake for building
- GoogleTest for unit testing
- Follow the implementation plan in `implementation.md`

### 2. Python Development

- Use `pip install -e .` for development install
- pytest for testing
- Black for code formatting
- mypy for type checking

### 3. GUI Development

- Electron + React + TypeScript
- Use `npm run dev` for development server
- Hot reload enabled

### 4. Testing

- C++: `cd build && make test`
- Python: `cd py && python -m pytest`
- Integration: `cd tests && python -m pytest`

## VS Code Development

1. **Install VS Code with Dev Containers extension**
2. **Open in container:**

   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Select "Dev Containers: Reopen in Container"

3. **Extensions automatically installed:**
   - C/C++ tools
   - Python tools
   - TypeScript/React tools
   - CMake tools

## Build Configuration

### CMake Options

- `CMAKE_BUILD_TYPE`: Debug/Release
- `BUILD_TESTS`: Enable/disable tests
- `BUILD_PYTHON_BINDINGS`: Enable pybind11

### Environment Variables

- `PYTHONPATH`: Python module search path
- `CMAKE_BUILD_PARALLEL_LEVEL`: Parallel build jobs

## Troubleshooting

### Common Issues

1. **CMake not found:**

   ```bash
   # Install CMake
   sudo apt-get install cmake  # Ubuntu/Debian
   brew install cmake          # macOS
   ```

2. **Python dependencies:**

   ```bash
   cd py && pip install -r requirements.txt
   ```

3. **Node.js dependencies:**

   ```bash
   cd gui && npm install
   ```

4. **Docker issues:**
   ```bash
   # Rebuild container
   docker-compose build --no-cache
   docker-compose up -d
   ```

## Next Steps

Follow the implementation plan in `implementation.md`:

1. ✅ Step 0.1: Project bootstrap
2. ✅ Step 0.2: Build & dev-container setup
3. 🔄 Step 1.1: Define engine interfaces
4. 🔄 Step 1.2: Implement CSV data source
5. 🔄 Step 1.3: Implement order book engine
