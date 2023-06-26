#include <cmath>
#include <cstring>
#include <curses.h>

#include "tui.hpp"
#include "samplegenerator.hpp"

// Executes mvprintw with given y and x offsets.
void TUI::displayString(int y, int x, char *symbol)
{
    mvprintw(y + WINDOW_Y_OFFSET, x + WINDOW_X_OFFSET, symbol);
}

// Draws a rectangle defined by given coordinates.
void TUI::drawRect(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);

    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

// Draws the waveform window.
void TUI::drawWaveWindow()
{
    int y1 = WINDOW_Y_OFFSET - 1;
    int x1 = WINDOW_X_OFFSET - 1;
    int y2 = WINDOW_HEIGHT + WINDOW_Y_OFFSET + 1;
    int x2 = WINDOW_WIDTH + WINDOW_X_OFFSET;
    drawRect(y1, x1, y2, x2);
}

// Clears the waveform window.
void TUI::clearWaveWindow()
{
    for (int row = 0; row < WINDOW_HEIGHT + 1; row++)
    {
        for (int col = 0; col < WINDOW_WIDTH; col++)
        {
            displayString(row, col, (char *)" ");
        }
    }
}

// Draws the waveform.
void TUI::drawWave()
{
    clearWaveWindow();

    // Get samples
    double samples[WINDOW_WIDTH];
    sg->fillSamples(samples, WINDOW_WIDTH, 0, sg->wave_shape);

    for (int s = 0; s < WINDOW_WIDTH; s++)
    {
        int scaled_sample = round(samples[s] * SCALE_FACTOR);
        displayString(scaled_sample + (WINDOW_HEIGHT / 2), s, (char *)"*");
    }
}

// Initializes the TUI.
void TUI::init()
{
    // Allocate space for SampleGenerator member
    sg = (SampleGenerator *)malloc(sizeof(SampleGenerator));

    // Initialize amplitude, frequency, octave, wave shape in generator
    sg->amplitude = 255;
    sg->semitones = 0;
    sg->octave = 0;
    sg->wave_shape = 0;

    // Initialize upper octave boolean in TUI
    in_upper_octave = 0;

    // Initialize ncurses
    initscr();            // Initialize ncurses screen
    curs_set(0);          // Hide cursor
    timeout(-1);          // No timeout for getch()
    noecho();             // Suppress keyboard input print
    keypad(stdscr, TRUE); // Allow for arrow key input

    drawWaveWindow();
}

// Updates the TUI (one frame).
int TUI::update()
{
    drawWave();

    // Get current amplitude, frequency, octave
    int amplitude = sg->amplitude;
    int semitones = sg->semitones;
    int octave = sg->octave;

    // Display amplitude and frequency
    mvprintw(WINDOW_HEIGHT + 4 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6.2f %%", amplitude * 100 / (double)255);
    mvprintw(WINDOW_HEIGHT + 5 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6d Hz", sg->toHz());

    // Set local values and display according to keyboard input
    char display[20];
    switch (getch())
    {
    case 'q':
        return 1;
    case '1':
        strcpy(display, "sine   ");
        sg->wave_shape = 0;
        break;
    case '2':
        strcpy(display, "saw    ");
        sg->wave_shape = 1;
        break;
    case KEY_UP:
        strcpy(display, "amp++  ");
        if (amplitude <= 255 - AMP_STEP)
            amplitude += AMP_STEP;
        break;
    case KEY_DOWN:
        strcpy(display, "amp--  ");
        if (amplitude >= AMP_STEP)
            amplitude -= AMP_STEP;
        break;
    case KEY_RIGHT:
        strcpy(display, "freq++ ");
        if (semitones < 32) // F7 - A4 = 32
            semitones++;
        break;
    case KEY_LEFT:
        strcpy(display, "freq-- ");
        if (semitones > -33) // A4 - C2 = -33
            semitones--;
        break;
    case 'x':
        strcpy(display, "oct++  ");
        if (octave < 2)
            octave++;
        break;
    case 'z':
        strcpy(display, "oct--  ");
        if (octave > -2)
            octave--;
        break;
    case 'a':
        strcpy(display, "C      ");
        semitones = -9 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'w':
        strcpy(display, "C# / Db");
        semitones = -8 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 's':
        strcpy(display, "D      ");
        semitones = -7 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'e':
        strcpy(display, "D# / Eb");
        semitones = -6 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'd':
        strcpy(display, "E      ");
        semitones = -5 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'f':
        strcpy(display, "F      ");
        semitones = -4 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 't':
        strcpy(display, "F# / Gb");
        semitones = -3 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'g':
        strcpy(display, "G      ");
        semitones = -2 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'y':
        strcpy(display, "G# / Ab");
        semitones = -1 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'h':
        strcpy(display, "A      ");
        semitones = 0 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'u':
        strcpy(display, "A# / Bb");
        semitones = 1 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'j':
        strcpy(display, "B      ");
        semitones = 2 + 12 * octave;
        in_upper_octave = 0;
        break;
    case 'k':
        strcpy(display, "C      ");
        semitones = 3 + 12 * octave;
        in_upper_octave = 1;
        break;
    case 'o':
        strcpy(display, "C# / Db");
        semitones = 4 + 12 * octave;
        in_upper_octave = 1;
        break;
    case 'l':
        strcpy(display, "D      ");
        semitones = 5 + 12 * octave;
        in_upper_octave = 1;
        break;
    case 'p':
        strcpy(display, "D# / Eb");
        semitones = 6 + 12 * octave;
        in_upper_octave = 1;
        break;
    case ';':
        strcpy(display, "E      ");
        semitones = 7 + 12 * octave;
        in_upper_octave = 1;
        break;
    case '\'':
        strcpy(display, "F      ");
        semitones = 8 + 12 * octave;
        in_upper_octave = 1;
        break;
    default:
        strcpy(display, "       ");
    }

    // Display octave
    char octave_display = (octave + 4 + in_upper_octave) + 48;
    strncat(display, &octave_display, 1);
    displayString(WINDOW_HEIGHT + 2, 0, (char *)display);

    // Set amplitude, frequency, octave
    sg->amplitude = amplitude;
    sg->semitones = semitones;
    sg->octave = octave;

    return 0;
}

// Closes the TUI.
int TUI::close()
{
    endwin();
    free(sg);

    return 0;
}
