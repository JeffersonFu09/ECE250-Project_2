#ifndef hashTable
#define hashTable
#include "process.hpp"
#include "memory.hpp"
#include <string>
using namespace std;


class HashTable{
    private:
        int n;
        int p;
        int m;
        vector<Process> *hashMap;
        string state;
        Memory * memorySpace;
        
    public:
        HashTable(int n, int p, string state );
        bool insert(unsigned int PID);
        int search(unsigned int PID);
        bool write(unsigned int PID, int ADDR, int x);
        int read(unsigned int PID, int ADDR);
        bool del(unsigned int PTD);
        void print(int position);
        int secondaryHash(unsigned int PID);
        ~HashTable();
};
#endif