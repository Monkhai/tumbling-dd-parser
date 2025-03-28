#include <iostream>
#include <cassert>
#include "token/token.hpp"

void test_token_creation()
{
    std::cout << "\n=== Starting test_token_creation() ===\n";
    string tests[] = {"(", "f", "^", "-", "2/."};
    bool all_passed = true;

    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        string count = "[" + to_string(i + 1) + "]: ";
        try
        {
            Token token = Token(tests[i]);
            if (token.token == tests[i])
            {
                std::cout << "✓ " << count << tests[i] << "\n";
            }
            else
            {
                std::cout << "✗ " << tests[i] << "\n";
                all_passed = false;
            }
        }
        catch (...)
        {
            std::cout << "✗\n";
            all_passed = false;
        }
    }

    if (all_passed)
    {
        std::cout << "=== test_token_creation() passed successfully! ===\n";
    }
    else
    {
        std::cout << "=== test_token_creation() failed! ===\n";
    }
}

int main()
{
    test_token_creation();
    return 0;
}