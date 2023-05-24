#include "midi_driver.h"

/*
 * A MIDI message consists of three bytes
 *  ---- ----   ---- ----   ---- ----
 *  The first is a status byte, the next two are data bytes. Every status byte starts with a 1, every data byte starts with a 0. So, in hex,
 *  the status bytes are all 0x80 or up, and the data bytes are all 0x7F and below.
 */

uint8_t buffer[10];
midi_messages messages = {0x90, 0x80, 0x08};

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
	  buffer[0] = messages.note_on | (midi_struct.channel - 1);
	  buffer[1] = 0x7f & note;
	  buffer[2] = 0x7f & 100;

	  send_midi(*buffer,midi_struct);
}

// Create and send a MIDI note off message
//		these messages tell the device that a note has been released
void note_off(uint32_t note, midi_t midi_struct)
{
	  buffer[0] = 0x80;
	  buffer[1] = 0x7f & note;
	  buffer[2] = 0x00;

	  send_midi(*buffer,midi_struct);
}

// Create and send a MIDI CC message
//		these messages tell the device that a control value has been changed (knob turn, pitch wheel move, etc)
void midi_cc(uint32_t cc_num, uint32_t cc_val, midi_t midi_struct)
{
	  buffer[0] = 0xb0 | (midi_struct.channel - 1);
	  buffer[1] = 0x7f & cc_num;
	  buffer[2] = 0x7f & cc_val;

	  send_midi(*buffer,midi_struct);
}

void send_midi(char msg, midi_t midi)
{
	  HAL_UART_Transmit(midi.uartptr,(uint8_t*)buffer,3,1000);
}
