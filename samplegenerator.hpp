#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
public:
    int amplitude;
    int semitones;
    int octave;

    int wave_shape;

    int toHz();
    void fillSamples(double *, int, double, int);
};

#endif /* SAMPLEGENERATOR_H */
