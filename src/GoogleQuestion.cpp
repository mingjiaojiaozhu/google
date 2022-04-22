#include <iostream>
#include <array>
#include <cmath>
using namespace std;

static int get_iterations(int digit);
static long long calculate(array<long long, 100> &e, int index, int number, long long remainder);
static int get_total(long long value);
static bool is_prime(long long value);

int main(int argc, char **argv) {
    array<long long, 100> e{};
    e.fill(0L);
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
        cout << result << endl;
        total = total_pivot;
    }

    array<int, 10> numbers{};
    for (long long *p = begin(e) + 1; p != end(e); ++p) {
        long long value = *p;
        for (int i = 9; i >= 0; --i) {
            numbers[i] = (int) (value % 10);
            value /= 10;
        }

        for (int number : numbers) {
            if (total) {
                total += number - (int) (result / (long long) 1e9);
                if (total == total_pivot) {
                    result = (result % (long long) 1e9) * 10 + number;
                    cout << result << endl;
                    return 0;
                }
            }

            result = (result % (long long) 1e9) * 10 + number;
            if (!total && is_prime(result)) {
                cout << result << endl;
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

static long long calculate(array<long long, 100> &e, int index, int number, long long remainder) {
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

static bool is_prime(long long value) {
    if (!(value & 1)) {
        return false;
    }

    auto border = (long long) sqrt(value);
    for (long long i = 3L; i <= border; i += 2) {
        if (!(value % i)) {
            return false;
        }
    }
    return true;
}
