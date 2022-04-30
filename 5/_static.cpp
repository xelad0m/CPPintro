#include <iostream>


struct  User {
    int pub;
private:                            // приватная - кто попало менять не может, только методы этого класса
    static  size_t  instances_;     // объявили статическое поле (живет даже когда экземпляров нет)
    int i;
};

size_t  User::instances_ = 10;

int main()
{
    User u1;
    u1.pub = 15;
    User u2;

    printf("u1.pub=%d, u2.pub=%d", u1.pub, u2.pub);
    return 0;
}

