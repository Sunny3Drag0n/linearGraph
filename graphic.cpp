#include "graphic.h"

Graphic::Graphic(int a, int T) {
    this->R = a;
    this->T = T;
}

class GraphicPlot : public QCustomPlot {
public:
    GraphicPlot() : QCustomPlot() {
        setAttribute(Qt::WA_DeleteOnClose);

        xAxis->setLabel("x");
        yAxis->setLabel("y");

        periodRect = new QCPItemRect(this);
        periodRect->setSelectable(true);
        QBrush brush;
        QColor color(Qt::gray);
        color.setAlpha(80);
        brush.setColor(color);
        brush.setStyle(Qt::SolidPattern);
        periodRect->setBrush(brush);
    }
    void setPeriod(float pos, float T, float height) {
        periodRect->topLeft->setCoords(pos, height / 2);
        periodRect->bottomRight->setCoords(pos + T, -height / 2);
    }
private:
    QCPItemRect *periodRect;
};

void Graphic::plot(float left, float right, float step) {
    GraphicPlot *customPlot = new GraphicPlot;
    auto graph = customPlot->addGraph();
    for (float X = left; X < right; X += step) {
        graph->addData(X, getY(X));
    }
    graph->rescaleAxes();
    customPlot->setPeriod(0, T, R * 2);
    customPlot->replot();
    customPlot->resize(800, 600);
    customPlot->show();
}

float Graphic::getY(float X) {
    float startFrgm;
//    if (abs((int)shift) % frgmSize) {
        if (X < 0) {
            startFrgm = (int)(X - 1) / frgmSize() * frgmSize() - 1;
        } else {
            startFrgm = (int)(X + 1) / frgmSize() * frgmSize() - 1;
        }
//    } else {
//        if (X < 0) {
//            startFrgm = (int)(X) / frgmSize() * frgmSize() - 2;
//        } else {
//            startFrgm = (int)(X) / frgmSize() * frgmSize();
//        }
//    }
    LinearFragment frgm(startFrgm, frgmSize());
    if (isSemicircle(frgm)) {
        return -semicircle(X, frgm.center());
    } else {
        return tooth(X, frgm.center());
    }
}

float Graphic::sheet(float x) {
    return x;
}

bool Graphic::isSemicircle(const LinearFragment &frgm) {
    static LinearFragment circleFrgm(-1, frgmSize(), 0);
    return (abs((int)frgm.shift(circleFrgm) / frgmSize()) % frgmSize());
}

float Graphic::tooth(float X, int center) {
    return abs(frgmSize() * abs(X - center) - R) - R;
}

float Graphic::semicircle(float x, int center) {
    return -sqrt(pow(R, 2) - pow(x - center, 2));
}

int Graphic::frgmSize() {
    return T / 2;
}
