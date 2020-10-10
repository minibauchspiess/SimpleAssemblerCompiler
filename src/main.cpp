
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <locale>
#include <map>

#include "teste.h"
#include "passages.h"
#include "preprocessClass.h"

using namespace std;


int main(int argc, char* argv[]){
    string fileName(argv[1]);
    preprocessClass ppObj(fileName);
    /*ppObj.Run();*/
    string a = "  ajnf :     af      a  e  ,   oak ,      a ";
    map<string, string> mapa = {{"uno", "1"}};
    
    string msg="haha";
    try
    {
        msg = mapa.at("uno");
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    cout<<msg<<endl;
    ppObj.~preprocessClass();
    return 1;
}