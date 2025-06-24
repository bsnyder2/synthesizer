#include <cmath>
#include <cstring>
#include <curses.h>

#include "tui.hpp"
#include "samplegenerator.hpp"

static const char *KEY_TEXTURES[] = {
    "|##| | | |  |  | | | | | |  |  | | | |  |   |\n|##|_| |_|  |  |_| |_| |_|  |  |_| |_|  |   |\n|###|   |   |   |   |   |   |   |   |   |   |\n|###|___|___|___|___|___|___|___|___|___|___|\n",
    "|  |#| | |  |  | | | | | |  |  | | | |  |   |\n|  |#| |_|  |  |_| |_| |_|  |  |_| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | |#| |  |  | | | | | |  |  | | | |  |   |\n|  |_|#|_|  |  |_| |_| |_|  |  |_| |_|  |   |\n|   |###|   |   |   |   |   |   |   |   |   |\n|___|###|___|___|___|___|___|___|___|___|___|\n",
    "|  | | |#|  |  | | | | | |  |  | | | |  |   |\n|  |_| |#|  |  |_| |_| |_|  |  |_| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |##|  | | | | | |  |  | | | |  |   |\n|  |_| |_|##|  |_| |_| |_|  |  |_| |_|  |   |\n|   |   |###|   |   |   |   |   |   |   |   |\n|___|___|###|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |##| | | | | |  |  | | | |  |   |\n|  |_| |_|  |##|_| |_| |_|  |  |_| |_|  |   |\n|   |   |   |###|   |   |   |   |   |   |   |\n|___|___|___|###|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  |#| | | | |  |  | | | |  |   |\n|  |_| |_|  |  |#| |_| |_|  |  |_| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  | |#| | | |  |  | | | |  |   |\n|  |_| |_|  |  |_|#|_| |_|  |  |_| |_|  |   |\n|   |   |   |   |###|   |   |   |   |   |   |\n|___|___|___|___|###|___|___|___|___|___|___|\n",
    "|  | | | |  |  | | |#| | |  |  | | | |  |   |\n|  |_| |_|  |  |_| |#| |_|  |  |_| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  | | | |#| |  |  | | | |  |   |\n|  |_| |_|  |  |_| |_|#|_|  |  |_| |_|  |   |\n|   |   |   |   |   |###|   |   |   |   |   |\n|___|___|___|___|___|###|___|___|___|___|___|\n",
    "|  | | | |  |  | | | | |#|  |  | | | |  |   |\n|  |_| |_|  |  |_| |_| |#|  |  |_| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  | | | | | |##|  | | | |  |   |\n|  |_| |_|  |  |_| |_| |_|##|  |_| |_|  |   |\n|   |   |   |   |   |   |###|   |   |   |   |\n|___|___|___|___|___|___|###|___|___|___|___|\n",
    "|  | | | |  |  | | | | | |  |##| | | |  |   |\n|  |_| |_|  |  |_| |_| |_|  |##|_| |_|  |   |\n|   |   |   |   |   |   |   |###|   |   |   |\n|___|___|___|___|___|___|___|###|___|___|___|\n",
    "|  | | | |  |  | | | | | |  |  |#| | |  |   |\n|  |_| |_|  |  |_| |_| |_|  |  |#| |_|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  | | | | | |  |  | |#| |  |   |\n|  |_| |_|  |  |_| |_| |_|  |  |_|#|_|  |   |\n|   |   |   |   |   |   |   |   |###|   |   |\n|___|___|___|___|___|___|___|___|###|___|___|\n",
    "|  | | | |  |  | | | | | |  |  | | |#|  |   |\n|  |_| |_|  |  |_| |_| |_|  |  |_| |#|  |   |\n|   |   |   |   |   |   |   |   |   |   |   |\n|___|___|___|___|___|___|___|___|___|___|___|\n",
    "|  | | | |  |  | | | | | |  |  | | | |##|   |\n|  |_| |_|  |  |_| |_| |_|  |  |_| |_|##|   |\n|   |   |   |   |   |   |   |   |   |###|   |\n|___|___|___|___|___|___|___|___|___|###|___|\n",
    "|  | | | |  |  | | | | | |  |  | | | |  |###|\n|  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |###|\n|   |   |   |   |   |   |   |   |   |   |###|\n|___|___|___|___|___|___|___|___|___|___|###|\n"};

