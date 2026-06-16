#include "rsa.hpp"
#include "evklid.hpp"
#include "stepen.hpp"
#include <iostream>

void generateKeys(RSAKey &key, long long p, long long q) {
//модуль n = p * q
    key.n = p * q;
    
//функция Эйлера
    long long phi = (p - 1) * (q - 1);
    
    //открытая экспонента
    key.e = 65537;
    
    //закрытая экспонента: d = e^(-1) mod φ(n)
    key.d = modInverse(key.e, phi);
    
    //вывод ключей
    std::cout << "n = " << key.n << ", e = " << key.e << ", d = " << key.d << "\n";
}

//шифрование одного символа
long long encryptChar(long long m, long long e, long long n) {
//вычисляем m^e mod n
    return fastBinStep(m, e, n);
}

//расшифрование одного символа
long long decryptChar(long long c, long long d, long long n) {
    //вычисляем c^d mod n
    return fastBinStep(c, d, n);
}

//шифрование строки
std::vector<long long> encryptString(std::string text, long long e, long long n) {
    std::vector<long long> result;
    std::cout << "\nШифрование:\n";
    
    //проходим по каждому символу
    for (char ch : text) {
    //превращаем символ в число (его код)
        long long code = (long long)ch;
        
    //шифруем: encrypted = code^e mod n
        long long encrypted = encryptChar(code, e, n);
        
    //добавляем в результат
        result.push_back(encrypted);
        
    //выводим промежуточный шаг
        std::cout << "'" << ch << "' (" << code << ") -> " << encrypted << "\n";
    }
    
    return result;
}

//расшифрование строки
std::string decryptString(std::vector<long long> cipher, long long d, long long n) {
    std::string result;
    std::cout << "\nРасшифрование:\n";
    
    //проходим по каждому зашифрованному числу
    for (long long c : cipher) {
        //расшифровываем: decrypted = c^d mod n
        long long decrypted = decryptChar(c, d, n);
        
        //превращаем число обратно в символ
        result.push_back((char)decrypted);
        
        //выводим промежуточный шаг
        std::cout << c << " -> " << decrypted << " -> '" << (char)decrypted << "'\n";
    }
    
    return result;
}