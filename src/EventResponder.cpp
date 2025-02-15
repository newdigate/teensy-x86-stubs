/* EventResponder - Simple event-based programming for Arduino
 * Copyright 2017 Paul Stoffregen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
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

/* EventResponder is an experimental API, almost certain to
 * incompatibly change as it develops.  Please understand any
 * programs you write now using EventResponder may need to be
 * updated as EventResponder develops.
 *
 * Please post EventResponder post your feedback here:
 *     https://forum.pjrc.com/threads/44723-Arduino-Events
 */

#include "Arduino.h"
#include "EventResponder.h"

EventResponder * EventResponder::firstYield = nullptr;
EventResponder * EventResponder::lastYield = nullptr;
EventResponder * EventResponder::firstInterrupt = nullptr;
EventResponder * EventResponder::lastInterrupt = nullptr;
bool EventResponder::runningFromYield = false;

// TODO: interrupt disable/enable needed in many places!!!
// BUGBUG: See if file name order makes difference?

void EventResponder::triggerEventNotImmediate()
{
	bool irq = disableInterrupts();
	if (_triggered == false) {
		// not already triggered
		if (_type == EventTypeYield) {
			// normal type, called from yield()
			if (firstYield == nullptr) {
				_next = nullptr;
				_prev = nullptr;
				firstYield = this;
				lastYield = this;
			} else {
				_next = nullptr;
				_prev = lastYield;
				_prev->_next = this;
				lastYield = this;
			}
		} else if (_type == EventTypeInterrupt) {
			// interrupt, called from software interrupt
			if (firstInterrupt == nullptr) {
				_next = nullptr;
				_prev = nullptr;
				firstInterrupt = this;
				lastInterrupt = this;
			} else {
				_next = nullptr;
				_prev = lastInterrupt;
				_prev->_next = this;
				lastInterrupt = this;
			}
		} else {
			// detached, easy :-)
		}
		_triggered = true;
	}
	enableInterrupts(irq);
}

extern "C" void pendablesrvreq_isr(void)
{
	EventResponder::runFromInterrupt();
}

void EventResponder::runFromInterrupt()
{
	while (1) {
		bool irq = disableInterrupts();
		EventResponder *first = firstInterrupt;
		if (first) {
			firstInterrupt = first->_next;
			if (firstInterrupt) {
				firstInterrupt->_prev = nullptr;
			} else {
				lastInterrupt = nullptr;
			}
			enableInterrupts(irq);
			first->_triggered = false;
			(*(first->_function))(*first);
		} else {
			enableInterrupts(irq);
			break;
		}
	}
}

bool EventResponder::clearEvent()
{
	bool ret = false;
	bool irq = disableInterrupts();
	if (_triggered) {
		if (_type == EventTypeYield) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstYield = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastYield = _prev;
			}
		} else if (_type == EventTypeInterrupt) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstInterrupt = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastInterrupt = _prev;
			}
		}
		_triggered = false;
		ret = true;
	}
	enableInterrupts(irq);
	return ret;
}

// this detach must be called with interrupts disabled
void EventResponder::detachNoInterrupts()
{
	if (_type == EventTypeYield) {
		if (_triggered) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstYield = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastYield = _prev;
			}
		}
		_type = EventTypeDetached;
	} else if (_type == EventTypeInterrupt) {
		if (_triggered) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstInterrupt = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastInterrupt = _prev;
			}
		}
		_type = EventTypeDetached;
	}
}


void EventResponder_runFromYield(void)
{
	EventResponder::runFromYield();
}

