#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
public:
    int semitones;
    int amplitude;

    char *note_name;
    int octave;

    int wave_shape;

    double toHz();
    void fillSamples(double *, int, double, int);
};

#endif /* SAMPLEGENERATOR_H */
