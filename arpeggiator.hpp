#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <vector>

class Arpeggiator
{
private:
    bool active;
    std::vector<int> held_semitones;

public:
    void start();
    void stop();
};

#endif /* ARPEGGIATOR_H */
