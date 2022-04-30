#include <iostream>
#include <ctime>

using namespace std;

bool contains1 (int * m, int size, int value)   {
    for (int i = 0; i != size; ++i) {
        if (m[i] == value)  {return true;}
    }
    return false;
}

bool contains2 (int * p, int * q, int value)    {
    for (; p != q; ++p) {
        if (*p == value)    {return true;}
    }
    return false;
}


int main()
{
    int massive[20] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,22};
    int search_value = 22;

    int *m_start = &massive[0];
    int *m_finish = m_start + 20;

    unsigned int start_time =  clock();
    if ((contains1(massive,20,search_value)) == true) { cout << "1 FOUND!" << endl;}
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << "1 FUNCTION TIME : " << search_time << endl;

    start_time =  clock();
    if ((contains2(m_start,m_finish,search_value)) == true) { cout << "2 FOUND!" << endl;}
    end_time = clock();
    search_time = end_time - start_time;
    cout << "2 FUNCTION TIME : " << search_time << endl;

    return 0;
}