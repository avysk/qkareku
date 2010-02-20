#include "blip.h"

Blip::Blip()
{
}

double Blip::ADSR(double t)
{
        return ADSR_linear(t);
}

double Blip::ADSR_linear(double t)
{
        return 1 - t;
}
