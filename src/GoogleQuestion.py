import math
from typing import List

def main() -> None:
    e = [0 for _ in range(100)]
    for i in range(get_iterations(1000), 1, -1):
        remainder = calculate(e, 0, i, 1)
        for j in range(1, 100):
            remainder = calculate(e, j, i, remainder)

    result = e[0]
    total_pivot, total = get_total(result), 0
    if is_prime(result):
        print(result)
        total = total_pivot

    numbers = [0 for _ in range(10)]
    for value in e[1:]:
        for i in range(9, -1, -1):
            numbers[i] = value % 10
            value //= 10

        for number in numbers:
            if total:
                total += number - result // int(1e9)
                if total == total_pivot:
                    result = (result % int(1e9)) * 10 + number
                    print(result)
                    return

            result = (result % int(1e9)) * 10 + number
            if not total and is_prime(result):
                print(result)
                total = total_pivot

def get_iterations(digit: int) -> int:
    result, remainder = 1, 1.0 / math.e
    while digit >= 0:
        while remainder < 1:
            result += 1
            remainder *= result
        while remainder >= 1 and digit >= 0:
            remainder /= 10
            digit -= 1
    return result - 1

def calculate(e: List[int], index: int, number: int, remainder: int) -> int:
    value = e[index] + remainder * int(1e10)
    e[index] = value // number
    if e[index] >= int(1e10):
        e[index] -= int(1e10)
        e[index - 1] += 1
    return value % number

def get_total(value: int) -> int:
    result = 0
    while value:
        result += value % 10
        value //= 10
    return result

def is_prime(value: int) -> bool:
    if not (value & 1):
        return False

    border = int(math.sqrt(value))
    for i in range(3, border + 1, 2):
        if not value % i:
            return False
    return True

if __name__ == '__main__':
    main()
