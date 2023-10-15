#include "pc_speaker.h"

#include "../../os/hard/port_io.h"
#include "pit/pit.h"

#include <stddef.h>

#define SOUND_PORT 0x61
#define SOUND_MASK 0b11111100
#define TIMER_CHANNEL 2

#define STATE_IN 0b00
#define STATE_OUT 0b10
#define STATE_TIMER_OFF 0b01
#define STATE_TIMER_ON 0b11

// STATE_TIMER_OFF is unused since it is not very useful

// This is private since it doesn't really make sense to use directly.
void timerOn(void) {
    // set both bits to on (this enables timer 2)
    outb(SOUND_PORT, inb(SOUND_PORT) | STATE_TIMER_ON);
}

void soundOn(void) {
    // sets the bottom 2 bits to 0.
    uint8_t tmp = inb(SOUND_PORT) & SOUND_MASK;

    // This pushes the speaker out.
    outb(SOUND_PORT, tmp | STATE_OUT);
}

void soundOff(void) {
    // This brings the speaker in and disables timer 2's influence
    outb(SOUND_PORT, inb(SOUND_PORT) & SOUND_MASK);
}

void playFrequency(uint32_t frequency) {
    // sets timer 2 to generate a square wave
    init_timer(frequency, TIMER_CHANNEL);

    timerOn();
}

void playWelcomeTune(void) {
    sleep(1);
    playFrequency(note_D5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_E5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_F5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_G5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_G5);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(note_B5);
    sleep(10);
    soundOff();
    sleep(40);
    playFrequency(note_D6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_E6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_F6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_E6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_F6);
    sleep(5);
    soundOff();
    sleep(10);
    playFrequency(note_E6);
    sleep(5);
    soundOff();
    sleep(10);
    playFrequency(note_D6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_C6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_C6);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_G5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_A5);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(note_F5);
    sleep(20);
    soundOff();
}
