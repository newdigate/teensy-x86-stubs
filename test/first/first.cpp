#include <Arduino.h>

int main() {
    initialize_mock_arduino();
    delay(100);
    char s[10] = "123123\0";
    Serial.printf("Hello %s\n", s);
    int m = millis();
    Serial.printf("Please type a sentance.... %d\n", m);

    String s2 = Serial.readStringUntil('\n');
    Serial.printf("Thank you for your response '%s' \n", s2.c_str());
    return 0;
}