cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = soundgen tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -rf $(targets) *.dSYM/

soundgen: soundgen.cpp 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o $@ $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread
	
tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses

wavedrawtest: wavedrawtest.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^ -lncurses

refactor: refactor.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^
