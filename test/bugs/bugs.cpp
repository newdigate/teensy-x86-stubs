// Regression tests for bugs found in the teensy-x86-stubs emulation layer.
//
// Unlike test/blink and test/first (which fetch the library from GitHub via
// DeclareAndFetch), this test links against the LOCAL src/ so it verifies the
// current working tree. Each CHECK encodes the *correct* behaviour, so a
// failing CHECK means the bug is present; once the bug is fixed the test passes.
//
// Run with stdin redirected from /dev/null so the console/keyboard paths are
// deterministic:  ./bugs < /dev/null

#include <Arduino.h>
#include <cstdio>
#include <cstring>
#include <string>

static int g_failures = 0;
static int g_total = 0;

#define CHECK(cond, msg)                                            \
    do {                                                            \
        ++g_total;                                                  \
        if (cond) {                                                 \
            std::printf("  [PASS] %s\n", msg);                      \
        } else {                                                    \
            ++g_failures;                                           \
            std::printf("  [FAIL] %s\n", msg);                      \
        }                                                           \
    } while (0)

// Drain anything left in the simulated-input queue between tests.
static void drain() {
    while (Serial.read() != -1) { /* discard */ }
}

// Bug #1: nanos() subtracts the start baseline a second time (core_pins.cpp).
// Correct: nanos() ~= micros() * 1000. Buggy: astronomically large (underflow).
static void test_nanos_baseline() {
    std::printf("Bug #1  nanos() double-subtracts baseline\n");
    delay(5);
    unsigned long us_before = micros();
    unsigned long ns        = nanos();
    unsigned long us_after  = micros();
    // ns should fall within [us_before*1000, us_after*1000] plus a little slack.
    unsigned long lo = (unsigned long)us_before * 1000UL;
    unsigned long hi = (unsigned long)us_after  * 1000UL + 5UL * 1000000UL;
    CHECK(ns >= lo && ns <= hi, "nanos() approximately equals micros()*1000");
}

// Bug #2: t_start declared `time_t` in core_pins.cpp but defined `unsigned` in
// Arduino.cpp. This is UB and may pass by luck; included as a sanity guard.
static void test_millis_sanity() {
    std::printf("Bug #2  t_start type mismatch (sanity, may pass despite UB)\n");
    uint32_t m = millis();
    CHECK(m < 60u * 60u * 1000u, "millis() is a small 'since start' value, not an epoch");
}

// Bug #3: peek() reads std::cin and ignores the simulated-input queue that
// read() honours. Every Stream parser relies on peek().
static void test_peek_uses_queue() {
    std::printf("Bug #3  peek() ignores simulated-input queue\n");
    drain();
    char in[] = {'7', 'x'};
    Serial.queueSimulatedCharacterInput(in, 2);
    int p = Serial.peek();
    int r = Serial.read();
    CHECK(p == '7', "peek() returns the next queued character");
    CHECK(r == '7', "read() returns the next queued character");
    CHECK(p == r,   "peek() agrees with the following read()");
    drain();
}

// Bug #4: readStringUntil() captures `length` once and never updates it, so the
// `max` cap is never enforced. Terminator present => no hang.
static void test_readstringuntil_max_cap() {
    std::printf("Bug #4  readStringUntil() ignores its max cap\n");
    drain();
    std::string in(200, 'a');       // 200 chars, more than the default max of 120
    in.push_back('\n');             // terminator so the call returns
    Serial.queueSimulatedCharacterInput(const_cast<char*>(in.data()),
                                        (long)in.size());
    String s = Serial.readStringUntil('\n');   // default max = 120
    CHECK(s.length() <= 120, "readStringUntil() honours the 120-char max cap");
    drain();
}

// Bug #5: write() returns 0 instead of the number of bytes written, violating
// the Arduino Print contract (Print::print sums these returns).
static void test_write_return_value() {
    std::printf("Bug #5  write() returns 0 instead of bytes written\n");
    std::printf("  (the next line prints 'hello!' to stdout as a side effect)\n  ");
    size_t n_buf  = Serial.write((const unsigned char*)"hello", 5);
    size_t n_byte = Serial.write((uint8_t)'!');
    std::printf("\n");
    CHECK(n_buf  == 5, "write(buf, 5) returns 5");
    CHECK(n_byte == 1, "write(byte) returns 1");
}

// Bug #8: available() collapses the byte count to a 0/1 boolean.
static void test_available_count() {
    std::printf("Bug #8  available() returns 0/1 instead of a byte count\n");
    drain();
    char in[5] = {'a', 'b', 'c', 'd', 'e'};
    Serial.queueSimulatedCharacterInput(in, 5);
    int av = Serial.available();
    CHECK(av == 5, "available() returns the number of queued bytes (5)");
    drain();
}

int main() {
    initialize_mock_arduino();

    test_nanos_baseline();
    test_millis_sanity();
    test_peek_uses_queue();
    test_readstringuntil_max_cap();
    test_write_return_value();
    test_available_count();

    std::printf("\n%d/%d checks passed, %d failed\n",
                g_total - g_failures, g_total, g_failures);
    return g_failures == 0 ? 0 : 1;
}
