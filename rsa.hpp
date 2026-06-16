#ifndef rsa_hpp
#define rsa_hpp

#include <string>
#include <vector>
#include <cstdint>

struct RSAKey {
    int64_t n;    //модуль (p * q)
    int64_t e;    //открытая экспонента (для шифрования)
    int64_t d;    //закрытая экспонента (для расшифрования)
};

//генерация ключей на основе простых чисел p и q
void generateKeys(RSAKey &key, int64_t p, int64_t q);

//шифрование одного символа: c = m^e mod n
int64_t encryptChar(int64_t m, int64_t e, int64_t n);

//расшифрование одного символа: m = c^d mod n
int64_t decryptChar(int64_t c, int64_t d, int64_t n);

//шифрование всей строки: каждый символ -> число -> зашифрованное число
std::vector<int64_t> encryptString(std::string text, int64_t e, int64_t n);

//расшифрование: каждое число -> расшифрованное число -> символ
std::string decryptString(std::vector<int64_t> cipher, int64_t d, int64_t n);

#endif