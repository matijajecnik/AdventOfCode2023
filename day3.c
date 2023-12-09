#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUMS 4096

typedef struct Number {
    int n;
    int x, y;
} Number;

typedef struct Symbol {
    int x, y;
    int star;
} Symbol;

Number numbers[MAXNUMS];
Symbol symbols[MAXNUMS];
int iNum, iSym;

int ndigits(int n) {
    if (n < 10)
        return 1;
    return 1 + ndigits(n / 10);
}

void addNum(int n, int x, int y) {
    numbers[iNum++] = (Number) {
        .n = n, .x = x, .y = y
    };
}

void addSym(int x, int y, int w) {
    symbols[iSym++] = (Symbol) {
        .x = x, .y = y, .star = w
    };
}

int neighbors(int xa, int ya, int xb, int yb) {
    return abs(xa - xb) <= 1 && abs(ya - yb) <= 1;
}

int isNumberAdjacentToSymbol(Number n, Symbol s) {
    int nd, i;
    nd = ndigits(n.n);
    for (i = 0; i < nd; i++) {
        if (neighbors(n.x + i, n.y, s.x, s.y))
            return 1;
    }
    return 0;
}

int doesNumTouchAnySymbol(Number n) {
    int j;
    for (j = 0; j < iSym; j++)
        if (isNumberAdjacentToSymbol(n, symbols[j]))
            return 1;
    return 0;
}

int64_t isGear(Symbol s) {
	int i, n = 0;
	int64_t prod = 1;
	for (i = 0; i < iNum; i++)
		if (isNumberAdjacentToSymbol(numbers[i], s)) {
			prod *= numbers[i].n;
			n += 1;
		}
	return (n == 2) * prod;
}

int getSum() {
    int i, res = 0;
    for (i = 0; i < iNum; i++)
        if (doesNumTouchAnySymbol(numbers[i]))
            res += numbers[i].n;
    return res;
}

void parseLine(char *l, ssize_t lineLen, int y) {
    int j = 0, tnum = 0, x = 0, sx = 0;
    char rnum[8] = {0}; 
    while (x < lineLen) {
        if (isdigit(l[x])) {
            if (j == 0) 
                sx = x;
            rnum[j++] = l[x];
        } else if (j > 0) { 
            rnum[j] = '\0';
            tnum = atoi(rnum);
            addNum(tnum, sx, y);
            j = 0;
        }
        if (l[x] != '.' && ispunct(l[x]))
            addSym(x, y, l[x] == '*');
        x += 1;
    }
}

int64_t getSum2() {
	int i;
	int64_t res = 0;
	for (i = 0; i < iSym; i++)
		if (symbols[i].star)
			res += isGear(symbols[i]);
	return res;
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t linesize = 512;
    ssize_t lineLen;
    
    if (argc != 2) {
        printf("Usage: %s <inputFile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    int acc1 = 0, lnum = 0, i = 0;
    
    while ((lineLen = getline(&line, &linesize, file)) != -1) {
        parseLine(line, lineLen, lnum);
        lnum += 1;
    }
    printf("%d\n", getSum());
    printf("%lld\n", getSum2());

    free(line);
    fclose(file);
    return 0;
}
