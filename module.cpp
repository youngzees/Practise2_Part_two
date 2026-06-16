#include "module.hpp"
#include <cmath> 
#include <iostream> 
#include <cstdint>

bool isPrime(int64_t n) {
// Числа меньше или равные 1 — не простые
    if (n <= 1) return false;
// 2 и 3 — простые
    if (n <= 3) return true;
// Если число делится на 2 или 3 — оно составное
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Перебираем делители до корня из n
    for (int64_t i = 5; i * i <= n; i += 6) { // Все простые числа имеют вид 6k ± 1, поэтому шаг 6
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    
    return true; //не подошел - простое
}

// Проверка теоремы Ферма
bool checkFerma(int64_t a, int64_t p) {
    //только для простого p
    if (!isPrime(p)) {
        std::cout << "Модуль p = " << p << " не простой. Теорема Ферма не работает.\n";
        return false;
    }
    
    //если a кратно p, то a mod p = 0, результат тривиальный
    if (a % p == 0) {
        std::cout << "a делится на p, тривиальный случай.\n";
        return true;
    }
    
    //иначе теорема Ферма применима
    std::cout << "Проверка теоремы Ферма: a^(p-1) ≡ 1 (mod p)\n";
    return true;
}