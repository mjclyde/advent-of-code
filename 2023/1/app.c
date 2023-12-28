// app.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH	255

char stringNumbers[9][10] = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

struct MatchResult {
	int firstIndex;
	int lastIndex;
	int foundSomething;
};

struct NumericResult {
	int firstNumber;
	int firstIndex;
	int lastNumber;
	int lastIndex;
	int foundFirst;
	int foundLast;
};

int isDigit(char ch) {
	return ch >= '1' && ch <= '9';
}

int charDigitToInt(char ch) {
	return (ch - '0');
}

struct MatchResult findFirstAndLastMatch(char *str, char *search) {
	struct MatchResult result = {0, 0, 0};
	char *match = NULL;
	char *nextStr = str;
	do {
		match = strstr(nextStr, search);
		if (match != NULL) {
			nextStr = match + 1;
			result.lastIndex = (int)(match - str);
			if (!result.foundSomething) {
				result.foundSomething = 1;
				result.firstIndex = result.lastIndex;
			}
		}
	} while (NULL != match);
	return result;
}

struct NumericResult findFirstAndLastNumbers(char *str) {
	struct NumericResult result = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < strlen(str); i++) {
		if (isDigit(str[i])) {
			result.lastNumber = charDigitToInt(str[i]);
			result.lastIndex = i;
			result.foundLast = 1;
			if (!result.foundFirst) {
				result.foundFirst = 1;
				result.firstNumber = result.lastNumber;
				result.firstIndex = i;
			}
		}
	}
	return result;
}

struct NumericResult findFirstAndLastStringNumbers(char *str) {
	struct NumericResult result = {0, 0, 0, 0, 0, 0};
	for (int i = 1; i <= 9; i++) {
		struct MatchResult res = findFirstAndLastMatch(str, stringNumbers[i - 1]);
		if (!res.foundSomething) {
			continue;
		}
		if (res.firstIndex < result.firstIndex || !result.foundFirst) {
			result.firstIndex = res.firstIndex;
			result.firstNumber = i;
			result.foundFirst = 1;
		}
		if (res.lastIndex > result.lastIndex || !result.foundLast) {
			result.lastIndex = res.lastIndex;
			result.lastNumber = i;
			result.foundLast = 1;
		}
	}
	return result;
}

int main() {
	FILE *ptr;
	char ch;

	int val = 0;
	int sum = 0;

	char line[MAX_LINE_LENGTH]; 
	int charIndex = 0;

	ptr = fopen("input.txt", "r");

	if (NULL == ptr) {
		printf("file cannot be opened\n");
	}

	do {
		ch = fgetc(ptr);
		if (ch == EOF && !charIndex) {
			continue;
		}
		line[charIndex] = ch == '\n' || ch == EOF ? '\0' : ch;

		if ('\0' == line[charIndex]) {
			printf("%s\n", line);
			struct NumericResult resultA = findFirstAndLastNumbers(line);
			struct NumericResult resultB = findFirstAndLastStringNumbers(line);

			int firstNumber = 0;
			int lastNumber = 0;
			if (resultA.foundFirst && !resultB.foundFirst) {
				firstNumber = resultA.firstNumber;
			} else if (!resultA.foundFirst && resultB.foundFirst) {
				firstNumber = resultB.firstNumber;
			} else {
				firstNumber = resultA.firstIndex < resultB.firstIndex ? resultA.firstNumber : resultB.firstNumber;
			}

			if (resultA.foundLast && !resultB.foundLast) {
				lastNumber = resultA.lastNumber;
			} else if (!resultA.foundLast && resultB.foundLast) {
				lastNumber = resultB.lastNumber;
			} else {
				lastNumber = resultA.lastIndex > resultB.lastIndex ? resultA.lastNumber : resultB.lastNumber;
			}

			printf("%d%d\n", firstNumber, lastNumber);
			sum += (firstNumber * 10 + lastNumber);
			charIndex = 0;
		} else {
			charIndex++;
		}
	} while (ch != EOF);

	printf("Sum: %d\n", sum);

	fclose(ptr);

	return 0;
}

