#include <iostream>
#include "module.hpp"
#include "stepen.hpp"
#include "evklid.hpp"
#include "rsa.hpp"

enum class Menu {
    CALC_MOD_POW = 1, // Задание 1
    FIND_REVERSE_FULL = 2, // Задание 2
    FIND_REVERSE_SIMPLE = 3, // Задание 3
    RUN_RSA = 4, // Задание 4
    EXIT = 5
};

// Прототипы функций
void calcModPow(); // Задание 1
void findReverseFull(); // Задание 2
void findReverseSimple(); // Задание 3
void runRSA(); // Задание 4

int main() {
    int choice;
    
    do {
        std::cout << "\nМЕНЮ\n";
        std::cout << "1. a^x mod p (Ферма + двоичный)\n";
        std::cout << "2. Обратное число по модулю (с u и v)\n";
        std::cout << "3. Обратное число по модулю (только результат)\n";
        std::cout << "4. RSA шифрование\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите: ";
        std::cin >> choice;
        
        // Превращаем число в элемент перечисления
        Menu selected = static_cast<Menu>(choice);
        
        // Выбираем действие через switch
        switch (selected) {
            case Menu::CALC_MOD_POW:
                calcModPow();
                break;
                
            case Menu::FIND_REVERSE_FULL:
                findReverseFull();
                break;
                
            case Menu::FIND_REVERSE_SIMPLE:
                findReverseSimple();
                break;
                
            case Menu::RUN_RSA:
                runRSA();
                break;
                
            case Menu::EXIT:
                std::cout << "Выход...\n";
                break;
                
            default:
                std::cout << "Неверный выбор!\n";
                break;
        }
        
    } while (choice != 5);
    
    return 0;
}

// ЗАДАНИЕ 1: a^x mod p
void calcModPow() {
    std::cout << "\na^x mod p\n";
    
    long long a, x, p;
    
    //ввод данных
    std::cout << "Введите a: ";
    std::cin >> a;
    std::cout << "Введите степень x: ";
    std::cin >> x;
    std::cout << "Введите модуль p: ";
    std::cin >> p;
    
    //проверка, что p > 0
    if (p <= 0) {
        std::cerr << "Ошибка: p > 0\n";
        return;
    }
    
    //проверка простоты p
    if (isPrime(p)) {
        std::cout << "p = " << p << " — простое\n";
    } else {
        std::cout << "p = " << p << " — составное\n";
    }
    
    //проверка теоремы Ферма
    checkFerma(a, p);
    
    //вычисление через calcStep
    long long res = calcStep(a, x, p, true);
    
    //вывод результата
    std::cout << "Ответ: " << a << "^" << x << " mod " << p << " = " << res << "\n";
}

// ЗАДАНИЕ 2: обратное число с выводом u и v
void findReverseFull() {
    std::cout << "\nОбратное число (с u и v)\n";
    
    long long c, m;
    long long u, v;
    //будут заполнены в findReverse
    
    //ввод данных
    std::cout << "Введите c: ";
    std::cin >> c;
    std::cout << "Введите m: ";
    std::cin >> m;
    
    //вызов функции (она выведет u и v)
    long long d = findReverse(c, m, u, v);
    
    //вывод результата
    if (d != -1) {
        std::cout << "Результат: d = " << d << "\n";
        std::cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
    } else {
        std::cout << "Обратного числа не существует\n";
    }
}

// ЗАДАНИЕ 3: обратное число (только результат, без u и v)
void findReverseSimple() {
    std::cout << "\nОбратное число (только результат)\n";
    
    long long c, m;
    
    //ввод данных
    std::cout << "Введите c: ";
    std::cin >> c;
    std::cout << "Введите m: ";
    std::cin >> m;
    
    //вызов функции (без u и v)
    long long d = modInverse(c, m);
    
    //вывод результата
    if (d != -1) {
        std::cout << c << "^{-1} mod " << m << " = " << d << "\n";
        std::cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
    } else {
        std::cout << "Обратного числа не существует\n";
    }
}

// ЗАДАНИЕ 4: RSA шифрование
void runRSA() {
    std::cout << "\nRSA шифрование\n";
    
    RSAKey key;
    long long p, q;
    std::string text;
    
    //ввод простых чисел
    std::cout << "Введите простое p: ";
    std::cin >> p;
    std::cout << "Введите простое q: ";
    std::cin >> q;
    
    //генерация ключей
    generateKeys(key, p, q);
    
    //вывод ключей
    std::cout << "Открытый ключ: (n = " << key.n << ", e = " << key.e << ")\n";
    std::cout << "Закрытый ключ: (n = " << key.n << ", d = " << key.d << ")\n";
    
    //ввод текста для шифрования
    std::cout << "Введите текст: ";
    std::cin.ignore();  //очищаем буфер
    std::getline(std::cin, text);   //читаем строку с пробелами
    
    //шифрование
    std::vector<long long> encrypted = encryptString(text, key.e, key.n);
    
    //вывод зашифрованного текста
    std::cout << "Зашифровано: ";
    for (long long c : encrypted) {
        std::cout << c << " ";
    }
    std::cout << "\n";
    
    //расшифрование
    std::string decrypted = decryptString(encrypted, key.d, key.n);
    
    //вывод расшифрованного текста
    std::cout << "Расшифровано: " << decrypted << "\n";
}