#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <math.h>
#include "qcustomplot.h"

class Graphic {
public:
    Graphic(int a, int T);
    void plot(float left, float right, float step);
    float getY(float X);

private:
    int R = 1;
    int T = 4;
    float sheet(float x);
    float tooth(float X, int center);
    float semicircle(float x, int center);
};

#endif // GRAPHIC_H
