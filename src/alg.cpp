// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Priority(char sym) {
    if (sym == '(')
        return 0;
    else if (sym == ')')
        return 1;
    else if (sym == '+' || sym == '-')
        return 2;
    else if (sym == '*' || sym == '/')
        return 3;
}
bool Operand(char sym) {
    if (sym != '(' && sym != ')' && sym != '+' && sym != '-' && sym != '/' && sym != '*')
        return true;
    return false;
}
std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string pstf;
    for (char sym : inf) {
        if (Operand(sym)) {
            pstf.push_back(sym);
            pstf.push_back(' ');
        } else if (Priority(sym) == 0) {
            stack.push(sym);
        } else if (Priority(sym) == 1) {
            while (Priority(stack.get()) != 0) {
                pstf.push_back(stack.get());
                pstf.push_back(' ');
                stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() && (Priority(sym) <= Priority(stack.get()))) {
                pstf.push_back(stack.get());
                pstf.push_back(' ');
                stack.pop();
            }
            stack.push(sym);
        }
    }
    while (!stack.isEmpty()) {
        pstf.push_back(stack.get());
        pstf.push_back(' ');
        stack.pop();
    }
    pstf.pop_back();
    return pstf;
}

int eval(std::string pref) {
    TStack<int, 100> stack;
    for (char sym : pref) {
        if (sym >= '0' && sym <= '9') {
            stack.push(sym - '0');
        } else if (sym == '+' || sym == '-' || sym == '/' || sym == '*') {
            int num2 = stack.get();
            stack.pop();
            int num1 = stack.get();
            stack.pop();
            if (sym == '+') {
                stack.push(num1 + num2);
            } else if (sym == '-') {
                stack.push(num1 - num2);
            } else if (sym == '*') {
                stack.push(num1 * num2);
            } else if (sym == '/') {
                stack.push(num1 / num2);
            }
        }
    }
    return stack.get();
}
