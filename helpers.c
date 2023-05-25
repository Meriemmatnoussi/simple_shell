#include "helpers.h"

// Implementation of strip_whitespace function
char* strip_whitespace(char* str) {
    int length = strlen(str);

    // Remove leading whitespaces
    while (isspace(str[0])) {
        memmove(str, str + 1, length);
        length--;
    }

    // Remove trailing whitespaces
    while (length > 0 && isspace(str[length - 1])) {
        str[length - 1] = '\0';
        length--;
    }

    return str;
}
