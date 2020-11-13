#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
#include <string>
#include <type_traits>
#include <cctype>
#include <cassert>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Deserializer {
public:
    explicit Deserializer(std::istream &fout)
        : stream(fout) {
    }

    template <typename... Args>
    Error operator()(Args&&... args) {
        return build(std::forward<Args>(args)...);
    }

    template <typename T>
    Error load(T &value) {
        return value.serialize(*this);
    }

private:
    static constexpr char sep = ' ';
    std::istream &stream;

    template <typename CurArg>
    Error build(CurArg &&ans) {
        std::string s;
        stream >> s;
        if (s == "true") {
            ans = true;
        } else if (s == "false") {
            ans = false;
        } else if (digit(s)){
            try {
                ans = std::stoull(s);
            } catch (std::out_of_range) {
                return Error::CorruptedArchive;
            }
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <typename CurArg, typename... Args>
    Error build(CurArg &&value, Args&&... args) {
        bool flag = false;
        if (build(value) != Error::NoError) {
            flag = true;
        }
        if (build(std::forward<Args>(args)...) != Error::NoError) {
            flag = true;
        }
        return flag ? Error::CorruptedArchive : Error::NoError;
    }

    bool digit (const std::string &s) const {
        for (const auto &i : s) {
            if (!isdigit((unsigned char) i)) {
                return false;
            }
        }
        return true;
    }
};

class Serializer {
public:
    explicit Serializer(std::ostream &fin)
        : stream(fin) {
    }

    template <typename T>
    Error save(T &value) {
        return value.serialize(*this);
    }

    template <typename... Args>
    Error operator() (Args&&...args) {
        return process(std::forward<Args>(args)...);
    }

private:
    static constexpr char sep = ' ';
    std::ostream &stream;

    template <typename CurType>
    Error process(CurType &&val) {
        stream << val;
        return Error::NoError;
    }

    template <typename CurType, typename... Args>
    Error process(CurType &&val, Args&&... args) {
        stream << std::boolalpha << val << sep;
        process(std::forward<Args>(args)...);
        return Error::NoError;
    }
};

#endif
