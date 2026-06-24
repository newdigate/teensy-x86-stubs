/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2018 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef __cplusplus
#ifndef __INTERVALTIMER_H__
#define __INTERVALTIMER_H__

#include <stddef.h>
#include <cstdint>
#include <atomic>
#include <thread>
#include <chrono>
// IntervalTimer provides access to hardware timers which can run an
// interrupt function a precise timing intervals.
// https://www.pjrc.com/teensy/td_timing_IntervalTimer.html
// Up to 4 IntervalTimers may be in use simultaneously.  Many
// libraries use IntervalTimer, so some of these 4 possible
// instances may be in use by libraries.
//
// On the host this is emulated with one std::thread per active timer: the
// callback runs on its own thread at the requested period. Up to MAX_TIMERS
// (4, matching the Teensy 4.x PIT channels) may run at once; begin() returns
// false once they are all in use.
class IntervalTimer {
private:
	static const uint32_t MAX_PERIOD = UINT32_MAX / (24000000 / 1000000);
	static const int MAX_TIMERS = 4;       // Teensy 4.x exposes 4 PIT channels
	static std::atomic<int> s_activeCount;  // number of timers currently running
public:
	IntervalTimer() {}
	~IntervalTimer() {
		end();
	}
	// IntervalTimer owns a thread and atomics, so it is not copyable/movable.
	IntervalTimer(const IntervalTimer&) = delete;
	IntervalTimer& operator=(const IntervalTimer&) = delete;

	using callback_t = void (*)(void);
	// Start the hardware timer and begin calling the function.  The
	// interval is specified in microseconds, using integer or float
	// for precise timing.  Returns true is sucessful, or false if
	// all hardware timers are already in use.
	template <typename period_t>
	bool begin(callback_t funct, period_t period) {
		uint32_t microseconds = (uint32_t)period;
		return beginMicros(funct, microseconds);
	}
	// Change the timer's interval.  The current interval is completed
	// as previously configured, and then the next interval begins with
	// with this new setting.
	void update(unsigned int microseconds) {
		if (microseconds == 0 || microseconds > MAX_PERIOD) return;
		_period_us.store(microseconds);
	}
	// Change the timer's interval.  The current interval is completed
	// as previously configured, and then the next interval begins with
	// with this new setting.
	template <typename period_t>
	void update(period_t period) {
		update((unsigned int)period);
	}

	// Stop calling the function. The hardware timer resource becomes available
	// for use by other IntervalTimer instances.
	void end();
	// Set the interrupt priority level, controlling which other interrupts this
	// timer is allowed to interrupt. Lower numbers are higher priority, with 0
	// the highest and 255 the lowest. Most other interrupts default to 128. As
	// a general guideline, interrupt routines that run longer should be given
	// lower priority (higher numerical values).
	void priority(uint8_t n) {
	}

private:
	bool beginMicros(callback_t funct, uint32_t microseconds);
	void run();

	callback_t _func = nullptr;
	std::atomic<uint32_t> _period_us{0};
	std::atomic<bool> _active{false};
	std::thread _thread;
};

#endif //__INTERVALTIMER_H__
#endif //__cplusplus