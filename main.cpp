#include <GL/glut.h>
#include <stdio.h>
int *xa, *ya, *xb, *yb, *cx, *cy , *R;
void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(1.5);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1280, 0, 720);
}
void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x, y);
	glEnd();
}

void plot(int x, int y, int pntX1, int pntY1)
{
	glBegin(GL_POINTS);
	glVertex2i(x + pntX1, y + pntY1);
	glEnd();
}
void draw_line(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else
	{
		draw_pixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

void midPointCircleAlgo(int x1, int y1, int r)
{
	int x = 0;
	int y = r;
	float decision = 5 / 4 - r;
	plot(x, y, x1, y1);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2 * x + 1;
		}
		else
		{
			y--;
			x++;
			decision += 2 * (x - y) + 1;
		}
		plot(x, y,x1,y1);
		plot(x, -y, x1, y1);
		plot(-x, y, x1, y1);
		plot(-x, -y, x1, y1);
		plot(y, x, x1, y1);
		plot(-y, x, x1, y1);
		plot(y, -x, x1, y1);
		plot(-y, -x, x1, y1);
	}

}

void ellipseMidPoint()
{
	int rx = 20, ry = 10;
	int xCenter = 700, yCenter = 350;
	float x = 0;
	float y = ry;//(0,ry) ---
	float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * (0.25);
	//slope
	float dx = 2 * (ry * ry) * x;
	float dy = 2 * (rx * rx) * y;
	while (dx < dy)
	{
		//plot (x,y)
		draw_pixel(xCenter + x, yCenter + y);
		draw_pixel(xCenter - x, yCenter + y);
		draw_pixel(xCenter + x, yCenter - y);
		draw_pixel(xCenter - x, yCenter - y);
		if (p1 < 0)
		{
			x = x + 1;
			dx = 2 * (ry * ry) * x;
			p1 = p1 + dx + (ry * ry);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dx = 2 * (ry * ry) * x;
			dy = 2 * (rx * rx) * y;
			p1 = p1 + dx - dy + (ry * ry);
		}
	}
	float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);


	while (y > 0)
	{
		//plot (x,y)
		draw_pixel(xCenter + x, yCenter + y);
		draw_pixel(xCenter - x, yCenter + y);
		draw_pixel(xCenter + x, yCenter - y);
		draw_pixel(xCenter - x, yCenter - y);     //glEnd();
		if (p2 > 0)
		{
			x = x;
			y = y - 1;
			dy = 2 * (rx * rx) * y;
			//dy = 2 * rx * rx *y;
			p2 = p2 - dy + (rx * rx);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dy = dy - 2 * (rx * rx);
			dx = dx + 2 * (ry * ry);
			p2 = p2 + dx -
				dy + (rx * rx);
		}
	}

}
void myDisplay()
{
	for (int i = 0; i < 18; i++)
	{
		draw_line(xa[i], xb[i], ya[i], yb[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		midPointCircleAlgo(cx[i], cy[i], R[i]);
	}
	ellipseMidPoint();
	glFlush();
}
int main(int argc, char** argv)
{
	int a[18] = { 320, 500, 360, 680, 320, 500, 680, 320, 360, 500, 625, 750, 890, 930, 570, 680 , 697, 703 };
	int b[18] = { 930, 750, 570, 890, 930, 570, 750, 320, 360, 500, 625, 750, 890, 930, 570, 680 , 687, 713 };
	int c[18] = { 160, 420, 570, 570, 640, 470, 470, 160, 160, 160, 160, 160, 160, 160, 470, 470 , 375, 375 };
	int d[18] = { 160, 420, 570, 570, 640, 470, 470, 640, 570, 470, 420, 470, 570, 640, 570, 570 , 360, 360 };
	int e[3] = { 605, 645, 700 };
	int f[3] = { 300, 300, 375 };
	int g[3] = {6, 6, 3};
	xa = a; xb = b; ya = c; yb = d; cx = e; cy = f; R = g;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