// Executes mvprintw with given y and x offsets.
void TUI::displayString(int y, int x, char *symbol)
{
    mvprintw(y + WINDOW_Y_OFFSET, x + WINDOW_X_OFFSET, symbol);
}

// Draws a rectangle defined by given coordinates.
void TUI::drawRect(int y1, int x1, int y2, int x2)
{
    // Draw edge lines
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);

    // Draw corners
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

    // Get enough samples to fill the window
    int n_samples = WINDOW_WIDTH * WINDOW_HSCALE;
    double samples[MAX_DISPLAY_SAMPLES];
    sg->fillSamples(samples, n_samples, 0, sg->wave_shape);

    // draw every WINDOW_HSCALEth sample
    for (int s = 0; s < n_samples; s++)
    {
        int scaled_sample = round(samples[s] * WINDOW_VSCALE);
        displayString((WINDOW_HEIGHT / 2) - scaled_sample, s / WINDOW_HSCALE, (char *)"*");
    }
}

// Draws the keyboard window.
void TUI::drawKeyboardWindow(const char *note)
{
    // MAKE SURE:
    // redraw ENTIRE keyboard window every time there is a change.
    // To avoid unnecessary complexity, just have string constants for all 18 keyboard images
    // (Can have entire keyboard image in one string just using '\n's)

    mvprintw(0, 1, "  ____ __  __ __  _  _____  _   _   ____  _   _");
    mvprintw(1, 1, " (_ (_`\\ \\/ /|  \\| ||_   _|| |_| | (_ (_`| |_| |");
    mvprintw(2, 1, ".__)__) |__| |_|\\__|  |_|  |_| |_|.__)__)|_| |_|");

    int j = 12;
    int k = 22;

    int tspaces[] = {0, 3, 5, 7, 9, 12, 15, 17, 19, 21, 23, 25, 28, 31, 33, 35, 37, 40};

    for (int tval : tspaces)
    {
        mvaddch(j + 1, k + tval, ACS_TTEE);
    }
    mvaddch(j + 1, k + 44, ACS_RTEE);

    WINDOW *wave_window = newwin(6, 50, j + 2, k);

    wprintw(wave_window, note);

    const char *KEY_LABELS = " (a) (s) (d) (f) (g) (h) (j) (k) (l) (;) (')\n   (w) (e)     (t) (y) (u)     (o) (p)";

    wprintw(wave_window, KEY_LABELS);

    refresh();
    wrefresh(wave_window);
}

void TUI::drawControlWindow()
{
    WINDOW *control_window = newwin(6, 20, WINDOW_HEIGHT + 2 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET);

    // (don't need to print this every time)
    mvwprintw(control_window, 2, 10, "(</>)");
    mvwprintw(control_window, 3, 10, "(^/v)");
    mvwprintw(control_window, 4, 10, "(# keys)");
    mvwprintw(control_window, 5, 10, "(z/x)");

    // Get current generator values
    int amplitude = sg->amplitude;
    int octave = sg->octave;
    int wave_shape = sg->wave_shape;

    // Display frequency amplitude, wave shape
    mvwprintw(control_window, 2, 0, "%6d Hz", (int)sg->toHz());
    mvwprintw(control_window, 3, 0, "%6.2f %%", amplitude * 100 / (double)255);

    char wave_display[64];
    // these are sorted by perceived loudness
    switch (wave_shape)
    {
    case 0:
        strcpy(wave_display, "sine");
        break;
    case 1:
        strcpy(wave_display, "triangle");
        break;
    case 2:
        strcpy(wave_display, "saw");
        break;
    case 3:
        strcpy(wave_display, "square");
        break;
    }
    mvwprintw(control_window, 4, 0, wave_display);

    // Display note and octave
    mvwprintw(control_window, 0, 0, sg->note_name);
    char octave_display = (octave + 4 + in_upper_octave) + 48;
    mvwaddch(control_window, 0, 10, octave_display);

    refresh();
    wrefresh(control_window);
}

// Initializes the TUI.
void TUI::init()
{
    // Allocate space for SampleGenerator member
    sg = (SampleGenerator *)malloc(sizeof(SampleGenerator));

    // Initialize values for sample generator
    sg->semitones = 0;
    sg->amplitude = 255;
    sg->note_name = (char *)"A";
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
    drawKeyboardWindow(KEY_TEXTURES[9]);
}

