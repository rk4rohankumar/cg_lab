#include <bits/stdc++.h>
#include <graphics.h>
#define ROUND(a) ((int)(a + 0.5))
#define TRUE 1
#define FALSE 0
using namespace std;

struct dcPt
{
    int x, y;
};

struct wcPt2
{
    float x, y;
};

void DDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    float m = dy / dx;
    int steps = max(abs(dx), abs(dy));

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = x1;
    float Y = y1;

    for (int i = 0; i <= steps; i++)
    {
        if (X - int(X) < 0.5 && Y - int(Y) < 0.5)
        {
            putpixel(round(int(X)), round(int(Y)), RED);
            delay(10);
        }
        else if (X - int(X) < 0.5 && Y - int(Y) >= 0.5)
        {
            putpixel(round(int(X)), round(int(Y) + 1), RED);
            delay(10);
        }
        else if (X - int(X) >= 0.5 && Y - int(Y) < 0.5)
        {
            putpixel(round(int(X) + 1), round(int(Y)), RED);
            delay(10);
        }
        else
        {
            putpixel(round(int(X) + 1), round(int(Y) + 1), RED);
            delay(10);
        }

        X += Xinc;
        Y += Yinc;
    }
}

int clipTest(float p, float q, float *t1, float *t2)
{
    float r;
    int retVal = TRUE;
    if (p < 0.0)
    {
        r = q / p;
        if (r > *t2)
            retVal = FALSE;
        else if (r > *t1)
            *t1 = r;
    }
    else if (p > 0.0)
    {
        r = q / p;
        if (r < *t1)
            retVal = FALSE;
        else if (r < *t2)
            *t2 = r;
    }
    else
    {
        if (q < 0.0)
            retVal = FALSE;
    }

    return retVal;
}

void clipLine(dcPt winMin, dcPt winMax, wcPt2 p1, wcPt2 p2)
{
    float t1 = 0.0, t2 = 1.0, dx = p2.x - p1.x, dy;
    if (clipTest(-dx, p1.x - winMin.x, &t1, &t2))
        if (clipTest(dx, winMax.x - p1.x, &t1, &t2))
        {
            dy = p2.y - p1.y;
            if (clipTest(-dy, p1.y - winMin.y, &t1, &t2))
                if (clipTest(dy, winMax.y - p1.y, &t1, &t2))
                {
                    if (t2 < 1.0)
                    {
                        p2.x = p1.x + t2 * dx;
                        p2.y = p1.y + t2 * dy;
                    }

                    if (t1 > 0.0)
                    {
                        p1.x += t1 * dx;
                        p1.y += t1 * dy;
                    }

                    DDA(ROUND(p1.x), ROUND(p1.y), ROUND(p2.x), ROUND(p2.y));
                }
        }
}

int main()
{

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    dcPt winMin = {100, 100};
    dcPt winMax = {500, 400};
    setcolor(WHITE);
    rectangle(winMin.x, winMin.y, winMax.x, winMax.y);

    wcPt2 p1 = {50.0, 50.0}; // Start point
    wcPt2 p2 = {600.0, 300.0};
    wcPt2 p3 = {200.0, 350.0}; // End point
    // Draw the original line
    line(ROUND(p1.x), ROUND(p1.y), ROUND(p2.x), ROUND(p2.y));
    line(ROUND(p2.x), ROUND(p2.y), ROUND(p3.x), ROUND(p3.y));
    line(ROUND(p3.x), ROUND(p3.y), ROUND(p1.x), ROUND(p1.y));
    clipLine(winMin, winMax, p1, p2);
    clipLine(winMin, winMax, p2, p3);
    clipLine(winMin, winMax, p3, p1);
    closegraph();
    return 0;
}