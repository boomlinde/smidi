Simple MIDI
-----------

Simple MIDI is a library for parsing byte streams of MIDI and emit MIDI
events.

- Simple event based interface
- Handles running status
- Handles system real-time messages

Example
-------

The example program reads MIDI data on stdin and outputs a textual
representation of some MIDI events. Pipe a MIDI stream into it to use as
a simple MIDI monitor.

    ./example </dev/midi1

Handling SYSEX
--------------

System exclusive messages was not made a special case in the parser and
system exclusive data works as though it was a single-data byte status;
MIDI\_SYSEX will not be emitted until the first following data byte
(vendor ID) appears, and each following data byte will appear as a
MIDI\_SYSEX event, until interrupted by another status (normally EOX,
end of SysEx).

Note off events
---------------

This library makes no effort to hide the fact that some vendors use
note-on events with velocity 0 instead of note-off. This is allowed by
the MIDI 1.0 specification.

Building
--------

-   `make` to build the library
-   `make example` to build the example program

