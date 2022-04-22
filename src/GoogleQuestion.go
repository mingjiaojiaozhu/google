package main

import (
    "fmt"
    "math"
)

func main() {
    e := make([]int64, 100)
    for i := 0; i < 100; i++ {
        e[i] = 0
    }
    for i := getIterations(1000); i > 1; i-- {
        remainder := calculate(e, 0, i, 1)
        for j := 1; j < 100; j++ {
            remainder = calculate(e, j, i, remainder)
        }
    }

    result := e[0]
    totalPivot := getTotal(result)
    total := 0
    if isPrime(result) {
        fmt.Println(result)
        total = totalPivot
    }

    numbers := [10]int{}
    for _, value := range e[1 : ] {
        for i := 9; i >= 0; i-- {
            numbers[i] = int(value % 10)
            value /= 10
        }

        for _, number := range numbers {
            if 0 != total {
                total += number - int(result / int64(1e9))
                if total == totalPivot {
                    result = (result % int64(1e9)) * 10 + int64(number)
                    fmt.Println(result)
                    return
                }
            }

            result = (result % int64(1e9)) * 10 + int64(number)
            if 0 == total && isPrime(result) {
                fmt.Println(result)
                total = totalPivot
            }
        }
    }
}

func getIterations(digit int) int {
    result := 1
    remainder := 1.0 / math.E
    for digit >= 0 {
        for remainder < 1 {
            result += 1
            remainder *= float64(result)
        }
        for remainder >= 1 && digit >= 0 {
            remainder /= 10
            digit -= 1
        }
    }
    return result - 1
}

func calculate(e []int64, index int, number int, remainder int64) int64 {
    value := e[index] + remainder * int64(1e10)
    e[index] = value / int64(number)
    if (e[index] >= int64(1e10)) {
        e[index] -= int64(1e10)
        e[index - 1]++
    }
    return value % int64(number)
}

func getTotal(value int64) int {
    result := 0
    for 0 != value {
        result += int(value % 10)
        value /= 10
    }
    return result
}

func isPrime(value int64) bool {
    if 0 == (value & 1) {
        return false
    }

    border := int64(math.Sqrt(float64(value)))
    for i := int64(3); i < border; i += 2 {
        if 0 == (value % i) {
            return false
        }
    }
    return true
}
