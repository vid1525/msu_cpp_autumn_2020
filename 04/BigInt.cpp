#include "BigInt.h"

BigInt::BigInt() {
    number = new int32_t[1];
    number[0] = 0;
    size = 1;
    last = 0;
    sign = false;
}

BigInt::BigInt(const int64_t val) {
    number = new int32_t[1];
    number[0] = 0;
    size = 1;
    last = 0;
    sign = false;
    int64_t newVal = val;
    if (val < 0) {
        sign = true;
        newVal = -val;
    }
    while (newVal > 0) {
        appendNumber(newVal % BASE);
        newVal /= BASE;
    }
}

BigInt::BigInt(const std::string &str) {
    number = new int32_t[1];
    number[0] = 0;
    size = 1;
    last = 0;
    sign = false;
    if (str != "") {
        sign = str[0] == '-' ? true : false;
    } else {
        return ;
    }
    if (sign) {
        int64_t beg = 1;
        while (str[beg] == '0') {
            ++beg;
        }
        --beg;
        if (beg == (int64_t) str.size() - 1) {
            sign = false;
        }
        int64_t n = str.size() - 1;
        for (int64_t i = n; i > beg; i -= LEN) {
            std::string cur;
            for (int64_t j = i; j > i - LEN && j > beg; --j) {
                cur = str[j] + cur;
            }
            std::stringstream val;
            val << cur;
            int32_t x;
            val >> x;
            appendNumber(x);
        }
    } else {
        int64_t beg = 0;
        while (str[beg] == '0') {
            ++beg;
        }
        int64_t n = str.size() - 1;
        for (int64_t i = n; i >= beg; i -= LEN) {
            std::string cur;
            for (int64_t j = i; j > i - LEN && j >= beg; --j) {
                cur = str[j] + cur;
            }
            std::stringstream val;
            val << cur;
            int32_t x;
            val >> x;
            appendNumber(x);
        }
    }
}

BigInt::BigInt(const BigInt &val) {
    size = val.size;
    last = val.last;
    sign = val.sign;
    number = new int32_t[size];
    std::fill(number, number + size, 0);
    for (int64_t i = 0; i < last; ++i) {
        number[i] = val.number[i];
    }
}

BigInt::BigInt(BigInt &&val) {
    number = val.number;
    sign = val.sign;
    last = val.last;
    size = val.size;

    val.number = nullptr;
}

BigInt::~BigInt() {
    delete [] number;
}

        /// BigInt OPERATORS ///

BigInt BigInt::operator -() const {
    BigInt a(*this);
    a.sign = !a.sign;
    return a;
}

BigInt &BigInt::operator =(const BigInt &val) {
    if (val == *this) {
        return *this;
    }
    delete [] number;
    size = val.size;
    last = val.last;
    sign = val.sign;
    number = new int32_t[size];
    std::fill(number, number + size, 0);
    for (int64_t i = 0; i < last; ++i) {
        number[i] = val.number[i];
    }
    return *this;
}

BigInt &BigInt::operator =(BigInt &&val) {
    if (&val == this) {
        return *this;
    }

    delete [] number;
    number = val.number;
    sign = val.sign;
    last = val.last;
    size = val.size;

    val.number = nullptr;

    return *this;
}

bool BigInt::operator >(const BigInt &val) const {
    if (!sign && !val.sign) {
        return comparePositive(*this, val) > 0;
    } else if (!sign && val.sign) {
        return true;
    } else if (sign && !val.sign) {
        return false;
    }
    return comparePositive(*this, val) < 0;
}

bool BigInt::operator >=(const BigInt &val) const {
    return (*this > val) || (*this == val);
}

bool BigInt::operator <(const BigInt &val) const {
    return !(*this >= val);
}

bool BigInt::operator <=(const BigInt &val) const {
    return !(*this > val);
}

