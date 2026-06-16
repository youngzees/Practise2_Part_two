#include "rsa.hpp"
#include "evklid.hpp"
#include "stepen.hpp"
#include <iostream>
#include <cstdint>

void generateKeys(RSAKey &key, int64_t p, int64_t q) {
//модуль n = p * q
    key.n = p * q;
    
//функция Эйлера
    int64_t phi = (p - 1) * (q - 1);
    
    //открытая экспонента
    key.e = 65537;
    
    //закрытая экспонента: d = e^(-1) mod φ(n)
    key.d = modInverse(key.e, phi);
    
    //вывод ключей
    std::cout << "n = " << key.n << ", e = " << key.e << ", d = " << key.d << "\n";
}

//шифрование одного символа
int64_t encryptChar(int64_t m, int64_t e, int64_t n) {
//вычисляем m^e mod n
    return fastBinStep(m, e, n);
}

//расшифрование одного символа
int64_t decryptChar(int64_t c, int64_t d, int64_t n) {
    //вычисляем c^d mod n
    return fastBinStep(c, d, n);
}

//шифрование строки
std::vector<int64_t> encryptString(std::string text, int64_t e, int64_t n) {
    std::vector<int64_t> result;
    std::cout << "\nШифрование:\n";
    
    //проходим по каждому символу
    for (char ch : text) {
    //превращаем символ в число (его код)
        int64_t code = (int64_t)ch;
        
    //шифруем: encrypted = code^e mod n
        int64_t encrypted = encryptChar(code, e, n);
        
    //добавляем в результат
        result.push_back(encrypted);
        
    //выводим промежуточный шаг
        std::cout << "'" << ch << "' (" << code << ") -> " << encrypted << "\n";
    }
    
    return result;
}

//расшифрование строки
std::string decryptString(std::vector<int64_t> cipher, int64_t d, int64_t n) {
    std::string result;
    std::cout << "\nРасшифрование:\n";
    
    //проходим по каждому зашифрованному числу
    for (int64_t c : cipher) {
        //расшифровываем: decrypted = c^d mod n
        int64_t decrypted = decryptChar(c, d, n);
        
        //превращаем число обратно в символ
        result.push_back((char)decrypted);
        
        //выводим промежуточный шаг
        std::cout << c << " -> " << decrypted << " -> '" << (char)decrypted << "'\n";
    }
    
    return result;
}