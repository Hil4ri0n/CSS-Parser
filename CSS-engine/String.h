#pragma once
#include <iostream>
class String {
private:
    char* cString;
    size_t length;
public:
    String();
    friend std::istream& operator>>(std::istream& in, String& str);
    friend std::ostream& operator<<(std::ostream& out, const String& str);

    String(const char* str);
    String(const String& other);

    ~String();

    size_t size() const;

    const char* c_str() const;

    String& operator=(const String& other);
    String operator+(const String& other) const;

    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;
    bool operator<=(const String& other) const;
    bool operator>=(const String& other) const;

    char& operator[](size_t index);

    char& at(size_t index);

    int to_int() const;
};
