#include<math.h>
#include <GL/glut.h>
#include <stdio.h>
#define sign(x) ((x>0)?1:((x<0)?-1:0))

int x00, y00, x01, y01;

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -500, 500);
}

void writepixel(int x, int y,int cond) {
	glPointSize(1);
	glBegin(GL_POINTS);
		glColor3f(1,1,1);
		if(cond)
			glVertex2f(-x, y);
		else
			glVertex2f(x, y);
	glEnd();
	glFlush();
}

void drawline(int x1, int y1, int x2, int y2)
{
	
    float dx, dy, p, x, y,m,cond = 0;
	float end;
	dx = abs(x1 - x2);
    dy = abs(y1 - y2);
	
	if(dx!=0){
		m = (y1-y2)*1.0 / (x1-x2)*1.0;
		if(m < 0){
			cond = 1;
			x1 = -x1;
			x2 = -x2;
		}
	}
	
	if(dx!=0 && abs(dy/dx)<=1){
		p = 2 * dy - dx;
		if(x1 > x2)
		{
				x = x2;
				y = y2;
				end = x1;
		}
		else
		{
				x = x1;
				y = y1;
				end = x2;
		}
		writepixel(x, y , cond);
		while(x < end)
		{
				x = x + 1;
				if(p < 0)
				{
					p = p + 2 * dy;
				}
				else
				{
					y = y + 1;
					p = p + 2 * (dy - dx);
				}
				writepixel(x, y,cond);
		}
	}
	else{
		p = 2 * dx - dy;
		if(y1 > y2)
		{
				x = x2;
				y = y2;
				end = y1;
		}
		else
		{
				x = x1;
				y = y1;
				end = y2;
		}
		writepixel(x, y,cond);
		while(y < end)
		{
				y = y + 1;
				if(p < 0)
				{
					p = p + 2 * dx;
				}
				else
				{
					x = x + 1;
					p = p + 2 * (dx - dy);
				}
				writepixel(x, y,cond);
		}

	}
}

void display(){
		drawline(x00,y00,x01,y01);
		glFlush();
}


int main(int argc, char **argv) {

	printf( "Enter (x0, y0, x1, y1)\n");
	scanf("%d %d %d %d", &x00, &y00, &x01, &y01);

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Midpoint Line Algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}