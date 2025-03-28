#include <iostream>
#include <cassert>
#include "parser/parser.hpp"

// Simple test helper function
void testParse()
{
    std::cout << "\n=== Starting testParse() ===\n";
    bool allPassed = true;
    vector<int> failedTests;
    string input = "(^^^f2-/.";
    Parser parser(input);
    string expected = "RO whip whip whip flic full-in straight";
    string result = parser.parse();
    if (result == expected)
    {
        std::cout << "✓ " << result << "\n";
    }
    else
    {
        std::cout << "✗ expected " << "'" << expected << "'" << " got " << result << "'\n";
    }
}

int main()
{
    testParse();
    return 0;
}