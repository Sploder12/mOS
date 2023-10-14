import MIDI
import socket
import time

flist = {
    'c#7': 2217,
    'f#7': 2960,
    'd6': 1175,
    'f7': 2794,
    'd#7': 2489,
    'a#6': 1865,
    'f6' : 1397,
    'd#6': 1245,
    'f#6': 1480,
    'g#6': 1661,
    'b5' : 988,
    'c#6': 1109,
    'a#5': 932,
    'd#5': 622,
    'f5': 698,
    'f#5': 740,
    'g#5': 831,
    'a#4': 466,
    'd5': 587,
    'c#5':554,
    'g5': 784,
    'a5': 880,
    'c6': 1047,
    'g6': 1568,
    'a6': 1760,
    'c7': 2093,
}

def parse(file):
    c = MIDI.MIDIFile(file)
    c.parse()

    with open("apple.mos", "bw") as f:
        for idx, track in enumerate(c):
            track.parse()

            prev = 0
            for i, event in enumerate(track):
                if (isinstance(event, MIDI.Events.MIDIEvent)):
                    if (event.command == 0x90): #on
                        if (prev != 0):
                            f.write((event.time - prev).to_bytes(4, "little"))

                        prev = event.time
                    elif (event.command == 0x80): #off
                        dur = event.time - prev
                        f.write(flist[event.message.note.note + str(event.message.note.octave)].to_bytes(4, "little"))
                        f.write(dur.to_bytes(4, "little"))

            if (prev != 0):
                f.write((0).to_bytes(4, "little"))

parse("apple.mid")

PORT = 1111
LOCALHOST = "127.0.0.1"
DATA_DELAY = 0.1
SLICE_SIZE = 128

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((LOCALHOST, PORT))
    time.sleep(1)

    s.send(b"snd\0")

    with open("apple.mos", "rb") as binary:
        bin = binary.read()

        s.send(len(bin).to_bytes(4, "little"))

        chunks = int(len(bin) / SLICE_SIZE)

        for i in range(0, chunks):
            chunk = bin[i*SLICE_SIZE:(i+1)*SLICE_SIZE]
            s.send(chunk)
            time.sleep(DATA_DELAY)
            print("sent chunk " + str(i) + " of " + str(chunks))
                
        last = bin[chunks * SLICE_SIZE:]
        if (len(last) > 0):
            s.send(last)