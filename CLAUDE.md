# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A library of stub/mock implementations of the Arduino + Teensyduino core APIs so that Teensy
(Teensy 4.x / IMXRT1062) sketches and libraries can be compiled, run, and debugged natively on
x86/x64 (Linux, macOS, Windows) instead of on the microcontroller. It is the base of an
ecosystem of companion stub libraries (sd, audio, st7735, midi, bounce2, encoder) that depend
on it.

The implementations are deliberately minimal: most hardware functions (GPIO, ADC, PWM,
interrupts, RTC, tempmon) are empty no-ops. The parts that have real behavior are timing,
serial I/O, string handling, and timers — emulated using the host OS.

## Build

```sh
mkdir cmake-build-debug && cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

The root build (`CMakeLists.txt` → `src/CMakeLists.txt`) only produces the `teensy_x86_stubs`
library; it has no `main`. To actually run something you build one of the test apps, which are
**standalone consumer projects**, not part of the root build:

```sh
cd test/blink   # or test/first
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
./blink         # test/first produces ./basic
```

Each `test/*/CMakeLists.txt` pulls the library fresh from GitHub (`main` branch) via the
`DeclareAndFetch` macro in `test/cmake_declare_and_fetch.cmake.in` — it does **not** use the
local working copy. So when changing library code, verify against the root build, or temporarily
point `DeclareAndFetch` at your branch/local path to test end-to-end.

There is no unit-test framework and no lint step. CI (`.github/workflows/{root,blink,first}.yml`)
simply runs the three CMake builds above on every push.

## Architecture notes

- **Target emulation.** `src/CMakeLists.txt` sets `__IMXRT1062__`, `ARDUINO_TEENSY41`, and
  `ARDUINO=158` as compile definitions, and C++17. Code that branches on these macros is
  pretending to be a Teensy 4.1.
- **Headers mirror Teensyduino.** Files like `Arduino.h`, `Print.h`, `Stream.h`, `WString.h`,
  `core_pins.h`, `IntervalTimer.h`, `AudioStream.h`, `EventResponder.h`, `imxrt.h`, `arm_math.h`
  keep the same names/signatures as the real Teensy core so unmodified sketches compile. When
  stubbing a new API, match the upstream Teensyduino signature exactly.
- **Timing is real, hardware is fake.** `millis()`/`micros()`/`nanos()` (`core_pins.cpp`) read
  `std::chrono::system_clock`; `delay*` call `std::this_thread::sleep_for`. The baseline is set
  by `initialize_mock_arduino()` (`Arduino.cpp`), which captures the start epoch so timers read
  as "since program start". **Sketches must call `initialize_mock_arduino()` at the top of
  `main()`** or timing values are absolute epoch values.
- **`IntervalTimer`** (`IntervalTimer.cpp`) runs each active timer on its own `std::thread`,
  with a static slot counter capped at 4 (matching the Teensy 4.x PIT channels) — `begin()`
  returns false once all 4 are in use. Because it uses `std::thread`, `src/CMakeLists.txt` links
  `Threads::Threads` as a PUBLIC dependency so consumers link pthread transitively.
- **Concurrency / interrupts.** There is no ISR model. `__disable_irq`/`__enable_irq`
  (`Arduino.cpp`) are a `std::mutex` critical section guarded by the global
  `arduino_should_exit` flag. `yield()` sleeps and optionally drives the `EventResponder` (via
  the `YIELD_CHECK_EVENT_RESPONDER` flag and `yield_active_check_flags`).
- **`setup`/`loop`** are declared with `asm("_setup")`/`asm("_loop")` aliases — test apps
  typically provide their own `main()` instead of relying on the Arduino setup/loop runtime.
- **MSVC.** `ctz_clz.cpp` is compiled only under MSVC (count-trailing/leading-zero intrinsics
  GCC/Clang already provide). Several files have `#ifdef _MSC_VER` branches; preserve them when
  editing.

## Conventions

- Many source files carry the PJRC Teensyduino MIT license header verbatim because they are
  derived from / kept signature-compatible with the upstream core. Keep these headers when
  editing such files.
- Adding a new stub means editing `src/CMakeLists.txt`'s `SOURCE_FILES`/`HEADER_FILES` lists —
  there is no glob.
