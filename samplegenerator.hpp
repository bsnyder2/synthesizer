#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
public:
    int amplitude;
    int semitones;
    int octave;

    int toHz();
    void getSamples(double *, int, double);
};

#endif /* SAMPLEGENERATOR_H */
