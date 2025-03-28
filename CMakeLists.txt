cmake_minimum_required(VERSION 3.10)
project(dd_parser)

set(CMAKE_CXX_STANDARD 23)  # or 23 for the newest standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Enable testing
enable_testing()

# Add source files (excluding main.cpp)
set(LIB_SOURCES
    src/token/token.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
)

# Add header files
set(HEADERS
    src/token/token.hpp
    src/lexer/lexer.hpp
    src/parser/parser.hpp
)

# Create a library with all the source files except main
add_library(dd_parser_lib ${LIB_SOURCES} ${HEADERS})
target_include_directories(dd_parser_lib PUBLIC src)

# Create the main executable
add_executable(dd_parser src/main.cpp)
target_link_libraries(dd_parser PRIVATE dd_parser_lib)

# Add test files
set(TEST_SOURCES
    tests/lexer_test.cpp
    tests/parser_test.cpp
    tests/token_test.cpp
)

# Create test executables
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE dd_parser_lib)
    # Set output directory for test executables
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()


