#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXLEN 256
#define MAXELM 20
typedef struct 
{
    char name[MAXLEN], email[MAXLEN];
} studentProfile;
struct node {
    studentProfile profile;
    struct node *next;
};
typedef struct node LinkedList;
int main(){
    char filename[] = "binaryfile";
    FILE *fp = fopen(filename, "wb");
    studentProfile profile[] = {{"a student", "std1.com"}, {"another student", "std2.com"}};
    fwrite(profile, sizeof(studentProfile), 2, fp);
    fclose(fp);
    studentProfile readProfile[MAXELM];
    fp = fopen(filename, "rb");
    int read = fread(readProfile, sizeof(studentProfile), MAXELM, fp);
    printf("READ: %d\n", read);
    for (int i = 0; i < read; ++i){
        printf("%s ??? %s\n", readProfile[i].name, readProfile[i].email);
    }
    return 0;
}
