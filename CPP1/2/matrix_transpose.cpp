// Напишите функцию, которая принимает на вход целочисленную матрицу M (другими словами, просто двумерный 
// целочисленный массив) размера rows×cols, и возвращает транспонированную матрицу MT (тоже двумерный целочисленный 
// массив) размера cols×rows. Если в M на пересечении i-ой строки и j-ого столбца стояло число x, то на пересечении  
// j-ой строки и i-ого столбца в матрице MT тоже будет стоять число x, или другими словами MT[j][i]=M[i][j].

// Обратите внимание, что вам неизвестно, каким именно способом выделялась память для массива M. Выделять память под
// массив MT можете любым удобным вам способом. Изменять исходную матрицу нельзя. 

#include <iostream>
using namespace std;

int ** create_array2d(unsigned rows, unsigned cols)     // инициализируется нулями
{
    int ** m = new int *[rows];
    m[0] = new int[rows * cols];
    for (unsigned i = 1; i != rows; ++i)
        m[i] = m[i - 1] + cols;
    return m;
}

void free_array2d(int ** m) 
{
    delete [] m[0];
    delete [] m;
}

void rand_array(int ** m, unsigned rows, unsigned cols) 
{
    for (int i = 0 ; i < rows; ++i)
        for (int j=0; j < cols; ++j)
             m[i][j] = rand() % (rows * cols) + 1;      // rand() => 0..RAND_MAX
}

void print_array(int ** m, unsigned rows, unsigned cols) 
{
    for (int i = 0 ; i < rows; ++i) {
        for (int j=0; j < cols; ++j)
            printf("%3d ", m[i][j]);
        printf("\n");
    }
}

int ** transpose(const int * const * m, unsigned rows, unsigned cols)
{   
    int ** M = create_array2d(cols, rows);

    for (int i = 0 ; i < rows; ++i)
        for (int j=0; j < cols; ++j)
            M[j][i] = m[i][j];

    return M;
}


int main() 
{  
    unsigned r = 3;
    unsigned c = 4;

    int ** M = create_array2d(r, c);

    cout << "M:\n";
    rand_array(M, r, c);
    print_array(M, r, c);

    int ** MT =  transpose(M, r, c);
    
    cout << "\nMT:\n";
    print_array(MT, c, r);

    return 0;
}