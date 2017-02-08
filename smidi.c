#include <stdbool.h>
#include <stdint.h>

#include "smidi.h"

static const int msglen[256] =
    {[MIDI_NOTE_OFF] = 2,        [MIDI_NOTE_ON] = 2,
     [MIDI_POLY_AFTERTOUCH] = 2, [MIDI_CONTROL_CHANGE] = 2,
     [MIDI_PROGRAM_CHANGE] = 1,  [MIDI_CHANNEL_AFTERTOUCH] = 1,
     [MIDI_WHEEL_RANGE] = 2,     [MIDI_SYSEX] = 1,
     [MIDI_SONG_POSITION] = 2,   [MIDI_SONG_SELECT] = 1,
     [MIDI_TUNE_REQUEST] = 0,    [MIDI_EOX] = 0,
     [MIDI_TIMING_CLOCK] = 0,    [MIDI_START] = 0,
     [MIDI_CONTINUE] = 0,        [MIDI_STOP] = 0,
     [MIDI_ACTIVE_SENSING] = 0,  [MIDI_RESET] = 0};

bool
smidi_next(smidi_t *msg, uint8_t b)
{
	if (b >= 0xf8) {
		msg->event = b;
		return true;
	} else if (b >= 0xf0) {
		msg->status = b;
		msg->len = 0;
	} else if (b >= 0x80) {
		msg->status = b & 0xf0;
		msg->channel = b & 0x0f;
		msg->len = 0;
	} else {
		msg->data[msg->len] = b;
		msg->len++;
	}

	if (msg->status && msg->len >= msglen[msg->status]) {
		msg->event = msg->status;
		msg->len = 0;
		return true;
	}
	return false;
}
