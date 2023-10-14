#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

// see https://en.wikipedia.org/wiki/Piano_key_frequencies
typedef enum {
    note_C0 = 16,
    note_Db0 = 17,
    note_D0 = 18,
    note_Eb0 = 19,
    note_E0 = 20,
    note_F0 = 21,
    note_Gb0 = 23,
    note_G0 = 24,
    note_Ab0 = 26,
    note_A0 = 28,
    note_Bb0 = 29,
    note_B0 = 31,

    note_C1 = 33,
    note_Db1 = 35,
    note_D1 = 37,
    note_E1 = 41,
    note_F1 = 44,
    note_Gb1 = 46,
    note_G1 = 49,
    note_Ab1 = 52,
    note_A1 = 55,
    note_Bb1 = 58,
    note_B1 = 62,

    note_C2 = 65,
    note_Db2 = 69,
    note_D2 = 73,
    note_Eb2 = 78,
    note_E2 = 82,
    note_F2 = 87,
    note_Gb2 = 93,
    note_G2 = 98,
    note_Ab2 = 104,
    note_A2 = 110,
    note_Bb2 = 117,
    note_B2 = 123,

    note_C3 = 131,
    note_Db3 = 139,
    note_D3 = 147,
    note_Eb3 = 156,
    note_E3 = 165,
    note_F3 = 175,
    note_Gb3 = 185,
    note_G3 = 196,
    note_Ab3 = 208,
    note_A3 = 220,
    note_Bb3 = 233,
    note_B3 = 247,

    note_C4 = 262,
    note_middleC = note_C4,
    note_Db4 = 277,
    note_D4 = 294,
    note_Eb4 = 311,
    note_E4 = 330,
    note_F4 = 349,
    note_Gb4 = 370,
    note_G4 = 392,
    note_Ab4 = 415,
    note_A4 = 440,
    note_Bb4 = 466,
    note_B4 = 494,

    note_C5 = 523,
    note_Db5 = 554,
    note_D5 = 587,
    note_Eb5 = 622,
    note_E5 = 659,
    note_F5 = 698,
    note_Gb5 = 740,
    note_G5 = 784,
    note_Ab5 = 831,
    note_A5 = 880,
    note_Bb5 = 932,
    note_B5 = 988,

    note_C6 = 1047,
    note_Db6 = 1109,
    note_D6 = 1175,
    note_Eb6 = 1245,
    note_E6 = 1319,
    note_F6 = 1397,
    note_Gb6 = 1480,
    note_G6 = 1568,
    note_Ab6 = 1661,
    note_A6 = 1760,
    note_Bb6 = 1865,
    note_B6 = 1976,

    note_C7 = 2093,
    note_Db7 = 2217,
    note_D7 = 2349,
    note_Eb7 = 2489,
    note_E7 = 2637,
    note_F7 = 2794,
    note_Gb7 = 2960,
    note_G7 = 3136,
    note_Ab7 = 3322,
    note_A7 = 3520,
    note_Bb7 = 3729,
    note_B7 = 3951,

    note_C8 = 4186,
} KeyNote;

void playFrequency(uint32_t frequency);

void soundOff(void);

void playWelcomeTune(void);

#endif