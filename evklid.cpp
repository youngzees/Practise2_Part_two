#include "evklid.hpp"
#include <iostream>

//расширенный алгоритм Евклида (рекурсивный)
long long extendedGcd(long long c, long long m, long long &u, long long &v) {
//если m = 0, то НОД(c, 0) = c
// c * 1 + 0 * 0 = c, поэтому u = 1, v = 0
    if (m == 0) {
        u = 1;
        v = 0;
        return c;
    }
    
    //рекурсивно вызываем с
    long long u1, v1;
    long long gcd = extendedGcd(m, c % m, u1, v1);
    
//формулы обратного хода:
    u = v1;
    v = u1 - (c / m) * v1;
    
    return gcd;
}

//находит обратное число с выводом u и v
long long findReverse(long long c, long long m, long long &u, long long &v) {
    std::cout << "Поиск d: " << c << " * d ≡ 1 (mod " << m << ")\n";
    
    //проверка, что модуль положительный
    if (m <= 0) {
        std::cerr << "Ошибка: m > 0\n";
        return -1;
    }
    
    //приводим c к положительному остатку
    c = ((c % m) + m) % m;
    std::cout << "c = " << c << "\n";
    
    //если c = 0, обратного числа нет (0 * d ≡ 0 mod m)
    if (c == 0) {
        std::cout << "Обратного числа нет\n";
        return -1;
    }
    
    long long gcd = extendedGcd(c, m, u, v);
    
    //вывод u и v 
    std::cout << "НОД(" << c << ", " << m << ") = " << gcd << "\n";
    std::cout << "Найдены коэффициенты: u = " << u << ", v = " << v << "\n";
    std::cout << "Проверка: " << c << " * " << u << " + " << m << " * " << v << " = " << (c*u + m*v) << "\n";
    
    //если НОД не равен 1, обратного числа нет
    if (gcd != 1) {
        std::cout << "Обратного числа нет\n";
        return -1;
    }
    
    //приводим u к положительному остатку — это и есть d
    long long d = (u % m + m) % m;
    std::cout << "d = u mod m = " << u << " mod " << m << " = " << d << "\n";
    
    return d;
}

//обратное число без вывода u и v
long long modInverse(long long c, long long m) {
    //проверка, что модуль положительный
    if (m <= 0) return -1;
    
    //приводим c к положительному остатку
    c = ((c % m) + m) % m;
    
    //если c = 0, обратного числа нет
    if (c == 0) return -1;
    
    //вызываем расширенный алгоритм Евклида
    long long u, v;
    long long gcd = extendedGcd(c, m, u, v);
    
    //если НОД не равен 1, обратного числа нет
    if (gcd != 1) return -1;
    
    //приводим u к положительному остатку — это и есть d
    return (u % m + m) % m;
}