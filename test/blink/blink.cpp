#include "../../src/Arduino.h"
#include "../../src/IntervalTimer.h"
//#include <Arduino.h>
IntervalTimer myTimer;

void blinkLED() {
  Serial.printf("BLINK\n");
}

int main() {
    initialize_mock_arduino();

    myTimer.begin(blinkLED, 250000);  // blinkLED to run every 0.15 seconds
    delay(100);
    char s[10] = "123123\0";
    Serial.printf("Hello %s\n", s);

    int m = millis();
    Serial.printf("Please type a sentance.... %d\n", m);

    String s2 = Serial.readStringUntil('\n');
    Serial.printf("Thank you for your response '%s' \n", s2.c_str());

    delay(1000000);

    return 0;
}