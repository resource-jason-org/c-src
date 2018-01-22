#include <iostream>
#include <fstream>
#include <stdlib.h>    
using namespace std ;
int main () {
    char buffer[256];
    ifstream in("test.txt");
    if (! in.is_open())
    { cout << "Error opening file"; exit (1); }
    while (!in.eof() )
    {
        in.getline (buffer,100);
        cout << buffer << endl;
    }
     return 0;
}
