#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std ;
int main () {
   /* ofstream out("out.txt"); 
   if (out.is_open()) 
   {
        out << "This is a line." << endl;
        out << "This is another line." << endl;
        out.close();
    }
   */
    ofstream outfile;
    outfile.open("out.txt", ios::app);
    if(!outfile) //检查文件是否正常打开//不是用于检查文件是否存在
   {
   cout<<"abc.txt can't open"<<endl;
   abort(); //打开失败，结束程序
   }
    else
   {
    outfile << "world" << endl;
    outfile.close();
   }


    return 0;
}
