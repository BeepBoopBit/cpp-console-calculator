#include "header/calculator.h"

int main(){
    Calculator _calc;
    std::string expression = "32 + 44 / 2 * 8 + 223 * 3";
    int answer = _calc.calculateExpression(expression);
    std::cout << expression << " = " << answer << std::endl;
    return 0;
}