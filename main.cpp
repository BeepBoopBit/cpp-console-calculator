#include "header/calculator.h"

int main(){
    Calculator _calc;
    std::string expression = "3x + 2 = 8";
    std::cout << _calc.calculateExpression(expression) << "\n\n";
    //while(expression != "0"){
    //    std::cout << "> ";
    //    std::getline(std::cin, expression);
    //    std::cout << _calc.calculateExpression(expression) << "\n\n";
    //}
    return 0;
}



// 3+(4/2)*8+(2*3)
// +3+*/428*23