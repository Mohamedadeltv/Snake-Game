#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<math.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
#include <math.h>
#include <errno.h>
#include <fenv.h>
#include <ctime>
#include <time.h>
#include <fstream>
#include "game.h"

#define ROWS 40.0
#define COLUMNS 40.0

std::ofstream ofile;
std::ifstream ifile;
bool game_over=false;
extern int sDirection;
int score=0;
float FSB=10;
int phyWidth = 600;
int phyHeight = 600;
int logWidth = 40;
int logHeight = 40;
int status=0;
int mouseXX,mouseYY;
int centerX=20,centerY=20;
int mouseX= centerX, mouseY = centerY;
int sqWid=5;
int cx1=20,cy1=5,cx2=20,cy2=20,cx3=20,cy3=35;
int cx4=35,cy4=5,cx5=35,cy5=20,cx6=35,cy6=35;
int cx7=5,cy7=5;
int cx8=5,cy8=20;
bool sqUp=true;
int sqDelta=0;
int maxY=1;
int a1=1,a2=0,a3=1;
int paused=1;

void init();
void display_callback();
void input_callback(int,int,int);
void reshape_callback(int,int);
void timer_callback(int);
void GameMode();
void chooseFood();
void help();


void printSome(char *str, int x, int y){
glRasterPos2d(x,y);
for(int i=0;i<strlen(str);i++){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}
}

void drawSquares(){
glColor3f(0.0f, 1.0f, 1.0f); //
glBegin(GL_POLYGON);
glVertex2f(cx1-5-sqWid/2, cy1-sqWid/2+sqDelta); // x, y
glVertex2f(cx1+5+sqWid/2, cy1-sqWid/2+sqDelta); // x, y
glVertex2f(cx1+5+sqWid/2, cy1+sqWid/2+sqDelta); // x, y
glVertex2f(cx1-5-sqWid/2, cy1+sqWid/2+sqDelta); // x, y
glEnd();
glColor3f(0,0,0);
printSome("food color", cx1-2.5, cy1);
glColor3f(1.0f, 1.0f, 0.0f); //
glBegin(GL_POLYGON);
glVertex2f(cx2-5-sqWid/2, cy2-sqWid/2+sqDelta); // x, y
glVertex2f(cx2+5+sqWid/2, cy2-sqWid/2+sqDelta); // x, y
glVertex2f(cx2+5+sqWid/2, cy2+sqWid/2+sqDelta); // x, y
glVertex2f(cx2-5-sqWid/2, cy2+sqWid/2+sqDelta); // x, y
glEnd();
glColor3f(0,0,0);
printSome("mouse", cx2-2.5, cy2);
glColor3f(0.0f, 1.0f, 0.0f); //
glBegin(GL_POLYGON);
glVertex2f(cx3-5-sqWid/2, cy3-sqWid/2+sqDelta); // x, y
glVertex2f(cx3+5+sqWid/2, cy3-sqWid/2+sqDelta); // x, y
glVertex2f(cx3+5+sqWid/2, cy3+sqWid/2+sqDelta); // x, y
glVertex2f(cx3-5-sqWid/2, cy3+sqWid/2+sqDelta); // x, y
glEnd();
glColor3f(0,0,0);
printSome("keyboard", cx3-2.5, cy3);
glColor3f(0.0f, 1.0f, 0.0f); //
glBegin(GL_POLYGON);
glVertex2f(cx7-2-sqWid/2, cy7-sqWid/2+sqDelta); // x, y
glVertex2f(cx7+2+sqWid/2, cy7-sqWid/2+sqDelta); // x, y
glVertex2f(cx7+2+sqWid/2, cy7+sqWid/2+sqDelta); // x, y
glVertex2f(cx7-2-sqWid/2, cy7+sqWid/2+sqDelta); // x, y
glEnd();
glColor3f(0,0,0);
printSome("help", cx7-1.5, cy7);
glColor3f(0.0f, 1.0f, 0.0f); //
glBegin(GL_POLYGON);
glVertex2f(cx8-2-sqWid/2, cy8-sqWid/2+sqDelta); // x, y
glVertex2f(cx8+2+sqWid/2, cy8-sqWid/2+sqDelta); // x, y
glVertex2f(cx8+2+sqWid/2, cy8+sqWid/2+sqDelta); // x, y
glVertex2f(cx8-2-sqWid/2, cy8+sqWid/2+sqDelta); // x, y
glEnd();
glColor3f(0,0,0);
printSome("diff game", cx8-2.5, cy8);
if (abs(sqDelta)<=maxY) sqUp=!sqUp ;
if (sqUp) sqDelta+=1; else sqDelta-=1;
}


