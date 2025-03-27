#include <iostream>
#include <cassert>

void test_basic()
{
    // A very simple test
    assert(2 + 2 == 4);
    std::cout << "Test passed!" << std::endl;
}

int main()
{
    test_basic();
    return 0;
}