#include <iostream>
#include <vector>
#include <functional>
#include "ThreadPool.h"

struct A {};

int foo(const A&) {return 10;}

bool test1() {
    ThreadPool pool(8);
    std::vector<int> x;
    auto task1 = pool.exec(foo, A());
    x.push_back(task1.get());

    auto task2 = pool.exec([]() { return 1; });
    x.push_back(task2.get());

    return x[0] == 10 && x[1] == 1;
}

bool test2() {
    ThreadPool pool(8);
    auto task = pool.exec([](int x, int y, int z){return x * y + z;}, 7, 8, 9);
    return task.get() == 65;
}

bool test3() {
    ThreadPool pool(4);
    auto task1 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 7, 8, 9);
    auto task2 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 700, 8, 10);
    auto task3 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 70000, 8, 11);
    auto task4 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 7000000, 8, 12);
    auto task5 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 700000000, 8, 13);
    return task1.get() == 17 && task2.get() == 18 && task3.get() == 19
            && task4.get() == 20 && task5.get() == 21;
}

bool test4() {
    ThreadPool pool(4);
    auto task5 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 700000000, 8, 13);
    auto task4 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 7000000, 8, 12);
    auto task1 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 7, 8, 9);
    auto task2 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 700, 8, 10);
    auto task3 = pool.exec([](int x, int y, int z){
        for (int i = 0; i < x; ++i); return y + z;
    }, 70000, 8, 11);

    return task1.get() == 17 && task2.get() == 18 && task3.get() == 19
            && task4.get() == 20 && task5.get() == 21;
}

bool test5() {
    ThreadPool pool(4);
    int x = 8;
    auto task5 = pool.exec([](int &x, int y, int z){
        x++;
        for (int i = 0; i < x; ++i);
        --x;
        return y + z;
    }, 700000000, x, 13);
    auto task4 = pool.exec([](int &x, int y, int z){
        x++;
        for (int i = 0; i < x; ++i);
        --x;
        return y + z;
    }, 7000000, x, 12);
    auto task1 = pool.exec([](int &x, int y, int z){
        x++;
        for (int i = 0; i < x; ++i);
        --x;
        return y + z;
    }, 7, x, 9);
    auto task2 = pool.exec([](int &x, int y, int z){
        x++;
        for (int i = 0; i < x; ++i);
        --x;
        return y + z;
    }, 700, x, 10);
    auto task3 = pool.exec([](int &x, int y, int z){
        x++;
        for (int i = 0; i < x; ++i);
        --x;
        return y + z;
    }, 70000, x, 11);

    return task1.get() == 17 && task2.get() == 18 && task3.get() == 19
            && task4.get() == 20 && task5.get() == 21;
}

int main() {
    std::vector<std::function<bool()>> tests {
        test1,
        test2,
        test3,
        test4,
        test5
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << i + 1 << " -- " << (tests[i]() ? "ok" : "WA") << "\n";
    }
    return 0;
}
