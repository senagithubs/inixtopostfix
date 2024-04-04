#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOYUT 100


typedef struct ornek {
    char islem;
    int tip, islenen, oncelik;



} ornek;


typedef struct Yigin {
    int ust;
    ornek elemanlar[MAX_BOYUT];
} Yigin;


void baslat(Yigin* s) {
    s->ust = -1;
}

int bosMu(Yigin* s) {
    return s->ust == -1;
}

int doluMu(Yigin* s) {
    return s->ust == MAX_BOYUT - 1;
}

void it(Yigin* s, ornek eleman) {
    if (doluMu(s)) {
        printf("Yığın dolu eleman eklenemedi.\n");
        return;
    }
    s->elemanlar[++(s->ust)] = eleman;
}

ornek cikar(Yigin* s) {
    if (bosMu(s)) {
        printf("Yığın boş eleman çıkartılamaz.");
        exit(EXIT_FAILURE);
    }
    return s->elemanlar[(s->ust)--];
}

ornek bak(Yigin* s) {
    if (bosMu(s)) {
        printf("Yığın boş, eleman alınamaz.");
        exit(EXIT_FAILURE);
    }
    return s->elemanlar[s->ust];
}

// Operatör önceliği
int oncelikBelirle(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

// Infix  to  postfix
void infixToPostfix(char* infix) {
    Yigin yigin;
    baslat(&yigin);

    char postfix[MAX_BOYUT];
    int postfixIndex = 0;

    int i = 0;
    while (infix[i] != '\0') {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[postfixIndex++] = infix[i];
        }
        else if (infix[i] == '(') {
            ornek o;
            o.islem = infix[i];
            it(&yigin, o);
        }
        else if (infix[i] == ')') {
            while (!bosMu(&yigin) && bak(&yigin).islem != '(') {
                postfix[postfixIndex++] = cikar(&yigin).islem;
            }
            cikar(&yigin);
        }
        else {
            while (!bosMu(&yigin) && oncelikBelirle(infix[i]) <= oncelikBelirle(bak(&yigin).islem)) {
                postfix[postfixIndex++] = cikar(&yigin).islem;
            }
            ornek o;
            o.islem = infix[i];
            it(&yigin, o);
        }
        i++;
    }

    while (!bosMu(&yigin)) {
        postfix[postfixIndex++] = cikar(&yigin).islem;
    }
    postfix[postfixIndex] = '\0';

    printf("Postfix ifade: %s\n", postfix);
}

int main() {
    char infix[MAX_BOYUT];
    printf("Infix ifadeyi gir:: ");
    fgets(infix, MAX_BOYUT, stdin);
    infixToPostfix(infix);

    return 0;
}
