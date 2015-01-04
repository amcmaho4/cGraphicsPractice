#include <stdio.h>
#include<math.h>
#include "gfx2.h"
#include <unistd.h>
#include <stdlib.h>


void makeWheel(float,float,float,int);
void makePulley(int, int, int, int);
void makeCart(int, int, int,float,float);
void makePulleySystem(float,float, float, float, float);
void makeRotaters(float, float, float, float);
void makeSmallRotaters(float, float, float,float);
void makeCartWheels(int,int ,int,float,float);
int wd = 600, ht = 600;

int main()
{
	float dx=8*M_PI;
	int m=1, c;
	float mWR=100; //mainWheelRadius
	float sWR=20;//smallWheelRadius
	float eD=40; //distance from small wheels to edge oof screen
	float cS= 100; //cart size
	

	gfx_open(wd, ht, "My window"); 
	gfx_clear_color( 10, 10, 200 );


	while(c != 'q') {  
		gfx_clear(); 
		makePulleySystem(dx, mWR,sWR, eD,cS);
		dx+=(m*.0173);
		if(dx>=16*M_PI||dx<1*M_PI){			
			m=-m;
		}

		usleep(5000);
		if(gfx_event_waiting()) {
			c = gfx_wait();              
   			
			gfx_clear();
			
		}
	}
}




void makePulleySystem(float dx, float mWR, float sWR,float eD, float cS){
	float cWS=cS/10; // cart wheel radius
	float cartdx=2*M_PI*dx;
	float cSP=sWR*2+eD; //cart start position

	makeRotaters(mWR,sWR,eD,-dx);
	
	//make pulleys between large and small spinners
	makePulley(eD+1,ht-eD-sWR-7,(wd/2)-mWR+9,ht/2-40);
	makePulley(wd-eD-1,ht-eD-sWR-7,(wd/2)+mWR-9,ht/2-40);
	
	makeCart(cSP+cartdx,wd-cS-cWS, cS,cWS, dx);
	
        //make pulleys between cart and small spinners
	makePulley(wd-sWR-eD,ht-eD,cSP+cartdx+100,ht-eD);
	makePulley(sWR+eD,ht-eD,cSP+cartdx,ht-eD);

}

void makeWheel(float X, float Y, float dx,int radius){
	int pX,pY;
	float angle,i=0;
	gfx_circle(X,Y,radius); 
	//draw spokes
	for(angle=dx;angle<=2*M_PI+dx;angle+=M_PI/4) {  
		pX=X+radius*cos(angle);
		pY=Y+radius*sin(angle);
		gfx_color(255, 255, 255);
		gfx_line(X,Y,pX,pY);
	}
}

void makeRotaters(float mWR, float sWR, float eD,float dx){
	// make main rotater
	makeWheel(wd/2,ht/2,dx/10,100);
	// make smaller rotaters
	makeSmallRotaters(mWR,sWR, eD,dx);
}

void makeSmallRotaters(float mWR, float sWR, float eD,float dx){
	makeWheel(sWR+eD,ht-sWR-eD,dx/2,sWR);
	makeWheel(wd-sWR-eD,ht-sWR-eD,dx/2,sWR);
}

void makePulley(int x1, int y1, int x2, int y2){
	gfx_line(x1,y1,x2,y2);
}

void makeCart(int X,int Y,int radius,float cWS,float dx){
	gfx_line(X,Y,X+radius,Y);
	gfx_line(X+radius,Y+radius,X+radius,Y);
	gfx_line(X,Y+radius,X,Y);
	gfx_line(X+radius,Y+radius,X,Y+radius);
	makeCartWheels(X,Y,radius,cWS, dx);
}

void makeCartWheels(int X,int Y,int radius,float cWS, float dx){
	makeWheel(X,Y+radius,dx,cWS);
	makeWheel(X+radius,Y+radius,dx,cWS);
}


