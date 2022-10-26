#ifndef R_CALCULATOR_H
#define R_CALCULATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>


/**
 * Since we tokenize it 
 * We have the operators
 * We have the values
 * then just use that to make a tree
 * it'll be faster than converting it to infix first
 */

class BinaryTree{

private:
    struct Node{
       std::string value;
       Node *left;
       Node *right;
       Node *parent; 
    };

public:
    BinaryTree(){
        _head = nullptr;
        _isRight = false;
    }

    void pushValue(std::string value){

        Node *tempNode = _head;
        if(_isRight){
            if(tempNode->right == nullptr){
                tempNode->right =  createNewNode(value, _head);
            }else{
                tempNode = tempNode->right;
            }
        }
        // Go as far right as possible
        while(tempNode->right != nullptr){
            tempNode = tempNode->right;
        }
        // if it's not an operator
        if(!isOperatorStr(tempNode->value)){
            tempNode = traverseFindOperator(tempNode);
        }
        if(tempNode->left == nullptr){
            tempNode->left = createNewNode(value, tempNode);
        }else{
            tempNode->right = createNewNode(value, tempNode);
        }
    }
    
    // assumes that this will be the first method to be called
    void pushOperator(std::string opValue){
        
        if(_head == nullptr){
            _head = createNewNode(opValue);
        }else{
            Node *tempNode = _head;
            // go as far right as possible
            while(tempNode->right != nullptr){
                tempNode = tempNode->right;
            }
            // if it's not an operator then it means we can't put it on the right side
            if(!isOperatorStr(tempNode->value)){
                tempNode=traverseFindOperator(tempNode);
            }
            if(tempNode->right == nullptr){
                tempNode->right = createNewNode(opValue, tempNode);
            }else{
                tempNode->left = createNewNode(opValue, tempNode);
            }
        }
    }

    void pushEqual(std::string equalValue){
        _head = createNewNode(equalValue, nullptr, _head);
        _isRight = true;
    }


    int solve(){
        // Traverse far right until the next value is not an operator
        Node *tempHead = _head;
        while(isOperatorStr(tempHead->right->value)){
            tempHead = tempHead->right;
        }
        auxillarySolve(tempHead);
        return std::stoi(_head->value);
    }

    void print(){
        Node *tempNode = _head;
        printRec(tempNode);
    }

    void erase(){
        delete _head;
        _head = nullptr;
    }

private:
    
    void auxillarySolve(Node *node){
        // then solve with it
        int left = 0, right = 0;
        bool isLeft = false, isRight = false;

        if(node->left == nullptr && node->right == nullptr){
            return;
        }

        if(isDigit(node->left->value.back())){
            left = std::stoi(node->left->value);
            isLeft = true;
        }
        // check if left is an operator
        else if(isOperatorStr(node->left->value)){
            auxillarySolve(node->left);
            return;
        }

        if(isDigit(node->right->value.back())){
            right = std::stoi(node->right->value);
            isRight = true;
        }else{
            auxillarySolve(node->right);
        }

        if(isLeft && isRight){
            node->value = std::to_string(solveValue(node->value, left, right));

            // Delete Left Node;
            delete node->left;
            node->left = nullptr;

            // Delete right Node;
            delete node->right;
            node->right = nullptr;
        }

        if(node->parent != nullptr){
            auxillarySolve(node->parent);
        }
    }

    bool isDigit(char value){
        switch (value)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return true;
                break;
        }
        return false;
    }

    void printRec(Node *node){
        std::cout << node->value << ' ';
        if(node->left != nullptr){
            printRec(node->left);
        }
        if(node->right != nullptr){
            printRec(node->right);
        }
    }

    Node *traverseFindOperator(Node *node){
        if((node->left == nullptr || node->right == nullptr) && isOperatorStr(node->value)){
            return node;
        }else if(isOperatorStr(node->value)){
            if(node->left != nullptr && isOperatorStr(node->left->value)){
                // since we need to check for right after checking left, we'll create a separate fuction for it
                return traverseFindOperatorLeft(node->left);
            }else{
                return traverseFindOperator(node->parent);
            }
        }
        else if(!isOperatorStr(node->value)){
            return traverseFindOperator(node->parent);
        }
        return node;
    }

    Node *traverseFindOperatorLeft(Node *node){
        if(node->right != nullptr && isOperatorStr(node->right->value)){
            return traverseFindOperatorLeft(node->right);
        }else if(node->left != nullptr && isOperatorStr(node->left->value)){
            return traverseFindOperator(node->left);
        }
        return node;
    }

    bool isOperatorStr(std::string str){
        if(str == "+" || str == "-" || str == "*" || str == "/" || str =="(" || str == "^"){
            return true;
        }
        return false;
    }

    Node *createNewNode(std::string value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr){
        Node *node = new Node();
        node->value = value;
        node->parent = parent;
        node->left = left;
        node->right = right;
        return node;
    }


