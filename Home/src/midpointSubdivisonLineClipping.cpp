#include <iostream>
#include <graphics.h>
using namespace std;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int computeCode(double x, double y, double xmin, double ymin, double xmax, double ymax) {
    int code = 0;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    return code;
}

void clipLine(double x1, double y1, double x2, double y2, double xmin, double ymin, double xmax, double ymax) {
    int code1, code2;
    bool accept = false;

    while (true) {
        code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
        code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);

        if (!(code1 | code2)) {  // Both endpoints inside window
            accept = true;
            break;
        } else if (code1 & code2) {  // Both endpoints outside window
            break;
        } else {
            double x, y;

            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
            } else {
                x2 = x;
                y2 = y;
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        setcolor(RED);
        rectangle(xmin, ymin, xmax, ymax);
        setcolor(WHITE);
        line(x1, y1, x2, y2);
    }

    delay(50000);
    closegraph();
}

int main() {
    double xmin = 50, ymin = 50, xmax = 300, ymax = 200;
    double x1, y1, x2, y2;

    cout << "Enter the coordinates of the first point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter the coordinates of the second point (x2 y2): ";
    cin >> x2 >> y2;

    // Initialize graphics mode
    initwindow(400, 300, "Cohen-Sutherland Line Clipping Algorithm");

    // Draw the clipping window
    rectangle(xmin, ymin, xmax, ymax);

    // Draw the original line
    line(x1, y1, x2, y2);

    // Clip the line against the window
    clipLine(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    return 0;
}
