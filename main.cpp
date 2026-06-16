#include "header.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    setRussianLocale();
    
    int choice;
    string expression;
    
    cout << "Компилятор постфиксных выражений в инструкции ВМ\n";
    cout << "Поддерживаются: + - * / и однобуквенные переменные\n";
    
    do {
        cout << "\nМеню:\n";
        cout << "1. Ввести выражение\n";
        cout << "2. Справка\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        
        if (!(cin >> choice)) {
            clearInputStream();
            cout << "Ошибка! Введите число.\n";
            continue;
        }
        
        clearInputStream();
        
        switch (choice) {
            case 1:
                cout << "Введите постфиксное выражение: ";
                getline(cin, expression);
                
                if (!validatePostfix(expression)) {
                    break;
                }
                
                cout << "\nИнструкции:\n";
                generateInstructions(expression);
                break;
                
            case 2:
                cout << "\nСправка:\n";
                cout << "Постфиксная форма (Обратная польская запись):\n";
                cout << "Сначала операнды, затем операция\n";
                cout << "Пример: AB+ = A+B\n";
                cout << "Пример: ABC*+DE-/ = (A+B*C)/(D-E)\n";
                cout << "Операнды: буквы A-Z, a-z\n";
                cout << "Операции: + - * /\n";
                break;
                
            case 0:
                cout << "До свидания!\n";
                break;
                
            default:
                cout << "Ошибка! Выберите 0, 1 или 2.\n";
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}
