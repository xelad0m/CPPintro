#include <iostream>
#include <list>

#include <future>
#include <vector>


// Реализовать аналог популярной концепции MapReduce в терминах потоков. 
// Последовательность разбивается на threads подпоследовательностей
// В каждом потоке:
// - унарный функтор f1 применяется ко всем элементам подпоследовательности
// - бинарный функтор f2 применяется получившимся значениям f2(pred, f1(next))
// - то что можно делать частичную свертку в потоках обеспечивается ассоциативностью f2 (если нет, то не получится)
// - возвращается результат f2
// Затем вне рабочих потоков:
// - полученные результатые еще раз пропускаются через f2

template <typename It, typename F1, typename F2>
auto sync_map_reduce(It p, It q, F1 f1, F2 f2) 
-> decltype(f2(f1(*p), f1(*p)))
{
    auto res = f1(*p);
    while (++p != q)
        res = f2(res, f1(*p));
    return res;
}

template <typename It, typename F1, typename F2>
auto map_reduce(It p, It q, F1 f1, F2 f2, size_t threads)
-> decltype(f2(f1(*p),f1(*p)))                                          // так удобнее всего вывести тип результат
{ 
    using TRes = decltype(f2(f1(*p),f1(*p)));                           // создадим для него алиас

    size_t length = std::distance(p, q);
    
    std::vector<std::future<TRes>> vecFut;                              // промисы

    for (size_t i = 0; i < threads; i++) {
        auto p1 = p;
        auto q1 = p;
        std::advance(p1, int(i * length / threads));                    // сдвинутые итераторы
        std::advance(q1, int((i + 1) * length / threads));
        
        // промисы нельзя копировать, поэтому только так
        vecFut.push_back(std::async(std::launch::async, sync_map_reduce<It, F1, F2>, p1, q1, f1, f2));
    }
   
    // в C++14 можно auto вместо std::future<TRes>&
    auto res = sync_map_reduce(vecFut.begin(), vecFut.end(), [](std::future<TRes>& fut) {return fut.get(); }, f2); 
    return res;
}

int main()
{
    std::list<int> l = {1,2,3,4,5,6,7,8,9,10};

    // параллельное суммирование в 3 потока
    auto sum = map_reduce(l.begin(), l.end(), 
                [](int i){return i;}, 
                std::plus<int>(), 3);

    // проверка наличия чётных чисел в 4 потока
    auto has_even = map_reduce(l.begin(), l.end(), 
                    [](int i){return i % 2 == 0;}, 
                    std::logical_or<bool>(), 4);


    std::cout << "55 : " << sum << std::endl;
    std::cout << "1 : " << has_even << std::endl;

    return 0;
}