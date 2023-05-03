#ifndef memory
#define memory
#include <vector>
using namespace std;
class Memory{
    private:
        int n;
        int m;
        int p;
        bool * freeSpace;
        int * physicalMemory;
    
    public:
        Memory(int n, int p, int m);
        int allocate();
        void write(int address, int x);
        int read(int address);
        void deallocate(int address);
        ~Memory();
};
#endif