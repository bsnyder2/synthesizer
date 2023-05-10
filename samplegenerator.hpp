#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
private:
    static constexpr double PI = 3.14159;

public:
    int amplitude;
    int semitones;

    int toHz();
    void set(int, int);
    void getSamples(double *, int, double);
};

#endif /* SAMPLEGENERATOR_H */
