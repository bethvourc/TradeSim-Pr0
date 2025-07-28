# Tests directory CMakeLists.txt

# Enable testing
enable_testing()

# Create test executable
add_executable(tradesim_tests
    # Engine interface tests
    engine/interfaces_test.cpp
    
    # Note: Other test files will be added in subsequent implementation steps
    # - datasources/csv_source_test.cpp
    # - orderbook/orderbook_test.cpp
    # - strategies/momentum_test.cpp
    # - strategies/market_maker_test.cpp
    # - strategies/arbitrage_test.cpp
)

# Link libraries
target_link_libraries(tradesim_tests
    PRIVATE
        tradesim_core
        gtest
        gtest_main
        gmock
        gmock_main
)

# Set include directories
target_include_directories(tradesim_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Set C++ standard
set_target_properties(tradesim_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Add tests
add_test(NAME TradesimTests COMMAND tradesim_tests)

# Set test properties
set_tests_properties(TradesimTests PROPERTIES
    TIMEOUT 300
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
) 