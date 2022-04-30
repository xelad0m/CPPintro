#include "pch.h"                    

#include<iostream>                  
using namespace std;                

#define N 10

void bubble_sort(short arr[], short n, bool reverse = false) {
    for (int i = 0; i < (n - 1); ++i) {
        short min = arr[i];
        short pos = i;

        for (int j = i + 1; j < n; ++j) {
            if (reverse == true) 
                if (min < arr[j]) {                 // по убыванию
                    pos = j;
                    min = arr[j];
                }
            if (reverse == false)
                if (min > arr[j]) {                 // по возрастанию
                    pos = j;
                    min = arr[j];
                }
        }
        short t = arr[i];
        arr[i] = arr[pos];
        arr[pos] = t;
    }
}


int main() 
{
    int powers[4] = {1, 2, 4, 6};       // init
    int data[] = {2, 4, 16, 32};        // init
    // int data[]                       // WRONG

    float y[N], k = 0.5, b = 2;
    for (int x = 0; x < N; ++x)
        y[x] = k * x + b;
    
    for (int x = 0; x < N; x++)         // x++ или ++x здесь неважно
        cout << y[x] << " ";
    
    int n = sizeof(y)/sizeof(int);      // 100*4 / 4
    cout << "\nSize of y: " << n << endl;

    short E[N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i == j) E[i][j] = 1;
            else E[i][j] = 0;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << E[i][j] << " ";
        cout << endl;        
    }
        
    // bubble_sort
    short arr[] = {5,3,4,1,6,2};
    short n1 = sizeof(arr)/sizeof(short);
    bubble_sort(arr, n1);
   

    for (int i = 0; i < n1; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}