void passiveMouse(int x,int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    mouseY = phyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
    glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y) {
if(key=='m')
    FSB++;
if (key== 'n')
    FSB--;
if (key== 'q')
    exit(0);
    if (key == 'a'){
        a1=1;a2=0;a3=1;
    }
    if (key == 'b'){
        a1=1;a2=1;a3=0;

    }
    if (key == 'c'){
        a1=0;a2=0;a3=1;
    }
    if (key == 'w'){
        if(sDirection!=DOWN)
            sDirection=UP;
    }
    if (key == 'a'){
        if(sDirection!=RIGHT)
            sDirection=LEFT;
    }
    if (key == 's'){
        if(sDirection!=UP)
            sDirection=DOWN;
    }
    if (key == 'd'){
        if(sDirection!=LEFT)
            sDirection=RIGHT;
    }
    if (key=='p')
{   if(paused == 0){
    FSB=10;
    paused = 1;

}
    if(paused==1){
        FSB=0.1;
       paused=0;
    }
}


glutPostRedisplay();

}
void mouseClick(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
    mouseXX = x;
    mouseXX=0.5+1.0*mouseXX*logWidth/phyWidth;
    mouseYY = phyHeight - y;
    mouseYY=0.5+1.0*mouseYY*logHeight/phyHeight;
    if( mouseXX>=(cx1-5-sqWid/2) && mouseXX<=(cx1+5+sqWid/2) && mouseYY >=(cy1-sqWid/2) && mouseYY <=(cy1+sqWid/2)){
    status=1;
        }
    if( mouseXX>=(cx2-5-sqWid/2) && mouseXX<=(cx2+5+sqWid/2) && mouseYY >=(cy2-sqWid/2) && mouseYY <=(cy2+sqWid/2)){
    status=2;
        }
    if( mouseXX>=(cx3-5-sqWid/2) && mouseXX<=(cx3+5+sqWid/2) && mouseYY >=(cy3-sqWid/2) && mouseYY <=(cy3+sqWid/2)){
    status=3;
        }
    if( mouseXX>=(cx4-2-sqWid/2) && mouseXX<=(cx4+2+sqWid/2) && mouseYY >=(cy4-sqWid/2) && mouseYY <=(cy1+sqWid/2)){
        FSB=25;
    status=4;
        }
    if( mouseXX>=(cx5-2-sqWid/2) && mouseXX<=(cx5+2+sqWid/2) && mouseYY >=(cy5-sqWid/2) && mouseYY <=(cy5+sqWid/2)){
        FSB=15;
    status=5;
        }
    if( mouseXX>=(cx6-2-sqWid/2) && mouseXX<=(cx6+2+sqWid/2) && mouseYY >=(cy6-2-sqWid/2) && mouseYY <=(cy6+2+sqWid/2)){
        FSB=5;
    status=6;
        }
    if( mouseXX>=(cx7-2-sqWid/2) && mouseXX<=(cx7+2+sqWid/2) && mouseYY >=(cy7-2-sqWid/2) && mouseYY <=(cy7+2+sqWid/2)){
    status=7;
    }
    if( mouseXX>=(cx8-2-sqWid/2) && mouseXX<=(cx8+2+sqWid/2) && mouseYY >=(cy8-2-sqWid/2) && mouseYY <=(cy8+2+sqWid/2)){
    status=8;
        }
    }

    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    status=0;
    }
    glutPostRedisplay();
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(phyHeight,phyWidth);
    glutCreateWindow("Snake game made by Omar Hesham & Mohamed Adel");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(0 ,timer_callback,0);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(Keyboard);
    init();
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    initGrid(COLUMNS,ROWS);
}

