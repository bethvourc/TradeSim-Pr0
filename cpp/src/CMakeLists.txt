# Source directory CMakeLists.txt

# Create the main library
add_library(tradesim_core SHARED
    # Engine interfaces
    engine/interfaces.cpp
    
    # Note: Other source files will be added in subsequent implementation steps
    # - datasources/csv_source.cpp
    # - orderbook/orderbook.cpp
    # - strategies/momentum.cpp
    # - strategies/market_maker.cpp
    # - strategies/arbitrage.cpp
    # - pybind/module.cpp
)

# Set include directories
target_include_directories(tradesim_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link libraries
target_link_libraries(tradesim_core
    PRIVATE
        # pybind11::module  # Will be enabled when Python bindings are implemented
)

# Set compile definitions
target_compile_definitions(tradesim_core
    PRIVATE
        TRADESIM_EXPORTS
)

# Set C++ standard
set_target_properties(tradesim_core PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Install rules
install(TARGETS tradesim_core
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
) 