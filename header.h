#ifndef HEADER_H
#define HEADER_H

#include <string>

// Установка кодировки Windows-1251
void setRussianLocale();

// Проверка корректности постфиксного выражения
bool validatePostfix(const std::string& expr);

// Генерация инструкций
void generateInstructions(const std::string& postfix);

// Очистка потока ввода
void clearInputStream();

#endif