// Updates the TUI (one frame).
int TUI::update()
{
    // Display current values for generator
    drawWave();
    drawControlWindow();

    // Get keyboard input to set new values for generator
    int semitones = sg->semitones;
    char note_name[64];
    strcpy(note_name, sg->note_name);

    switch (getch())
    {
    case 'q':
        return 1;
    case '1':
        sg->wave_shape = 0;
        break;
    case '2':
        sg->wave_shape = 1;
        break;
    case '3':
        sg->wave_shape = 2;
        break;
    case '4':
        sg->wave_shape = 3;
        break;
    case KEY_UP:
        if (sg->amplitude <= 255 - AMP_STEP)
            sg->amplitude += AMP_STEP;
        break;
    case KEY_DOWN:
        if (sg->amplitude >= AMP_STEP)
            sg->amplitude -= AMP_STEP;
        break;
    case KEY_RIGHT:
        if (semitones < 32) // F7 - A4 = 32
            semitones++;
        break;
    case KEY_LEFT:
        if (semitones > -45) // A4 - C1 = -45
            semitones--;
        break;
    case 'x':
        if (sg->octave < 2)
            sg->octave++;
        break;
    case 'z':
        if (sg->octave > -3)
            sg->octave--;
        break;
    case 'a':
        semitones = -9 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "C      ");
        drawKeyboardWindow(KEY_TEXTURES[0]);
        break;
    case 'w':
        semitones = -8 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "C#/Db  ");
        drawKeyboardWindow(KEY_TEXTURES[1]);
        break;
    case 's':
        semitones = -7 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "D      ");
        drawKeyboardWindow(KEY_TEXTURES[2]);
        break;
    case 'e':
        semitones = -6 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "D#/Eb  ");
        drawKeyboardWindow(KEY_TEXTURES[3]);
        break;
    case 'd':
        semitones = -5 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "E      ");
        drawKeyboardWindow(KEY_TEXTURES[4]);
        break;
    case 'f':
        semitones = -4 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "F      ");
        drawKeyboardWindow(KEY_TEXTURES[5]);
        break;
    case 't':
        semitones = -3 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "F#/Gb  ");
        drawKeyboardWindow(KEY_TEXTURES[6]);
        break;
    case 'g':
        semitones = -2 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "G      ");
        drawKeyboardWindow(KEY_TEXTURES[7]);
        break;
    case 'y':
        semitones = -1 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "G#/Ab  ");
        drawKeyboardWindow(KEY_TEXTURES[8]);
        break;
    case 'h':
        semitones = 0 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "A      ");
        drawKeyboardWindow(KEY_TEXTURES[9]);
        break;
    case 'u':
        semitones = 1 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "A#/Bb  ");
        drawKeyboardWindow(KEY_TEXTURES[10]);
        break;
    case 'j':
        semitones = 2 + (12 * sg->octave);
        in_upper_octave = 0;
        strcpy(note_name, "B      ");
        drawKeyboardWindow(KEY_TEXTURES[11]);
        break;
    case 'k':
        semitones = 3 + (12 * sg->octave);
        in_upper_octave = 1;
        strcpy(note_name, "C      ");
        drawKeyboardWindow(KEY_TEXTURES[12]);
        break;
    case 'o':
        semitones = 4 + (12 * sg->octave);
        in_upper_octave = 1;
        strcpy(note_name, "C#/Db  ");
        drawKeyboardWindow(KEY_TEXTURES[13]);
        break;
    case 'l':
        semitones = 5 + (12 * sg->octave);
        in_upper_octave = 1;
        strcpy(note_name, "D      ");
        drawKeyboardWindow(KEY_TEXTURES[14]);
        break;
    case 'p':
        semitones = 6 + (12 * sg->octave);
        in_upper_octave = 1;
        strcpy(note_name, "D#/Eb  ");
        drawKeyboardWindow(KEY_TEXTURES[15]);
        break;
    case ';':
        semitones = 7 + (12 * sg->octave);
        in_upper_octave = 1;
        strcpy(note_name, "E      ");
        drawKeyboardWindow(KEY_TEXTURES[16]);
        break;
    case '\'':
        semitones = 8 + (12 * sg->octave);
        in_upper_octave = 1;

        strcpy(note_name, "F      ");
        drawKeyboardWindow(KEY_TEXTURES[17]);
        break;
    }

    // Set semitones and note name
    sg->semitones = semitones;
    sg->note_name = note_name;

    return 0;
}

// Closes the TUI.
int TUI::close()
{
    endwin();
    free(sg);

    return 0;
}
