#ifndef STRING_H
#define STRING_H

#include <iostream>
using namespace std;

class String {

    int len{};
    int cap{};
    char* str{};

public:
    //constructors
    String();
    String(const char* s, int n);
    String(const String& s);
    String(const char* s);
    String(int n);

    //operator overload
    friend ostream& operator<<(ostream& os, const String& s);
    friend istream& operator>>(istream& in, String& s);
    String operator+(const String& s) const;
    String& operator+=(const String& s);
    String& operator=(const String& s);
    const char operator[](int i) const;
    char& operator[](int i);

    //utility functions
    static String itos(int n);
    String insert_char(int n, char s);
    String insert_string(int n, const String& sub);
    String& replace_first(char s);
    static int get_size(const char* s);
    void to_upper();
    void to_lower();
    String& trim();
    static String trim(const char* s);
    int stoi() const;
    void display() const;
    ~String();
    [[nodiscard]] bool is_equal(const String& m) const;
    [[nodiscard]] bool is_less(const String& m) const;

    [[nodiscard]] bool is_greater(const String& m) const;
    [[nodiscard]] String concat(const String& s) const;
    String* split(char s, int& count) const;
    String* split(const String& s, int& count) const;
    void remove_char(int n);
    void remove_first(char s);
    void remove_last(char s);
    void remove_all(char a);
    int* all_sub_string(const String& s, int& count) const;
    [[nodiscard]] int find_first(char s) const;
    [[nodiscard]] int find_last(char s) const;
    int* find_all(char s, int& count) const;
    String regrow();
    [[nodiscard]] int length()  const;
    void clear();
};

#endif