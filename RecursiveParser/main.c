//Name: Maria Esteban
/*Purpose: recursive-descent parser that evaluates arithmetic expressions defined by the following context-free grammar described in EBNF:
command -> expr ‘\n’
expr -> term { + term | - term }
term -> power { * power | / power | % power }
power -> factor [ ^ power ]
factor -> [-] factor1
factor1 -> ( expr ) | NUMBER
NUMBER = [0 - 9]+
*/
//Date: 12/01/24

#include <stdio.h>
#include <stdlib.h>

//Enumeration for token type
typedef enum { PLUS, MINUS, DIVIDE, MULT, REMAINDER, POWER, LPAREN, RPAREN, NUMBER, ERROR, EOL } TokenType;

//Struct definition for Token
struct Token {
    TokenType type;
    int value;
};
//Global variable that stores the currently parsed token
struct Token token;


struct Token getToken() {
    int currentCharacter = 0;
    while ((currentCharacter = getchar()) == ' ');
    token.value = 0;
    if (isdigit(currentCharacter)) {
        token.type = NUMBER;
        while (isdigit(currentCharacter)) {
            token.value = 10 * token.value + (currentCharacter - '0');
            currentCharacter = getchar();
        }
        ungetc(currentCharacter, stdin);
        printf("%d\tNUMBER\n", token.value);
        return token;
    }
    else{
        switch (currentCharacter){
        case'+':
            token.type = PLUS;
            printf("+\tPLUS\n");
            break;
        case '-':
            token.type = MINUS;
            printf("-\tMINUS\n");
            break;
        case '*':
            token.type = MULT;
            printf("*\tMULT\n");
            break;
        case '/':
            token.type = DIVIDE;
            printf("/\tDIVIDE\n");
            break;
        case '%':
            token.type = REMAINDER;
            printf("%%\tREMAINDER\n");
            break;
        case '^':
            token.type = POWER;
            printf("^\tPOWER\n");
            break;
        case '(':
            token.type = LPAREN;
            printf("(\tLPAREN\n");
            break;
        case ')':
            token.type = RPAREN;
            printf(")\tRPAREN\n");
            break;
        case '\n':
            token.type = EOL;
            return token;
        default:
            token.type = ERROR;
            printf("Unknown character: %c\n", currentCharacter);
            break;
        }
        return token;
    }
};

void match(TokenType tkType) {
    if (token.type == tkType) {
        token = getToken();
    } else {
        printf("Error\n");
    }
}

int factor1(void) {
    if (token.type == LPAREN) {
        match(LPAREN);
        int result = expr();
        match(RPAREN);
        return result;
    } else if (token.type == NUMBER) {
        int value = token.value;
        match(NUMBER);
        return value;
    } else {
        printf("Error\n");
        return 0;
    }
}

int factor(void) {
    if (token.type == MINUS) {
        match(MINUS);
        return -factor1();
    } else {
        return factor1();
    }
}

int power(void) {
    int base = factor();
    if (token.type == POWER) {
        match(POWER);
        int exponent = power();
        int result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
    return base;
}

int term(void) {
    int result = power();
    while (token.type == MULT || token.type == DIVIDE || token.type == REMAINDER) {
        if (token.type == MULT) {
            match(MULT);
            result *= power();
        } else if (token.type == DIVIDE) {
            match(DIVIDE);
            int divisor = power();
            if (divisor == 0) printf("Error: Division by zero");
            result /= divisor;
        } else if (token.type == REMAINDER) {
            match(REMAINDER);
            int divisor = power();
            if (divisor == 0) printf("Error: Modulo by zero");
            result %= divisor;
        }
    }
    return result;
}

int expr(void) {
    int result = term();
    while (token.type == PLUS || token.type == MINUS) {
        if (token.type == PLUS) {
            match(PLUS);
            result += term();
        } else if (token.type == MINUS) {
            match(MINUS);
            result -= term();
        }
    }
    return result;
}

void parse(void){
    token = getToken();
    int result = expr();

    if (token.type == EOL) {
        printf("\nResult: %d\n", result);
    }
    else {
        printf("Command Error\n");
    }
}

int main()
{
    printf("Enter an expression: ");
    parse();
    return 0;
}
