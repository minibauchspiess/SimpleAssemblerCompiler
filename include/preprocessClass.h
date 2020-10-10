#pragma once

#include <fstream>  //Bib para leitura e escrita de arquivos
#include <string.h>
#include <iostream>
#include <locale>
#include <map>

#include <unistd.h>


using namespace std;
#define CLINE_SIZE 160 //Maior qtd de chars em uma linha oficial (variaveis e rotulos de 50, comando copy)



/*
 *** Classe que lida com o preprocessamento de um arquivo .asm ***

 * Recebe como argumento o nome do arquivo com o codigo assembly
 * 
 * Realiza as operacoes de preprocessamento:
 *  - Regulariza cada linha:
 *      -- Retira tudo que vem depois do comentario
 *      -- Desconsidera linhas e em branco
 *      -- Junta linhas de label com comando, se necessario
 *      -- Retira espacos desnecessarios
 *      -- Torna tudo upper case
 *  - Executa as diretivas:
 *      -- EQU: mapeia a label com seu valor, desconsidera a linha
 *      -- IF: executa a comparacao e pega a proxima linha. Desconsidera a primeira linha, insere a seguinte somente se verdadeiro
 *      -- MACRO: gera a Macro Name Table (MNT) e a Macro Definition Table (MDT). Desconsidera linhas ate ENDMACRO
 *  - Substitui EQU por seu valor da tabela, se houver
 *  - Expande a macro, se houver
 *  - Insere o resultado das operacoes acima em um arquivo .pre
*/
class preprocessClass
{
private:

    //Arquivos manipulados
    ifstream inputFile;  //Arquivo original assembly, .asm
    ofstream ppFile;     //Arquivo preprocessado, .pre

    

    //Flag de inicializacao do objeto. '\n' deve ser inserido apenas a partir da 2 linha
    bool flagInit;

public:

    //Inicializador e destrutor. Abrem e fecham arquivos, setam flags
    preprocessClass(string inFileName);
    ~preprocessClass();

    //Principal funcao. Percorre o arquivo inteiro, fazendo as adaptacoes necessarias
    void Run();

    //Recebe uma linha do codigo, e retorna uma linha na forma padronizada
    string StandardLine();

    //Funcoes auxiliares de StandardLine
    string EraseComment(string line);   //Retorna a linha excluindo tudo escrito apos a ocorrencia de ';' (comentario)
    bool EmptyLine(string line);    //Indica se a linha esta vazia, ou contem apenas espacos
    bool LabelSplited(string line); //Indica se a linha possui apenas um label, com o comando inserido em outra linha
    string SingleSpaced(string line);   //Retira todos os espacos excessivos da linha
    string MakeUpper(string line);  //Converte todos os caracteres da linha para upper case


    //Executa a diretiva, se houver uma na linha. Essa funcao que insere as linhas no arquivo preprocessado
    void ExeDirective(string line);


};

