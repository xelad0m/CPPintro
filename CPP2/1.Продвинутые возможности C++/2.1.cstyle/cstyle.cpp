#include <iostream>


int main() {
    int a = 2;
    int b = 3;

    double size = ((double) a) / b * 100;

    void * data = malloc(sizeof(double) * int(size));

    double * array = (double *) data;

    char * bytes = (char *) array;

    return 0;
}
