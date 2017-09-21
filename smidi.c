#include <stdbool.h>

#include "smidi.h"

static int
msglen(enum status status)
{
	switch (status) {
    case MIDI_NOTE_OFF: return 2;
	case MIDI_NOTE_ON: return 2;
    case MIDI_POLY_AFTERTOUCH: return 2;
	case MIDI_CONTROL_CHANGE: return 2;
    case MIDI_PROGRAM_CHANGE: return 1;
	case MIDI_CHANNEL_AFTERTOUCH: return 1;
    case MIDI_BEND_CHANGE: return 2;
	case MIDI_SYSEX: return 1;
    case MIDI_SONG_POSITION: return 2;
	case MIDI_SONG_SELECT: return 1;
	default: return 0;
	}
}

int
smidi_next(struct smidi *msg, unsigned char b)
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

	if (msg->status && msg->len >= msglen(msg->status)) {
		msg->event = msg->status;
		msg->len = 0;
		return 1;
	}
	return 0;
}
