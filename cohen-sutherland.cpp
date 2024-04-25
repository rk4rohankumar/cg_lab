#include <stdio.h>
#include <graphics.h>

#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

int xmin, ymin, xmax, ymax; // Viewport coordinates

int computeCode(int x, int y) {
    int code = INSIDE;

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

void cohenSutherland(int x1, int y1, int x2, int y2) {
    int code1, code2, codeOut;
    int accept = 0, done = 0;

    while (!done) {
        code1 = computeCode(x1, y1);
        code2 = computeCode(x2, y2);

        if (!(code1 | code2)) { // Both endpoints are inside
            accept = 1;
            done = 1;
        } else if (code1 & code2) { // Both endpoints are outside
            done = 1;
        } else { // Some part of the line is inside
            int x, y;

            // Select the endpoint outside the viewport
            codeOut = code1 ? code1 : code2;

            // Calculate the intersection point
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

            // Replace the outside point with the intersection point
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
        // Draw the line segment within the viewport
        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Set viewport coordinates (adjust as needed)
    xmin = 50;
    ymin = 50;
    xmax = 400;
    ymax = 300;

    // Draw the viewport
    rectangle(xmin, ymin, xmax, ymax);

    // Input line coordinates
    int x1, y1, x2, y2;
    printf("Enter line coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    // Draw the original line
    setcolor(RED);
    line(x1, y1, x2, y2);

    // Apply Cohen-Sutherland algorithm to clip the line
    setcolor(WHITE);
    cohenSutherland(x1, y1, x2, y2);

    delay(50000); // Pause for 50 seconds
    closegraph();
    return 0;
}
