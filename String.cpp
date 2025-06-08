#include "String.h"
#include <iostream>
using namespace std;

// Default constructor
String::String() {
    len = 0;
    cap = 50;
    str = new char[cap];
    str[0] = '\0';
}

String::String(const char* s, int n) {
    cap = n;
    len = get_size(s);
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}

String::String(const String& s) {
    if (s.str == nullptr) {
        cap = 0;
        len = 0;
        str = nullptr;
    }
    else {
        cap = s.cap;
        len = s.len;
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = s.str[i];
        }
        str[len] = '\0';
    }
}

String::String(const char* s) {
    cap = 50;
    len = get_size(s);
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}

String::String(int n) {
    *this = itos(n);
}

ostream& operator<<(ostream& os, const String& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& in, String& s) {
    char temp[100] = { '\0' };
    in >> temp;
    s.len = String::get_size(temp);
    if (s.len >= s.cap) {
        delete[] s.str;
        s.cap = s.len + 1;
        s.str = new char[s.cap];
    }
    for (int i = 0; i < s.len; i++) {
        s.str[i] = temp[i];
    }
    s.str[s.len] = '\0';
    return in;
}

String String::operator+(const String& s) const {
    String temp("", s.len + len + 1);
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    for (int i = len; i < len + s.len; i++) {
        temp.str[i] = s.str[i - len];
    }
    temp.str[len + s.len] = '\0';
    temp.len = len + s.len;
    return temp;
}

String& String::operator+=(const String& s) {
    int origLen = len;
    int newLen = len + s.len;
    char* temp = new char[newLen + 1];

    for (int i = 0; i < origLen; i++) {
        temp[i] = str[i];
    }
    for (int i = 0; i < s.len; i++) {
        temp[origLen + i] = s.str[i];
    }
    temp[newLen] = '\0';

    delete[] str;
    str = temp;
    len = newLen;

    return *this;
}

String& String::operator=(const String& s) {
    if (this == &s)
        return *this;
    delete[] str;
    cap = s.cap;
    len = s.len;
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s.str[i];
    }
    str[len] = '\0';
    return *this;
}

const char String::operator[](int i) const {
    if (i < 0 || i >= len) {
        throw std::runtime_error("out of bounds access");
    }
    return str[i];
}

char& String::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::runtime_error("out of bounds access");
    }
    return str[i];
}

String String::itos(int n) {
    int i = 0;
    String s;
    if (n == 0) {
        s.str[0] = '0';
        s.str[1] = '\0';
        s.len = 1;
        return s;
    }
    bool isNeg = false;
    if (n < 0) {
        isNeg = true;
        n = -n;
    }
    while (n > 0) {
        int cur = n % 10;
        s.str[i++] = '0' + cur;
        n /= 10;
    }
    if (isNeg) {
        s.str[i++] = '-';
    }
    s.str[i] = '\0';
    s.len = i;
    s.cap = 50;
    for (int j = 0; j < s.len / 2; j++) {
        char temp = s.str[j];
        s.str[j] = s.str[s.len - j - 1];
        s.str[s.len - j - 1] = temp;
    }
    return s;
}

String String::insert_char(int n, char ch) {
    if (cap <= len + 1) {
        *this = regrow();
    }
    for (int i = len; i > n; i--) {
        str[i] = str[i - 1];
    }
    str[n] = ch;
    len++;
    str[len] = '\0';
    return *this;
}

// insert_string: insert a string at position n
String String::insert_string(int n, const String& sub) {
    if (cap <= len + sub.len) {
        *this = regrow();
    }
    int space = n - len;
    if (space > 0) {
        for (int i = 0; i < space; i++) {
            str[i + len] = ' ';
        }
    }
    for (int i = len; i >= sub.len; i--) {
        str[i + sub.len] = str[i];
    }
    for (int i = 0; i < sub.len; i++) {
        str[n + i] = sub.str[i];
    }
    len += sub.len;
    str[len] = '\0';
    return *this;
}

String& String::replace_first(char ch) {
    if (len > 0)
        str[0] = ch;
    return *this;
}

int String::get_size(const char* s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void String::to_upper() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

void String::to_lower() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

String& String::trim() {
    int start = 0;
    int end = len - 1;
    while (start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) {
        start++;
    }
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }
    int new_len = end - start + 1;
    for (int i = 0; i < new_len; i++) {
        str[i] = str[start + i];
    }
    str[new_len] = '\0';
    len = new_len;
    return *this;
}

