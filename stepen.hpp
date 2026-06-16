#ifndef stepen_hpp
#define stepen_hpp

#include <cstdint>
//вычисляет a^x mod p
int64_t fastBinStep(int64_t a, int64_t x, int64_t p);

//возведение в степень через теорему Ферма
//сначала упрощает степень, затем вызывает fastBinStep
int64_t fermaStep(int64_t a, int64_t x, int64_t p);

//основная функция выбора алгоритма
//если useFerma = true и p простое — использует fermaStep
//иначе — fastBinStep
int64_t calcStep(int64_t a, int64_t x, int64_t p, bool useFerma = true);

#endif