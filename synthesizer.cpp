#include "rtaudio-src/RtAudio.h"

#include "samplegenerator.hpp"
#include "tui.hpp"

// Sine wave generator function for use with RtAudio.
int sine(void *output_buffer, void *input_buffer, unsigned int n_frames,
         double stream_time, RtAudioStreamStatus status, void *user_data)
{
    // Input buffer is unused here
    (void)input_buffer;

    double *buffer = (double *)output_buffer;
    SampleGenerator *sg = (SampleGenerator *)user_data;

    if (status)
    {
        std::cout << "Stream underflow detected!" << std::endl;
        return 1;
    }

    sg->getSamples(buffer, n_frames, stream_time);

    return 0;
}

int main()
{
    // Initialize TUI
    TUI tui;
    tui.init();

    // Initialize RtAudio
    RtAudio dac;
    if (dac.getDeviceCount() < 1)
    {
        std::cout << "No audio devices found!" << std::endl;
        return 1;
    }
    RtAudio::StreamParameters params;
    params.deviceId = dac.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sample_rate = 44100;
    unsigned int buffer_frames = 256;
    try
    {
        dac.openStream(
            &params, NULL, RTAUDIO_FLOAT64,
            sample_rate, &buffer_frames, &sine,
            (void *)tui.sg);
        dac.startStream();
    }
    catch (RtAudioError &e)
    {
        e.printMessage();
        return 1;
    }

    int done = 0;
    while (!done)
    {
        done = tui.update();
    }

    tui.close();

    return 0;
}
