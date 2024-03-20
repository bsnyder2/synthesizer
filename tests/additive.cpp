#include <cstdio>
#include <cmath>

void addSine(double *buffer, int currentAmplitude, int currentFrequency)
{
    double stream_time = 0; // Actually determined by RtAudio

    for (int frame_i = 0; frame_i < 200; frame_i++)
    {
        double adjustedFrequency = currentFrequency * (frame_i / (double)44100 + stream_time);
        *buffer++ += (currentAmplitude / (double)255) *
                     sin(2 * M_PI * adjustedFrequency);
    }
}

int main()
{
    // Initializes to 0
    double bufferSine[200] = {};

    addSine(bufferSine, 100, 440);
    addSine(bufferSine, 100, 220);

    for (int i = 0; i < 200; i++)
    {
        printf("S%d: %f\n", i, bufferSine[i]);
    }

    return 0;
}
