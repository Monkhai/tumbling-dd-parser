#include <iostream>
#include <cassert>
#include "lexer/lexer.hpp"
#include "token/token_type.hpp"

using namespace std;

// Simple test helper function
void testNextToken_HAPPY()
{
    std::cout << "\n=== Starting testNextToken_HAPPY() ===\n";
    bool allPassed = true;
    vector<int> failedTests;
    string input = "(^^^f2/.";
    string tests[] = {
        "(",
        "^",
        "^",
        "^",
        "f",
        "2/.",
    };

    Lexer lexer(input);
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        Token token = lexer.nextToken();
        if (token.token == tests[i])
        {
            std::cout << "✓ " << tests[i] << "\n";
        }
        else
        {
            std::cout << "✗ expected " << "'" << tests[i] << "'" << " got " << token.token << "'\n";
            allPassed = false;
            // just add the index to the array at the last position
            failedTests[failedTests.size() - 1] = i;
        }
    }
    if (allPassed)
    {
        std::cout << "✓ testNextToken_HAPPY: All tests passed\n";
    }
    else
    {
        std::cout << "✗ testNextToken_HAPPY: Some tests failed\n";
        for (int i = 0; i < failedTests.size(); i++)
        {
            std::cout << "✗ Test " << "[" << failedTests[i] << "]" << " failed\n";
        }
    }
}

void testNextToken_ILLEGAL()
{
    std::cout << "\n=== Starting testNextToken_ILLEGAL() ===\n";
    bool allPassed = true;
    vector<int> failedTests;
    string inputs[] = {
        "a",
        "א",
        "0",
    };

    for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
    {
        Lexer lexer = Lexer(inputs[i]);
        Token token = lexer.nextToken();
        if (token.token == TokenType::ILLEGAL)
        {
            std::cout << "✓ " << inputs[i] << "\n";
        }
        else
        {
            std::cout << "✗ expected " << "'" << inputs[i] << "'" << " got " << token.token << "'\n";
            allPassed = false;
        }
    }
    if (allPassed)
    {
        std::cout << "✓ testNextToken_ILLEGAL: All tests passed\n";
    }
    else
    {
        std::cout << "✗ testNextToken_ILLEGAL: Some tests failed\n";
        for (int i = 0; i < failedTests.size(); i++)
        {
            std::cout << "✗ Test " << "[" << failedTests[i] << "]" << " failed\n";
        }
    }
}

void testNextToken_SAD()
{
    std::cout << "\n=== Starting testNextToken_SAD() ===\n";
    bool allPassed = true;
    vector<int> failedTests;

    struct TestCase
    {
        string input;
        vector<string> expected;
    };

    TestCase tests[] = {
        {"(-o/",
         {"(", "ILLEGAL"}}};

    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        TestCase test = tests[i];
        Lexer lexer(test.input);
        for (int j = 0; j < test.expected.size(); j++)
        {
            Token token = lexer.nextToken();
            if (token.token == test.expected[j])
            {
                std::cout << "✓ " << test.expected[j] << "\n";
            }
            else
            {
                std::cout << "✗ expected " << "'" << test.expected[j] << "'" << " got " << token.token << "'\n";
                allPassed = false;
            }
        }
    }
    if (allPassed)
    {
        std::cout << "✓ testNextToken_SAD: All tests passed\n";
    }
    else
    {
        std::cout << "✗ testNextToken_SAD: Some tests failed\n";
        for (int i = 0; i < failedTests.size(); i++)
        {
            std::cout << "✗ Test " << "[" << failedTests[i] << "]" << " failed\n";
        }
    }
}

int main()
{
    testNextToken_HAPPY();
    testNextToken_ILLEGAL();
    testNextToken_SAD();
    return 0;
}