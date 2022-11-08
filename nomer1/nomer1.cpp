#include <iostream>
#include <stack>
#include <queue>
using namespace std;

bool validate(string br){
    stack<char> s;
    queue<char> error;
    
    if (br.length() % 2 == 0){ //cek apakah panjang kurung genap, kalo ganjil udah pasti salah
        for (int i = 0; i < br.length(); i++){
            if (s.empty()){ //Kalo kosong tinggal push aja
                s.push(br[i]);
            }else if((s.top() == '(' && br[i] == ')') || (s.top() == '{' && br[i] == '}') || (s.top() == '[' && br[i] == ']')){
                //Kalo ketemu pasangannya pas tranversing, di pop
                s.pop();
            }else{
                if (br.length() / 2 <= i){ 
                    // kalo ga ketemu pasangannya dan udah 1/2 tranversing, dan 
                    // ga ketemu kurung tutup yang bener, masuk ke queue buat informasi error
                    if ((s.top() == '(' && br[i] != ')') || (s.top() == '{' && br[i] != '}') || (s.top() == '[' && br[i] != ']')){
                        error.push(br[i]); 
                    }
                    
                }else{
                    //kalo gaada apa2, push aja
                    //antisipasi kurung yang sama 2 kali, cont : (()) atau {{}}
                    s.push(br[i]); 

                }
            }
        }
    }else{
        throw invalid_argument {"ERROR: UNEQUAL AMOUNT OF BRACKETS"};
    }

    while (!error.empty()){ //keluarin semua kurung yg ga bener dari queue
        cout << "Kurung " << error.front() << " tidak dibuka!" << endl;
        error.pop();
    }
    

    if (s.empty()){
        return true;
    }
    return false;
}

int main(){
    string brackets;
    cin >> brackets; //(), {}, []
    if(validate(brackets)){
        cout << "BALANCED" << endl; 
    }else{
        cout << "INBALANCED" << endl;
    }

    return 0;
}