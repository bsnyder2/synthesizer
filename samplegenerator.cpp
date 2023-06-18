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
        switch (wave_shape)
        {
        case 0: // Sine wave
            *buffer++ = (amplitude / (double)255) *
                        sin(2 * 3.14159 * toHz() * ((frame_i / (double)44100) + stream_time));
            break;
        case 1: // Sawtooth wave
            *buffer++ = (amplitude / (double)255) *
                        (std::fmod((2 * toHz() * ((frame_i / (double)44100) + stream_time)), 2) - 1);
        }
    }
}
