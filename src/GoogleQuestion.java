import java.util.Arrays;

public class GoogleQuestion {
    public static void main(String[] args) {
        long[] e = new long[100];
        Arrays.fill(e, 0L);
        for (int i = getIterations(1000); i > 1; --i) {
            long remainder = calculate(e, 0, i, 1L);
            for (int j = 1; j < 100; ++j) {
                remainder = calculate(e, j, i, remainder);
            }
        }

        long result = e[0];
        int totalPivot = getTotal(result);
        int total = 0;
        if (isPrime(result)) {
            System.out.println(result);
            total = totalPivot;
        }

        int[] numbers = new int[10];
        for (int i = 1; i < 100; ++i) {
            long value = e[i];
            for (int j = 9; j >= 0; --j) {
                numbers[j] = (int) (value % 10);
                value /= 10;
            }

            for (int number : numbers) {
                if (0 != total) {
                    total += number - result / (long) 1e9;
                    if (total == totalPivot) {
                        result = (result % (long) 1e9) * 10 + number;
                        System.out.println(result);
                        return;
                    }
                }

                result = (result % (long) 1e9) * 10 + number;
                if (0 == total && isPrime(result)) {
                    System.out.println(result);
                    total = totalPivot;
                }
            }
        }
    }

    private static int getIterations(int digit) {
        int result = 1;
        double remainder = 1.0 / Math.E;
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

    private static long calculate(long[] e, int index, int number, long remainder) {
        long value = e[index] + remainder * (long) 1e10;
        e[index] = value / number;
        if (e[index] >= (long) 1e10) {
            e[index] -= (long) 1e10;
            ++e[index - 1];
        }
        return value % number;
    }

    private static int getTotal(long value) {
        int result = 0;
        while (0 != value) {
            result += value % 10;
            value /= 10;
        }
        return result;
    }

    private static boolean isPrime(long value) {
        if (0 == (value & 1)) {
            return false;
        }

        long border = (long) Math.sqrt(value);
        for (long i = 3L; i <= border; i += 2) {
            if (0 == (value % i)) {
                return false;
            }
        }
        return true;
    }
}
