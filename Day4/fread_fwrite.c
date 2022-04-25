#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MAX_LEN 100
#define MAX_SZ 20
typedef struct ElementType{
    char name[MAX_LEN];
    int age;
} Element;
void PrintMenu(){
    printf("ALL COMMANDS\n");
    printf("1. Create\n");
    printf("2. Load all\n");
    printf("3. Extend\n");
    printf("4. Read at\n");
    printf("5. Split File\n");
    printf("6. Merge File\n");
    printf("7. Quit\n");
}
void readFileName(char *filename){
    printf("Enter file name: ");
    scanf("%s", filename);
}
void executeCreate(){
    char filename[MAX_LEN];
    readFileName(filename);
    FILE *fp = fopen(filename, "wb");
    fclose(fp);
}
bool checkFileReadable(char *filename){
    FILE *fp = fopen(filename, "rb");
    bool readable = (fp == NULL);
    fclose(fp);
    return !readable;
}
void executeLoad(){
    char filename[MAX_LEN];
    readFileName(filename);
    if (!checkFileReadable(filename)){
        printf("Cannot open %s for reading\n", filename);
        return;
    }
    FILE *fp = fopen(filename, "rb");
    Element elmArr[MAX_SZ];
    while (true){
        int sz = fread(elmArr, sizeof(Element), MAX_SZ, fp);
        for (int i = 0; i < sz; ++i){
            printf("Name: %s. Age: %d\n", elmArr[i].name, elmArr[i].age);
        }
        if (sz < MAX_SZ) break;
    }
    fclose(fp);

}
void executeExtend(){
    char filename[MAX_LEN];
    readFileName(filename);
    Element elm;
    if (!checkFileReadable(filename)){
        printf("Cannot open %s for appending\n", filename);
        return;
    }
    FILE *fp = fopen(filename, "ab");
    printf("Enter name: ");
    scanf("%s", elm.name);
    printf("Enter age: ");
    scanf("%d", &elm.age);
    fwrite(&elm, sizeof(Element), 1, fp);
    fclose(fp);
}
void executeReadAt(){
    char filename[MAX_LEN];
    readFileName(filename);
    if (!checkFileReadable(filename)){
        printf("Cannot open %s for reading\n", filename);
        return;
    }
    FILE *fp = fopen(filename, "rb");
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    Element elm;
    fseek(fp, sizeof(Element) * index, SEEK_SET);
    int sz = fread(&elm, sizeof(Element), 1, fp);
    if (sz == 0) {
        printf("Cannot read element at index %d\n", index);
        return;
    }
    printf("Name: %s. Age: %d\n", elm.name, elm.age);

}
void executeSplit(){
    char filename[MAX_LEN];
    readFileName(filename);
    if (!checkFileReadable(filename)){
        printf("Cannot open %s for reading\n", filename);
        return;
    }
    FILE *fp = fopen(filename, "rb");
    char filename1[MAX_LEN], filename2[MAX_LEN];
    strcpy(filename1, filename);
    strcat(filename1, "_1");
    strcpy(filename2, filename);
    strcat(filename2, "_2");
    FILE *fp1 = fopen(filename1, "wb"), *fp2 = fopen(filename2, "wb");
    int n;
    printf("Enter number of element in the first file: ");
    scanf("%d", &n);
    while (n--){
        Element elm;
        int sz = fread(&elm, sizeof(Element), 1, fp);
        if (sz == 0)
            break;
        fwrite(&elm, sizeof(Element), 1, fp1);
    }
    while (true){
        Element elm;
        int sz = fread(&elm, sizeof(Element), 1, fp);
        if (sz == 0) break;
        fwrite(&elm, sizeof(Element), 1, fp2);
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}
bool runProgram(){
    printf("Choose a function: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 7) return false;
    switch (choice)
    {
    case 1:
        executeCreate();
        break;
    case 2:
        executeLoad();
        break;
    case 3:
        executeExtend();
        break;
    case 4:
        executeReadAt();
        break;
    case 5:
        executeSplit();
    default:
        printf("Invalid choice, the program will be terminated!\n");
        return false;
    }
    return true;
}
int main(){
    PrintMenu();
    while (runProgram());
    return 0;
}