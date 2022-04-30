#include <iostream>   
#include <cstring> 
using namespace std;                

int main() 
{   
    // NOT
    unsigned char var = 153;            // 10011001
    unsigned char not_var = ~var;       // 01100110    = 102
    cout << (int)not_var << endl;


    // AND
    unsigned char flags = 13;           // 00001101
    unsigned char mask = 5;             // 00000101
    
    unsigned char res = flags & mask;   // 00000101
    cout << (int)res << endl;
    
    if ((flags & mask) == mask) cout << "All mask bits are ON\n";   // ПРОВЕРЯЕТ биты по маске
    else cout << "Some mask bit(s) OFF\n";

    res = flags & ~mask;                // ВЫКЛЮЧАЕТ биты по маске
    flags &= ~mask;                     // аналогично с присвоением

    // OR
    flags = 8;                          // 00001000
    mask = 5;                           // 00000101

    res = flags | mask;                 // ВКЛЮЧАЕТ биты по маске   = 13 
    flags |= mask;                      // т.е. складывает числа
    cout << (int)flags << endl;

    // XOR
    flags = 9;                          // 00001001
    mask = 1;                           // 00000001
    
    flags = flags ^ mask;               // РЕВЕРСИТ биты по маске   = 8
    flags ^= mask;                      // опять 9
    cout << (int)flags << endl;

    // XOR шЫфр (например, защита по паролю архиватора zip - пароль это ключ)
    char msg[] = "Привет мир!";
    unsigned char key = 177;

    for (int i = 0; i < strlen(msg); ++i) 
        msg[i] ^= key;
    cout << msg << endl;

    for (int i = 0; i < strlen(msg); ++i) 
        msg[i] ^= key;
    cout << msg << endl;

    // << >> - битовый сдвиг (целочисленное деление/умножение на 2**n)
    unsigned char x = 160;              // 10100000
    x = x >> 1;                          // 01010000     =160/(2**1)=80
    x = x >> 1;                          // 00101000     =80/(2**1)=40
    x = x >> 2;                          // 00001010     =40/(2**2)=10
    
    return 0;
}