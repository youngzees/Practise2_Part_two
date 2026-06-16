#ifndef evklid_hpp
#define evklid_hpp

//находит НОД(c, m) и коэффициенты u, v такие, что: c * u + m * v = НОД(c, m)
long long extendedGcd(long long c, long long m, long long &u, long long &v);

//находит обратное число d для c по модулю m
//выводит u и v (для задания 2)
//возвращает d, если НОД(c, m) = 1, иначе -1
long long findReverse(long long c, long long m, long long &u, long long &v);

//находит обратное число d для c по модулю m
//без вывода u и v (для задания 3)
//возвращает d, если НОД(c, m) = 1, иначе -1
long long modInverse(long long c, long long m);

#endif