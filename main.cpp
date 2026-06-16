#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <limits>

#include "module.hpp"
#include "stepen.hpp"
#include "evklid.hpp"
#include "rsa.hpp"

enum class Menu {
    CALC_MOD_POW = 1,
    FIND_REVERSE_FULL = 2,
    FIND_REVERSE_SIMPLE = 3,
    RUN_RSA = 4,
    EXIT = 5
};

//защита от букв и мусора
int64_t getValidNumber(const std::string& prompt) {
    int64_t value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ошибка: введите число\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    int choice;
    do {
        std::cout << "\nменю\n";
        std::cout << "1. a^x mod p (ферма + двоичный)\n";
        std::cout << "2. обратное число (с u и v)\n";
        std::cout << "3. обратное число (только результат)\n";
        std::cout << "4. rsa шифрование\n";
        std::cout << "5. выход\n";
        std::cout << "выберите: ";
        choice = static_cast<int>(getValidNumber(""));
        Menu selected = static_cast<Menu>(choice);
        switch (selected) {
            case Menu::CALC_MOD_POW: {
                std::cout << "\na^x mod p\n";
                int64_t a = getValidNumber("введите a: ");
                int64_t x;
                do {
                    x = getValidNumber("введите степень x (x >= 0): ");
                    if (x < 0) std::cout << "ошибка: степень не может быть отрицательной\n";
                } while (x < 0);
                int64_t p;
                do {
                    p = getValidNumber("введите простой модуль p: ");
                    if (p <= 1 || !isPrime(p)) std::cout << "ошибка: модуль должен быть простым числом\n";
                } while (p <= 1 || !isPrime(p));
                if (isPrime(p)) {
                    std::cout << "p = " << p << " — простое\n";
                }
                checkFerma(a, p);
                int64_t res = calcStep(a, x, p, true);
                std::cout << "ответ: " << a << "^" << x << " mod " << p << " = " << res << "\n";
                break;
            }
            case Menu::FIND_REVERSE_FULL: {
                std::cout << "\nобратное число (с u и v)\n";
                int64_t c = getValidNumber("введите c: ");
                int64_t m;
                do {
                    m = getValidNumber("введите m (> 0): ");
                    if (m <= 0) std::cout << "ошибка: m должно быть > 0\n";
                } while (m <= 0);
                int64_t u, v;
                int64_t d = findReverse(c, m, u, v);
                if (d != -1) {
                    std::cout << "результат: d = " << d << "\n";
                    std::cout << "проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
                } else {
                    std::cout << "обратного числа не существует\n";
                }
                break;
            }
            case Menu::FIND_REVERSE_SIMPLE: {
                std::cout << "\nобратное число (только результат)\n";
                int64_t c = getValidNumber("введите c: ");
                int64_t m;
                do {
                    m = getValidNumber("введите m (> 0): ");
                    if (m <= 0) std::cout << "ошибка: m должно быть > 0\n";
                } while (m <= 0);
                int64_t d = modInverse(c, m);
                if (d != -1) {
                    std::cout << c << "^{-1} mod " << m << " = " << d << "\n";
                    std::cout << "проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
                } else {
                    std::cout << "обратного числа не существует\n";
                }
                break;
            }
            case Menu::RUN_RSA: {
                std::cout << "\nrsa шифрование\n";
                int64_t p, q;
                do {
                    p = getValidNumber("введите простое p: ");
                    if (!isPrime(p)) std::cout << "ошибка: p должно быть простым\n";
                } while (!isPrime(p));
                do {
                    q = getValidNumber("введите простое q: ");
                    if (!isPrime(q)) std::cout << "ошибка: q должно быть простым\n";
                } while (!isPrime(q));
                RSAKey key;
                generateKeys(key, p, q);
                std::cout << "открытый ключ: (n = " << key.n << ", e = " << key.e << ")\n";
                std::cout << "закрытый ключ: (n = " << key.n << ", d = " << key.d << ")\n";
                std::cout << "введите текст: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string text;
                std::getline(std::cin, text);
                std::vector<int64_t> encrypted = encryptString(text, key.e, key.n);
                std::cout << "зашифровано: ";
                for (int64_t c : encrypted) {
                    std::cout << c << " ";
                }
                std::cout << "\n";
                std::string decrypted = decryptString(encrypted, key.d, key.n);
                std::cout << "расшифровано: " << decrypted << "\n";
                break;
            }
            case Menu::EXIT:
                std::cout << "выход...\n";
                break;
            default:
                std::cout << "неверный выбор\n";
                break;
        }
    } while (choice != 5);
    return 0;
}