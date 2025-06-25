# synthsh
Ben Snyder, Emerson Rosen-Jones, Joshua Bowen, Ryan Beatty

## TODO
- Simple on-screen keyboard (done)
    - Octave should update whenever octave key is pressed (done)
    - C through F (done)
- Other displays:
    - Current note (X#) (done)
        - Octave should only update when next note is played (done)
    - Amplitude (%, meter on right of wave window)
    - Frequency (Hz)
    - Current waveshape selected
- Info pane on key press

### Big goals
- MIDI

### Synthesis
- Triangle wave preset, this should be pretty easy

### Larger goals
- Press same key for key up/end note (terminals don't have key up events), this should be pretty easy
- Play/pause button, this should be pretty easy
- Arpeggiator + hold, this should be pretty easy
    - shift to start hold. then we have an array of semitones values. e.g. [0, 4, 7] for major triad on C4
    - then can also set arp speed.
    - tempo setting?
- Draw one wave period with keyboard, set as waveshape, this is a cool unique features
- Polyphony - additive synthesis
- Waveform antialiasing
- Normalize amplitudes for waveshapes -> same perceived volume
