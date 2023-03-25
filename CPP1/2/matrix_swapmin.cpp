// Реализуйте функцию swap_min, которая принимает на вход двумерный массив целых чисел, ищет в этом массиве строку, 
// содержащую наименьшее среди всех элементов массива значение, и меняет эту строку местами с первой строкой массива.

// Подумайте, как обменять строки массива, не обменивая элементы строк по-отдельности. 

#include <iostream>
#include <ctime>        // инициировать srand()
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
    srand(time(0));
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

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    int min = 1U << (8*sizeof(1U) - 1) - 1;
    int min_row = 0;

    for (int i = 0 ; i < rows; ++i)
        for (int j=0; j < cols; ++j)
            if (m[i][j] < min) {
                min = m[i][j];
                min_row = i;
            }

    int * tmp = m[0];
    m[0] = m[min_row];
    m[min_row] = tmp;
}

int main() 
{  
    unsigned r = 5;
    unsigned c = 3;

    int ** M = create_array2d(r, c);

    cout << "M = \n";
    rand_array(M, r, c);
    print_array(M, r, c);

    swap_min(M, r, c);
    
    cout << "\nM = \n";
    print_array(M, r, c);

    return 0;
}

