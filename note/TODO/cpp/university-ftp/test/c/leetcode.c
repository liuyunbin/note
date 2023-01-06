

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recursion(char** st, int* i, char* s, int k, int left, int right, int n) {
    int temp = 0;
    if (k == 0) {
        strcpy(st[(*i)++], s);
        return 1;
    }
    if (right < n) {
        s[k] = ')';
        temp = recursion(st, i, s, k - 1, left, right + 1, n);
    }
    if (left <= right) {
        s[k] = '(';
        temp += recursion(st, i, s, k - 1, left + 1, right, n);
    }
    return temp;
}

char** generateParenthesis(int n, int* returnSize) {
    char** st;
    char* s;
    int i;

    *returnSize = n * n - 2 * n + 2;
    st = (char**)malloc(sizeof(char*) * 10000);
    for (i = 10000; i >= 0; --i)
        st[i] = (char*)malloc(sizeof(char) * (2 * n + 1));
    s = (char*)malloc(sizeof(char) * (2 * n + 1));
    i = 0;
    s[0] = '(';
    s[2 * n - 1] = ')';
    s[2 * n] = '\0';
    printf("%d\n", recursion(st, &i, s, 2 * n - 2, 1, 1, n));

    free(s);

    return st;
}

int main() {
    int n;
    char** st;
    int len;
    int i;

    scanf("%d", &n);
    puts("previous");
    st = generateParenthesis(n, &len);
    puts("123");
    //	for( i = 0; i < len; ++i )
    //		printf( "%s\n", st[i] );

    return 0;
}
