#include "arpeggiator.hpp"
#include <cstdio>

void Arpeggiator::start()
{
    active = true;
    puts("START");
}

void Arpeggiator::stop()
{
    active = false;
}
