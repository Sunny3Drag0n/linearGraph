#include <QApplication>
#include "mainwindow.h"
#include "graphic.h"
#include <iostream>

bool parameterCheck(const char *arg, const char *checked) {
    int length = ((strlen(arg) < strlen(checked)) ? strlen(arg) : strlen(checked)) + 1;
    int i;
    for (i = 0; i < length; i++)
        if (tolower(arg[i]) != tolower(checked[i]))
            break;
    return (i == length);
}

bool isGUI(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (parameterCheck(argv[i], "--gui")) {
            return true;
        }
        if (parameterCheck(argv[i], "--help") || parameterCheck(argv[i], "-h")) {
            printf("Парамерты запуска: \n"
            "\t--gui        включить GUI\n"
            "\t--help | -h  справка\n");
            fflush(stdout);
            exit(0);
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    int T = 4;
    float left = -5;
    float right = 5;
    float step = 0.3;

    for (int shift = -3; shift < 5; shift++) {
        printf("\nshift %d\n", shift);
        for (float X = left; X < right; X += step) {
            int frgmSize = (T/2);
            float startFrgm;
            if (abs((int)shift) % frgmSize) {
                if (X < 0) {
                    startFrgm = (int)(X - 1) / frgmSize * frgmSize - 1;
                } else {
                    startFrgm = (int)(X + 1) / frgmSize * frgmSize - 1;
                }
            } else {
                if (X < 0) {
                    startFrgm = (int)(X) / frgmSize * frgmSize - 2;
                } else {
                    startFrgm = (int)(X) / frgmSize * frgmSize;
                }
            }
            LinearFragment circleFrgm(shift, T/2);
            LinearFragment frgm(startFrgm, frgmSize);
            printf("frgm [%f..%f] shift %d ", frgm.start(), frgm.finish(), (int)frgm.shift(circleFrgm) - shift);
            if ((abs(((int)frgm.shift(circleFrgm) - shift) / (T/2)) % (T/2)) == 1) {
                printf("*** ");
            }
            if (frgm.contain(X)) {
                printf("X: %f, center %f\n", X, frgm.center());
            } else {
                printf("X: %f\n", X);
            }
        }
    }

    return 0;
//    if (isGUI(argc, argv)) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
//    } else {
//        float X = 0;
//        printf("Введи X:");fflush(stdout);
//        std::cin >> X;
//        Graphic g(1, 4);
//        float Y = g.getY(X);
//        printf("Y: %f\n", Y);fflush(stdout);
//        return 0;
//    }
}
