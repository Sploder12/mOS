#include "sound.h"

#include "../../os/hard/port_io.h"
#include "pit/pit.h"

#include <stddef.h>

#define SOUND_PORT 0x61
#define SOUND_MASK 0b11111100
#define TIMER_CHANNEL 2

// This is private since it doesn't really make sense to use directly.
void soundOn(void) {
    uint8_t tmp = inb(SOUND_PORT);

    // set both bits to on (this enables timer 2)
    outb(SOUND_PORT, tmp | ~SOUND_MASK);
}

void soundOff(void) {
    // sets the bottom 2 bits to 0. 
    uint8_t tmp = inb(SOUND_PORT) & SOUND_MASK;

    // This brings the speaker in and disables timer 2's influence
    outb(SOUND_PORT, tmp);
}

void playFrequency(uint32_t frequency) {
    init_timer(frequency, TIMER_CHANNEL);

    soundOn();
}

#define PITCH_SHIFT 1

void playWelcomeTune(void) {
    playFrequency(293 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(440 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(329 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(440 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(349 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(391 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(440 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(20);
    playFrequency(391 << PITCH_SHIFT);
    sleep(5);
    soundOff();
    sleep(40);
    playFrequency(493 << PITCH_SHIFT);
    sleep(10);
    soundOff();
}
