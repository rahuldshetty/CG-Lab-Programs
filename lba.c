#include<GL/glut.h>
#include<stdio.h>
float xmin,xmax,ymin,ymax;
float xvmin = 200,yvmin = 200, xvmax = 500, yvmax = 500;
int x0,y0,x1,y1;
int cliptest(double p,double q,double *t1,double *t2){
    double t = q/p;
    if(p<0.0){
        if(t>*t1)*t1 = t;
        if(t>*t2)return false;
    }
    else if(p>0.0)
    {
        if(t<*t2)*t2 = t;
        if(t<*t1)return false;
    }
    else if(p==0.0){
        if(q<0.0)return false;
        return true;
    }
}

void drawline(float x,float y,float a,float b){ 
    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(a,b);
    glEnd();
}

void drawrect(float x,float y,float a,float b){
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(a,y);
        glVertex2f(a,b);
        glVertex2f(x,b);
    glEnd();
}

void lbca(double x0,double y0,double x1,double y1){
    double dx = x1 - x0, dy = y1 - y0, te = 0.0, t1 = 1.0;
    if( cliptest(-dx,x0-xmin,&te,&t1) && cliptest(dx,xmax-x0,&te,&t1) && cliptest(-dy,y0-ymin,&te,&t1) && cliptest(dy,ymax-y0,&te,&t1) )
    {
        if(t1<1.0){
            x1 = x0 + t1*dx;
            y1 = y0 + t1*dy;
        }
        if(te > 0.0){
            x0 = x0 + te*dx;
            y0 = y0 + te*dy;
        }
        double sx = (xvmax-xvmin)/(xmax-xmin);
        double sy = (yvmax-yvmin)/(ymax-ymin);

        double vx0 = xvmin + (x0-xmin)*sx;
        double vy0 = yvmin + (y0-ymin)*sy;
        double vx1 = xvmin + (x1-xmin)*sx;
        double vy1 = yvmin + (y1-ymin)*sy;

        glColor3f(1,0,0);
        drawrect(xvmin,yvmin,xvmax,yvmax);

        glColor3f(0,0,1);
        drawline(vx0,vy0,vx1,vy1);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    drawline(x0,y0,x1,y1);
    glColor3f(0,0,1);
    drawrect(xmin,ymin,xmax,ymax);
    lbca(x0,y0,x1,y1);
    glFlush();
}

void myinit(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,1000);
}

int main(int argc,char **argv){
    printf("Enter view end points:");
    scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
    printf("Enter line end points:");
    scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
    
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("LBCA");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}