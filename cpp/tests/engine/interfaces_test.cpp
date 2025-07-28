#include <gtest/gtest.h>
#include "engine/interfaces.hpp"
#include <chrono>

using namespace tradesim;

class InterfacesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any common test data
    }
};

TEST_F(InterfacesTest, TradeCreation) {
    auto timestamp = std::chrono::system_clock::now();
    Trade trade("AAPL", 150.50, 100, BUY, timestamp);
    
    EXPECT_EQ(trade.getType(), EventType::TRADE);
    EXPECT_EQ(trade.getSymbol(), "AAPL");
    EXPECT_EQ(trade.getPrice(), 150.50);
    EXPECT_EQ(trade.getQuantity(), 100);
    EXPECT_EQ(trade.getSide(), BUY);
    EXPECT_EQ(trade.getTimestamp(), timestamp);
}

TEST_F(InterfacesTest, QuoteCreation) {
    auto timestamp = std::chrono::system_clock::now();
    Quote quote("AAPL", 150.00, 150.10, 1000, 500, timestamp);
    
    EXPECT_EQ(quote.getType(), EventType::QUOTE);
    EXPECT_EQ(quote.getSymbol(), "AAPL");
    EXPECT_EQ(quote.getBid(), 150.00);
    EXPECT_EQ(quote.getAsk(), 150.10);
    EXPECT_EQ(quote.getBidSize(), 1000);
    EXPECT_EQ(quote.getAskSize(), 500);
    EXPECT_NEAR(quote.getSpread(), 0.10, 1e-10);
    EXPECT_NEAR(quote.getMidPrice(), 150.05, 1e-10);
}

TEST_F(InterfacesTest, OrderCreation) {
    auto timestamp = std::chrono::system_clock::now();
    Order order(12345, "AAPL", BUY, 150.50, 100, timestamp);
    
    EXPECT_EQ(order.getId(), 12345);
    EXPECT_EQ(order.getSymbol(), "AAPL");
    EXPECT_EQ(order.getSide(), BUY);
    EXPECT_EQ(order.getPrice(), 150.50);
    EXPECT_EQ(order.getQuantity(), 100);
    EXPECT_EQ(order.getTimestamp(), timestamp);
    EXPECT_FALSE(order.isFilled());
    
    order.setQuantity(0);
    EXPECT_TRUE(order.isFilled());
}

TEST_F(InterfacesTest, TypeAliases) {
    // Test that type aliases work correctly
    OrderId id = 12345;
    Symbol sym = "AAPL";
    Price price = 150.50;
    Quantity qty = 100;
    Side side = BUY;
    
    EXPECT_EQ(side, BUY);
    EXPECT_EQ(id, 12345);
    EXPECT_EQ(sym, "AAPL");
    EXPECT_EQ(price, 150.50);
    EXPECT_EQ(qty, 100);
}

TEST_F(InterfacesTest, EventTypeEnum) {
    // Test that EventType enum values are correct
    EXPECT_EQ(static_cast<int>(EventType::TRADE), 0);
    EXPECT_EQ(static_cast<int>(EventType::QUOTE), 1);
    EXPECT_EQ(static_cast<int>(EventType::ORDER_ADDED), 2);
    EXPECT_EQ(static_cast<int>(EventType::ORDER_CANCELLED), 3);
    EXPECT_EQ(static_cast<int>(EventType::ORDER_FILLED), 4);
    EXPECT_EQ(static_cast<int>(EventType::STRATEGY_SIGNAL), 5);
}

TEST_F(InterfacesTest, MarketEventPolymorphism) {
    auto timestamp = std::chrono::system_clock::now();
    
    // Test polymorphism with Trade
    std::shared_ptr<MarketEvent> trade_event = 
        std::make_shared<Trade>("AAPL", 150.50, 100, BUY, timestamp);
    EXPECT_EQ(trade_event->getType(), EventType::TRADE);
    EXPECT_EQ(trade_event->getSymbol(), "AAPL");
    EXPECT_EQ(trade_event->getTimestamp(), timestamp);
    
    // Test polymorphism with Quote
    std::shared_ptr<MarketEvent> quote_event = 
        std::make_shared<Quote>("AAPL", 150.00, 150.10, 1000, 500, timestamp);
    EXPECT_EQ(quote_event->getType(), EventType::QUOTE);
    EXPECT_EQ(quote_event->getSymbol(), "AAPL");
    EXPECT_EQ(quote_event->getTimestamp(), timestamp);
}

TEST_F(InterfacesTest, MarketEventCallback) {
    auto timestamp = std::chrono::system_clock::now();
    std::shared_ptr<MarketEvent> received_event = nullptr;
    
    // Create a callback that captures the event
    MarketEventCallback callback = [&received_event](const std::shared_ptr<MarketEvent>& event) {
        received_event = event;
    };
    
    // Create a trade event
    auto trade = std::make_shared<Trade>("AAPL", 150.50, 100, BUY, timestamp);
    
    // Call the callback
    callback(trade);
    
    // Verify the callback received the event
    EXPECT_NE(received_event, nullptr);
    EXPECT_EQ(received_event->getType(), EventType::TRADE);
    EXPECT_EQ(received_event->getSymbol(), "AAPL");
} 