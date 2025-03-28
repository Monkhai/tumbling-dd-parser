#include <iostream>
#include "parser/parser.hpp"

int main()
{
    // create a repl
    string input;
    while (true)
    {
        std::cout << "Enter a skill:\n";
        std::getline(std::cin, input);
        Parser parser(input);
        string result = parser.parse();
        if (result.empty())
        {
            std::cout << "Invalid skill\n";
        }
        vector<string> errors = parser.getErrors();
        if (!errors.empty())
        {
            std::cout << "Errors:\n";
            for (string error : errors)
            {
                std::cout << error << "\n";
            }
        }
        else
        {
            std::cout << parser.parse() << "\n\n"
                      << endl;
        }
    }
}