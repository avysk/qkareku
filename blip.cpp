#include "blip.h"

Blip::Blip()
        : hue(120), saturation(255), normalValue(160), inactiveAlpha(30), delay(250), echoDecay(2.5), steps(16)
{
        initFreqPentatonic();
}

double Blip::ADSR(double t)
{
        return ADSR_linear(t);
}

double Blip::ADSR_linear(double t)
{
        return 1 - t;
}

void Blip::initFreqPentatonic()
{
        freq[7] = 440.00; // A
        freq[6] = 493.88; // B
        freq[5] = 587.33; // D
        freq[4] = 659.26; // E
        freq[3] = 739.99; // Gb
        freq[2] = 2 * freq[7]; // A
        freq[1] = 2 * freq[6]; // B
        freq[0] = 2 * freq[5]; // D
}
