#include <iostream>
using namespace std;                


int main() 
{   
    char str[] = "Some\ntext\nfile!";
    
    FILE * fp;
    if ((fp = fopen("/home/user1/projects/cpp.try/my_file.txt", "w")) == NULL) {
        printf("Cannot write file.\n");
        exit(1);
    }
    else {
        for (int i = 0; str[i] != '\0'; i++)
            fputc(str[i], fp);
        fclose(fp);
    }


    FILE * pFile;       // уот так уот тут файлы читают...
    char buff[100];
    int i = 0;

    pFile = fopen ("/home/user1/projects/cpp.try/my_file.txt","r");
    if (pFile == NULL) perror ("Error opening file");
    else
    {
        do {
            buff[i] = fgetc(pFile);
            i++;
        } while (buff[i-1] != EOF);

        buff[i-1] = '\0';
        cout << buff << endl;

        fclose (pFile);
    }

    return 0;
}