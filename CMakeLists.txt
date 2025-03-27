cmake_minimum_required(VERSION 3.10)
project(dd_parser)

# Enable testing
enable_testing()

# Add source files
set(SOURCES
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/compiler/compiler.cpp
)

# Add header files
set(HEADERS
    src/lexer/lexer.hpp
    src/parser/parser.hpp
    src/compiler/compiler.hpp
)

# Create the main executable
add_executable(dd_parser ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(dd_parser PRIVATE src)

# Add test files
set(TEST_SOURCES
    tests/lexer_test.cpp
    tests/parser_test.cpp
    tests/compiler_test.cpp
)

# Create test executables
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PRIVATE src)
    # Set output directory for test executables
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach() 