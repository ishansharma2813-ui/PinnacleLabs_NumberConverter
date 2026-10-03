# Pinnacle Labs - Number Converter (C++)

Console program that converts whole numbers between **Decimal, Binary, Octal and Hexadecimal**.

## Features
- Convert from any base to any other base
- Show one number in all four bases at once
- Input validation (wrong digits for the chosen base, empty input, overflow)

## How it works
1. The input text is checked digit by digit against the chosen base.
2. It is converted to a number (`toDecimal`) using repeated multiply-and-add.
3. The number is converted to the target base (`fromDecimal`) using repeated division by the base.

## Run
```bash
g++ -std=c++17 -o number_converter number_converter.cpp
./number_converter
```

## Author
Ishan Sharma