private:

    bool isEqual(std::string str){
        return str == "=";
    }

    int solveValue(std::string value,int lhs, int rhs){
        if(value == "+"){
            return add(lhs,rhs);
        }else if(value == "-"){
            return sub(lhs,rhs);
        }else if(value == "*"){
            return mul(lhs,rhs);
        }else if(value == "/"){
            return div(lhs,rhs);
        }
        return -1;
    }

    int add(int lhs, int rhs){
        return lhs + rhs;
    }

    int sub(int lhs, int rhs){
        return lhs - rhs;
    }

    int mul(int lhs, int rhs){
        return lhs*rhs;
    }

    int div(int lhs, int rhs){
        return lhs/rhs;
    }

private:
    Node *_head;
    bool _isRight;

};

class Calculator{

public: // Constructors
    Calculator(){
        _tree = new BinaryTree();
    }

public: // Main Functions


    int calculate(std::string userInput){
        _userInput = userInput;

        // Working at O(n)
        tokenizeStr();
        // Working at O(n)
        //addParenthesis();
        // Working at O(n)
        constructMathStatement();
        // Working at O(n)
        //_userInput = convertToPrefix(_userInput);
        // Working at O(n)
        makeTree();

        // Storing the answer
        int value = _tree->solve();

        // Erasing Values
        truncateValue();
        _tree->erase();

        // Working at O(n)
        return value;
    }


private: // auxillary functions

    void truncateValue(){
        _lTokenizeValue = std::vector<std::string>(); // left 
        _rTokenizeValue = std::vector<std::string>(); // right
        _lTokenizeOperator = std::vector<std::string>(); // left
    }

    void makeTree(){

        std::string temp;
        for(int i = 0, val = 0; i < _lTokenizeOperator.size(); ++i, ++val){
            _lTokenizeValue[val].pop_back();
            _lTokenizeValue[val+1].pop_back();

            _tree->pushOperator(_lTokenizeOperator[i]);
            _tree->pushValue(_lTokenizeValue[val++]);
            _tree->pushValue(_lTokenizeValue[val]);
        }

        // problem with making a tree when there is a sign
        //std::string temp;
        //for(int i = 0; i < _userInput.length(); ++i){
        //    char value = _userInput[i];
        //    if(value == ';'){
        //        if(temp.length() != 0){
        //            _tree->pushValue(temp);
        //            temp = "";
        //        }
        //    }else if(isOperator(value)){
        //        if(isOperator(temp.back())){
        //            temp += value;
        //        }else{
        //            temp = "";
        //            temp+=value;
        //            _tree->pushOperator(temp);
        //            temp = "";
        //        }
        //    }else if(isVariable(value) || isDigit(value)){
        //        temp += value;
        //    }else if(value == '='){
        //        temp = "";
        //        temp+=value;
        //        _tree->pushEqual(temp);
        //        temp = "";
        //    }
        //}
    }

    void tokenizeStr(){
        std::string digitStr = "";
        for(int i = 0; i < _userInput.length(); ++i){
            char input = _userInput[i];
             if(input == ' '){
                // do nothing
            }else if(isDigit(input)){
                // accumulate the digit in a single string;
                digitStr += input;
            }else if(isOperator(input) || isEqual(input)){

                if(digitStr.empty()){
                    digitStr += input;
                    continue;
                }

                // push the digit
                _lTokenizeValue.push_back(digitStr + ';');

                // reset the digit
                digitStr = "";

                // put the operator in the digit (to avoid conversion)
                digitStr += input;

                // push the operator
                _lTokenizeOperator.push_back(digitStr);

                // reset the digit
                digitStr = "";
            }
            else{
                std::cout << "Unknown Token: " << _userInput[i] << std::endl;
                exit(-1);
            }
        }
        if(digitStr.length()){
            _lTokenizeValue.push_back(digitStr +  ';');
        }
    }

    void addParenthesis(){
        // Maybe try to put parenthesis with those that have sign
        bool previousMD = false;
        for(int i = 0; i < _lTokenizeOperator.size(); ++i){
            //_lTokenizeValue[i] = '(' + _lTokenizeValue[i] + ')';
            if((_lTokenizeOperator[i] == "*" || _lTokenizeOperator[i] == "/") && previousMD == false){
                _lTokenizeValue[i] = '(' + _lTokenizeValue[i];
                _lTokenizeValue[i+1] =  _lTokenizeValue[i+1] + ')';
                previousMD = true;
            }else{
                previousMD = false;
            }
        }
    }

