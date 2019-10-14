#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
typedef float point[3];
point v[] = {
	{0,0,1},{0,0.9,-0.3},{-0.8,-0.4,-0.3},{0.8,-0.4,-0.9}
};
int n;

void triangle(point a,point b,point c){
	glBegin(GL_POLYGON);
		glNormal3fv(a);		
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
	glFlush();
}

void divide_traingle(point a,point b,point c,int m){
	point v1,v2,v3;
	int j;
	if(m>0){
		for(j=0;j<3;j++){
			v1[j] = (a[j]+b[j])/2.0;
			v2[j] = (a[j]+c[j])/2.0;
			v3[j] = (c[j]+b[j])/2.0;
 		}
		divide_traingle(a,v1,v2,m-1);
		divide_traingle(c,v2,v3,m-1);
		divide_traingle(b,v3,v1,m-1);		
	}
	else
		triangle(a,b,c);
}

void tetrahydron(int m){
	glColor3f(1,0.2,0);
	divide_traingle(v[0],v[1],v[2],m);	
	
	glColor3f(0,0.0,1);
	divide_traingle(v[3],v[2],v[1],m);

	glColor3f(0.5,1.6,1.7);
	divide_traingle(v[0],v[3],v[1],m);

	glColor3f(0,1.0,0);
	divide_traingle(v[0],v[2],v[3],m);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahydron(n);
	glFlush();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0, 2.0 ,-2.0*h/w ,2.0*h/w ,-10.0 ,10.0);
	else 
		glOrtho(-2.0*w/h ,2.0*w/h ,-2.0 ,2.0 ,-10.0 ,10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc,char** argv){
	printf("Enter no. of division:");
	scanf("%d",&n);	
		
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutCreateWindow("3D Gasket");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
		
	glEnable(GL_DEPTH_TEST);	
	glClearColor(1,1,1,1);
	glutMainLoop();	

	return 0;
}