bool BigInt::operator ==(const BigInt &val) const {
    if (last != val.last || sign != val.sign) {
        return false;
    }
    for (int i = 0; i < last; ++i) {
        if (number[i] != val.number[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator !=(const BigInt &val) const {
    if (last != val.last || sign != val.sign) {
        return true;
    }
    for (int i = 0; i < last; ++i) {
        if (number[i] != val.number[i]) {
            return true;
        }
    }
    return false;
}


BigInt &BigInt::operator +=(const BigInt &val) {
    if (!sign && !val.sign) {
        addPositive(*this, val);
    } else if (!sign && val.sign) {
        if (*this >= -val) {
            subPositive(*this, val);
        } else {
            BigInt c(-val);
            subPositive(c, *this);
            *this = -c;
        }
    } else if (sign && !val.sign) {
        if (-*this > val) {
            this->sign = !this->sign;
            BigInt c(*this);
            subPositive(c, val);
            *this = c;
            this->sign = true;
        } else {
            BigInt c(val);
            this->sign = !this->sign;
            subPositive(c, *this);
            *this = c;
            this->sign = false;
        }
    } else {
        addPositive(*this, val);
        this->sign = true;
    }

    return *this;
}

BigInt &BigInt::operator -=(const BigInt &val) {
    if (!sign && !val.sign) {
        if (*this >= val) {
            subPositive(*this, val);
        } else {
            BigInt c(val);
            subPositive(c, *this);
            *this = -c;
        }
    } else if (!sign && val.sign) {
        addPositive(*this, val);
    } else if (sign && !val.sign) {
        addPositive(*this, val);
        this->sign = true;
    } else {
        if (*this < val) {
            subPositive(*this, val);
        } else {
            BigInt c(val);
            subPositive(c, *this);
            *this = c;
            this->sign = false;
        }
    }

    return *this;
}

BigInt &BigInt::operator *=(const BigInt &val) {
    int64_t len = this->last + val.last + 1;
    int32_t *num = new int32_t[len];
    std::fill(num, num + len, 0);

    for (int64_t i = 0; i < this->last; ++i) {
        for (int64_t j = 0, cur = 0; j < val.last || cur; ++j) {
            int64_t curSum = num[i + j] +
                    this->number[i] * 1ll * (j < val.last ? val.number[j] : 0) + cur;
            num[i + j] = curSum % BASE;
            cur = curSum / BASE;
        }
    }

    delete [] this->number;
    this->number = num;
    this->size = len;
    this->last = len;
    this->sign = sign ^ val.sign;

    while (last >= 1 && this->number[last - 1] == 0) {
        --last;
    }
    if (last == 0) {
        this->sign = false;
    }

    return *this;
}

BigInt BigInt::operator +(const BigInt &val) const {
    BigInt a(*this);
    a += val;
    return a;
}

BigInt BigInt::operator -(const BigInt &val) const {
    BigInt a(*this);
    a -= val;
    return a;
}

BigInt BigInt::operator *(const BigInt &val) const {
    BigInt a(*this);
    a *= val;
    return a;
}

              /// WITH INT ///

BigInt &BigInt::operator =(const int64_t val) {
    *this = BigInt(val);
    return *this;
}

bool BigInt::operator >(const int64_t val) const {
    return *this > BigInt(val);
}

bool BigInt::operator >=(const int64_t val) const {
    return *this >= BigInt(val);
}

bool BigInt::operator <(const int64_t val) const {
    return *this < BigInt(val);
}

bool BigInt::operator <=(const int64_t val) const {
    return *this <= BigInt(val);
}

bool BigInt::operator ==(const int64_t val) const {
    return *this == BigInt(val);
}

bool BigInt::operator !=(const int64_t val) const {
    return *this != BigInt(val);
}

BigInt BigInt::operator +(const int64_t val) const {
    return *this + BigInt(val);
}

BigInt BigInt::operator -(const int64_t val) const {
    return *this - BigInt(val);
}

BigInt BigInt::operator *(const int64_t val) const {
    return *this * BigInt(val);
}

BigInt &BigInt::operator *=(const int64_t val) {
    return *this *= BigInt(val);
}

BigInt &BigInt::operator +=(const int64_t val) {
    return *this += BigInt(val);
}

BigInt &BigInt::operator -=(const int64_t val) {
    return *this -= BigInt(val);
}

              /// OUTPUT ///

std::ostream &operator << (std::ostream &fout, const BigInt &value) {
    if (value.sign) {
        fout << "-";
    }
    if (value.last > 0) {
        fout << value.number[value.last - 1];
    } else {
        fout << 0;
    }
    for (int64_t i = value.last - 2; i >= 0; --i) {
        int32_t k = value.BASE / 10;
        int32_t cur = value.number[i];
        for (int64_t j = 0; j < value.LEN; ++j) {
            fout << cur / k;
            cur %= k;
            k /= 10;
        }
    }
    return fout;
}

            /// PRIVATE ///

void BigInt::realloc() {
    size <<= 1;
    int32_t *new_ptr = new int32_t[size];
    std::fill(new_ptr, new_ptr + size, 0);
    for (int64_t i = 0; i < size / 2; ++i) {
        new_ptr[i] = number[i];
    }
    delete [] number;
    number = new_ptr;
}

void BigInt::appendNumber(const int32_t x) {
    if (last + 1 >= size) {
        realloc();
    }
    number[last] = x;
    ++last;
}

int BigInt::comparePositive(const BigInt &a, const BigInt &b) const {
    if (a.last > b.last) {
        return 1;
    }
    if (a.last < b.last) {
        return -1;
    }
    for (int i = last - 1; i >= 0; --i) {
        if (a.number[i] > b.number[i]) {
            return 1;
        } else if (a.number[i] < b.number[i]) {
            return -1;
        }
    }
    return 0;
}

void BigInt::addPositive(BigInt &a, const BigInt &val) const {
    int64_t maxLen = std::max(a.last, val.last);
    int32_t cur = 0;

    for (int64_t i = 0; i < maxLen; ++i) {
        if (i < a.last) {
            cur += a.number[i];
        }
        if (i < val.last) {
            cur += val.number[i];
        }
        if (i < a.last) {
            a.number[i] = cur % BASE;
        } else {
            a.appendNumber(cur % BASE);
        }
        cur /= BASE;
    }

    if (cur > 0) {
        a.appendNumber(cur % BASE);
    }
}

void BigInt::subPositive(BigInt &a, const BigInt &val) const {
    int32_t cur = 0;

    for (int64_t i = 0; i < val.last || cur; ++i) {
        a.number[i] -= cur + (i < val.last ? val.number[i] : 0);
        cur = a.number[i] < 0;
        if (cur) {
            a.number[i] += a.BASE;
        }
    }

    while (a.last > 1 && a.number[a.last - 1] == 0) {
        --a.last;
    }
}
