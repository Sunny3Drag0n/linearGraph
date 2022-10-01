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
    int _mod;
    int center;
    if (X < 0) {
        center = int((X - R) / 2) * 2;
        _mod = abs((int(X) - R) % 4);
    } else {
        center = int((X + R) / 2) * 2;
        _mod = abs((int(X) + R) % 4);
    }
    if (((_mod > 0) && (T/2 <= _mod) && (_mod < T))) {
        return -semicircle(X, center);
    } else {
        return tooth(X, center);
    }
}

float Graphic::sheet(float x) {
    return x;
}

float Graphic::tooth(float X, int center) {
    return abs(T / 2 * abs(X - center) - R) - R;
}

float Graphic::semicircle(float x, int center) {
    return -sqrt(pow(R, 2) - pow(x - center, 2));
}
