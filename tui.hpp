#ifndef TUI_H
#define TUI_H

#include <string>

#include "samplegenerator.hpp"

class TUI
{
private:
    static const int WINDOW_Y_OFFSET = 4;
    static const int WINDOW_X_OFFSET = 2;
    static const int WINDOW_HEIGHT = 8;
    static const int WINDOW_WIDTH = 64;

    static const int WINDOW_VSCALE = WINDOW_HEIGHT / 2;
    static const int WINDOW_HSCALE = 4;
    static const int MAX_DISPLAY_SAMPLES = 65536;
    static const int AMP_STEP = 5;

    int in_upper_octave;

    void displayString(int, int, char *);
    void drawRect(int, int, int, int);

    void drawWaveWindow();
    void clearWaveWindow();
    void drawWave();
    void drawKeyboardWindow(const char *);
    void drawControlWindow();

public:
    SampleGenerator *sg;

    void init();
    int update();
    int close();
};

#endif /* TUI_H */
