#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

int priority(std::string& elem) {
    if (elem == "+" || elem == "-")
        return 0;
    else if (elem == "*" || elem == "/")
        return 1;
    else if (elem == "^" || elem == "sin" || elem == "cos" || elem == "tg" || elem == "ctg" || elem == "exp")
        return 2;
    return 3;
}

bool ifthereisx(std::queue <std::string> q) {
    while (!q.empty()) {
        if (q.front() == "x") {
            return true;
        }
        q.pop();
    }
    return false;
}


std::queue <std::string> toPostfix(const std::string& expr) {
    std::stack <std::string> st;
    std::vector <std::string> elements;
    std::string last;
    std::queue <std::string> q;

    bool un_minus = true;
    for (auto ch : expr) {
        if (un_minus && ch == '-')
        {
            elements.push_back("0");
        }
        if (ch == ' ')
        {
            if (last.size() > 0) {
                elements.push_back(last);
                last = "";
            }
        }
        else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '(' || ch == ')' || ch == '^') {
            if (last.size() > 0) {
                elements.push_back(last);
                last = "";
            }
            last += ch;
            elements.push_back(last);
            last = "";
        }
        else {
            last += ch;
        }
        if (ch == '(')
            un_minus = true;
        else
            un_minus = false;

    }
    if (last.size() > 0) {
        elements.push_back(last);
        last = "";
    }

    for (auto elem : elements) {
        if (elem == "+" || elem == "-" || elem == "/" || elem == "*" ||
                       elem == "^" || elem == "sin" || elem == "cos" || elem == "tg" || elem == "ctg" || elem == "exp") {
            if (st.empty() || st.top() == "(" || priority(st.top()) <= priority(elem)) {
                st.push(elem);
            }
            else {
                while (!st.empty() && st.top() != "(" && priority(st.top()) >= priority(elem)) {
                    q.push(st.top());
                    st.pop();
                }
                st.push(elem);
            }
        }
        else if (elem == "(") {
            st.push(elem);
        }
        else if (elem == ")") {
            while (st.top() != "(") {
                q.push(st.top());
                st.pop();
            }
            st.pop();
        }
        else {
            st.push(elem);
        }
    }
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
    return q;
}

bool isNumber(std::string str) {
    for (char c : str) {
        if ((c < '0' || c > '9') and c != '.')
            return false;
    }
    return true;
}

double countPostfix(std::queue <std::string>& postfix, double& value) {
    std::stack <double> temp;
    while (!postfix.empty()) {
        double a, b;
        if (isNumber(postfix.front())) {
            temp.push(stod(postfix.front()));
            postfix.pop();
        }
        else if (postfix.front() == "x") {
            temp.push(value);
            postfix.pop();
        }
        else if (postfix.front() == "+") {
            a = temp.top();
            temp.pop();
            b = temp.top();
            temp.pop();
            temp.push(a + b);
            postfix.pop();
        }
        else if (postfix.front() == "-") {
            a = temp.top();
            temp.pop();
            b = temp.top();
            temp.pop();
            temp.push(b - a);
            postfix.pop();
        }
        else if (postfix.front() == "cos") {
            a = temp.top();
            temp.pop();
            temp.push(std::cos(a));
            postfix.pop();
        }
        else if (postfix.front() == "sin") {
            a = temp.top();
            temp.pop();
            temp.push(std::sin(a));
            postfix.pop();
        }
        else if (postfix.front() == "tg") {
            a = temp.top();
            temp.pop();
            temp.push(std::sin(a) / std::cos(a));
            postfix.pop();
        }
        else if (postfix.front() == "ctg") {
            a = temp.top();
            temp.pop();
            temp.push(std::cos(a) / std::sin(a));
            postfix.pop();
        }
        else if (postfix.front() == "/") {
            a = temp.top();
            temp.pop();
            b = temp.top();
            temp.pop();
            temp.push(b / a);
            postfix.pop();
        }
        else if (postfix.front() == "*") {
            a = temp.top();
            temp.pop();
            b = temp.top();
            temp.pop();
            temp.push(b * a);
            postfix.pop();
        }
        else if (postfix.front() == "exp") {
            a = temp.top();
            temp.pop();
            temp.push(std::exp(a));
            postfix.pop();
        }
        else if (postfix.front() == "^") {
            a = temp.top();
            temp.pop();
            b = temp.top();
            temp.pop();
            temp.push(std::pow(b, a));
            postfix.pop();
        }
    }
    return temp.top();
}

#endif