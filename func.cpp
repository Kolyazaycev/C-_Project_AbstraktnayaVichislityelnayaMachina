#include "header.h"
#include <iostream>
#include <cctype>
#include <limits>
#include <windows.h>

using namespace std;


void initStack(Stack& s) {
    s.top = -1;
}

bool isEmpty(const Stack& s) {
    return s.top == -1;
}

bool isFull(const Stack& s) {
    return s.top == MAX_STACK_SIZE - 1;
}

void push(Stack& s, const string& value) {
    if (isFull(s)) {
        cerr << "Ошибка: переполнение стека\n";
        return;
    }
    s.top++;
    s.data[s.top] = value;
}

string pop(Stack& s) {
    if (isEmpty(s)) {
        cerr << "Ошибка: стек пуст\n";
        return "";
    }
    string value = s.data[s.top];
    s.top--;
    return value;
}

string top(const Stack& s) {
    if (isEmpty(s)) {
        cerr << "Ошибка: стек пуст\n";
        return "";
    }
    return s.data[s.top];
}

int size(const Stack& s) {
    return s.top + 1;
}


void setRussianLocale() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool validatePostfix(const string& expr) {
    if (expr.empty()) {
        cout << "Ошибка: выражение не может быть пустым\n";
        return false;
    }
    
    int operandCount = 0;
    int operatorCount = 0;
    
    for (char c : expr) {
        if (isalpha(c)) {
            operandCount++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            operatorCount++;
        }
        else {
            cout << "Ошибка: недопустимый символ '" << c << "'\n";
            return false;
        }
    }
    
    // Первый уровень валидации
    if (operandCount != operatorCount + 1) {
        cout << "Ошибка: некорректное постфиксное выражение\n";
        return false;
    }
    
    // Второй уровень валидации
    Stack checkStack;
    initStack(checkStack);
    
    for (char c : expr) {
        if (isalpha(c)) {
            push(checkStack, "1");
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (size(checkStack) < 2) {
                cout << "Ошибка: недостаточно операндов для операции '" << c << "'\n";
                return false;
            }
            pop(checkStack);
            pop(checkStack);
            push(checkStack, "1");
        }
    }
    
    return true;
}

void generateInstructions(const string& postfix) {
    Stack operands;
    initStack(operands);
    
    int tempCounter = 1;
    
    for (size_t idx = 0; idx < postfix.length(); idx++) {
        char c = postfix[idx];
        
        if (isalpha(c)) {
            push(operands, string(1, c));
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            string right = pop(operands);
            string left = pop(operands);
            
            cout << "LD " << left << endl;
            switch (c) {
                case '+': cout << "AD " << right << endl; break;
                case '-': cout << "SB " << right << endl; break;
                case '*': cout << "ML " << right << endl; break;
                case '/': cout << "DV " << right << endl; break;
            }
            
            bool isLastOperation = (idx == postfix.length() - 1);
            
            if (!isLastOperation) {
                string result;
                
                if (right[0] == 'T') {
                    result = right;
                }
                else if (left[0] == 'T') {
                    result = left;
                }
                else {
                    result = "T" + to_string(tempCounter);
                    tempCounter++;
                }
                
                cout << "ST " << result << endl;
                push(operands, result);
            }
        }
    }
}

void clearInputStream() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
