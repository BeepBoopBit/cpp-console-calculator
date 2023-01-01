#ifndef NCALCULATOR_H
#define NCALCULATOR_H

#include <string>
#include <iostream>
#include <sstream>

class Calculator{
public:
    Calculator(){

    }

public:
    void solve(std::string equation){

        // Identify the missing variables
        int count = identifyMissingVariables(equation);

        // _simplexCalculator.solve(equation);



    }

private:
    int identifyMissingVariables(std::string equation){
        int count = 0;
        for(int i = 0; i < equation.length(); i++){
            if(equation[i] == 'x' || equation[i] == 'y' || equation[i] == 'z''){
                count++;
            }
        }
        return count;
    }


};

#endif // NCALCULATOR_H