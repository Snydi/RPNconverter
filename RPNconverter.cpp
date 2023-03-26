#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 's';
}

int precedence(char c) {
    if (c == '^' || c == 's') {
        return 3;
    }
    else if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

string to_rpn(string expr) {
    stack<char> op_stack;
    string rpn;
    int i = 0;
    while (i < expr.length()) {
        if (isdigit(expr[i])) {
            int j = i;
            while (j < expr.length() && isdigit(expr[j])) {
                j++;
            }
            rpn += expr.substr(i, j - i) + ' ';
            i = j;
        }
        else if (expr[i] == '(') {
            op_stack.push(expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                rpn += op_stack.top();
                op_stack.pop();
                rpn += ' ';
            }
            if (!op_stack.empty()) {
                op_stack.pop();
            }
            i++;
        }
        else if (is_operator(expr[i])) {
            while (!op_stack.empty() && is_operator(op_stack.top()) && precedence(op_stack.top()) >= precedence(expr[i])) {
                rpn += op_stack.top();
                op_stack.pop();
                rpn += ' ';
            }
            op_stack.push(expr[i]);
            i++;
        }
        else {
            i++;
        }
    }
    while (!op_stack.empty()) {
        rpn += op_stack.top();
        op_stack.pop();
        rpn += ' ';
    }
    return rpn;
}

double evaluate_rpn(string rpn) {
    stack<double> operand_stack;
    int i = 0;
    while (i < rpn.length()) {
        if (isdigit(rpn[i])) {
            int j = i;
            while (j < rpn.length() && rpn[j] != ' ') {
                j++;
            }
            double operand = stod(rpn.substr(i, j - i));
            operand_stack.push(operand);
            i = j + 1;
        }
        else if (rpn[i] == 's') {
            double operand = operand_stack.top();
            operand_stack.pop();
            operand_stack.push(sqrt(operand));
            i += 2;
        }
        else if (is_operator(rpn[i])) {
            double rhs = operand_stack.top();
            operand_stack.pop();
            double lhs = operand_stack.top();
            operand_stack.pop();
            switch (rpn[i]) {
            case '+':
                operand_stack.push(lhs + rhs);
                break;
            case '-':
                operand_stack.push(lhs - rhs);
                break;
            case '*':
                operand_stack.push(lhs * rhs);
                break;
            case '/':
                operand_stack.push(lhs / rhs);
                break;
            case '^':
                operand_stack.push(pow(lhs, rhs));
                break;
            }
            i += 2;
        }
        else {
            i++;
        }
    }
    return operand_stack.top();
}

int main() {
    string expr;
    cout << "Enter expression in normal notation: ";
    getline(cin, expr);
    string rpn = to_rpn(expr);
    cout << "RPN expression: " << rpn << endl;
    double result = evaluate_rpn(rpn);
    cout << "Result: " << result << endl;
    return 0;
}

