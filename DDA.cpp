#include <iostream>
#include <graphics.h>

using namespace std;

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = static_cast<float>(dx) / static_cast<float>(steps);
    float yIncrement = static_cast<float>(dy) / static_cast<float>(steps);

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        putpixel(static_cast<int>(x), static_cast<int>(y), WHITE);
        x += xIncrement;
        y += yIncrement;
        delay(100);
    }

    delay(5000);
    closegraph();
}

int main() {
    int x1, y1, x2, y2;

    cout << "Enter starting point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter ending point (x2 y2): ";
    cin >> x2 >> y2;

    drawLineDDA(x1, y1, x2, y2);

    return 0;
}
