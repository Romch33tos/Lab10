#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class BigInt {
private:
    string value;

    void removeLeadingZeros() {
        while (value.length() > 1 && value[0] == '0') {
            value.erase(value.begin());
        }
        if (value.empty()) {
            value = "0"; 
        }
    }

public:
  
    BigInt() : value("0") {}

    BigInt(const string& str) {
        if (!isValid(str)) {
            value = "0"; 
        } else {
            value = str;
        }
        removeLeadingZeros();
    }

    bool isValid(const string& str) const {
        return all_of(str.begin(), str.end(), ::isdigit);
    }

    // Ввод большого числа
    void input() {
        cout << "Введите число: ";
        cin >> value;
        if (!isValid(value)) {
            value = "0"; 
        }
        removeLeadingZeros();
    }

    // Вывод числа
    void print() const {
        cout << value << endl;
    }

    BigInt operator+(const BigInt& other) const {
        string result;
        const string& num1 = this->value;
        const string& num2 = other.value;

        int carry = 0;
        int maxLength = max(num1.size(), num2.size());
        for (int i = 0; i < maxLength || carry; ++i) {
            int digit1 = i < num1.size() ? num1[num1.size() - 1 - i] - '0' : 0;
            int digit2 = i < num2.size() ? num2[num2.size() - 1 - i] - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10; // считаем перенос
            result.push_back(sum % 10 + '0'); // текущая цифра результата
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    // Оператор вычитания
    BigInt operator-(const BigInt& other) const {
        if (*this < other) {
            return BigInt("0");
        }

        string result;
        const string& num1 = this->value;
        const string& num2 = other.value;

        int borrow = 0;
        for (int i = 0; i < num1.size(); i++) {
            int digit1 = num1[num1.size() - 1 - i] - '0';
            int digit2 = i < num2.size() ? num2[num2.size() - 1 - i] - '0' : 0;

            int sub = digit1 - digit2 - borrow;
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(sub + '0');
        }
        reverse(result.begin(), result.end());
        return BigInt(result); 
    }

    // Оператор умножения
    BigInt operator*(const BigInt& other) const {
        const string& num1 = this->value;
        const string& num2 = other.value;

        string result(num1.size() + num2.size(), '0');
        for (int i = num1.size() - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = num2.size() - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0') + carry + (result[i + j + 1] - '0');
                carry = mul / 10;
                result[i + j + 1] = (mul % 10) + '0';
            }
            result[i] += carry; 
        }
        return BigInt(result); 
    }

    // Оператор целочисленного деления
    BigInt operator/(const BigInt& other) const {
        if (other.value == "0") {
            // Возвращаем "0" (или какое-либо другое значение) вместо исключения
            return BigInt("0");
        }

        BigInt dividend = *this;
        BigInt divisor = other;
        BigInt quotient;
        BigInt current;

        for (char digit : dividend.value) {
            current.value += digit;
            int count = 0;
            while (current >= divisor) {
                current = current - divisor;
                count++;
            }
            quotient.value += (char)(count + '0');
        }

        quotient.removeLeadingZeros(); 
        return quotient;
    }

    // Операторы сравнения
    bool operator>(const BigInt& other) const {
        if (this->value.length() != other.value.length())
            return this->value.length() > other.value.length();
        return this->value > other.value;
    }

    bool operator<(const BigInt& other) const {
        return !(*this >= other);
    }

    bool operator==(const BigInt& other) const {
        return this->value == other.value;
    }

    bool operator>=(const BigInt& other) const {
        return (*this > other) || (*this == other);
    }

    bool operator<=(const BigInt& other) const {
        return (*this < other) || (*this == other);
    }
};

int main() {
    BigInt num1, num2;
    num1.input();
    num2.input();

    cout << "Сложение: ";
    (num1 + num2).print();

    cout << "Вычитание: ";
    (num1 - num2).print();

    cout << "Умножение: ";
    (num1 * num2).print();

    cout << "Целочисленное деление: ";
    (num1 / num2).print();

    cout <<  "Первое больше чем второе? : " << ((num1 > num2) ? "да" : "нет") << endl;
    cout << "Первое меньше второго? : " << ((num1 < num2) ? "да" : "нет") << endl;
    cout << "Числа равны? : " << ((num1 == num2) ? "да" : "нет") << endl;

    return 0;
}
