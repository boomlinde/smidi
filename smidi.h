#ifndef _SMIDI_H_
#define _SMIDI_H_

#include <stdbool.h>
#include <stdint.h>

/* MIDI event and parser state representation */
typedef struct {
	uint8_t channel;
	uint8_t event;
	uint8_t data[2];

	uint8_t len;
	uint8_t status;
} smidi_t;

/* MIDI status and real-time message bytes */
enum {
	MIDI_NOTE_OFF = 0x80,
	MIDI_NOTE_ON = 0x90,
	MIDI_POLY_AFTERTOUCH = 0xa0,
	MIDI_CONTROL_CHANGE = 0xb0,
	MIDI_PROGRAM_CHANGE = 0xc0,
	MIDI_CHANNEL_AFTERTOUCH = 0xd0,
	MIDI_WHEEL_RANGE = 0xe0,
	MIDI_SYSEX = 0xf0,
	MIDI_SONG_POSITION = 0xf2,
	MIDI_SONG_SELECT = 0xf3,
	MIDI_TUNE_REQUEST = 0xf6,
	MIDI_EOX = 0xf7,
	MIDI_TIMING_CLOCK = 0xf8,
	MIDI_START = 0xfa,
	MIDI_CONTINUE = 0xfb,
	MIDI_STOP = 0xfc,
	MIDI_ACTIVE_SENSING = 0xfe,
	MIDI_RESET = 0xff
};

/* Consume a byte and emit a MIDI event at msg if returning true */
bool smidi_next(smidi_t *msg, uint8_t b);

#endif /* _SMIDI_H_ */
