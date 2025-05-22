#include "anglefunctor.h"
#include <cmath>

AngleFunctor::AngleFunctor(): mode(Mode::RAD) {}

void AngleFunctor::setMode(Mode newMode)
{
    mode = newMode;
}

AngleFunctor::Mode AngleFunctor::getMode() const
{
    return mode;
}

double AngleFunctor::operator()(double angle) const
{
    switch(mode) {
    case Mode::DEG:
        return sin(angle * M_PI / 180.0);
    case Mode::GON:
        return sin(angle * M_PI / 200.0);
    default: // RAD
        return sin(angle);
    }
}
