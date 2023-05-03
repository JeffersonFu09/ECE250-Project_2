#include "hashTable.hpp"
#include <iostream>
using namespace std;

HashTable::HashTable(int n, int p, string state){
    this->n = n;
    this->p = p;
    this->m = n/p;
    memorySpace = new Memory(n, p, m);
    hashMap = new vector<Process>[m];
    this->state = state;
}

bool HashTable::insert(unsigned int PID){
    int location = search(PID);
    if (location !=-1 ){
        return false;
    }
    int newStartingAddress = memorySpace->allocate();
    if (newStartingAddress == -1){
        return false;
    }

    Process currPID = Process(PID, newStartingAddress); 
    int hashValue = (PID) % m;
    if (state == "ORDERED" ){
        for (int i =0 ; i < hashMap[hashValue].size(); i++){
            if (hashMap[hashValue][i].getPID() < PID){
                hashMap[hashValue].insert(hashMap[hashValue].begin()+i,currPID);
                return true;
            }
        }
        hashMap[hashValue].push_back(currPID);
    }else{
        int offSet = secondaryHash(PID);
        while(!hashMap[hashValue].empty()){
            hashValue = (hashValue + offSet) % m;
        }
        hashMap[hashValue].push_back(currPID);
    }

    return true;
}
int HashTable::search(unsigned int PID){
    int hashValue = (PID) % m;
    if (this->state == "ORDERED"){
        for(int i = 0; i< hashMap[hashValue].size(); i++){
            if (hashMap[hashValue][i].getPID() == PID){
                return hashValue;
            } 
        }
    }else{
        int originalHashValue= hashValue;
        if (!hashMap[hashValue].empty()){
            if (hashMap[hashValue][0].getPID() == PID){
                return hashValue;
            }
        }
        int offSet = secondaryHash(PID); 
        hashValue = (hashValue + offSet) % m;
        while(hashValue != originalHashValue){
            if(!hashMap[hashValue].empty()){   
                if(hashMap[hashValue][0].getPID() == PID){
                    return hashValue;
                }
            }
            hashValue = (hashValue + offSet) % m;
        }
    }
    return -1;
}

bool HashTable::write(unsigned int PID, int ADDR, int x){
    int location = search(PID);
    int hashValue =(PID) % m;
    int currStartingAddr;
    if (location == -1){
        return false;
    }
    if (this->state == "ORDERED"){
        if(ADDR >= p || ADDR <0){
            return false;
        }
        for (int i = 0; i < hashMap[location].size(); i++){
            if (hashMap[location][i].getPID() == PID){
                currStartingAddr = hashMap[location][i].getStartAddress()+ADDR;
                break;
            }
        }
        memorySpace->write(currStartingAddr, x);
        return true;
    }else{
        if(ADDR >= p || ADDR <0){
            return false;
        }
        currStartingAddr = hashMap[location][0].getStartAddress() + ADDR;
        memorySpace->write(currStartingAddr, x);
        return true;
    }
}

int HashTable::read(unsigned int PID, int ADDR){
    int location = search(PID);
    int currStartingAddr = 0;
    if (location == -1){
        return -1;
    }
    if (this->state == "ORDERED"){
        if (ADDR >= p || ADDR < 0){
            return -1;
        }
        for (int i =0 ; i < hashMap[location].size(); i++){
            if(hashMap[location][i].getPID()==PID){
                currStartingAddr = hashMap[location][i].getStartAddress() + ADDR;
            }
        }
        return memorySpace->read(currStartingAddr);
    }else{
        if (ADDR >= p || ADDR < 0){
            return -1;
        }
        int currStartingAddr = hashMap[location][0].getStartAddress() + ADDR;
        return memorySpace->read(currStartingAddr);
    }
}

bool HashTable::del(unsigned int PID){
    int location = search(PID);
    if(location == -1 ){
        return false;
    }
    if (state == "ORDERED"){
        for (int i = 0; i < hashMap[location].size(); i++){
            if(hashMap[location][i].getPID() == PID){
                int deletingAddress = hashMap[location][i].getStartAddress();
                hashMap[location].erase(hashMap[location].begin()+i);
                memorySpace->deallocate(deletingAddress);
            }
        }
    }else{
        int currStartingAddr = hashMap[location][0].getStartAddress();
        hashMap[location].erase(hashMap[location].begin());
        memorySpace->deallocate(currStartingAddr);
    }
    return true;
}

void HashTable::print(int position){
    if(hashMap[position].empty()){
        cout << "chain is empty" << endl;
        return;
    }
    for (int i = 0; i < hashMap[position].size(); i++){
        cout<< hashMap[position][i].getPID() << " ";
    }
    cout << endl;
}

int HashTable::secondaryHash(unsigned int PID){
    int offSet= (PID / m) % m; 
    if (offSet % 2 ==0){
        return offSet +1;
    } else {
        return offSet;
    }
}

HashTable::~HashTable(){
    delete memorySpace;
    delete []hashMap;
}