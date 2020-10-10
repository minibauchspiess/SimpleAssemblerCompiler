#include "preprocessClass.h"



preprocessClass::preprocessClass(string inFileName){
    //Recupera o nome, sem a extensao
    string rawInFileName = inFileName.substr(0, inFileName.find_last_of('.'));  //Mesma string ate a ultima ocorrencia de '.'

    //Abre os arquivos de leitura e de saida (preprocessado)
    inputFile.open(inFileName);
    ppFile.open(rawInFileName+".pre");
    
    //Inicializa a flagInit como 1 (objeto acaba de ser criado, nenhuma passagem por linha foi feita)
    flagInit = true;


}

preprocessClass::~preprocessClass(){
    //Fecha os arquivos
    inputFile.close();
    ppFile.close();
}


void preprocessClass::Run(){

    string line;

    //Pega linha

    //Normaliza a linha (o normalizador pega mais linhas, se preciso)

    //Separa os tokens

    //Identifica se ha uma diretiva pelos tokens e a executa, se houver

    //Realiza o preprocessamento enquanto o arquivo nao chega ao fim
    while (!inputFile.eof()){
        //Busca uma linha normalizada de codigo
        line = StandardLine();




    }
    
   

}

//Funcoes de normalizacao
string preprocessClass::StandardLine(){
string stdLine, line;

//Pega a proxima linha para padronizar
getline(inputFile, line);

//Apaga o comentario que houver, para analisar a linha sem comentario
line = EraseComment(line);

//Caso seja uma linha vazia, a desconsidera e busca a seguinte
while(EmptyLine(line)){
    getline(inputFile, line);
    line = EraseComment(line);
}

stdLine = line;

//Caso haja um label dividido em mais de uma linha, mistura mais de uma linha na linha final
if(LabelSplited(line)){
    //Busca nas proximas linhas ate encontrar uma nao vazia
    do{
        getline(inputFile, line);
        line = EraseComment(line);
    }while(EmptyLine(line));
    stdLine.append(" "+line);
}

//Remove todos os espacos desnecessarios da linha criada
stdLine = SingleSpaced(stdLine);

//Torna todas as letras maiusculas
stdLine = MakeUpper(stdLine);

return stdLine;
}

string preprocessClass::EraseComment(string line){
//Busca a posicao de ';' na string
size_t comentPos = line.find_first_of(';');

//Caso tenha encontrado, apaga tudo que esta escrito apos o ';'
if(comentPos != string::npos){
    line.erase(comentPos);
}

//Retorna a linha reduzida
return line;
}

bool preprocessClass::EmptyLine(string line){
//Percorre a string procurando algum char diferente de ' '
size_t pos = line.find_first_not_of(' ');

//Caso nao tenha encontrado, retorna que a linha esta vazia (true)
if(pos == string::npos){
    return true;
}
//Caso contrario, a linha nao esta vazia
else{
    return false;
}
}

bool preprocessClass::LabelSplited(string line){
//Detecta a presenca de um label (indicado pela presenca de ':')
size_t labelPos = line.find_first_of(':');

//Caso nao tenha achado nenhuma label, a linha ja nao estara dividida
if(labelPos == string::npos){
    return false;
}

//Caso tenha encontrado uma label, verifica se ha algo escrito apos ela
size_t comPos = line.find_first_not_of(' ', labelPos+1);

//Caso haja um comando depois da label, a linha nao esta dividida
if(comPos != string::npos){
    return false;
}
//Caso contrario, o resto do comando esta em linhas posteriores
else{
    return true;
}
}

string preprocessClass::SingleSpaced(string line){
//Char que percorre a string comparando cada elemento seu
char c, lastC = 'a';

//Indice que percorre a string
size_t pos = line.find_first_not_of(' ');

//String compactada, de saida
string outString;

//Percorre a string enquanto ainda houverem elementos em seu interior a serem analisados
while ((pos <= line.length()) && (pos != string::npos)){
    c = line[pos];  //Busca novo valor a ser analizado

    //Dependendo do char lido, o padrao de tirar linhas podera ser diferente
    if((c == ':') || (c == ',')){   //Sem espacos antes, com espaco depois, pula para o proximo item
        outString.push_back(c);
        outString.push_back(' ');

        lastC = c;
        pos = line.find_first_not_of(' ', pos+1);
    }
    else if(c == ' '){  //Nao insere, pula para o proximo valor que nao e espaco
        lastC = c;
        pos = line.find_first_not_of(' ', pos+1);
    }
    else if(lastC == ' '){  //Se for uma letra ou _ e anteriormente tiver tido um ' ', insere o espaco e a letra, e segue adiante
        outString.push_back(' ');
        outString.push_back(c);

        lastC = c;
        pos++;
    }
    else{   //Se for uma letra, e o ultimo valor lido nao for um espaco, apenas insere o espaco
        outString.push_back(c);

        lastC = c;
        pos++;
    }

}

//Retorna a string montada
return outString;

}

string preprocessClass::MakeUpper(string line){
    locale loc;
    for(uint i=0; i<line.length(); i++){
        line[i] = toupper(line[i], loc);
    }
    return line;
}



//Funcoes de execucao de diretivas
void preprocessClass::ExeDirective(string line){
    
}


