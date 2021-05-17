#include "../../src/Arduino.h"

int main() {
    initialize_mock_arduino();
    delay(100);
    char s[10] = "123123\0";
    Serial.printf("Hello %s", s);
    int m = millis();
    Serial.printf("Hello %d", m);
    return 0;
}