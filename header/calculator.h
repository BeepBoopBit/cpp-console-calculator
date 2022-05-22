#ifndef R_CALCULATOR_H
#define R_CALCULATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>


// No need to be separated by spaces

/**
 * Solving Expression
 * 1.) Tokenize and Separate the values and operators
 * 2.) Add Parenthesis
 * 3.) Convert the Infix to postfix
 * 4.) Solve it using stack
 */

class Calculator{

public: // Constructors
    Calculator(){

    }

public: // Main Functions


    void calculateExpression(std::string userInput){
        _userExpression = userInput;
        tokenizeStr();
        addParenthesis();
        constructExpression();
        print_token();
    }

private: // auxillary functions

    // Working at O(n)
    void tokenizeStr(){
        std::string digitStr = "";
        for(int i = 0; i < _userExpression.length(); ++i){
            char input = _userExpression[i];
            if(isDigit(input)){
                // accumulate the digit in a single string;
                digitStr += input;
            }else if(isOperator(input)){
                // push the digit
                _tokenizeValue.push_back(digitStr);

                // reset the digit
                digitStr = "";

                // put the operator in the digit (to avoid conversion)
                digitStr += input;

                // push the operator
                _tokenizeOperator.push_back(digitStr);

                // reset the digit
                digitStr = "";
            }else if(isVariable(input)){
                // push the digits
                _tokenizeValue.push_back(digitStr);

                // reset the digit
                digitStr = "";

                // put the variable in the digit (to avoid conversion)
                digitStr += input;

                // push the Variable
                _tokenizeValue.push_back(digitStr);

                // reset the digit
                digitStr  = "";
            }else if(input == ' '){
                // do nothing
            }else{
                std::cout << "Unknown Token: " << _userExpression[i] << std::endl;
                exit(-1);
            }
        }
        if(digitStr.length()){
            _tokenizeValue.push_back(digitStr);
        }
    }

    // Should Take O(n)
    void addParenthesis(){
        bool previousMD = false;
        for(int i = 0; i < _tokenizeOperator.size(); ++i){
            if((_tokenizeOperator[i] == "*" || _tokenizeOperator[i] == "/") && previousMD == false){
                _tokenizeValue[i] = '(' + _tokenizeValue[i];
                _tokenizeValue[i+1] =  _tokenizeValue[i+1] + ')';
                previousMD = true;
            }else{
                previousMD = false;
            }
        }
    }

    void constructExpression(){
        std::string tempExpression = "";
        for(int valueIndex = 0, operatorIndex = 0; valueIndex < _tokenizeValue.size(); ++valueIndex){
            if(valueIndex >= 1){
                tempExpression += _tokenizeOperator[operatorIndex++] + ' ';
            }
            tempExpression += _tokenizeValue[valueIndex] + ' ';
        }
        _userExpression = tempExpression;
    }

    bool isDigit(char value){
        switch (value)
        {
            case '0':
                return true;
                break;
            case '1':
                return true;
                break;
            case '2':
                return true;
                break;
            case '3':
                return true;
                break;
            case '4':
                return true;
                break;
            case '5':
                return true;
                break;
            case '6':
                return true;
                break;
            case '7':
                return true;
                break;
            case '8':
                return true;
                break;
            case '9':
                return true;
                break;
        }
        return false;
    }

    bool isOperator(char value){
        switch (value)
        {
        case '+':
            return true;
            break;
        case '-':
            return true;
            break;
        case '*':
            return true;
            break;
        case '/':
            return true;
            break;
        case '^':
            return true;
            break;
        }
        return false;
    }

    bool isVariable(char value){
        // ASCII corresponding A-Z and a-z
        if(value >= 65 && value <= 90){
            return true;
        }else if(value >= 97 && value <= 122){
            return true;
        }
        return false;
    }


private: // debug
    void print_token(){
        for(int i = 0; i < _tokenizeValue.size(); ++i){
            std::cout << _tokenizeValue[i] << ' ';
        }
        std::cout << std::endl;
        for(int i = 0; i < _tokenizeOperator.size(); ++i){
            std::cout << _tokenizeOperator[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << _userExpression;
    }

private: // Variables
    std::vector<std::string> _tokenizeValue;
    std::vector<std::string> _tokenizeOperator;
    std::string _userExpression;

};


#endif // R_CALCULATOR_H
