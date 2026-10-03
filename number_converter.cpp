// Pinnacle Labs C++ Internship - Number Converter
// Converts non-negative whole numbers between Decimal, Binary,
// Octal and Hexadecimal. Input is validated before converting.

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

typedef unsigned long long ull;

struct Base {
    int value;
    string name;
};

const Base BASES[] = {
    {10, "Decimal"},
    {2,  "Binary"},
    {8,  "Octal"},
    {16, "Hexadecimal"}
};

int digitValue(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    ch = toupper(ch);
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    return -1;
}

// Check that every character is a valid digit for the base.
bool isValid(const string& s, int base) {
    if (s.empty()) return false;
    for (char ch : s) {
        int d = digitValue(ch);
        if (d < 0 || d >= base) return false;
    }
    return true;
}

// Text in `base` -> number. Returns false on overflow.
bool toDecimal(const string& s, int base, ull& result) {
    result = 0;
    for (char ch : s) {
        int d = digitValue(ch);
        if (result > (numeric_limits<ull>::max() - d) / base) return false;
        result = result * base + d;
    }
    return true;
}

// Number -> text in `base`.
string fromDecimal(ull n, int base) {
    if (n == 0) return "0";
    const string digits = "0123456789ABCDEF";
    string out;
    while (n > 0) {
        out += digits[n % base];
        n /= base;
    }
    reverse(out.begin(), out.end());
    return out;
}

int chooseBase(const string& prompt) {
    cout << "\n" << prompt << "\n";
    for (int i = 0; i < 4; i++)
        cout << "  " << i + 1 << ". " << BASES[i].name << "\n";
    while (true) {
        cout << "Choice (1-4): ";
        int c;
        if (cin >> c && c >= 1 && c <= 4) return BASES[c - 1].value;
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice.\n";
    }
}

string baseName(int base) {
    for (const Base& b : BASES)
        if (b.value == base) return b.name;
    return "";
}

void convertOne() {
    int from = chooseBase("Convert FROM:");
    int to = chooseBase("Convert TO:");

    string input;
    cout << "\nEnter the " << baseName(from) << " number: ";
    cin >> input;

    if (!isValid(input, from)) {
        cout << "Invalid " << baseName(from) << " number.\n";
        return;
    }
    ull value;
    if (!toDecimal(input, from, value)) {
        cout << "Number is too large.\n";
        return;
    }
    cout << "\n" << input << " (" << baseName(from) << ") = "
         << fromDecimal(value, to) << " (" << baseName(to) << ")\n";
}

void convertAll() {
    int from = chooseBase("Your number is in:");
    string input;
    cout << "\nEnter the " << baseName(from) << " number: ";
    cin >> input;

    if (!isValid(input, from)) {
        cout << "Invalid " << baseName(from) << " number.\n";
        return;
    }
    ull value;
    if (!toDecimal(input, from, value)) {
        cout << "Number is too large.\n";
        return;
    }
    cout << "\nDecimal     : " << fromDecimal(value, 10) << "\n";
    cout << "Binary      : " << fromDecimal(value, 2) << "\n";
    cout << "Octal       : " << fromDecimal(value, 8) << "\n";
    cout << "Hexadecimal : " << fromDecimal(value, 16) << "\n";
}

int main() {
    while (true) {
        cout << "\n========== NUMBER CONVERTER ==========\n";
        cout << "1. Convert from one base to another\n";
        cout << "2. Show a number in all bases\n";
        cout << "0. Exit\n";
        cout << "======================================\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }
        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        } else if (choice == 1) {
            convertOne();
        } else if (choice == 2) {
            convertAll();
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
