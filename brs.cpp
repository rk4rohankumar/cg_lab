#include <iostream>
#include <graphics.h>

using namespace std;

void drawLine(int x1, int y1, int x2, int y2) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int slope = dy > dx;

    if (slope) {
        swap(x1, y1);
        swap(x2, y2);
    }

    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int p = 2 * dy - dx;
    int x = x1, y = y1;

    for (int i = 0; i <= dx; ++i) {
        if (slope)
            putpixel(y, x, WHITE);
        else
            putpixel(x, y, WHITE);

        while (p >= 0) {
            p = p - 2 * dx;
            if (slope)
                x += (x2 > x1 ? 1 : -1);
            else
                y += (y2 > y1 ? 1 : -1);
        }

        p = p + 2 * dy;

        if (slope)
            y += (y2 > y1 ? 1 : -1);
        else
            x += (x2 > x1 ? 1 : -1);
    }

    delay(50000);
    closegraph();
}

int main() {
    int x1, y1, x2, y2;

    cout << "Enter starting point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter ending point (x2 y2): ";
    cin >> x2 >> y2;

    drawLine(x1, y1, x2, y2);

    return 0;
}
