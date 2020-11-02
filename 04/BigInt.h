#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <sstream>

#ifndef BIGINT_H
#define BIGINT_H

class BigInt {
public:

    BigInt();
    BigInt(const int64_t val);
    BigInt(const std::string &str);
    BigInt(const BigInt &val);
    BigInt(BigInt &&val);
    ~BigInt();

        /// WITH BigInt ///
    BigInt operator -() const;
    BigInt &operator =(const BigInt &val);
    BigInt &operator =(BigInt &&val);
    bool operator >(const BigInt &val) const;
    bool operator >=(const BigInt &val) const;
    bool operator <(const BigInt &val) const;
    bool operator <=(const BigInt &val) const;
    bool operator ==(const BigInt &val) const;
    bool operator !=(const BigInt &val) const;

    BigInt operator +(const BigInt &val) const;
    BigInt operator -(const BigInt &val) const;
    BigInt operator *(const BigInt &val) const;
    BigInt &operator *=(const BigInt &val);
    BigInt &operator +=(const BigInt &val);
    BigInt &operator -=(const BigInt &val);


        /// WITH INT ///
    BigInt &operator =(const int64_t val);
    bool operator >(const int64_t val) const;
    bool operator >=(const int64_t val) const;
    bool operator <(const int64_t val) const;
    bool operator <=(const int64_t val) const;
    bool operator ==(const int64_t val) const;
    bool operator !=(const int64_t val) const;

    BigInt operator +(const int64_t val) const;
    BigInt operator -(const int64_t val) const;
    BigInt operator *(const int64_t val) const;
    BigInt &operator *=(const int64_t val);
    BigInt &operator +=(const int64_t val);
    BigInt &operator -=(const int64_t val);

    friend std::ostream &operator << (std::ostream &fout, const BigInt &value);

private:
    const int64_t BASE = 10000;
    const int64_t LEN = 4;
    int32_t *number;
    bool sign;     /// false == 1; true == -1
    int64_t size;  /// count of cells
    int64_t last;  /// last used index

    void setDefault();
    void appendNumber(const int32_t x);
    void realloc();
    int comparePositive(const BigInt &a, const BigInt &b) const;
    void addPositive(BigInt &a, const BigInt &b) const;
    void subPositive(BigInt &a, const BigInt &val) const;
    void buildByString(int64_t beg, const std::string &str);
};

#endif
