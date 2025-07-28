# TradeSim Pro

> A cross-language trading simulation platform for historical market data replay, live feed injection, multi-strategy execution, and real-time desktop GUI visualization.

## Project Vision

TradeSim Pro is a comprehensive trading simulation platform designed for quantitative researchers, algorithmic traders, and financial educators. It combines the performance of C++ with the analytical power of Python to provide a robust environment for strategy development, backtesting, and real-time market simulation.

## Architecture

- **C++ Core Engine**: High-performance market data processing, order book management, and strategy execution
- **Python Analytics**: Data analysis, backtesting framework, and strategy development tools
- **Desktop GUI**: Real-time visualization using Electron + React for live market data and portfolio tracking
- **Cross-Platform**: Runs on Windows, macOS, and Linux

## Project Structure

```
TradeSim-Pro/
├── cpp/           # C++ core engine and strategies
├── py/            # Python analytics and backtesting
├── gui/           # Desktop GUI application
├── tests/         # Test suites and sample data
└── docs/          # Documentation and examples
```

## Key Features

- **Historical Data Replay**: Fast CSV-based market data simulation
- **Live Feed Integration**: Real-time market data injection capabilities
- **Multi-Strategy Support**: Momentum, market-making, and arbitrage strategies
- **Real-Time GUI**: Live market tape, charts, and portfolio tracking
- **Python Integration**: Seamless C++/Python interop via pybind11
- **Docker Support**: Containerized development and deployment

## Technology Stack

- **Backend**: C++17, CMake, GoogleTest
- **Analytics**: Python 3.8+, pandas, numpy, pybind11
- **Frontend**: Electron, React, TypeScript, Recharts
- **Infrastructure**: Docker, GitHub Actions

## Development Status

This project is currently under active development. See [implementation.md](implementation.md) for detailed development roadmap and step-by-step implementation plan.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Follow the implementation plan in `implementation.md`
4. Submit a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Quick Start

_Coming soon as development progresses_

---

**Note**: This is a work in progress.
