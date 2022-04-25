#include<stdio.h>
#include<ctype.h>
void CharReadWrite(FILE *fin, FILE *fout){
    int c;
    while ((c = fgetc(fin)) != EOF){
        if (isupper(c)){
            c = tolower(c);
        } else if (islower(c)){
            c = toupper(c);
        }
        fputc(c, fout);
        putchar(c);
    }
    putchar('\n');
}
int main(){
    FILE *fin = fopen("FIN.INP", "r"), *fout = fopen("FOUT.OUT", "w");
    CharReadWrite(fin, fout);
}