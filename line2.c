#include<stdio.h>
#include<GL/glut.h>

float x0,y0,x1,y1;

void init(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-900,900,-900,900);
}

void writepixel(float x,float y,int cond){
    glBegin(GL_POINTS);
    if(cond)
        glVertex2f(-x,y);
    else
        glVertex2f(x,y);
    glEnd();
}   

void drawline(){

    float dx = abs(x1-x0);
    float dy = abs(y1-y0);
    float p,end,x,y;

    int cond = 0;
    if( dx!=0 && ((y1-y0)*1.0)/((x1-x0)*1.0) < 0 ){
        // bring points to make positive slopes 
        cond = 1;
        x0 = -x0;
        x1 = -x1;
    }   
    int swap = 0;
    if(dx!=0 && dy/dx<=1){
        // first case when slop less than 1
        p = 2*dy - dx;
        // to make sure to keep condition x0 < x1
        if(x0 > x1)
        {
            x = x1;
            y = y1;
            end = x0;
        }
        else{
            x = x0;
            y = y0;
            end = x1;
        }
    }
    else{
         // second case when slop greater than 1
        p = 2*dx - dy;
        // to keep condition y0 < y1
        if(y0 > y1)
        {
            x = y1;
            y = x1;
            end = y0;
        }
        else{
            x = y0;
            y = x0;
            end = y1;
        }
        float t = dx;
        dx = dy;
        dy = t;
        swap = 1;
    }
    if(swap)
            writepixel(y,x,cond);
        else
            writepixel(x,y,cond);
    while(x<end)
    {
        if(p<0)
            p = p + 2*dy;
        else{
            p = p + 2*(dy-dx);
            y++;
        }
        x++;
        if(swap)
            writepixel(y,x,cond);
        else
            writepixel(x,y,cond);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // draw axes
    glColor3f(0,0,0);
    for(int i=-900;i<=900;i++)
    {
        writepixel(0,i,0);
        writepixel(i,0,0);
    }
    glColor3f(1,0,0);
    drawline();


    glFlush();
}

int main(int argc,char** argv){
    
    printf("Enter line coordinates:");
    scanf("%f%f%f%f",&x0,&y0,&x1,&y1);

    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("LINE");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}