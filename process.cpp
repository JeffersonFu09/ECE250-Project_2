#include <iostream>
#include "process.hpp" 

// Will probably not need start add as a parameter and just calculate it?
Process::Process(unsigned int pid, int startAdd){
    this->pid = pid;
    this->startAdd = startAdd;
}

int Process::getStartAddress(){
    return this->startAdd;
}