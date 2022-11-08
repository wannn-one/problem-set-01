#include <iostream>
#include <stack>
using namespace std;

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

int evaluate(string postfix){
    stack<int> ns; //bikin stack dulu buat masukin angka2nya
    for (int i = 0; i < postfix.length(); i++){
        char c = postfix[i];
        if (c == ' '){ //kalo spasi diskip aja
            continue; 
        }else if(isdigit(c)){
            int n = 0;
            while (isdigit(c)){
                n = n * 10 + (int)(c - '0'); 
                // Konsepnya angka yang lebih depan itu nanti dikali 10
                // Misal 121, nanti 
                // iterasi ke-1 => n = 0 * 10 + 1
                //                 n = 1
                // iterasi ke-2 => n = 1 * 10 + 2
                //                 n = 12
                // iterasi ke-3 => n = 12 * 10 + 1
                //                 n = 121
                i++;
                c = postfix[i];
            }
            i--; 
            ns.push(n); //push angkanya ke stack
            
        }else{
            int val1 = ns.top(); ns.pop(); //Ambil 2 angka paling pucuk buat dioperasiin
            int val2 = ns.top(); ns.pop();
            switch (c){
            case '+':
                ns.push(val2 + val1);
                break;
            case '-':
                ns.push(val2 - val1);
                break;
            case '*':
                ns.push(val2 * val1);
                break;
            case '/':
                ns.push(val2 / val1);
                break;
            default:
                throw invalid_argument{
                    "ERROR: INVALID OPERATOR"
                };
                break;
            }
        }
    }
    return ns.top();
}


int main(){
    string number = "(2+3)*3-(10/5)";
    string postfix = convertInfixToPostfix(number);
    cout << convertInfixToPostfix(number) << endl;
    cout << evaluate(postfix);
    
    return 0;
}
