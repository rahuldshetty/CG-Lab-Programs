#include<stdio.h>
#include<GL/glut.h>

float xmin,ymin,xmax,ymax;
float x0,y0,x1,y1;
float xvmin=200,yvmin =200, xvmax=300,yvmax=300;

const int INSIDE = 0, LEFT = 1 , RIGHT = 2, BOTTOM = 4, TOP = 8 ; 
bool accept = false;
   
int outcode(float x,float y){
    int code = INSIDE;

    if( x < xmin )
        code |= LEFT;
    else if( x > xmax )
        code |= RIGHT;
    
    if( y < ymin )
        code |= BOTTOM;
    else if( y > ymax )
        code |= TOP;
    return code;
}

void CSL(){
    int code1 = outcode(x0,y0);
    int code2 = outcode(x1,y1);

    while(true){
        
        if((code1==0) && (code2==0)){
            // case 1 -both inside
            accept = true;
            break;
        }
        else if(code1 & code2){
            //case 3 -  outside rect but same region 
            break;
        }
        else{
            // some lie within and some out maybe
            int codeout;
            double x,y;

            //case 2 - at leat one endpoint outside
            if(code1 != 0)
                codeout = code1;
            else 
                codeout = code2;

            //find intersection
            // formula: y = y1 + m * ( x-x1 )
            if( codeout & TOP )
            {
                x = x0 + (x1-x0)*(ymax - y0)/(y1 - y0);
                y = ymax;
            }
            else if(codeout & BOTTOM)
            {
                x = x0 + (x1-x0)*(ymin-y0)/(y1-y0);
                y = ymin;
            }
            else if(codeout & RIGHT){
                y = y0 + (y1-y0)*(xmax - x0)/(x1- x0);
                x = xmax;
            }
            else if(codeout & LEFT){
                y = y0 + (y1-y0)*(xmin - x0)/(x1- x0);
                x = xmin;
            }

            //replace point outside with intersection point
            if(codeout==code1){
                x0 = x;
                y0 = y;
                code1 = outcode(x0,y0);
            }
            else{
                x1 = x;
                y1 = y;
                code2 = outcode(x1,y1);
            }
        }
    }
}

void drawline(float a,float b,float c,float d){
    glBegin(GL_LINES);
        glVertex2f(a,b);
        glVertex2f(c,d);
    glEnd();
}

void drawrect(float a,float b,float c,float d){
    glBegin(GL_LINE_LOOP);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
}

void drawViewPort(){
    double sx=(xvmax-xvmin)/(xmax-xmin);  // scale parameter in x direction
    double sy=(yvmax-yvmin)/(ymax-ymin); // scale parameter in y direction
    double vx0 = xvmin+(x0-xmin)*sx;
    double vy0 = yvmin+(y0-ymin)*sy;
    double vx1 = xvmin+(x1-xmin)*sx;
    double vy1 = yvmin+(y1-ymin)*sy;

    glColor3f(1.0,0.0,0.0);
    drawrect(xvmin,yvmin,xvmax,yvmax);
    glColor3f(0.0,0.0,1.0);
    if(accept)
        drawline(vx0,vy0,vx1,vy1);
    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    // draw the originals
    glColor3f(1.0,0.0,0.0);
    drawline(x0,y0,x1,y1);
    glColor3f(0.0,0.0,1.0);
    drawrect(xmin,ymin,xmax,ymax);
    
    //draw the new one
    CSL();
    drawViewPort();
    glFlush();
}


void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}


int main(int argc,char** argv){
    printf("Enter clipping window coordinates:");
    scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
    printf("Enter line coordinates:");
    scanf("%f%f%f%f",&x0,&y0,&x1,&y1);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen-Sutherland Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}