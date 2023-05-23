#include "midi_driver.h"

/*
 * A MIDI message consists of three bytes
 *  ---- ----   ---- ----   ---- ----
 *  The first is a status byte, the next two are data bytes. Every status byte starts with a 1, every data byte starts with a 0. So, in hex,
 *  the status bytes are all 0x80 or up, and the data bytes are all 0x7F and below.
 */

char buffer[10];
midi_messages messages = {0x80, 0x90, 0x08};

/* Create and send a MIDI note on message
*  		These messages tell the device that a note has been played
*
*  		The byte structure is as follows:
*  		0x9*   **** ****   **** ****
*
*  		The first half of the status byte is the type of command (note on in this case). The second half is the channel to send the message on.
*  		The data bytes give note and velocity, respectively. the following example sends a middle C with velocity 100 on channel 10:
*
*  		0x9A 0x3C 0x64
*/
void note_on(uint32_t note, midi_t midi_struct)
{
	  buffer[0] = midi_messages.note_on;
	  buffer[1] = 0x90 | midi_struct.channel;
	  buffer[2] = 0x7f & note;
	  send_midi(*buffer,midi_struct);
}

// Create and send a MIDI note off message
//		these messages tell the device that a note has been released
void note_off(uint32_t note, midi_t midi_struct)
{
	  buffer[0] = 0x08;
	  buffer[1] = 0x80 | midi_struct.channel;
	  buffer[2] = 0x7f & note;
	  send_midi(*buffer,midi_struct);
}

// Create and send a MIDI CC message
//		these messages tell the device that a control value has been changed (knob turn, pitch wheel move, etc)
void midi_cc(midi_t midi_struct, uint32_t cc_num, uint32_t value)
{
	  buffer[0] = 0x0b;
	  buffer[1] = 0xb0 | midi_struct.channel;
	  buffer[2] = 0x7f & cc_num;
	  send_midi(*buffer,midi_struct);
}

void send_midi(char msg, midi_t midi)
{
	  HAL_UART_Transmit(midi.uartptr,(uint8_t*)buffer,3,1000);
}
