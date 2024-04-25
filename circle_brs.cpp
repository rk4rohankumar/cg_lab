#include <graphics.h>
#include <iostream>

using namespace std;

void drawPixel(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, GREEN);
    putpixel(xc + x, yc + y, GREEN);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + y, yc - x, RED);
    putpixel(xc - y, yc - x, BLUE);
    putpixel(xc + y, yc + x, BLUE);
    putpixel(xc - y, yc + x, RED);

    // Print pixel coordinates to console
    cout << "(" << xc + x << ", " << yc - y << ") ";
    cout << "(" << xc - x << ", " << yc - y << ") ";
    cout << "(" << xc + x << ", " << yc + y << ") ";
    cout << "(" << xc - x << ", " << yc + y << ") ";
    cout << "(" << xc + y << ", " << yc - x << ") ";
    cout << "(" << xc - y << ", " << yc - x << ") ";
    cout << "(" << xc + y << ", " << yc + x << ") ";
    cout << "(" << xc - y << ", " << yc + x << ")" << endl;
}

void drawCircle(int xc, int yc, int x, int y) {
    drawPixel(xc, yc, x, y);
    drawPixel(xc, yc, y, x);
}

void drawCompleteCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        drawCircle(xc, yc, x, y);

        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        drawCircle(xc, yc, x, y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    // Get the center of the screen
    int xc = getmaxx() / 2;
    int yc = getmaxy() / 2;

    int radius;

    cout << "Enter the radius of the circle: ";
    cin >> radius;

    drawCompleteCircle(xc, yc, radius);

    delay(5000);
    closegraph();
    return 0;
}
