
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <locale>
#include <map>
#include <vector>

#include "preprocessClass.h"

using namespace std;


#define POS 13

int main(int argc, char* argv[]){

    //Caso passe uma diretiva de compilacao (-p ou -o), executa somente a etapa requerida
    if(argc==3){
        string fileName(argv[2]);

        string ppCommand="-p", mComannd = "-o";

        //Caso seja -p, apenas preprocessamento eh feito, fileName eh um .asm
        if(argv[1] == ppCommand){
            preprocessClass ppObj(fileName);
            ppObj.Run();
            ppObj.~preprocessClass();
        }
        //Caso seja -o, apenas montagem, filename eh um .pre
        else if(argv[1] == mComannd){
            //mounterClass mountObj(fileName);
            cout<<"Falta montar"<<endl;
        }
    }
    //Caso nao haja uma diretiva de compilacao, preprocessa e compila
    else{
        string fileName(argv[1]), ppFileName;

        //Preprocessa
        preprocessClass ppObj(fileName);
        ppFileName = ppObj.Run();
        ppObj.~preprocessClass();

        //Monta
        //mounterClass mountObj(fileName);
        cout<<"Montando com arquivo "<<ppFileName<<endl;
        
    }
    /*string fileName(argv[2]);
    preprocessClass ppObj(fileName);
    string aux = ppObj.Run();
    ppObj.~preprocessClass();*/
    return 1;
}