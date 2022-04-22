#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int get_iterations(int digit);
static long long calculate(long long *e, int index, int number, long long remainder);
static int get_total(long long value);
static int is_prime(long long value);

int main(int argc, char **argv) {
    long long *e = (long long *) malloc(sizeof(long long) * 100);
    memset(e, 0L, sizeof(long long) * 100);
    for (int i = get_iterations(1000); i > 1; --i) {
        long long remainder = calculate(e, 0, i, 1L);
        for (int j = 1; j < 100; ++j) {
            remainder = calculate(e, j, i, remainder);
        }
    }

    long long result = e[0];
    int total_pivot = get_total(result);
    int total = 0;
    if (is_prime(result)) {
        printf("%lld\n", result);
        total = total_pivot;
    }

    int *numbers = (int *) malloc(sizeof(int) * 10);
    for (int i = 1; i < 100; ++i) {
        long long value = e[i];
        for (int j = 9; j >= 0; --j) {
            numbers[j] = (int) (value % 10);
            value /= 10;
        }

        for (int j = 0; j < 10; ++j) {
            if (total) {
                total += numbers[j] - (int) (result / (long long) 1e9);
                if (total == total_pivot) {
                    result = (result % (long long) 1e9) * 10 + numbers[j];
                    printf("%lld\n", result);
                    return 0;
                }
            }

            result = (result % (long long) 1e9) * 10 + numbers[j];
            if (!total && is_prime(result)) {
                printf("%lld\n", result);
                total = total_pivot;
            }
        }
    }
    return 0;
}

static int get_iterations(int digit) {
    int result = 1;
    double remainder = 1.0 / M_E;
    while (digit >= 0) {
        while (remainder < 1) {
            ++result;
            remainder *= result;
        }
        while (remainder >= 1 && digit >= 0) {
            remainder /= 10;
            --digit;
        }
    }
    return result - 1;
}

static long long calculate(long long *e, int index, int number, long long remainder) {
    long long value = e[index] + remainder * (long long) 1e10;
    e[index] = value / number;
    if (e[index] >= (long long) 1e10) {
        e[index] -= (long long) 1e10;
        ++e[index - 1];
    }
    return value % number;
}

static int get_total(long long value) {
    int result = 0;
    while (value) {
        result += (int) (value % 10);
        value /= 10;
    }
    return result;
}

static int is_prime(long long value) {
    if (!(value & 1)) {
        return 0;
    }

    long long border = (long long) sqrt((double) value);
    for (long long i = 3L; i <= border; i += 2) {
        if (!(value % i)) {
            return 0;
        }
    }
    return 1;
}
