#include <graphics.h>
#include <iostream>

using namespace std;

void drawCircle(int xc, int yc, int radius) {
    int x = radius;
    int y = 0;
    int p = 1 - radius;

    while (x > y) {
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, GREEN);
        putpixel(xc + x, yc + y, GREEN);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + y, yc - x, RED);
        putpixel(xc - y, yc - x, BLUE);
        putpixel(xc + y, yc + x, BLUE);
        putpixel(xc - y, yc + x, RED);

        y++;

        if (p <= 0)
            p = p + 2 * y + 1;
        else {
            x--;
            p = p + 2 * (y - x) + 5;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    //center of the screen
    int xc = getmaxx() / 2;
    int yc = getmaxy() / 2;

    //alternate 
    // cout << "Enter the center coordinates (xc, yc): ";
    // cin >> xc >> yc;

    int radius;

    cout << "Enter the radius of the circle: ";
    cin >> radius;

    drawCircle(xc, yc, radius);

    delay(5000);
    closegraph();
    return 0;
}
