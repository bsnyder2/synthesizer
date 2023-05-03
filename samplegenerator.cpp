#include <iostream> // For debugging; delete eventually

#include "aquila-src/aquila/aquila.h"

class SampleGenerator
{
private:
    static const int N_SAMPLES = 50;
    static const int WINDOW_HEIGHT = 8;
    int amplitude;
    int frequency;

    // Returns a note's frequency given semitone difference from A4 = 440Hz.
    static double toFreq(int semitones)
    {
        return 440 * pow(2, semitones / (double)12);
    }

    static double addSemitones(double frequency, int semitones)
    {
        return frequency * pow(2, semitones / double(12));
    }

public:
    void set(int a, int f)
    {
        amplitude = a;
        frequency = f;
    }

    void getScaledSamples(int *scaled_samples)
    {
        // Generate waveform
        Aquila::SineGenerator sinegen(1000);
        sinegen.setFrequency(frequency)
            .setAmplitude(amplitude)
            .generate(N_SAMPLES);

        const Aquila::SampleType *samples = sinegen.toArray();

        for (int s = 0; s < N_SAMPLES; s++)
        {
            scaled_samples[s] = round(samples[s] * (WINDOW_HEIGHT / ((double)255 * 2)));
        }
    }
};
