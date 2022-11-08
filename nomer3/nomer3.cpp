#include <iostream>
#include <stack>
#include "nomer3.hpp"

using namespace std;

int main(){
    string expression = "3+((5+9)*2)";
    // cout << "Enter math expression : "; cin >> expression;

    string postfix = convertInfixToPostfix(expression);

    Node *a, *b, *newNode;
    Tree t;
    Stack s;

    for (int i = 0; i < postfix.length(); i++){
        if (postfix[i] == ' '){
            continue;
        }
        // kalo pas looping postfix, dan ketemu operator, maka pop 2
        // elemen dari stack, masukin sebagai child dengan parentnya operator
        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'){
            newNode = new Node(postfix[i]);
            a = s.pop();
            b = s.pop();
            newNode->left = b;
            newNode->right = a;
            s.push(newNode);
        }else{
            newNode = new Node(postfix[i]);
            s.push(newNode);
        }
    }
    t.inOrder(newNode); //Tree diprint dalam bentuk inOrder
    return 0;
}

