CXXFLAGS = -pedantic -Wall -Wextra -std=c++23
TARGETS = synthesizer.o samplegenerator.o tui.o

rtaudio = rtaudio-src/RtAudio.cpp

all: $(TARGETS)

clean:
	rm -rf $(TARGETS) synth

alsa: synthesizer.o samplegenerator.o tui.o $(rtaudio)
	g++ $(CXXFLAGS) -o synth $^ -D'__LINUX_ALSA__' -I/usr/include/rtaudio -lasound -lpthread -lncurses

mac: synthesizer.o samplegenerator.o tui.o $(rtaudio)
	g++ $(CXXFLAGS) -o synth $^ -D'__MACOSX_CORE__' -framework CoreAudio -framework CoreFoundation -lpthread -lncurses

synthesizer.o: synthesizer.cpp samplegenerator.hpp tui.hpp
	g++ $(CXXFLAGS) -c -o $@ $<

samplegenerator.o: samplegenerator.cpp samplegenerator.hpp
	g++ $(CXXFLAGS) -c -o $@ $<

tui.o: tui.cpp tui.hpp samplegenerator.hpp
	g++ $(CXXFLAGS) -c -o $@ $<
