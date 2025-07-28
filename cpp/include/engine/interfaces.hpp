#pragma once

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <functional>

namespace tradesim
{

    // Forward declarations
    class Order;
    class Trade;
    class Quote;
    class MarketEvent;

    // Type aliases for common types
    using Timestamp = std::chrono::system_clock::time_point;
    using OrderId = uint64_t;
    using Symbol = std::string;
    using Price = double;
    using Quantity = uint64_t;
    using Side = enum { BUY,
                        SELL };

    /**
     * @brief Market event types for the simulation engine
     */
    enum class EventType
    {
        TRADE,
        QUOTE,
        ORDER_ADDED,
        ORDER_CANCELLED,
        ORDER_FILLED,
        STRATEGY_SIGNAL
    };

    /**
     * @brief Base class for all market events
     */
    class MarketEvent
    {
    public:
        virtual ~MarketEvent() = default;
        virtual EventType getType() const = 0;
        virtual Timestamp getTimestamp() const = 0;
        virtual Symbol getSymbol() const = 0;
    };

    /**
     * @brief Represents a trade execution
     */
    class Trade : public MarketEvent
    {
    public:
        Trade(Symbol symbol, Price price, Quantity quantity, Side side, Timestamp timestamp)
            : symbol_(std::move(symbol)), price_(price), quantity_(quantity),
              side_(side), timestamp_(timestamp) {}

        EventType getType() const override { return EventType::TRADE; }
        Timestamp getTimestamp() const override { return timestamp_; }
        Symbol getSymbol() const override { return symbol_; }

        Price getPrice() const { return price_; }
        Quantity getQuantity() const { return quantity_; }
        Side getSide() const { return side_; }

    private:
        Symbol symbol_;
        Price price_;
        Quantity quantity_;
        Side side_;
        Timestamp timestamp_;
    };

    /**
     * @brief Represents a market quote (bid/ask)
     */
    class Quote : public MarketEvent
    {
    public:
        Quote(Symbol symbol, Price bid, Price ask, Quantity bidSize, Quantity askSize, Timestamp timestamp)
            : symbol_(std::move(symbol)), bid_(bid), ask_(ask),
              bidSize_(bidSize), askSize_(askSize), timestamp_(timestamp) {}

        EventType getType() const override { return EventType::QUOTE; }
        Timestamp getTimestamp() const override { return timestamp_; }
        Symbol getSymbol() const override { return symbol_; }

        Price getBid() const { return bid_; }
        Price getAsk() const { return ask_; }
        Quantity getBidSize() const { return bidSize_; }
        Quantity getAskSize() const { return askSize_; }
        Price getSpread() const { return ask_ - bid_; }
        Price getMidPrice() const { return (bid_ + ask_) / 2.0; }

    private:
        Symbol symbol_;
        Price bid_;
        Price ask_;
        Quantity bidSize_;
        Quantity askSize_;
        Timestamp timestamp_;
    };

    /**
     * @brief Represents an order in the system
     */
    class Order
    {
    public:
        Order(OrderId id, Symbol symbol, Side side, Price price, Quantity quantity, Timestamp timestamp)
            : id_(id), symbol_(std::move(symbol)), side_(side),
              price_(price), quantity_(quantity), timestamp_(timestamp) {}

        OrderId getId() const { return id_; }
        Symbol getSymbol() const { return symbol_; }
        Side getSide() const { return side_; }
        Price getPrice() const { return price_; }
        Quantity getQuantity() const { return quantity_; }
        Timestamp getTimestamp() const { return timestamp_; }

        void setQuantity(Quantity quantity) { quantity_ = quantity; }
        bool isFilled() const { return quantity_ == 0; }

    private:
        OrderId id_;
        Symbol symbol_;
        Side side_;
        Price price_;
        Quantity quantity_;
        Timestamp timestamp_;
    };

    /**
     * @brief Callback function type for market events
     */
    using MarketEventCallback = std::function<void(const std::shared_ptr<MarketEvent> &)>;

    /**
     * @brief Abstract interface for market data sources
     *
     * This interface allows for different types of market data sources:
     * - CSV file replay
     * - Live market data feeds
     * - Synthetic data generators
     */
    class IMarketDataSource
    {
    public:
        virtual ~IMarketDataSource() = default;

        /**
         * @brief Initialize the data source
         * @return true if initialization successful
         */
        virtual bool initialize() = 0;

        /**
         * @brief Start streaming market data
         * @param callback Function to call when new market events arrive
         */
        virtual void startStreaming(MarketEventCallback callback) = 0;

