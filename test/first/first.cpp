#include "../../src/Arduino.h"

int main() {
    char s[10] = "123123\0";
    Serial.printf("Hello %s", s);
    return 0;
}