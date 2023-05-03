#include "hashTable.hpp"
#include "memory.hpp"
#include <iostream>
#include <string> 
using namespace std;
int main();
int main(){
    string cmd;
    string state;
    int n;
    int p;
    unsigned int PID;
    int ADDR; 
    int x;
    bool check;
    HashTable * map;
    while (cin >> cmd){
        if (cmd == "OPEN"){
            state = "OPEN";
        }else if (cmd == "ORDERED"){
            state = "ORDERED";
        }else if (cmd == "M"){
            cin >> n;
            cin >> p;
            map = new HashTable(n,p,state);
            cout << "success" << endl;
        }else if (cmd == "INSERT"){
            cin >> PID; 
            check = map->insert(PID);
            if (check){
                cout << "success" << endl;
            }else{
                cout << "failure" << endl;
            }
        }else if (cmd == "SEARCH"){
            cin >> PID;
            int position = map->search(PID);
            if (position == -1){
                cout << "not found" << endl;
            }else{
                cout << "found " << PID << " in " << position << "" << endl;
            }
        }else if (cmd == "WRITE"){
            cin >> PID;
            cin >> ADDR;
            cin >> x;
            check = map->write(PID, ADDR, x);
            if (check){
                cout << "success" << endl;
            }else{
                cout << "failure" << endl;
            }
        }else if (cmd == "READ"){
            cin >> PID;
            cin >> ADDR;
            int val = map->read(PID, ADDR);
            if (val != -1){
                cout << ADDR << " " << val << endl;
            }else{
                cout << "failure" << endl;
            }
        }else if (cmd == "PRINT"){
            cin >> x;
            map->print(x);
        }else if (cmd == "DELETE"){
            cin >> PID;
            check = map->del(PID);
            if (check){
                cout << "success" << endl;
            }else{
                cout << "failure" << endl;
            }
        }else if (cmd == "END"){
            delete map;
            break;
        }
    }
    return 0;
}