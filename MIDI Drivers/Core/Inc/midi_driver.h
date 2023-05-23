#ifndef __MIDI_H
#define __MIDI_H
#include "stm32f4xx_hal.h"

typedef struct midi_struct{
	uint32_t channel;
	UART_HandleTypeDef* uartptr;
}midi_t;

typedef struct midi_messages{
	uint8_t note_on;
	uint8_t note_off;
	uint8_t midi_cc;
}midi_messages;

void note_on(uint32_t note, midi_t midi_struct);
void note_off(uint32_t note, midi_t midi_struct);
void midi_cc(midi_t midi_struct, uint32_t cc_num, uint32_t value);
void send_midi(char msg, midi_t midi_struct);

#endif __MIDI_H
