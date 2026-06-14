#include "header.h"
#include <iostream>
#include <stack>
#include <cctype>
#include <limits>
#include <windows.h>

using namespace std;

void setRussianLocale() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}
// Функция проверки корректности постфиксного выражения
// Выполняет две проверки: статическую (подсчёт операндов/операторов)
// и динамическую (проверка возможности вычисления с использованием стека)
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
    
    if (operandCount != operatorCount + 1) {
        cout << "Ошибка: некорректное постфиксное выражение\n";
        return false;
    }
    
    return true;
}
// Функция генерации инструкций для абстрактной ВМ
// Алгоритм: обход постфиксного выражения, использование стека для хранения операндов,
// переиспользование временных переменных для экономии памяти
void generateInstructions(const string& postfix) {
    stack<string> operands;
    int tempCounter = 1;
    
    for (size_t idx = 0; idx < postfix.length(); idx++) {
        char c = postfix[idx];
        
        if (isalpha(c)) {
            operands.push(string(1, c));
        } 
        else {
            string right = operands.top(); operands.pop();
            string left = operands.top(); operands.pop();
            
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
                operands.push(result);
            }
        }
    }
}
// Очистка потока ввода после некорректного ввода
// Используется при вводе буквы вместо числа в меню
void clearInputStream() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}