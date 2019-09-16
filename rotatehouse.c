#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

float theta;
GLfloat square[9][3] = {
	{200,200,1},{300,200,1},{300,300,1},{200,300,1},{250,400,1},{225,200,1},{275,200,1},{275,250,1},{225,250,1}
};
GLfloat rot_mat[3][3],m,n,res[9][3];
GLfloat tx = 200, ty = 200;
int p,q,r;

void multiply(){
	for(p=0;p<9;p++)
		for(q=0;q<3;q++)
		{
			res[p][q] = 0;
			for(r=0;r<3;r++)
				res[p][q] = res[p][q] + square[p][r]*rot_mat[r][q];			
		}
}

void rotate(){
	m = (-tx*cos(theta)) + (ty*sin(theta)) + tx;
	n = (-tx*sin(theta)) - (ty*cos(theta)) + ty;
	rot_mat[0][0] = cos(theta);
	rot_mat[0][1] = sin(theta);
	rot_mat[0][2] = 0;
	rot_mat[1][0] = -sin(theta);
	rot_mat[1][1] = cos(theta);
	rot_mat[1][2] = 0;
	rot_mat[2][0] = m;
	rot_mat[2][1] = n;
	rot_mat[2][2] = 1;
	multiply();	
}	

void drawsquare(GLfloat square[9][3],float r,float g,float b){	
	glBegin(GL_LINE_LOOP);
		glColor3f(r,g,b);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(r,g,b);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
		glVertex2f(square[4][0],square[4][1]);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(r,g,b);
		glVertex2f(square[5][0],square[5][1]);
		glVertex2f(square[6][0],square[6][1]);
		glVertex2f(square[7][0],square[7][1]);
		glVertex2f(square[8][0],square[8][1]);
	glEnd();
}

void display(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawsquare(square,1,0,0);
	rotate();
	drawsquare(res,0,0,1);
	glFlush();
}

void init(){
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv){
	printf("Enter angle of rotation:");
	scanf("%f",&theta);
	theta = (theta*3.14)/180;
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutCreateWindow("House");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;	
}
