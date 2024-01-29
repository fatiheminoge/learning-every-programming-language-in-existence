#include <stdio.h>

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int toInt(char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        result = result * 10 + str[i] - '0';
    }
    return result;
}

int runOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int main() {
    char line[100];

    for (;;) {
        printf("Enter your calculation (+,*,-,/), for exit press q\n");

        if (fgets(line, sizeof(line), stdin)) {
            int currentSum = 0;
            char currentNum[100] = "";
            int lastTwoNums[2] = {0, 0};
            char currentOp = '+';
            for (int j = 0; line[j] != '\0'; j++) {
                char ch = line[j];

                if (ch == '\n') {
                    if (currentNum[0] != '\0') {
                        lastTwoNums[0] = lastTwoNums[1];
                        lastTwoNums[1] = toInt(currentNum);
                        currentSum = runOperation(lastTwoNums[0], lastTwoNums[1], currentOp);
                    }
                    printf("Result: %d\n", currentSum);
                    break;
                } else if (ch == 'q') {
                    return 0;
                } else if (isDigit(ch)) {
                    int len = 0;
                    while (currentNum[len] != '\0') len++;
                    currentNum[len] = ch;
                    currentNum[len + 1] = '\0';
                } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                    if (currentNum[0] != '\0') {
                        lastTwoNums[0] = lastTwoNums[1];
                        lastTwoNums[1] = toInt(currentNum);
                        currentSum = runOperation(lastTwoNums[0], lastTwoNums[1], currentOp);
                        currentOp = ch;
                        currentNum[0] = '\0';
                    }
                } else {
                    printf("Error: you entered an unsupported operation\n");
                    break;
                }
            }
        }
    }

    return 0;
}