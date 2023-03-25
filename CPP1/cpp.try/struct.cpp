#include <iostream>   
#include <cstring>
using namespace std;                

#define N 5

struct tag_book {
    char title[100];
    char author[20];
    short year;
    short pages;
    float price;
    static int count;     // статическая переменная будет только в одном экземпляре (точнее разделяется между всеми экземплярами)
};

int tag_book::count = 0;  // например, это счетчик экземпляров

void show_book(struct tag_book book) {
    cout << "Автор: "       << book.author << endl
         << "Название: "    << book.title << endl
         << "Год: "         << book.year << endl
         << "Число стр.: "  << book.pages << endl
         << "Цена: "        << book.price << endl;
    cout << endl;
}

int main() 
{   
    setlocale(LC_ALL, "rus");
      
    // 1 структура
    struct tag_book book;
    strcpy(book.title, "Евгений Онегин");
    strcpy(book.author, "Пушкин А.С.");
    book.year = 2001;
    book.pages = 81;
    book.price = 145.51;

    // массив структур
    struct tag_book lib[N];
    lib[0] = book;
    lib[0].count++;


    strcpy(lib[1].title, "Война и мир");
    strcpy(lib[1].author, "Толстой Л.Н.");
    lib[1].year = 2011;
    lib[1].pages = 654;
    lib[1].price = 1025.11;
    lib[1].count++;                                 // статическая переменная любого экземпляра одна для всех

    lib[2] = lib[0];
    lib[2].count++;

    struct tag_book book3 = {"Книга еще одна", "Иванов И.И.", 1995};
    lib[3] = book3;
    book3.count++;

    // struct tag_book book4 = {.title="И еще книга еще одна", .author="Петров И.И.", .year=1999};    //C99 designator ‘title’ outside aggregate initializer
    struct tag_book book4 = {"И еще книга еще одна", "Петров И.И.", 1999};
    book4.count++;
    lib[4] = book4;

    for (int i = 0; i < N; ++i)
        show_book(lib[i]);
    
    cout << book.count << " книг положено в библиотеку" << endl;

    return 0;
}