        /**
         * @brief Stop streaming market data
         */
        virtual void stopStreaming() = 0;

        /**
         * @brief Check if the data source is currently streaming
         * @return true if streaming is active
         */
        virtual bool isStreaming() const = 0;

        /**
         * @brief Get the symbol(s) this data source provides
         * @return Vector of symbols
         */
        virtual std::vector<Symbol> getSymbols() const = 0;

        /**
         * @brief Get the current timestamp of the data source
         * @return Current timestamp
         */
        virtual Timestamp getCurrentTimestamp() const = 0;
    };

    /**
     * @brief Abstract interface for order book management
     *
     * This interface defines the core order book operations:
     * - Add orders
     * - Cancel orders
     * - Match orders
     * - Query order book state
     */
    class IOrderBook
    {
    public:
        virtual ~IOrderBook() = default;

        /**
         * @brief Add an order to the order book
         * @param order The order to add
         * @return true if order was added successfully
         */
        virtual bool addOrder(const Order &order) = 0;

        /**
         * @brief Cancel an order from the order book
         * @param orderId ID of the order to cancel
         * @return true if order was cancelled successfully
         */
        virtual bool cancelOrder(OrderId orderId) = 0;

        /**
         * @brief Get the current best bid price
         * @return Best bid price, or 0.0 if no bids
         */
        virtual Price getBestBid() const = 0;

        /**
         * @brief Get the current best ask price
         * @return Best ask price, or 0.0 if no asks
         */
        virtual Price getBestAsk() const = 0;

        /**
         * @brief Get the current spread
         * @return Spread (ask - bid), or 0.0 if no orders
         */
        virtual Price getSpread() const = 0;

        /**
         * @brief Get the current mid price
         * @return Mid price ((bid + ask) / 2), or 0.0 if no orders
         */
        virtual Price getMidPrice() const = 0;

        /**
         * @brief Get the total quantity at a specific price level
         * @param price The price level to query
         * @param side The side (bid/ask) to query
         * @return Total quantity at that price level
         */
        virtual Quantity getQuantityAtPrice(Price price, Side side) const = 0;

        /**
         * @brief Get the order book depth up to a specified number of levels
         * @param levels Number of price levels to return
         * @return Vector of (price, quantity) pairs for each side
         */
        virtual std::pair<std::vector<std::pair<Price, Quantity>>,
                          std::vector<std::pair<Price, Quantity>>>
        getOrderBookDepth(size_t levels) const = 0;

        /**
         * @brief Process a market event (trade/quote) and trigger matching
         * @param event The market event to process
         */
        virtual void processMarketEvent(const std::shared_ptr<MarketEvent> &event) = 0;

        /**
         * @brief Get the symbol this order book manages
         * @return Symbol
         */
        virtual Symbol getSymbol() const = 0;
    };

    /**
     * @brief Abstract interface for trading strategies
     *
     * This interface allows for different trading strategies:
     * - Momentum strategies
     * - Market making strategies
     * - Arbitrage strategies
     * - Custom strategies
     */
    class IStrategy
    {
    public:
        virtual ~IStrategy() = default;

        /**
         * @brief Initialize the strategy
         * @param symbol The symbol to trade
         * @param orderBook Reference to the order book
         * @return true if initialization successful
         */
        virtual bool initialize(const Symbol &symbol, std::shared_ptr<IOrderBook> orderBook) = 0;

        /**
         * @brief Process a market event
         * @param event The market event to process
         */
        virtual void onMarketEvent(const std::shared_ptr<MarketEvent> &event) = 0;

        /**
         * @brief Process an order event (add/cancel/fill)
         * @param order The order that was affected
         * @param eventType The type of order event
         */
        virtual void onOrderEvent(const Order &order, EventType eventType) = 0;

        /**
         * @brief Get the strategy name
         * @return Strategy name
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Get the symbol this strategy trades
         * @return Symbol
         */
        virtual Symbol getSymbol() const = 0;

        /**
         * @brief Get the current position
         * @return Current position (positive = long, negative = short)
         */
        virtual int64_t getPosition() const = 0;

        /**
         * @brief Get the current P&L
         * @return Current profit/loss
         */
        virtual double getPnL() const = 0;

        /**
         * @brief Start the strategy
         */
        virtual void start() = 0;

        /**
         * @brief Stop the strategy
         */
        virtual void stop() = 0;

        /**
         * @brief Check if the strategy is running
         * @return true if strategy is active
         */
        virtual bool isRunning() const = 0;
    };

} // namespace tradesim