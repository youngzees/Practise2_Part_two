#ifndef rsa_hpp
#define rsa_hpp

#include <string>
#include <vector>

struct RSAKey {
    long long n;    //модуль (p * q)
    long long e;    //открытая экспонента (для шифрования)
    long long d;    //закрытая экспонента (для расшифрования)
};

//генерация ключей на основе простых чисел p и q
void generateKeys(RSAKey &key, long long p, long long q);

//шифрование одного символа: c = m^e mod n
long long encryptChar(long long m, long long e, long long n);

//расшифрование одного символа: m = c^d mod n
long long decryptChar(long long c, long long d, long long n);

//шифрование всей строки: каждый символ -> число -> зашифрованное число
std::vector<long long> encryptString(std::string text, long long e, long long n);

//расшифрование: каждое число -> расшифрованное число -> символ
std::string decryptString(std::vector<long long> cipher, long long d, long long n);

#endif