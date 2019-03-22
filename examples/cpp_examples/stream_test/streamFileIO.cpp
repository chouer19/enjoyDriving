#include <iostream>
#include <fstream>
 
using namespace std;
 
int main()
{
        ofstream ofs("a.txt",ios::app);
        if(ofs.good())
        {
                ofs<<"Hello a.txt, I'm appending this on you.";
        }
        return 0;
}