    void constructMathStatement(){
        std::string tempExpression = "";
        for(int valueIndex = 0, operatorIndex = 0; valueIndex < _lTokenizeValue.size(); ++valueIndex){
            if(valueIndex >= 1){
                tempExpression += _lTokenizeOperator[operatorIndex++] + ' ';
            }
            tempExpression += _lTokenizeValue[valueIndex] + ' ';
        }
        _userInput = tempExpression;
    }

    std::string convertToPrefix(std::string userInput){
        int l = userInput.size();
    
        std::reverse(userInput.begin(), userInput.end());
    
        for (int i = 0; i < l; i++) {
    
            if (userInput[i] == '(') {
                userInput[i] = ')';
            }
            else if (userInput[i] == ')') {
                userInput[i] = '(';
            }
        }
    
        std::string prefix = convertToPostfix(userInput);
    
        // Reverse postfix
        std::reverse(prefix.begin(), prefix.end());

        return prefix;
    }

    std::string convertToPostfix(std::string userInput){
        std::stack<char> st;
        std::string result;
        for (int i = 0; i < userInput.length(); i++) {
            char c = userInput[i];
            if(c == ' '){
                // do nothing
            }else if (isVariable(c) || isDigit(c) || c == ';'){
                result += c;
            }
            else if (c == '('){
                st.push('(');
            }
            else if (c == ')') {
                while (st.top() != '(') {
                    result += st.top();
                    st.pop();
                }
                st.pop();
            }
            else {
                // if the next value is operator, then it means that the current character is a sign
                if((userInput.length() < i+1 && isOperator(userInput[i+1])) || (i == userInput.length()-1 && isOperator(userInput[i]))){
                    result += c;
                }else{
                    while (!st.empty()
                        && getPrecedency(userInput[i]) <= getPrecedency(st.top())) {
                        if (c == '^' && st.top() == '^')
                            break;
                        else {
                            result += st.top();
                            st.pop();
                        }
                    }
                    st.push(c);
                }
            }
        }
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }

    int solveExpression(){
        std::stack<int> values;
        std::string tempValues;
        for(int i = 0; i < _userInput.length(); ++i){
            char value = _userInput[i];
            if(value == ';'){
                try{
                    values.push(std::stoi(tempValues));
                }catch(...){
                    std::cout << "Error When Converting Value";
                }
                tempValues = "";
            }else{
                if(isDigit(value)){
                    tempValues += value;
                }else if(isOperator(value)){
                    int lhs = values.top();
                    values.pop();
                    int rhs = values.top();
                    values.pop();

                    if(value == '+'){
                        values.push(add(rhs,lhs));
                    }else if(value == '-'){
                        values.push(sub(rhs,lhs));
                    }else if(value == '*'){
                        values.push(mul(rhs,lhs));
                    }else if(value == '/'){
                        values.push(div(rhs,lhs));
                    }else if(value == '^'){
                        values.push(pow(rhs,lhs));
                    }
                }
            }
        }
        int result = values.top();
        values.pop();
        return result;
    }


private: // auxillary functions

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

    bool isEqual(char value){
        return value == '=';
    }

    bool isOperator(char value){
        switch (value)
        {
        // P E MD AS
        case '/':
        case '-':
        case '+':
        case '*':
        case '(':
            return true;
            break;
        }
        return false;
    }

    int getPrecedency(char vOperator){
        if (vOperator == '^')
            return 3;
        else if (vOperator == '/' || vOperator == '*')
            return 2;
        else if (vOperator == '+' || vOperator == '-')
            return 1;
        else
            return -1;
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


private: // operations
    int add(int a, int b){
        return a + b;
    }

    int sub(int a, int b){
        return a - b;
    }

    int mul(int a, int b){
        return a * b;
    }

    int div(int a, int b){
        return a/b;
    }

    int pow(int a, int b){
        int value = a;
        for(int i = 0; i < b; ++i){
            value *= a;
        }
        return value;
    }

private: // debug
    void print_token(){
        for(int i = 0; i < _lTokenizeValue.size(); ++i){
            std::cout << _lTokenizeValue[i] << ' ';
        }
        std::cout << std::endl;
        for(int i = 0; i < _lTokenizeOperator.size(); ++i){
            std::cout << _lTokenizeOperator[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << _userInput;
    }

private: // Variables

    // expression variables
    std::vector<std::string> _lTokenizeValue; // left 
    std::vector<std::string> _rTokenizeValue; // right
    std::vector<std::string> _lTokenizeOperator; // left


    // the equation or expression
    std::string _userInput;

    BinaryTree *_tree;

};


#endif // R_CALCULATOR_H
