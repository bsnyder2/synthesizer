#include <cstdio>
#include <cmath>

// See desmos: https://www.desmos.com/calculator/pvy8xppm0a

void fillSine(double *buffer, int n_frames)
{
    double stream_time = 0; // Actually determined by RtAudio
    int currentAmplitude = 100;
    int currentFrequency = 440;

    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        /* equation for the sin wave.
        everything until "freq" converts a time to radians;
        everything after gets a time based on the time elapsed since the start of the
        stream and the time per sample, incremented for each sample */
        double adjustedFrequency = currentFrequency * (frame_i / (double)44100 + stream_time);
        *buffer++ = (currentAmplitude / (double)255) *
                    sin(2 * M_PI * adjustedFrequency);
    }
}

void fillSaw(double *buffer, int n_frames)
{
    double stream_time = 0; // Actually determined by RtAudio
    int currentAmplitude = 100;
    int currentFrequency = 440;

    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        double adjustedFrequency = currentFrequency * (frame_i / (double)44100 + stream_time);
        *buffer++ = (currentAmplitude / (double)255) *
                    2 * (adjustedFrequency - floor(0.5 + adjustedFrequency));
    }
}

void fillSquare(double *buffer, int n_frames)
{
    double stream_time = 0; // Actually determined by RtAudio
    int currentAmplitude = 100;
    int currentFrequency = 440;

    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        double adjustedFrequency = currentFrequency * (frame_i / (double)44100 + stream_time);
        *buffer++ = (currentAmplitude / (double)255) *
                    std::copysign(1.0, sin(2 * M_PI * adjustedFrequency));
    }
}

void fillTri(double *buffer, int n_frames)
{
    double stream_time = 0; // Actually determined by RtAudio
    int currentAmplitude = 100;
    int currentFrequency = 440;

    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        double adjustedFrequency = currentFrequency * (frame_i / (double)44100 + stream_time);
        double adjustedAmplitude = (currentAmplitude / (double)255);
        // *buffer++ = (4 * adjustedAmplitude * (double)currentFrequency);
        // *buffer++ = 400 * fmod(frame_i - (1 / (4 * (double)currentFrequency)), (1 / (double)currentFrequency));
        // *buffer++ = (4 * adjustedAmplitude * (double)currentFrequency) * abs(fmod(frame_i - (1 / (4 * (double)currentFrequency)), (1 / (double)currentFrequency)) - (1 / (2 * (double)currentFrequency)) - currentAmplitude);
        // *buffer++ = (4 * adjustedAmplitude / (double)adjustedFrequency) * abs(fmod(frame_i - (adjustedFrequency / (double)4), adjustedFrequency) - (adjustedFrequency / (double)2)) - adjustedAmplitude;
        // *buffer++ = (4 * adjustedAmplitude / (double)adjustedFrequency);
        // *buffer++ = (4 * adjustedAmplitude / adjustedFrequency) * abs(fmod(frame_i - (adjustedFrequency/4)), adjustedFrequency) - (1 / (2 * adjustedFrequency))) - adjustedAmplitude;
        double m = 44100 / (double)currentFrequency;
        double thing = (adjustedAmplitude * (4 / (double)m) * abs(fmod(frame_i + (44100 * stream_time) - (m / (double)4), m) - (m / (double)2))) - adjustedAmplitude;
        // *buffer++ = fabs(fmod(frame_i + (44100 * stream_time) - (m / (double)4), m) - (m / (double)2));
        //   *buffer++ = thing;
        // fake
        *buffer++ = adjustedAmplitude * (2 / (double)M_PI) * asin(sin(2 * M_PI * adjustedFrequency));
    }
}

int main()
{
    double bufferSine[200];
    double bufferSaw[200];
    double bufferSquare[200];
    double bufferTri[200];

    fillSine(bufferSine, 200);
    fillSaw(bufferSaw, 200);
    fillSquare(bufferSquare, 200);
    fillTri(bufferTri, 200);

    for (int i = 0; i < 200; i++)
    {
        printf("S%d: SIN: %f     SAW: %f     SQR: %f    TRI: %f\n", i, bufferSine[i], bufferSaw[i], bufferSquare[i], bufferTri[i]);
    }

    return 0;
}