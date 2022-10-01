#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <math.h>
#include "qcustomplot.h"

class LinearFragment {
public:
    LinearFragment(float startFrgm, float len) : startFrgm(startFrgm), len(len) {}
    LinearFragment(float startFrgm, float len, float shift) : LinearFragment(startFrgm + shift, len) {

    }
    float center() const {
        return startFrgm + len / 2;
    }
    bool contain(float X) const {
        return (startFrgm <= X) && (X <= (startFrgm + len));
    }
    float start() const {
        return startFrgm;
    }
    float finish() const {
        return startFrgm + len;
    }
    float size() {
        return len;
    }
    float shift(const LinearFragment &other) const {
        return other.start() - startFrgm;
    }
private:
    float startFrgm;
    float len;
};

class Graphic {
public:
    Graphic(int a, int T);
    void plot(float left, float right, float step);
    float getY(float X);

private:
    int R = 1;
    int T = 4;
    float sheet(float x);
    bool isSemicircle(const LinearFragment &frgm);
    float tooth(float X, int center);
    float semicircle(float x, int center);
    int frgmSize();
};

#endif // GRAPHIC_H
