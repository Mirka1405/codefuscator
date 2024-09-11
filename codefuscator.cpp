#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

bool isCyrillicCompatible(char c){
    for(char i: "aAeEToOxXyKHcCM")
        if(c==i) return true;
    return false;
}
void cyrillifyToOut(char c,std::ostream& o){
    switch (c){
        case 'a': o<<(unsigned char[]){0xe2, 0x80, 0x8b, 0xd0, 0xb0, 0x00};break;
        case 'A': o<<(unsigned char[]){0xd0,0x90, 0x00};break;
        case 'e': o<<(unsigned char[]){0xd0,0xb5, 0x00};break;
        case 'E': o<<(unsigned char[]){0xd0,0x95, 0x00};break;
        case 'T': o<<(unsigned char[]){0xd0,0xa2, 0x00};break;
        case 'o': o<<(unsigned char[]){0xd0,0xbe, 0x00};break;
        case 'O': o<<(unsigned char[]){0xd0,0x9e, 0x00};break;
        case 'x': o<<(unsigned char[]){0xd1,0x85, 0x00};break;
        case 'X': o<<(unsigned char[]){0xd0,0xa5, 0x00};break;
        case 'y': o<<(unsigned char[]){0xd1,0x83, 0x00};break;
        case 'K': o<<(unsigned char[]){0xd0,0x9a, 0x00};break;
        case 'H': o<<(unsigned char[]){0xd0,0x9d, 0x00};break;
        case 'c': o<<(unsigned char[]){0xd1,0x81, 0x00};break;
        case 'C': o<<(unsigned char[]){0xd0,0xa1, 0x00};break;
        case 'M': o<<(unsigned char[]){0xd0,0x9c, 0x00};break;
    }
}
float randFloat(){return ((double) rand() / (RAND_MAX));}
int getArg(char*& argstr, float& argval){
    if(argval>0) {
        std::cout<<"Error: argument provided twice"<<std::endl;
        return 1;
    }
    if(strlen(argstr)==1){
        argval=0.3;
        return 0;
    }
    argval=std::stof(argstr+1);
    return 0;
}
int main(int argc, char** argv){
    if(argc<4){
        std::cout<<"Arguments: codefuscator <input file> <output file> <options>\noptions may contain any combination of the following:\ng - replace semicolons with greek question marks\nz - randomly place ZWSP characters\nc - turn compatible latin letters into cyrillic\nAfter an option write a number to set the probability (0 to 1, default: 0.3)\nPossible syntax: codefuscator in.txt out.txt g0.5 c1"<<std::endl;
        return 0;
    }
    std::srand(std::time(nullptr));

    const unsigned char greek_question[] = {0xcd, 0xbe, 0x00};
    const unsigned char zero_w_space[] = {0xe2, 0x80, 0x8b, 0x00};
    
    // option parsing
    float greek = 0;
    float zwsp = 0;
    float cyril = 0;
    for(int o=3;o<argc;o++){
        switch(argv[o][0]){
            case 'c':
                getArg(argv[o],cyril);
                break;
            case 'z':
                getArg(argv[o],zwsp);
                break;
            case 'g':
                getArg(argv[o],greek);
                break;
            default:
                std::cout << "Error: unknown argument"<<std::endl;
        }
    }

    // start parsing file
    std::ifstream inputfile(argv[1]);
    std::ofstream outputfile(argv[2]);
    int unicode = 0; // prevent zwsp breaking unicode chars

    while(true){
        char c = inputfile.get();
        if(inputfile.eof()) break;
        unsigned char uni_c = c;
        if(unicode==0&&uni_c&0b10000000){
            for(int i=0;i<7;i++){
                uni_c<<=1;
                if(uni_c&0b10000000==0) break;
                unicode++;
            }
        }
        if(unicode>0) {unicode--;outputfile<<c;}
        else{
            if(randFloat()<zwsp) outputfile<<zero_w_space;
            if(c==';'&&randFloat()<greek) outputfile<<greek_question;
            else if(isCyrillicCompatible(c)&&randFloat()<cyril) cyrillifyToOut(c,outputfile);
            else outputfile<<c;
        }
    }
}