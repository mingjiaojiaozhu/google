function main() {
    let e = new Array(100).fill(0);
    for (let i = getIterations(1000); i > 1; --i) {
        let remainder = calculate(e, 0, i, 1)
        for (let j = 1; j < 100; ++j) {
            remainder = calculate(e, j, i, remainder)
        }
    }

    let result = e[0]
    let totalPivot = getSum(result)
    let total = 0
    if (isPrime(result)) {
        console.log(result)
        total = totalPivot
    }

    let numbers = new Array(10)
    for (let value of e.slice(2)) {
        for (let i = 9; i >= 0; --i) {
            numbers[i] = value % 10
            value = Math.floor(value / 10)
        }

        for (let number of numbers) {
            if (total) {
                total += number - Math.floor(result / 1e9)
                if (total === totalPivot) {
                    result = (result % 1e9) * 10 + number
                    console.log(result)
                    return
                }
            }

            result = (result % 1e9) * 10 + number
            if (!total && isPrime(result)) {
                console.log(result)
                total = totalPivot
            }
        }
    }
}

function getIterations(digit) {
    let result = 1
    let remainder = 1.0 / Math.E
    while (digit >= 0) {
        while (remainder < 1) {
            ++result
            remainder *= result
        }
        while (remainder >= 1 && digit >= 0) {
            remainder /= 10
            --digit
        }
    }
    return result - 1
}

function calculate(e, index, number, remainder) {
    let value = e[index] + remainder * 1e10
    e[index] = Math.floor(value / number)
    if (e[index] >= 1e10) {
        e[index] -= 1e10
        ++e[index - 1]
    }
    return value % number
}

function getSum(value) {
    let result = 0
    while (value) {
        result += value % 10
        value = Math.floor(value / 10)
    }
    return result
}

function isPrime(value) {
    if (0 === (value & 1)) {
        return false
    }

    let border = Math.floor(Math.sqrt(value))
    for (let i = 3; i <= border; i += 2) {
        if (!(value % i)) {
            return false
        }
    }
    return true
}

main()
