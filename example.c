#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "smidi.h"

int
main(void)
{
	int fd;
	uint8_t b;
	smidi_t m = {0};

	fd = fileno(stdin);

	for (;;) {
		if (read(fd, &b, 1) <= 0) {
			return errno;
		}

		if (smidi_next(&m, b)) {
			switch (m.event) {
			case MIDI_NOTE_OFF:
				printf("(%d) ", m.channel + 1);
				printf("Note OFF %d (velocity %d)\n", m.data[0], m.data[1]);
				break;
			case MIDI_NOTE_ON:
				printf("(%d) ", m.channel + 1);
				printf("Note ON %d (velocity %d)\n", m.data[0], m.data[1]);
				break;
			case MIDI_CONTROL_CHANGE:
				printf("(%d) ", m.channel + 1);
				printf("Control Change %d: %d\n", m.data[0], m.data[1]);
				break;
			case MIDI_SYSEX:
				printf("SYSEX data: %02x\n", m.data[0]);
				break;
			case MIDI_EOX:
				printf("End of SYSEX\n");
				break;
			case MIDI_TIMING_CLOCK:
			case MIDI_ACTIVE_SENSING:
				break;
			default:
				printf("Unhandled: %02x (%d)\n", m.event, m.event);
				break;
			}
		}
	}
	return 0;
}
