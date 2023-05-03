#ifndef process
#define process
using namespace std;

class Process{
    private:
        unsigned int pid; 
        int startAdd;
    public: 
        Process(unsigned int pid, int startAdd);
        unsigned int getPID();
        int getStartAddress();
};
#endif