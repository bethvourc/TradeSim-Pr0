# Engine Interfaces

This directory contains the core engine interfaces that define the architecture for the TradeSim Pro trading simulation platform.

## Overview

The engine interfaces establish a clean separation of concerns between different components of the trading system:

- **Market Data Sources**: Abstract interface for different types of market data (CSV replay, live feeds, synthetic data)
- **Order Book**: Core matching engine for order management and execution
- **Strategies**: Trading strategy implementations that react to market events

## Key Design Principles

### 1. Loose Coupling

All components communicate through well-defined interfaces, allowing for easy testing and modular development.

### 2. Event-Driven Architecture

The system uses an event-driven model where market events (trades, quotes, orders) flow through the system and trigger appropriate responses.

### 3. Polymorphic Design

Market events use inheritance to provide a unified interface while maintaining type-specific functionality.

### 4. Callback-Based Communication

Components communicate through callback functions, enabling asynchronous processing and real-time updates.

## Core Classes

### MarketEvent Hierarchy

- `MarketEvent`: Base class for all market events
- `Trade`: Represents executed trades
- `Quote`: Represents bid/ask quotes

### Order Management

- `Order`: Represents limit orders in the system
- `IOrderBook`: Interface for order book operations

### Data Sources

- `IMarketDataSource`: Abstract interface for market data providers

### Strategies

- `IStrategy`: Abstract interface for trading strategies

## Type System

The interfaces use strong type aliases for common trading concepts:

- `Timestamp`: Time points for event ordering
- `OrderId`: Unique order identifiers
- `Symbol`: Trading instrument symbols
- `Price`: Price values (double)
- `Quantity`: Order quantities (uint64_t)
- `Side`: Buy/Sell enumeration

## Testing

Comprehensive unit tests verify:

- Object creation and property access
- Polymorphic behavior
- Event callback mechanisms
- Type system correctness

## Next Steps

These interfaces will be implemented by concrete classes in subsequent steps:

1. CSV data source implementation
2. Order book matching engine
3. Strategy implementations
4. Python bindings
