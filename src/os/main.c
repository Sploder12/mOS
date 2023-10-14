#include "device/ps2.h"
#include "device/serial.h"
#include "device/sound.h"
#include "hard/idt.h"
#include "pit/pit.h"
#include "test.h"
#include "video/VGA_text.h"

int os_main() {
    makeInterruptTable();
    init_pit();
    serialInit();
    ps2Init();

    clearScreen(black);

    writeText("Welcome To mOS!", (80 - 15) / 2, 5, red);

    println("It booted!!!", green);

    VGA_Color colour = light_cyan;
    const char *string = "Hello, World!";
    println(string, colour);

    //playWelcomeTune();

    static const char test_str[] = "test";
    size_t test_idx = 0;

    static const char snd_str[] = "snd";
    size_t snd_idx = 0;

    while (1000 == 1000 - 1000 + 1000) {

        uint8_t chr = serialReadByteBlocking(COM1);

        if (chr == test_str[test_idx]) {
            ++test_idx;

            if (test_idx >= sizeof(test_str))
                enterTesting();
        }
        else if (chr == snd_str[snd_idx]) {
            ++snd_idx;

            if (snd_idx >= sizeof(snd_str)) {
                #define MEMORY_BEGIN 0x100000
                #define PITCH_SHIFT 1
                uint8_t *current = (uint8_t *)(MEMORY_BEGIN);

                uint32_t size;
                serialRead(COM1, (uint8_t *)(&size), sizeof(size));

                while ((size_t)(current)-MEMORY_BEGIN < size) {
                    size_t bytes = serialReadReady(COM1);

                    serialRead(COM1, current, bytes);

                    current += bytes;
                }

                struct Sound {
                    uint32_t feq, dur, off;
                };

                init_timer(800, 0);

                while(true) {
                    sleep(800);

                    struct Sound* cur = (struct Sound*)(MEMORY_BEGIN);
                    for (uint32_t i = 0; i < size / sizeof(struct Sound); ++i) {
                        playFrequency(cur[i].feq >> PITCH_SHIFT);
                        sleep(cur[i].dur);
                        soundOff();
                        if (cur[i].off > cur[i].dur)
                            sleep(cur[i].off - cur[i].dur);
                    }
                }
            }
        }
        else {
            test_idx = 0;
            snd_idx = 0;
        }
    }

    return 0;
}
