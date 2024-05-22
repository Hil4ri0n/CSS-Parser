#define _CRT_SECURE_NO_WARNINGS 
#include "String.h"
#include <iostream>
#include <string.h>

String::String() : cString(nullptr), length(0) {}

String::String(const String& other) {
    length = other.length;
    cString = new char[length + 1];
    strcpy(cString, other.cString);
}

String::String(const char* str) {
    length = strlen(str);
    cString = new char[length + 1];
    strcpy(cString, str);
}

String::~String() {
    delete[] cString;
}

size_t String::size() const {
    return length;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] cString;
        length = other.length;
        cString = new char[length + 1];
        strcpy(cString, other.cString);
    }
    return *this;
}

String String::operator+(const String& other) const {
    size_t new_size = length + other.length;
    char* new_data = new char[new_size + 1];
    strcpy(new_data, cString);
    strcat(new_data, other.cString);
    String new_string(new_data);
    delete[] new_data;
    return new_string;
}

bool String::operator==(const String& other) const {
    return strcmp(cString, other.cString) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator<(const String& other) const {
    return strcmp(cString, other.cString) < 0;
}

bool String::operator>(const String& other) const {
    return strcmp(cString, other.cString) > 0;
}

bool String::operator<=(const String& other) const {
    return strcmp(cString, other.cString) <= 0;
}

bool String::operator>=(const String& other) const {
    return strcmp(cString, other.cString) >= 0;
}

char& String::operator[](size_t index) {
    return cString[index];
}

const char* String::c_str() const {
    return cString;
}

char& String::at(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range.");
    }
    return cString[index];
}

int String::to_int() const {
    return std::atoi(cString);
}

std::istream& operator>>(std::istream& in, String& str) {
    char buffer[4096];
    in >> buffer;
    str = String(buffer);
    return in;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.cString;
    return out;
}

