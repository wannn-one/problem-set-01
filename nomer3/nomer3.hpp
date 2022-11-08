#ifndef nomer3_hpp
#define nomer3_hpp

#include <iostream>
#include <stack>
using namespace std;

class Node {
    public:
        char value;
        Node *left; 
        Node *right; 
        Node *next = NULL; 
    
        Node (char c){
            this->value = c;
            left = NULL;
            right = NULL;
        }

        Node(){
            left = NULL;
            right = NULL;
        }

    friend class Tree;
    friend class Stack;
};

class Stack {
    Node *head = NULL;
    public:
        void push(Node*);
        Node* pop();
        friend class Tree;
};

class Tree {
    public:
    void inOrder(Node *n){
        if (n == NULL){
            exit(0);
        }else{
            inOrder(n->left);
            cout << n->value << " ";
            inOrder(n->right);
        }
    }
};

void Stack::push(Node *e){
    if (head == NULL){
        head = e;
    }else{
        e->next = head;
        head = e;
    }
}

Node *Stack::pop(){ 
    Node *p = head;
    head = head->next;
    return p;
}

int orderOfOperations(char token) {
// Order operasi
    int priority = 0;
    switch (token) {
        case '*': 
        case '/': 
            priority = 2;
            break;
        case '-': 
        case '+':
            priority = 1;
            break;
    }
    return priority;
}

bool isMathOperator(char token) {
// cek kalo dia math ooperator atau bukan
    switch (token) {
        case '+': 
        case '-': 
        case '*': 
        case '/': 
            return true;
            break;
        default:
            return false;
            break;
    }
}

string convertInfixToPostfix(string infix) {
    string postfix;
    stack<char> charStack; //stack operator
 
    for (int x = 0; x < infix.length(); x++) {
        // Masukin angka ke string 'postfix' 
        if (isdigit(infix[x])) { 
            if (postfix.length() > 0 && !isdigit(postfix.back())) { 
                //Cek kalo karakter di postfix paling belakang bukan angka / bukan digit
                if (!isspace(postfix.back())) { 
                    //cek kalo karakter postfix paling belakang bukan space
                    postfix += " "; //Dikasih space setelah digit selesai
                }
            }
            postfix += infix[x]; // misal postfix.back() nya bukan suatu digit, langsung push ke string
        }else if (isMathOperator(infix[x])) {  //Dicek apakah ekspresinya berupa math operator
            if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                postfix += " ";
            }
            // while nya ngecek, selama stacknya ga kosong dan
            // math operator di pucuk stack, apakah lebih besar sama dengan dari
            // math operator pada tranversing sekarang
            while ((!charStack.empty()) && (orderOfOperations(charStack.top()) >= orderOfOperations(infix[x]))) {
                // Kalo bener lebih besar
                // math operator di pucuk stack dipush ke string postfix
                
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                    postfix += " ";
                }
                postfix += charStack.top();
                charStack.pop(); //Jangan lupa dipop
            }
            // push sisa operator yang belum ke stack
            charStack.push(infix[x]);
        }else if (infix[x] == '(') { //Kurung buka dipush tersendiri ke stack
            charStack.push(infix[x]);
 
        }else if (infix[x] == ')') { //kalo ketemu kurung tutup..
            //while ngecek selama ga empty, dan pucuk stack nya bukan kurung buka
            while ((!charStack.empty()) && (charStack.top() != '(')) {
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
                    postfix += " ";
                }
                
                postfix += charStack.top(); //Operator sebelum '(' push semua
                charStack.pop(); //Jangan lupa dipop
            }
 
            // pop '(' symbol off the stack
            if (!charStack.empty()) {
                charStack.pop();
            } else {
                //Misal ga ketemu '(' sampe akhir
                throw invalid_argument {
                    "ERROR: INVALID PARENTHESIS"
                };
            }
        } else {
            throw invalid_argument {
                "ERROR: INVALID INPUT"
            };
        }
    }
 
    //Masukin sisanya ke string postfix
    while (!charStack.empty()) {
        if (postfix.length() > 0 && !isspace(postfix.back())) { //Kalo setelah operator gaada spasi, dikasih spasi
            postfix += " ";
        }
        postfix += charStack.top(); //Masukin lagi
        charStack.pop(); //Jangan lupa dipop
    }
    return postfix;
}

#endif