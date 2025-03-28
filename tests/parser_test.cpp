#include <iostream>
#include <cassert>
#include "parser/parser.hpp"

struct TestCase
{
    string input;
    string expected;
};

void testParse()
{
    std::cout << "\n=== Starting testParse() ===\n";
    bool allPassed = true;
    vector<int> failedTests;

    TestCase testCases[] = {
        {"(^^^f2-/.", "RO whip whip whip flic full-in straight"},
        {"(^^^f2-o.", "RO whip whip whip flic full-in tuck"},
        {"(^^^f22o.", "RO whip whip whip flic full-full tuck"},
        {"(^^^f2--o.", "RO whip whip whip flic full-in triple tuck"},
        {"(^^^f--/.", "RO whip whip whip flic double straight"},
        {"(^^^f-2/.", "RO whip whip whip flic back-in full-out straight"},
    };

    for (TestCase testCase : testCases)
    {
        Parser parser(testCase.input);
        string result = parser.parse();
        if (result == testCase.expected)
        {
            std::cout << "✓ " << result << "\n";
        }
        else
        {
            std::cout << "✗ expected " << "'" << testCase.expected << "'" << " got " << "'" << result << "'" << "\n";

            std::cout << "errors: \n";

            vector<string> errors = parser.getErrors();
            for (string error : errors)
            {
                std::cout << "  " << error << "\n";
            }
        }
    }
}

int main()
{
    testParse();
    return 0;
}