// Реализуйте функцию getline, которая считывает поток ввода посимвольно, пока не достигнет конца потока 
// или не встретит символ переноса строки ('\n'), и возвращает C-style строку с прочитанными символами.

// Обратите внимание, что так как размер ввода заранее неизвестен, то вам нужно будет перевыделять память в 
// процессе чтения, если в потоке ввода оказалось больше символов, чем вы ожидали.

// Память, возвращенная из функции будет освобождена оператором delete[]. Символ переноса строки ('\n') 
// добавлять в строку не нужно, но не забудьте, что в конце C-style строки должен быть завершающий нулевой символ. 

#include <iostream>
using namespace std;

char *resize(char *str, unsigned size, unsigned new_size)
{
	char *new_str = new char [new_size];
    
    for (int i = 0; i < size && i < new_size; ++i)
        *(new_str + i) = *(str + i);

    delete [] str;

    return new_str;
}

char *getline()
{   
    int i = 0;
    int str_size = 4;
    int buff_size = 4;

    char ch;
    char *str = new char [str_size];

    while (std::cin.get(ch) && ch != '\n') {
        *(str + i) = ch;
        i++;

        if (i == str_size) {
            str = resize(str, str_size, str_size + buff_size);
            str_size = str_size + buff_size;
        }
    }

    str[i] = '\0';
    return str;
}

int main() 
{  
    char * cin_str = new char;

    cin_str = getline();
    cout << "=> " << cin_str << endl;

    return 0;
}
