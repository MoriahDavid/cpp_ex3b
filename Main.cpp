#include <iostream>
#include <string.h>
#include "Matrix.hpp"

using namespace std;
using namespace zich;
// [0 1 2], [3 4 5], [6 7 8]

// [1 0 0], [0 1 0], [0 0 1]

int main(){

    char ans;
    string act;
    bool is_running = true;
    vector<string> my_list = {"+", "-", "*", ">", ">=", "<", "<=", "==", "!=", "++", "--"}; //++, -- after change (++x)
    vector<string> mul_opt = {"m*m", "m*n"};

    while(is_running){

        try{

            //get the FIRST mat
            cout << "Type your matrix [v1], [v2], [v3]... : ";
            Matrix m1, m2;
            try{
                cin >> m1;
            }
            catch (exception & ex) {
                cout << "invalid input: " << ex.what() << endl;
                continue;
            }

            cout << "math actions: ";
            for(unsigned int i = 0; i < my_list.size(); i++){
                cout << my_list.at(i) << " ";
            }
            cout << endl;
            cout << "Choose your matrix math action: "; // Type and press enter
            cin >> act; // Get user input for math action
            // act = "+";
            if(find(my_list.begin(), my_list.end(), act) == my_list.end()){
                cout << "invalid input: Insert only chars from the list" << endl;
                continue;
            }
            //get the SECOND mat
            if(act.compare("*") != 0 && act.compare("++") != 0 && act.compare("--") != 0){ // no need second mat
                cout << "Type your second matrix [v1], [v2], [v3]... : ";
                try{
                    cin >> m2;
                }
                catch (exception & ex) {
                    cout << "invalid input: " << ex.what() << endl;
                    continue;
                }
            }

            if(act.compare("*") == 0){ // 0 --> equals
                cout << "multiply actions: ";
                for(unsigned int i = 0; i < mul_opt.size(); i++){
                    cout << mul_opt.at(i) << " ";
                }
                cout << endl;
                cout << "Choose your mul action: "; // Type and press enter
                string m_act;
                cin >> m_act; // Get user input for math action
                //one mat
                if(m_act.compare("m*n") == 0){
                    double n;
                    cout << "Enter your num: ";
                    cin >> n;
                    cout << "the result: " << endl;
                    cout << (m1*n);
                }
                //two mats
                else if(m_act.compare("m*m") == 0){
                    cout << "Type your second matrix [v1], [v2], [v3]... : ";
                    try{
                        cin >> m2;
                    }
                    catch (exception & ex) {
                        cout << "invalid input: " << ex.what() << endl;
                        continue;
                    }
                    cout << "the result: " << endl;
                    cout << (m1*m2);
                }
            }
            else if(act.compare("+") == 0){
                cout << "the result: " << endl;
                cout << (m1 + m2);
            }
            else if(act.compare("-") == 0){
                cout << "the result: " << endl;
                cout << (m1 - m2);
            }
            else if(act.compare(">") == 0){
                cout << "the result: " << endl;
                cout << ((m1 > m2) ? "True" : "False");
            } 
            else if(act.compare(">=") == 0){
                cout << "the result: " << endl;
                cout << ((m1 >= m2) ? "True" : "False");
            }
            else if(act.compare("<") == 0){
                cout << "the result: " << endl;
                cout << ((m1 < m2) ? "True" : "False");
            }
            else if(act.compare("<=") == 0){
                cout << "the result: " << endl;
                cout << ((m1 <= m2) ? "True" : "False");

            }  
            else if(act.compare("==") == 0){
                cout << "the result: " << endl;
                cout << ((m1 == m2) ? "True" : "False");
            }
            else if(act.compare("!=") == 0){
                cout << "the result: " << endl;
                cout << ((m1 != m2) ? "True" : "False");
            }
            //one mat
            else if(act.compare("++") == 0){
                cout << "the result: " << endl;
                cout << (++m1);
            }
            else if(act.compare("--") == 0){
                cout << "the result: " << endl;
                cout << (--m1);
            }         
        }
        catch (exception & ex) {
            cout << "invalid input: " << ex.what() << endl;
            continue;
        }
        cout << endl;
        cout << "Do you want to continue calculate? (y/n) ";
        cin >> ans; // Get user answer
        if(ans == 'n'){
            is_running = false;
        }
}

}    