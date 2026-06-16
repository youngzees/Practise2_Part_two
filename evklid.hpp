#ifndef evklid_hpp
#define evklid_hpp

#include <cstdint>
//находит НОД(c, m) и коэффициенты u, v такие, что: c * u + m * v = НОД(c, m)
int64_t extendedGcd(int64_t c, int64_t m, int64_t &u, int64_t &v);

//находит обратное число d для c по модулю m
//выводит u и v (для задания 2)
//возвращает d, если НОД(c, m) = 1, иначе -1
int64_t findReverse(int64_t c, int64_t m, int64_t &u, int64_t &v);

//находит обратное число d для c по модулю m
//без вывода u и v (для задания 3)
//возвращает d, если НОД(c, m) = 1, иначе -1
int64_t modInverse(int64_t c, int64_t m);

#endif