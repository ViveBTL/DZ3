#include "header.hpp"



    int main()
{
        double value;
        std::string expr;
        std::getline(std::cin, expr);
        std::queue <std::string> postfix = toPostfix(expr);
        if (ifthereisx(postfix)) {
            std::cout << "Enter x: ";
            std::cin >> value;
        }

        double res = countPostfix(postfix, value);
        std::cout << expr << " = " << res << "\n";
}

