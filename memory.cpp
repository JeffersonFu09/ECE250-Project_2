#include "memory.hpp"
#include <iostream>
using namespace std;
Memory::Memory(int n, int p, int m){
    this->n = n;
    this->p = p;
    this->m = m;
    this-> freeSpace = new bool [m] {false};
    this-> physicalMemory = new int [n];    

}

int Memory::allocate(){
    for(int i =0; i< m;i++){
        if (freeSpace[i] == false){
            freeSpace[i]=true;
            return i*p;
        }
    }

    return -1;
}
void Memory::write(int addr, int x){
    physicalMemory[addr] = x;
};

int Memory::read(int addr){
    return physicalMemory[addr];
}
void Memory::deallocate(int addr){
    freeSpace[addr/p] = false;    
}

Memory::~Memory(){
    delete []freeSpace;
    delete []physicalMemory;
}