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

void unit(int,int);
int random(int,int);
float randomm();
void unit2(int,int);


bool length_inc=false;
bool color=false;
bool seedflag = false;
extern int score;
extern bool game_over;
extern int mouseX;
extern int mouseY;
extern int a1;
extern int a2;
extern int a3;
bool food=false;
int rows=0,columns=0;
int sDirection = RIGHT;
int foodx,foody;
int posx[MAX+1]={4,3,2,1,0,-1,-1};
int posy[MAX+1]={10,10,10,10,10,10,10};
int length=7;



float x=0.0,y=1.0,z=0.0;
void initGrid(int x,int y)
{
    columns=x;
    rows=y;
}

void draw_grid()
{
    for(int i =0;i<columns;i++)
    {
        for(int j=0;j<rows;j++)
            {unit(i,j);}
    }
}

void draw_snake2(){
    for(int i =length-1;i>0;i--)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
    }
    for(int i=0;i<length;i++)
    {
        if(i==0)
        {
            switch(sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            if(posx[i]==0)
            posx[i]=rows-1;
            if(posx[i]==columns-1)
            posx[i]=0;
            if(posy[i]==0)
            posy[i]=rows-1;
            if(posy[i]==rows-1)
            posy[i]=0;
        if(posx[i]==foodx && posy[i]==foody)
            {
                food=false;
                color=true;
                score++;
                if(length<=MAX)
                    length_inc=true;
                if(length==MAX)
//                    MessageBox(NULL,"You Win\nYou can still keep playing but the snake will not grow.","Awsome",0);
                    length=1;
            }
            for(int j=1;j<length;j++)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=true;
            }
        }
        if(i==0){
            glColor3f(0.0,0.0,1.0);
        }
        else if (i!=0 && color==true ){
             x=randomm();
             y=randomm();
             z=randomm();
            glColor3f(x,y,z);
            color=false;
        }
        else{
            glColor3f(x,y,z);

        }

        glBegin(GL_QUADS);
            glVertex2d(posx[i],posy[i]); glVertex2d(posx[i]+1,posy[i]); glVertex2d(posx[i]+1,posy[i]+1); glVertex2d(posx[i],posy[i]+1);
        glEnd();
    }
    if(length_inc)
    {
        length++;
        length_inc=false;
    }
    
}
void draw_snake()
{
    for(int i =length-1;i>0;i--)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
    }
    for(int i=0;i<length;i++)
    {
        if(i==0)
        {
            switch(sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            if(posx[i]==0||posx[i]==columns-1||posy[i]==0||posy[i]==rows-1)
                game_over=true;
            else if(posx[i]==foodx && posy[i]==foody)
            {
                food=false;
                color=true;
                score++;
                if(length<=MAX)
                    length_inc=true;
                if(length==MAX)
//                    MessageBox(NULL,"You Win\nYou can still keep playing but the snake will not grow.","Awsome",0);
                    length=1;
            }
            for(int j=1;j<length;j++)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=true;
            }
        }
        if(i==0){
            glColor3f(0.0,0.0,1.0);
        }
        else if (i!=0 && color==true ){
             x=randomm();
             y=randomm();
             z=randomm();
            glColor3f(x,y,z);
            color=false;
        }
        else{
            glColor3f(x,y,z);

        }

        glBegin(GL_QUADS);
            glVertex2d(posx[i],posy[i]); glVertex2d(posx[i]+1,posy[i]); glVertex2d(posx[i]+1,posy[i]+1); glVertex2d(posx[i],posy[i]+1);
        glEnd();
    }
    if(length_inc)
    {
        length++;
        length_inc=false;
    }
}

void draw_food()
{
    if(!food)
    {
        foodx=random(2,columns-2);
        foody=random(2,rows-2);
        std::cout<<foodx<<foody<<std::endl;
        food=true;
    }
    glColor3f(a1,a2,a3);
    glBegin(GL_QUADS);
   glVertex2d(foodx,foody);
   glVertex2d(foodx+1,foody);
   glVertex2d(foodx+1,foody+1);
   glVertex2d(foodx,foody+1);
    glEnd();
}
void draw_grid2(int xx,int yy)
{
    for(int i =0;i<xx;i++)
    {
        for(int j=0;j<yy;j++)
            {unit2(i,j);}
    }
}
void unit2(int x,int y)
{
    glLoadIdentity();

        glColor3f(1.0,1.0,1.0);
        glLineWidth(1.0);
    glBegin(GL_LINES);
        glVertex2d(x,y); glVertex2d(x+1,y);
        glVertex2d(x+1,y); glVertex2d(x+1,y+1);
        glVertex2d(x+1,y+1); glVertex2d(x,y+1);
        glVertex2d(x,y+1); glVertex2d(x,y);
    glEnd();
}
void unit(int x,int y)
{
    glLoadIdentity();
    if(x==0||x==columns-1||y==0||y==rows-1)
    {
        glLineWidth(4.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glColor3f(1.0,1.0,1.0);
        glLineWidth(1.0);
    }
    glBegin(GL_LINES);
        glVertex2d(x,y); glVertex2d(x+1,y);
        glVertex2d(x+1,y); glVertex2d(x+1,y+1);
        glVertex2d(x+1,y+1); glVertex2d(x,y+1);
        glVertex2d(x,y+1); glVertex2d(x,y);
    glEnd();
}
int random(int _min,int _max)
{
    if(!seedflag)
    {
        srand(time(NULL));
        seedflag=true;
    }
    else
        seedflag=false;
    return _min+rand()%(_max-_min);
}


float randomm()
{
    float num =rand()/static_cast<float>(RAND_MAX);
    return num;
}
