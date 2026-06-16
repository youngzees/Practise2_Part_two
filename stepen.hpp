#ifndef stepen_hpp
#define stepen_hpp

//dычисляет a^x mod p
long long fastBinStep(long long a, long long x, long long p);

//возведение в степень через теорему Ферма
//сначала упрощает степень, затем вызывает fastBinStep
long long fermaStep(long long a, long long x, long long p);

//основная функция выбора алгоритма
//если useFerma = true и p простое — использует fermaStep
//иначе — fastBinStep
long long calcStep(long long a, long long x, long long p, bool useFerma = true);

#endif