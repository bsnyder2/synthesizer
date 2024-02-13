# synthsh
Ben Snyder, Emerson Rosen-Jones, Joshua Bowen, Ryan Beatty

## TODO
### UI
- Ignore below for UI- follow layout.txt

- Simple on-screen keyboard (done)
    - Octave should update whenever octave key is pressed (done)
    - C through F (done)
- Other displays:
    - Current note (X#) (done)
        - Octave should only update when next note is played (done)
    - Amplitude (%, meter on right of wave window)
    - Frequency (Hz)
    - Current waveshape selected
- Info pane on key press!

### Synthesis
- Triangle wave preset, this should be pretty easy

### Larger goals
- Press same key for key up/end note (terminals don't have key up events), this should be pretty easy
- Play/pause button, this should be pretty easy
- Arpeggiator + latch, this should be pretty easy
- Draw one wave period with keyboard, set as waveshape, this is a cool unique features
- Polyphony - additive synthesis
- Waveform antialiasing
- Normalize amplitudes for waveshapes -> same perceived volume
