#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BASE 10

void withIntAsOutput(int input, int base) {
    int cnt = 0;

    int temp = input;
    unsigned long result = 0;

    do {
        result += round(temp % base) * pow(DEFAULT_BASE, cnt);
        temp = temp / base;
        cnt++;
    } while (temp != 0);

    printf("Decimal: %d -> Base %d = %lu", input, base, result);
}

int countDigits(unsigned long num) {
    int digits = 0;
    if (num == 0) return 1;
    while (num > 0) {
        num /= DEFAULT_BASE;
        digits++;
    }
    return digits;
}

char toASCII(const unsigned long add) {
    return (char) add + (add > 26 ? 96 : 64);
}

int fromASCII(const char sub) {
    const int code = (int) sub;
    if (code < 64) return code - 48;
    //printf("%d\n", code);
    return code - (code - 64 > 26 ? 96 : 64) + 9;
}

void optimizedOutput(const unsigned long input, const unsigned long base) {

    if (input > 0) {
        optimizedOutput(input / base, base);
        const unsigned long tmp = input % base;
        if (tmp > 9) {
            printf("%c", toASCII(tmp - 9));
        } else printf("%lu", tmp);
    }

}

int getInput(unsigned long input, const unsigned long base) {
    double cnt = 0;
    double result = 0;
    while (input > 0) {
        result += (double) (input % DEFAULT_BASE) * pow((double) base, cnt);
        input /= DEFAULT_BASE;
        cnt++;
    }
    return round(result);
}

int main(void) {
    unsigned long inputNumber = 0, newBase = 10, currentBase = 10;
    char inputString[500];

    printf("Enter a non negative number: ");
    scanf("%s", inputString);
    fflush(stdin);

    printf("Current base: ");
    scanf("%lu", &currentBase);
    fflush(stdin);

    printf("Enter the base to convert to: ");
    scanf("%lu", &newBase);
    fflush(stdin);

    if (currentBase < 1 && newBase < 1) {
        printf("Invalid base. Base must be greater than 1!");
        return true;
    }

    const size_t size = strlen(inputString);
    //printf("strlen = %lu\n", size);

    for (size_t i = size; i > 0; i--) {
        const long num = fromASCII(inputString[i - 1]);
        if (num >= currentBase) {
            printf("Invalid base %lu for number %s! Can not contain %lu!", currentBase, inputString, num);
            return 0;
        }
        const long mltpr = (long) pow(currentBase, size - i);
        //printf("num = %ld\n", num);
        //printf("mltpr = %ld\n", mltpr);
        inputNumber += num * mltpr;
        //printf("cnt = %lu\n", i);
        //printf("inputNum = %ld\n", inputNumber);
    }
    currentBase = DEFAULT_BASE;

    inputNumber = getInput(inputNumber, currentBase);

    //withIntAsOutput(input, base);
    optimizedOutput(inputNumber, newBase);

    return 0;
}