String String::trim(const char* s) {
    int start = 0;
    int end = get_size(s) - 1;
    while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n') {
        start++;
    }
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')) {
        end--;
    }
    int new_len = end - start + 1;
    char* trimmed_str = new char[new_len + 1];
    for (int i = 0; i < new_len; i++) {
        trimmed_str[i] = s[start + i];
    }
    trimmed_str[new_len] = '\0';
    String result(trimmed_str);
    delete[] trimmed_str;
    return result;
}

int String::stoi() const {
    int i = 0;
    int num = 0;
    bool isNeg = false;
    if (str[0] == '-') {
        isNeg = true;
        i = 1;
    }
    while (i < len) {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return isNeg ? -num : num;
}

void String::display() const {
    std::cout << str;
}

String::~String() {
    delete[] str;
}

bool String::is_equal(const String& m) const {
    if (m.len != len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] != m.str[i]) {
            return false;
        }
    }
    return true;
}

bool String::is_less(const String& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] < m.str[i]) {
            return true;
        }
        if (str[i] > m.str[i]) {
            return false;
        }
    }
    return len < m.len;
}

bool String::is_greater(const String& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] > m.str[i]) {
            return true;
        }
        if (str[i] < m.str[i]) {
            return false;
        }
    }
    return len > m.len;
}

String String::concat(const String& s) const {
    String temp("", s.len + len + 1);
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    for (int i = len; i < len + s.len; i++) {
        temp.str[i] = s.str[i - len];
    }
    temp.str[len + s.len] = '\0';
    temp.len = len + s.len;
    return temp;
}

String* String::split(char delimiter, int& count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            count++;
        }
    }
    String* splitArr = new String[count];
    int curIndex = 0, curLen = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            splitArr[curIndex].len = curLen;
            splitArr[curIndex].str[curLen] = '\0';
            curLen = 0;
            curIndex++;
        }
        else {
            splitArr[curIndex].str[curLen] = str[i];
            curLen++;
        }
    }
    splitArr[curIndex].len = curLen;
    splitArr[curIndex].str[curLen] = '\0';
    return splitArr;
}

String* String::split(const String& delimiters, int& count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < delimiters.len; j++) {
            if (str[i] == delimiters.str[j]) {
                count++;
                break;
            }
        }
    }
    String* splitArr = new String[count];
    int curIndex = 0, curLen = 0;
    for (int i = 0; i < len; i++) {
        bool flag = false;
        for (int j = 0; j < delimiters.len; j++) {
            if (str[i] == delimiters.str[j]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            splitArr[curIndex].str[curLen] = '\0';
            splitArr[curIndex].len = curLen;
            curLen = 0;
            curIndex++;
        }
        else {
            splitArr[curIndex].str[curLen] = str[i];
            curLen++;
        }
    }
    splitArr[curIndex].len = curLen;
    splitArr[curIndex].str[curLen] = '\0';
    return splitArr;
}

void String::remove_char(int n) {
    for (int i = n; i < len - 1; i++) {
        str[i] = str[i + 1];
    }
    len--;
    str[len] = '\0';
}

void String::remove_first(char ch) {
    int first = find_first(ch);
    if (first != -1) {
        remove_char(first);
    }
}

void String::remove_last(char ch) {
    int last = find_last(ch);
    if (last != -1) {
        remove_char(last);
    }
}

void String::remove_all(char a) {
    int count = 0;
    int* indices = find_all(a, count);
    for (int i = 0; i < count; i++) {
        remove_char(indices[i] - i);
    }
    delete[] indices;
}

int* String::all_sub_string(const String& sub, int& count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i < len; i++) {
        bool flag = true;
        for (int j = 0; j < sub.len; j++) {
            if (i + j >= len || str[i + j] != sub.str[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            temp[count++] = i;
        }
    }
    return temp;
}

int String::find_first(char ch) const {
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int String::find_last(char ch) const {
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int* String::find_all(char ch, int& count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            temp[count++] = i;
        }
    }
    return temp;
}

String String::regrow() {
    int newCap = cap + cap; // double the capacity
    String temp("", newCap);
    temp.len = len;
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    temp.str[len] = '\0';
    cap = newCap;
    delete[] str;
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = temp.str[i];
    }
    str[len] = '\0';
    return *this;
}

int String::length() const {
    return len;
}

void String::clear() {
    len = 0;
    if (str != nullptr) {
        str[0] = '\0';
    }
}