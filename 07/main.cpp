#include <iostream>
#include <vector>
#include <functional>
#include "Vector.h"

bool test1() {
    Vector<int> a;
    if (a.capacity() != 0 || a.size() != 0) {
        return false;
    }
    Vector<double> b(1);
    if (b.capacity() != 1 || b.size() != 1) {
        return false;
    }
    Vector<unsigned> c(12, 897);
    for (int i = 0; i < 12; ++i) {
        if (c[i] != 897) {
            return false;
        }
    }
    if (c.capacity() != 12 || c.size() != 12) {
        return false;
    }

    return true;
}

bool test2() {
    Vector<int> a;
    for (int i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    if (a.size() != 10 && a.capacity() != 16) {
        return false;
    }
    a.pop_back();
    a.pop_back();
    for (int i = 0; i < 8; ++i) {
        if (a[i] != i) {
            return false;
        }
    }

    if (a.size() != 8 && a.capacity() != 16 && !a.empty()) {
        return false;
    }
    a.clear();

    if (a.size() != 0 && a.capacity() != 16 && a.empty()) {
        return false;
    }

    return true;
}

bool test3() {
    Vector<int> b(10);
    for (int i = 0; i < 10; ++i) {
        b[i] = 7 * i - 16;
    }
    Vector<int> a(b);

    a.reserve(5);
    if (a.size() != 10 || a.capacity() != 10) {
        return false;
    }
    a.reserve(100);
    if (a.size() != 10 || a.capacity() != 100) {
        return false;
    }

    return true;
}

bool test4() {
    Vector<int> b;
    for (int i = 0; i < 17; ++i) {
        b.push_back(i * 8 + 15);
    }
    if (b.size() != 17) {
        return false;
    }
    for (int i = 0; i < 17; ++i) {
        b.pop_back();
        if (b.size() != 17 - i - 1) {
            return false;
        }
    }
    return true;
}

bool test5() {
    Vector<int> a(10, 12);
    for (auto &i : a) {
        if (i != 12) {
            return false;
        }
    }
    return true;
}

bool test6() {
    Vector<int> a;
    std::vector<int> b;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            a.push_back(i * j);
            b.push_back(i * j);
        }
        auto it = a.begin();
        auto jt = b.begin();
        for (; it != a.end() && jt != b.end(); ++it, ++jt) {
            if (*it != *jt) {
                return false;
            }
        }
        auto itr = a.rbegin();
        auto jtr = b.rbegin();
        for (; itr != a.rend() && jtr != b.rend(); ++itr, ++jtr) {
            if (*itr != *jtr) {
                return false;
            }
        }
    }
    return true;
}

bool test7() {
    Vector<int> a;
    std::vector<int> b;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            a.push_back(i * j);
            b.push_back(i * j);
        }
        auto it = a.begin();
        auto jt = b.begin();
        for (; it < a.end() && jt < b.end(); it += 2, jt += 2) {
            if (*it != *jt) {
                return false;
            }
        }
        auto itr = a.rbegin();
        auto jtr = b.rbegin();
        for (; itr < a.rend() && jtr < b.rend(); itr += 2, jtr += 2) {
            if (*itr != *jtr) {
                return false;
            }
        }

        it -= 2;
        jt -= 2;
        for (; it >= a.begin() && jt >= b.begin(); it -= 2, jt -= 2) {
            if (*it != *jt) {
                return false;
            }
        }

        itr -= 2;
        jtr -= 2;
        for (; itr >= a.rbegin() && jtr >= b.rbegin(); itr -= 2, jtr -= 2) {
            if (*itr != *jtr) {
                return false;
            }
        }
    }
    return true;
}

bool test8() {
    Vector<int> a;
    std::vector<int> b;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            a.push_back(i * j);
            b.push_back(i * j);
        }
        auto it = a.begin();
        auto jt = b.begin();
        for (; it < a.end() && jt < b.end(); it += 7, jt += 7) {
            if (*it != *jt) {
                return false;
            }
        }
        auto itr = a.rbegin();
        auto jtr = b.rbegin();
        for (; itr < a.rend() && jtr < b.rend(); itr += 7, jtr += 7) {
            if (*itr != *jtr) {
                return false;
            }
        }

        it -= 7;
        jt -= 7;
        for (; it >= a.begin() && jt >= b.begin(); it -= 7, jt -= 7) {
            if (*it != *jt) {
                return false;
            }
        }

        itr -= 7;
        jtr -= 7;
        for (; itr >= a.rbegin() && jtr >= b.rbegin(); itr -= 7, jtr -= 7) {
            if (*itr != *jtr) {
                return false;
            }
        }
    }
    return true;
}

class Person {
public:
    Person() {}

    Person(const std::string name, const int age)
        : Name(name)
        , Age(age) {}

    bool operator !=(const Person &x) const {
         return Name != x.Name || Age != x.Age;
    }
private:
    std::string Name;
    int Age;
};

bool test9() {
    std::vector<Person> a;
    Vector<Person> b;
    a.emplace_back("first", 15);
    a.emplace_back("second", 16);
    a.emplace_back("third", 20);


    b.emplace_back("first", 15);
    b.emplace_back("second", 16);
    b.emplace_back("third", 20);

    for (int i = 0; i < 3; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    std::vector<std::function<bool()>> tests {
        test1,
        test2,
        test3,
        test4,
        test5,
        test6,
        test7,
        test8,
        test9
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << i + 1 << " -- " << (tests[i]() ? "ok" : "WA") << "\n";
    }
    return 0;
}
