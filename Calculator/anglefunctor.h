#ifndef ANGLEFUNCTOR_H
#define ANGLEFUNCTOR_H

#include<cmath>
class AngleFunctor
{
public:
    enum class Mode { RAD, DEG, GON };
    AngleFunctor();
    void setMode(Mode newMode);
    Mode getMode() const;
    double operator()(double angle) const;

private:
    Mode mode;
};

#endif // ANGLEFUNCTOR_H