//Callbacks
void display_callback()
{
    if(game_over)
    {
        ofile.open("score.dat",std::ios::trunc);
        ofile<<score<<std::endl;
        ofile.close();
        ifile.open("score.dat",std::ios::in);
        char a[4];
        ifile>>a;
        std::cout<<a;
        char text[50]= "Your score : ";
        strcat(text,a);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if(status==0){drawSquares();}
    else if(status==1) {
        chooseFood();

    }
    else if(status==2) {
        draw_grid();
        draw_food();
        draw_snake();
        glutPassiveMotionFunc(passiveMouse);
    }
    else if(status==3) {

        GameMode();
}
    else if(status==4 || status==5 || status==6){
        draw_grid();
        draw_food();
        draw_snake();
    }
    else if (status==7){
        help();
    }
    else if (status==8){
        draw_grid();
        draw_food();
        draw_snake2();

    }

    glutSwapBuffers();
}

void help(){
    glColor3f(1,1,1);
    printSome("Press M - To increase the speed of the snake ", 1, 34);
    printSome("Press N - To decrease the speed of the snake ", 1, 30);
    printSome("press Q - To exit the game ", 1, 26);
    printSome("press P - To pause the game ", 1, 22);
    printSome("press A or B or C - To change the color of the food ", 1, 18);
    printSome("Right Mouse Click - To go back to the previous page ", 1, 14);
}

void chooseFood(){
    glColor3f(1,1,1);
    printSome("press A or B or C on your keyboard ", 7, 5);
    printSome("to choose the food color", 10, 3);
    printSome("click on left & right mouse when you finish ", 5, 1);

    glColor3f(1,0,1);
    glRectd(17.5, 10,  22.5, 15);
    glEnd();
    glColor3f(0,0,0);
    printSome("A", 19.5, 12);

    glColor3f(1,1,0);
    glRectd(17.5, 20,  22.5, 25);
    glEnd();
    glColor3f(0,0,0);
    printSome("B", 19.5, 22);

    glColor3f(0,0,1);
    glRectd(17.5, 30,  22.5, 35);
    glEnd();
    glColor3f(0,0,0);
    printSome("C", 19.5, 32);

}

void GameMode(){
    glColor3f(0.0f, 1.0f, 1.0f); //
    glBegin(GL_POLYGON);
    glVertex2f(cx4-2-sqWid/2, cy4-sqWid/2); // x, y
    glVertex2f(cx4+2+sqWid/2, cy4-sqWid/2); // x, y
    glVertex2f(cx4+2+sqWid/2, cy4+sqWid/2); // x, y
    glVertex2f(cx4-2-sqWid/2, cy4+sqWid/2); // x, y
    glEnd();
    glColor3f(0,0,0);
    printSome("hard", cx4-1.5, cy4);
    glColor3f(1.0f, 1.0f, 0.0f); //
    glBegin(GL_POLYGON);
    glVertex2f(cx5-2-sqWid/2, cy5-sqWid/2); // x, y
    glVertex2f(cx5+2+sqWid/2, cy5-sqWid/2); // x, y
    glVertex2f(cx5+2+sqWid/2, cy5+sqWid/2); // x, y
    glVertex2f(cx5-2-sqWid/2, cy5+sqWid/2); // x, y
    glEnd();
    glColor3f(0,0,0);
    printSome("medium", cx5-2.5, cy5);
    glColor3f(0.0f, 1.0f, 0.0f); //
    glBegin(GL_POLYGON);
    glVertex2f(cx6-2-sqWid/2, cy6-sqWid/2); // x, y
    glVertex2f(cx6+2+sqWid/2, cy6-sqWid/2); // x, y
    glVertex2f(cx6+2+sqWid/2, cy6+sqWid/2); // x, y
    glVertex2f(cx6-2-sqWid/2, cy6+sqWid/2); // x, y
    glEnd();
    glColor3f(0,0,0);
    printSome("easy", cx6-1.5, cy6);
    glColor3f(0.0f, 1.0f, 0.0f);
    draw_grid2(20, 40);

    glColor3f(1.0, 0.9122f, 0.432f);

    for(int i=15;i<17;i++){
        for(int j=35;j<37;j++){
            glRectd(i, j, i +1, j +1);
        }
    }

    glColor3f(0.24421f, 0.5f, 0.0f);

    for(int i=5;i<15;i++){
        for(int j=35;j<37;j++){
            glRectd(i, j, i +1, j +1);
        }
    }
    glColor3f(0.24421f, 0.5f, 0.0f);

    for(int i=3;i<5;i++){
        for(int j=26;j<37;j++){
            glRectd(i, j, i +1, j +1);
        }
    }
    glColor3f(0.24421f, 0.5f, 0.0f);

    for(int i=3;i<17;i++){
        for(int j=26;j<28;j++){
            glRectd(i, j, i +1, j +1);
        }
    }
    glColor3f(0.24421f, 0.5f, 0.0f);

    for(int i=15;i<17;i++){
        for(int j=12;j<26;j++){
            glRectd(i, j, i +1, j +1);
        }
    }
    glColor3f(0.24421f, 0.5f, 0.0f);

    for(int i=3;i<17;i++){
        for(int j=12;j<14;j++){
            glRectd(i, j, i +1, j +1);
        }
    }
}

void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLfloat)w,GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FSB,timer_callback,0);
}
void input_callback(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}
