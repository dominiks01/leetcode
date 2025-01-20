#include <limits.h>
#include <stdlib.h>

int divide(int dividend, int divisor) {

    if (divisor == 0) {
        return INT_MAX;
    }

    if (divisor == 1) {
        return dividend;
    }

    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    int isNegative = (dividend < 0) ^ (divisor < 0);

    long long absDividend = llabs(dividend);
    long long absDivisor = llabs(divisor);

    int quotient = 0;
    while (absDividend >= absDivisor) {
        long long temp = absDivisor;
        long long multiple = 1;

        while (absDividend >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }

        absDividend -= temp;
        quotient += multiple;
    }

    return isNegative ? -quotient : quotient;
}