#include "stepen.hpp"
#include "module.hpp"
#include <iostream>
#include <vector>

//двоичный метод
long long fastBinStep(long long a, long long x, long long p) {
    long long result = 1;   //начинаем с 1 (нейтральный элемент)
    a = a % p;  //приводим a к остатку по модулю p
    
    //пока есть биты в степени x
    while (x > 0) {
    //если текущий бит = 1, умножаем результат на a
        if (x % 2 == 1) {
            result = (result * a) % p;
        }
        //переход к следующему биту
        a = (a * a) % p;
        //переходим к следующему биту (делим на 2)
        x = x / 2;
    }
    
    return result;
}

//возведение в степень через теорему Ферма
//упрощает степень: x = x % (p-1), затем вызывает fastBinStep
long long fermaStep(long long a, long long x, long long p) {
    //если p не простое — теорема Ферма не работает
    if (!isPrime(p)) {
        return fastBinStep(a, x, p);
    }
    
    //если a кратно p — результат 0
    if (a % p == 0) {
        return 0;
    }
    
    //упрощаем степень по теореме Ферма: a^(p-1) ≡ 1 (mod p)
    long long newX = x % (p - 1);
    
    //если новая степень 0, значит x кратен (p-1), результат 1
    if (newX == 0) {
        return 1;
    }
    
    //вычисляем уже упрощённую степень
    return fastBinStep(a, newX, p);
}

//основная функция выбора алгоритма
long long calcStep(long long a, long long x, long long p, bool useFerma) {
    //если useFerma = true и p простое — используем Ферма
    if (useFerma && isPrime(p)) {
        return fermaStep(a, x, p);
    } else {
    //иначе — обычный двоичный алгоритм
        return fastBinStep(a, x, p);
    }
}