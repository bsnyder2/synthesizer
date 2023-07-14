#include <cmath>

#include "samplegenerator.hpp"

// Returns the current generator frequency in Hz.
int SampleGenerator::toHz()
{
    return round(440 * pow(2, semitones / (double)12));
}

// Writes n samples of a waveform to a buffer.
void SampleGenerator::fillSamples(double *buffer, int n_frames, double stream_time, int wave_shape)
{
    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        double adjustedAmplitude = amplitude / (double)255;
        double adjustedFrequency = toHz() * (frame_i / (double)44100 + stream_time);
        switch (wave_shape)
        {
        case 0: // Sine wave
            *buffer++ = adjustedAmplitude *
                        sin(2 * M_PI * adjustedFrequency);
            break;
        case 1: // Sawtooth wave
            *buffer++ = adjustedAmplitude *
                        2 * (adjustedFrequency - floor(0.5 + adjustedFrequency));
            break;
        case 2: // Square wave
            *buffer++ = adjustedAmplitude *
                        std::copysign(1.0, sin(2 * M_PI * adjustedFrequency));
            break;
        }
    }
}
