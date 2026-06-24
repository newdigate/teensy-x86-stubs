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

#include "IntervalTimer.h"

std::atomic<int> IntervalTimer::s_activeCount{0};

bool IntervalTimer::beginMicros(callback_t funct, uint32_t microseconds)
{
    if (funct == nullptr) return false;
    if (microseconds == 0 || microseconds > MAX_PERIOD) return false;

    // Restart cleanly if this instance was already running (frees its slot).
    end();

    // Claim one of the limited timer slots, matching the Teensy's 4 PIT
    // channels: once all are in use, begin() fails just like on hardware.
    int cur = s_activeCount.load();
    do {
        if (cur >= MAX_TIMERS) return false;
    } while (!s_activeCount.compare_exchange_weak(cur, cur + 1));

    _func = funct;
    _period_us.store(microseconds);
    _active.store(true);
    _thread = std::thread(&IntervalTimer::run, this);
    return true;
}

void IntervalTimer::run()
{
    using namespace std::chrono;
    auto next = steady_clock::now();
    while (_active.load()) {
        // Schedule the next tick before sleeping so update() takes effect on
        // the following interval (the in-progress interval completes as set).
        next += microseconds(_period_us.load());
        std::this_thread::sleep_until(next);
        if (!_active.load()) break;
        callback_t f = _func;
        if (f) f();
    }
}

void IntervalTimer::end()
{
    bool was_active = _active.exchange(false);
    if (_thread.joinable()) {
        if (std::this_thread::get_id() == _thread.get_id()) {
            // Called from within the callback itself: can't join our own
            // thread, so let it finish and detach.
            _thread.detach();
        } else {
            _thread.join();
        }
    }
    if (was_active) {
        s_activeCount.fetch_sub(1);
    }
}