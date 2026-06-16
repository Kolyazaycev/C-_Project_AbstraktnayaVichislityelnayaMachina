#ifndef HEADER_H
#define HEADER_H

#include <string>


const int MAX_STACK_SIZE = 100;

struct Stack {
    std::string data[MAX_STACK_SIZE];
    int top;
};

// Инициализация стека
void initStack(Stack& s);

// Проверка на пустоту
bool isEmpty(const Stack& s);

// Проверка на заполненность
bool isFull(const Stack& s);

// Добавление элемента
void push(Stack& s, const std::string& value);

// Удаление и возврат верхнего элемента
std::string pop(Stack& s);

// Просмотр верхнего элемента без удаления
std::string top(const Stack& s);

// Получение размера стека
int size(const Stack& s);



void setRussianLocale();
bool validatePostfix(const std::string& expr);
void generateInstructions(const std::string& postfix);
void clearInputStream();

#endif
