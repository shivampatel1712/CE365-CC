#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <regex>
#include <cmath>
#include <map>

using namespace std;

map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

bool greaterPrecedence(char op1, char op2) {
    return precedence[op1] > precedence[op2];
}

double applyOperation(char op, double left, double right) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : throw runtime_error("Division by zero");
        case '^': return pow(left, right);
        default: throw runtime_error("Invalid operator");
    }
}

double evaluateExpression(const string& expression) {
    try {
        regex tokenPattern("\\d+\\.\\d+|\\d+|[+\\-*/^()]"), numberPattern("\\d+\\.\\d+|\\d+");
        sregex_iterator iter(expression.begin(), expression.end(), tokenPattern), end;
        vector<string> tokens;
        while (iter != end) {
            tokens.push_back(iter->str());
            iter++;
        }
        
        stack<double> values;
        stack<char> operators;
        
        for (const string& token : tokens) {
            if (regex_match(token, numberPattern)) {
                values.push(stod(token));
            } else if (precedence.count(token[0])) {
                while (!operators.empty() && operators.top() != '(' && greaterPrecedence(operators.top(), token[0])) {
                    char op = operators.top(); operators.pop();
                    double right = values.top(); values.pop();
                    double left = values.top(); values.pop();
                    values.push(applyOperation(op, left, right));
                }
                operators.push(token[0]);
            } else if (token == "(") {
                operators.push('(');
            } else if (token == ")") {
                while (!operators.empty() && operators.top() != '(') {
                    char op = operators.top(); operators.pop();
                    double right = values.top(); values.pop();
                    double left = values.top(); values.pop();
                    values.push(applyOperation(op, left, right));
                }
                if (!operators.empty()) operators.pop();
            }
        }
        
        while (!operators.empty()) {
            char op = operators.top(); operators.pop();
            double right = values.top(); values.pop();
            double left = values.top(); values.pop();
            values.push(applyOperation(op, left, right));
        }
        
        return values.top();
    } catch (...) {
        cout << "Invalid expression" << endl;
        return 0;
    }
}

int main() {
    vector<string> expressions = {
        "(3 + 5) * 2 ^ 3",
        "3 + 5 * 2",
        "3 + 5 * 2 ^ 2",
        "3 + (5 * 2)",
        "3 + 5 ^ 2 * 2",
        "3 * (5 + 2)",
        "(3 + 5) ^ 2",
        "3 ^ 2 * 3",
        "3 ^ 2 + 5 * 2",
        "(3 + 5 * 2 ^ 2 - 8) / 4 ^ 2 + 6"
    };
    
    for (const string& expr : expressions) {
        cout << "Expression: " << expr << " -> Result: " << evaluateExpression(expr) << endl;
    }
    
    return 0;
}
