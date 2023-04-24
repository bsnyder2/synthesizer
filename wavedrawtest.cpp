#include <iostream>
#include <cmath>
#include <curses.h>

#include "aquila-src/aquila/aquila.h"

#define PI 3.141592
#define Y_OFFSET 10
#define X_OFFSET 10

void drawRect(int y1, int x1, int y2, int x2)
{
	y1 += Y_OFFSET;
	y2 += Y_OFFSET;
	x1 += X_OFFSET;
	x2 += X_OFFSET;

	mvhline(y1, x1, 0, x2 - x1);
	mvhline(y2, x1, 0, x2 - x1);
	mvvline(y1, x1, 0, y2 - y1);
	mvvline(y1, x2, 0, y2 - y1);

	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);
}

// Executes mvprintw with given y and x offsets.
void displaySymbol(int y, int x, char *symbol)
{
	mvprintw(y + Y_OFFSET, x + X_OFFSET, symbol);
}

int main()
{
	int height = 12; // Height of wave window
	int n_samples = 50;
	int amplitude = 255;
	int frequency = 20;

	double scale_factor = amplitude / ((double)height * 255 * 4);

	initscr(); // Initialize ncurses screen

	Aquila::SineGenerator sinegen(1000);
	sinegen.setFrequency(frequency)
		.setAmplitude(amplitude)
		.generate(n_samples);

	const Aquila::SampleType *sample_array = sinegen.toArray();
	for (int s = 0; s < n_samples; s++)
	{
		int scaled_sample = round(sample_array[s] * scale_factor);
		std::cout << scaled_sample << "\n";
		displaySymbol(scaled_sample + (height / 2), s, (char *)"*");
	}

	drawRect(0, 0, height, n_samples + 1);

	getch();
	endwin();

	return 0;
}
