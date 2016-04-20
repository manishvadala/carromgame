#include <iostream>
#include <cmath>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawCircle(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void output();

// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.0f;
float ball_vely = 0.0f;
float ball_rad = 0.13f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.5f;
float theta = 0.0f; 

float coin_rad = 0.11f;
float striker_rad = 0.13f;
float hole_rad = 0.145f;
int flag[10][10] = {0};
int score=30;
char strin[100];
float ball1_x = 0.0f;
float ball1_y = -1.13f;
float ball1_velx = 0.0f;
float ball1_vely = 0.0f;
float ball1_rad = 0.11f;
int flagu=0;
int timer=0;
int c_count=0;
class draw_coin{
public:
	float pos_x;
	float pos_y;
	float vel_x;
	float vel_y;
	int id;
	void callo(float i,float k){
	    glPushMatrix();
	    if(this->pos_x==0 && this->pos_y==0 && k!=9.0f){
	    	//cout << "enter";
	      	this->pos_x=1.0f*cos(DEG2RAD(i*45))/2;
   			this->pos_y=1.0f*sin(DEG2RAD(i*45))/2;
   			glTranslatef(this->pos_x, this->pos_y, 0.0f);
   		}
   		else glTranslatef(this->pos_x,this->pos_y,0);
   		if(k == 0 || k == 1.0f)
   			glColor3f(k, k, k);
   		else
   			glColor3f(0.69f,0.08f,0.24f);
   		drawBall(coin_rad);
   		glPopMatrix();

   		//vel_x=0;
   		//vel_y=0;
	}
/*	void calla(float colr){
		glPushMatrix();
		glTranslatef(pos_x,pos_y,0);
		glColor3f(colr,colr,colr);
		drawBall(0.11f);
		glPopMatrix();
	}*/
};

draw_coin coin[10];
void call1(draw_coin c3);
void call2(draw_coin c1,draw_coin c2);
void call3(draw_coin u,draw_coin v);
void allign(int s);




/*
void call2(draw_coin c1,draw_coin c2){
	float temp1,temp2,temp3,temp4,alpha1,sin1x,cos1x;
    alpha1 = atan((c1.vel_y-c2.vel_y)/(c1.vel_x-c2.vel_x));
    sin1x=sin(alpha1);
    cos1x=cos(alpha1);
	if((c1.pos_x-c2.pos_x)*(c1.pos_x-c2.pos_x)+(c1.pos_y-c2.pos_y)*(c1.pos_y-c2.pos_y) <= 4*coin_rad*coin_rad  && c1.id != c2.id)
    {
    	//cout << c1.vel_x;
    	//cout << (c1.pos_x-c2.pos_x)*(c1.pos_x-c2.pos_x)+(c1.pos_y-c2.pos_y)*(c1.pos_y-c2.pos_y);
		temp1 = c1.vel_x*cos1x*cos1x - c1.vel_y*sin1x*cos1x + c2.vel_x*sin1x*sin1x + c2.vel_y*cos1x*sin1x;
		temp2 = c1.vel_y*sin1x*sin1x - c1.vel_x*cos1x*sin1x + c2.vel_x*sin1x*cos1x + c2.vel_y*cos1x*cos1x;
		temp3 = c2.vel_x*cos1x*cos1x - c2.vel_y*sin1x*cos1x + c1.vel_x*sin1x*sin1x + c1.vel_y*cos1x*sin1x;
		temp4 = c2.vel_y*sin1x*sin1x - c2.vel_x*cos1x*sin1x + c1.vel_x*sin1x*cos1x + c1.vel_y*cos1x*cos1x;
		c2.vel_x = temp1;
		c2.vel_y = temp2;
		c1.vel_y = temp3;
		c1.vel_x = temp4;
   	}
    coin[c1.id].pos_x += c1.vel_x;
    c1.pos_y += c1.vel_y;
    c2.pos_x += c2.vel_x;
    c2.pos_y += c2.vel_y;
}*/

void call2(draw_coin c1,draw_coin c2){
	float temp1,temp2,temp3,temp4,alpha1,sin1x,cos1x;
    if(abs(coin[c2.id].pos_x-coin[c1.id].pos_x)<= 0.00000001){
        if(coin[c1.id].pos_y-coin[c2.id].pos_y > 0) alpha1 = PI/2;
        else alpha1 = -1*PI/2;
    }
    else alpha1 = atan((coin[c1.id].pos_y-coin[c2.id].pos_y)/(coin[c2.id].pos_x-coin[c1.id].pos_x));
    sin1x=sin(alpha1);
    cos1x=cos(alpha1);
	if((coin[c1.id].pos_x-coin[c2.id].pos_x)*(coin[c1.id].pos_x-coin[c2.id].pos_x)+(coin[c1.id].pos_y-coin[c2.id].pos_y)*(coin[c1.id].pos_y-coin[c2.id].pos_y) <= 4*coin_rad*coin_rad  && c1.id != c2.id && flag[c1.id][c2.id] == 0 && flag[c2.id][c1.id] == 0)
    {
    	//cout << c1.id << "," << c2.id << "    0\n"; 
    	//cout << coin[c1.id].vel_x;
    	//cout << (coin[c1.id].pos_x-coin[c2.id].pos_x)*(coin[c1.id].pos_x-coin[c2.id].pos_x)+(coin[c1.id].pos_y-coin[c2.id].pos_y)*(coin[c1.id].pos_y-coin[c2.id].pos_y);
		//cout << tan(alpha1) << "\n";
        temp1 = coin[c1.id].vel_x*cos1x*cos1x - coin[c1.id].vel_y*sin1x*cos1x + coin[c2.id].vel_x*sin1x*sin1x + coin[c2.id].vel_y*cos1x*sin1x;
		temp2 = coin[c1.id].vel_y*sin1x*sin1x - coin[c1.id].vel_x*cos1x*sin1x + coin[c2.id].vel_x*sin1x*cos1x + coin[c2.id].vel_y*cos1x*cos1x;
		temp3 = coin[c2.id].vel_x*cos1x*cos1x - coin[c2.id].vel_y*sin1x*cos1x + coin[c1.id].vel_x*sin1x*sin1x + coin[c1.id].vel_y*cos1x*sin1x;
		temp4 = coin[c2.id].vel_y*sin1x*sin1x - coin[c2.id].vel_x*cos1x*sin1x + coin[c1.id].vel_x*sin1x*cos1x + coin[c1.id].vel_y*cos1x*cos1x;
        //cout << coin[c1.id].vel_x << " & " << coin[c1.id].vel_y << "\n";
        //cout << coin[c2.id].vel_x << " & " << coin[c2.id].vel_y << "\n\n";
		//if(coin[c1.id].vel_x*cos1x - coin[c1.id].vel_y*sin1x - coin[c2.id].vel_x*cos1x + coin[c2.id].vel_y*sin1x > 0){
		coin[c2.id].vel_x = temp1;
		coin[c2.id].vel_y = temp2;
        coin[c1.id].vel_x = temp3;
		coin[c1.id].vel_y = temp4;
        //cout << coin[c1.id].vel_x << " & " << coin[c1.id].vel_y << "\n";
        //cout << coin[c2.id].vel_x << " & " << coin[c2.id].vel_y << "\n\n";
		//}
		flag[c1.id][c2.id]=1;
		flag[c2.id][c1.id]=1;
    
   	}
   	if((coin[c1.id].pos_x-coin[c2.id].pos_x)*(coin[c1.id].pos_x-coin[c2.id].pos_x)+(coin[c1.id].pos_y-coin[c2.id].pos_y)*(coin[c1.id].pos_y-coin[c2.id].pos_y) > 4*coin_rad*coin_rad){
   		flag[c1.id][c2.id]=0;
   		flag[c2.id][c1.id]=0;
   	}
   // coin[c1.id].pos_x += coin[c1.id].vel_x;
    //coin[c1.id].pos_y += coin[c1.id].vel_y;
    //coin[c2.id].pos_x += coin[c2.id].vel_x;
    //coin[c2.id].pos_y += coin[c2.id].vel_y;
}



void call1(draw_coin c3){
	if(coin[c3.id].pos_x + coin_rad > box_len/2)
        if(coin[c3.id].vel_x > 0) coin[c3.id].vel_x *= -1;
    if(coin[c3.id].pos_x - coin_rad < -box_len/2)
    	if(coin[c3.id].vel_x < 0) coin[c3.id].vel_x *= -1;
    if(coin[c3.id].pos_y + coin_rad > box_len/2)
        if(coin[c3.id].vel_y > 0) coin[c3.id].vel_y *= -1;
    if(coin[c3.id].pos_y - coin_rad < -box_len/2)
    	if(coin[c3.id].vel_y < 0) coin[c3.id].vel_y *= -1;
	call3(coin[9],c3); 
	call2(c3,coin[0]);
	call2(c3,coin[1]);
	call2(c3,coin[2]);
	call2(c3,coin[3]);
	call2(c3,coin[4]);
	call2(c3,coin[5]);
	call2(c3,coin[6]);
	call2(c3,coin[7]);
	call2(c3,coin[8]);
}
void call3(draw_coin u,draw_coin v){
    float alpha,sinx,cosx,ux,uy,vx,vy,t1,t2,t3,t4;
    if(abs(coin[v.id].pos_x-coin[u.id].pos_x)<= 0.00000001){
        if(coin[u.id].pos_y-coin[v.id].pos_y > 0) alpha = PI/2;
        else alpha = -1*PI/2;
    }
    else alpha = atan((coin[u.id].pos_y-coin[v.id].pos_y)/(coin[v.id].pos_x-coin[u.id].pos_x));
    sinx=sin(alpha);
    cosx=cos(alpha);
    if(sqrt(pow((coin[u.id].pos_x-coin[v.id].pos_x),2)+pow((coin[u.id].pos_y-coin[v.id].pos_y),2)) <= (coin_rad+striker_rad) && flag[u.id][v.id] == 0 && flag[v.id][u.id] == 0)
    {
      //  cout << c1.id << "," << c2.id << "    0\n"; 
        //cout << coin[c1.id].vel_x;
        //cout << (coin[c1.id].pos_x-coin[c2.id].pos_x)*(coin[c1.id].pos_x-coin[c2.id].pos_x)+(coin[c1.id].pos_y-coin[c2.id].pos_y)*(coin[c1.id].pos_y-coin[c2.id].pos_y);
        //cout << tan(alpha) << "\n";
        ux=coin[u.id].vel_x;
        uy=coin[u.id].vel_y;
        vx=coin[v.id].vel_x;
        vy=coin[v.id].vel_y;
        t1=((ux*cosx-uy*sinx)+2*(vx*cosx-vy*sinx))/3;
        t2=ux*sinx+uy*cosx;
        t3=(4*(ux*cosx-uy*sinx)-(vx*cosx-vy*sinx))/3;
        t4=vx*sinx+vy*cosx;

        //cout << coin[u.id].vel_x << " & " << coin[u.id].vel_y << "\n";
        //cout << coin[v.id].vel_x << " & " << coin[v.id].vel_y << "\n\n";
        
        coin[u.id].vel_x=t1*cosx + t2*sinx;
        coin[u.id].vel_y=t2*cosx - t1*sinx;
        coin[v.id].vel_x=t3*cosx + t4*sinx;
        coin[v.id].vel_y=t4*cosx - t3*sinx;
        //temp1 = coin[c1.id].vel_x*cos1x*cos1x - coin[c1.id].vel_y*sin1x*cos1x + coin[c2.id].vel_x*sin1x*sin1x + coin[c2.id].vel_y*cos1x*sin1x;
        //temp2 = coin[c1.id].vel_y*sin1x*sin1x - coin[c1.id].vel_x*cos1x*sin1x + coin[c2.id].vel_x*sin1x*cos1x + coin[c2.id].vel_y*cos1x*cos1x;
        //temp3 = coin[c2.id].vel_x*cos1x*cos1x - coin[c2.id].vel_y*sin1x*cos1x + coin[c1.id].vel_x*sin1x*sin1x + coin[c1.id].vel_y*cos1x*sin1x;
        //temp4 = coin[c2.id].vel_y*sin1x*sin1x - coin[c2.id].vel_x*cos1x*sin1x + coin[c1.id].vel_x*sin1x*cos1x + coin[c1.id].vel_y*cos1x*cos1x;

        //if(coin[c1.id].vel_x*cos1x - coin[c1.id].vel_y*sin1x - coin[c2.id].vel_x*cos1x + coin[c2.id].vel_y*sin1x > 0){
        //coin[c2.id].vel_x = temp1;
        //coin[c2.id].vel_y = temp2;
        //coin[c1.id].vel_x = temp3;
        //coin[c1.id].vel_y = temp4;
        //cout << coin[u.id].vel_x << " & " << coin[u.id].vel_y << "\n";
        //cout << coin[v.id].vel_x << " & " << coin[v.id].vel_y << "\n\n";
        //}
        flag[u.id][v.id]=1;
        flag[v.id][u.id]=1;
    
    }
    if(sqrt(pow((coin[u.id].pos_x-coin[v.id].pos_x),2)+pow((coin[u.id].pos_y-coin[v.id].pos_y),2)) > (coin_rad+striker_rad)){
        flag[u.id][v.id]=0;
        flag[v.id][u.id]=0;
    } 
}

class power_level{
public:
	void callit(float len){
    glPushMatrix();
    glTranslatef(5.0f, -3.80f, -8.0f);
    glColor3f(1.0f, 0.55f, 0);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, len);
    //glVertex2f(2.0f, 2.0f);
    glVertex2f(-0.5f, len);
    glEnd();
   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
	}
};

power_level meter;

class striker_pointer{
public:
	void callthis(float len){
		glPushMatrix();
		glTranslatef(coin[9].pos_x, coin[9].pos_y,0);
		glRotatef(theta, 0, 0, 1.0f);
		glColor3f(0,0,0);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
	    //glVertex2f(coin[9].pos_x, coin[9].pos_y);
	    glVertex2f(0, 2.0f);
	    glTranslatef(-1*coin[9].pos_x, -1*coin[9].pos_y,0);
	    //coin[9].vel_y=2.0f;
	    //glVertex2f(coin[9].pos_x, 2.0f+coin[9].pos_y);
	    glEnd();
	    glPopMatrix();
	}
};
striker_pointer line;
float var1 = 0.22f,var2 = 0.22f,var3 = 0.22f;

void allign(int s){
    if((s+1) % 2 == 1 && s!=0){
        score+=5;
        c_count+=1;
        coin[s].pos_x = 3.0f + (var1=var1+0.22f);
        coin[s].pos_y = 2.0f;
    }
    else if((s+1) % 2 == 0){
        score-=5;
        if(s!=9){
            coin[s].pos_x = 3.0f + (var2=var2+0.22f);
            coin[s].pos_y = 1.5f;
        }
    }
    else {
        c_count+=1;
        score+=20;
        coin[s].pos_x = 3.0f + (var3=var3+0.22f);
        coin[s].pos_y = 1.0f;
    }
}


void pocketing(draw_coin m){
	if((m.pos_x-1.85f)*(m.pos_x-1.85f)+(m.pos_y-1.85f)*(m.pos_y-1.85f) < hole_rad*hole_rad){
		coin[m.id].vel_x=coin[m.id].vel_y=0;
        allign(m.id);
		//coin[m.id].pos_x += (m.id)*0.3f;
	}
	if((m.pos_x+1.85f)*(m.pos_x+1.85f)+(m.pos_y-1.85f)*(m.pos_y-1.85f) < hole_rad*hole_rad){
		coin[m.id].vel_x=coin[m.id].vel_y=0;
        allign(m.id);
		//coin[m.id].pos_x -= (m.id)*0.3f;
	}
	if((m.pos_x+1.85f)*(m.pos_x+1.85f)+(m.pos_y+1.85f)*(m.pos_y+1.85f) < hole_rad*hole_rad){
		coin[m.id].vel_x=coin[m.id].vel_y=0;
        allign(m.id);
		//coin[m.id].pos_x -= (m.id)*0.3f;
	}
	if((m.pos_x-1.85f)*(m.pos_x-1.85f)+(m.pos_y+1.85f)*(m.pos_y+1.85f) < hole_rad*hole_rad){
		coin[m.id].vel_x=coin[m.id].vel_y=0;
        allign(m.id);
		//coin[m.id].pos_x += (m.id)*0.3f;
	}
}
/*void output()
{
  glColor3f(0,0,0);
  glRasterPos2f(2.0f, 1.0f);
  int len, i;
 // len = (int)strlen(strin);
  for (i = 0; i < 5; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, strin[i]);
  }
}*/
void renderBitmapString(float x,float y,float z,void *font,char *string) {
    char *c;
    glRasterPos3f(x,y,z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
int isDragging;
double ox,oy,oz;
void mouseMove(int x, int y)
        {
            if (isDragging) {

                GLint viewport[4];
                GLdouble modelview[16],projection[16];
                GLfloat wx=x,wy,wz;

                glGetIntegerv(GL_VIEWPORT,viewport);
                y=viewport[3]-y;
                wy=y;
                glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
                glGetDoublev(GL_PROJECTION_MATRIX,projection);
                glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
                gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);

                oy*=80;
                ox*=80;
                oz*=80;


                if((ox>-1.2f) && (ox<1.2f))
                    coin[9].pos_x = ox;

            }
        }



        void mouseButton(int button, int state, int x, int y)
        {
            float slope;
            GLint viewport[4];
            GLdouble modelview[16],projection[16];
            GLfloat wx=x,wy,wz;

            glGetIntegerv(GL_VIEWPORT,viewport);
            y=viewport[3]-y;
            wy=y;
            glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
            glGetDoublev(GL_PROJECTION_MATRIX,projection);
            glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
            gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);

            oy*=80;
            ox*=80;
            oz*=80;

            if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) { // left mouse button pressed

            float d=sqrt(pow((coin[9].pos_x-ox),2)+pow((coin[9].pos_y-oy),2));
            if(d < striker_rad)
                isDragging = 1; // start dragging
        }
        else  {
            isDragging = 0;
        }
    }
    if(button == GLUT_LEFT_BUTTON)
    {

        if(state==GLUT_DOWN){
            tri_y = (oy+4.0f)*1.2;
            if(fabs(ox-coin[9].pos_x)>0.00001f){
                slope=(oy-coin[9].pos_y)/(ox-coin[9].pos_x);
                if(slope>=0)
                    theta = atan(slope)*180/PI;
                else
                    theta =180 + atan(slope)*180/PI;
            }
            else
            {
                if(oy-coin[9].pos_y>0.00001)
                    theta=90;
                else
                    theta=180;
            }
            theta=theta-90;
        }
        if(state==GLUT_UP){
            flagu=1;
            coin[9].vel_x=(tri_y/100)*((-2)*sin(DEG2RAD(theta)));
            coin[9].vel_y=(tri_y/100)*(2*cos(DEG2RAD(theta)));        
        }
    }
}
int main(int argc, char **argv) {
	coin[9].pos_x=0;
	coin[9].pos_y=-1.13f;

	//coin[1].vel_x=0.01f;


	for(int i=0 ; i<10; i++)
		coin[i].id = i;
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w ;
    int windowHeight = h;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("CSE251_sampleCode");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}
int i,timer2=0 ;
// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    //output();
  /*  glTranslatef(0.0f,0.0f,-1.0f);
    glColor4f( 255, 0, 0, 1);
    //glTranslatef(my_Camera.View().x, my_Camera.View().y, my_Camera.View().z); 
    glRasterPos2f(0.1f, 0.1f);
    glPrint("SCORE:",score);*/
    //Draw outerbox
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(0.611f, 0.4f, 0.121f);
    drawBox(box_len + 0.3f);
    glPopMatrix();


    // Draw Box
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(1.0f, 0.827f, 0.607f);
    drawBox(box_len);

    //Draw smallbox
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(0.0f, 0.4f, 0.0f);
    float len;
    len = 5.0f;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();


    //Draw Circle
    glPushMatrix();
    glTranslatef(0,0,0);
    glColor3f(0.0f, 0.4f, 0.0f);
    drawCircle(0.65f);
    glPopMatrix();
 /*   glPushMatrix();
    glTranslatef(0,0,0);
    glColor3f(1.0f, 0.96f, 0.56f);
    drawBall(0.65f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,0);
    glColor3f(1.0f, 0.827f, 0.607f);
    drawBall(0.37f);
    glPopMatrix();*/
    sprintf(strin,"%s","Score\n");
    renderBitmapString(-5.5f,5.0f,-6.0f,GLUT_BITMAP_TIMES_ROMAN_24,strin);
    sprintf(strin,"%d",score);
    renderBitmapString(-4.5f,5.0f,-6.0f,GLUT_BITMAP_TIMES_ROMAN_24,strin);
    if(score==0) {
        sprintf(strin,"%s","YOU LOSE\n");
        renderBitmapString(0.0f,5.0f,-6.0f,GLUT_BITMAP_TIMES_ROMAN_24,strin);
    }
    if(c_count==5){
         sprintf(strin,"%s","YOU WON THE GAME\n");
        renderBitmapString(-2.0f,5.0f,-6.0f,GLUT_BITMAP_TIMES_ROMAN_24,strin);       
    }


    /*for(i=0;i<10;i++) {
        if(coin[i].vel_x!=0 && coin[i].vel_y!=0)
            break;
    }
    if(i==10 && flagu==1){
        coin[9].pos_x = ball1_x; 
        coin[9].pos_y = ball1_y;
        theta=0;
        flagu=0;
    }*/
//	coin_1.pos_x = 1.0f;
//	coin_1.pos_y = 1.0f;



	meter.callit(tri_y);

	if(coin[9].vel_x == 0 && coin[9].vel_y == 0){
    	line.callthis(3.0f);
    }
    //cout << flagu << "\n";
    //cout << i << "\n";

    // Draw Balls
  /*  glPushMatrix();
    glTranslatef(ball_x, ball_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();    */
    // Draw Striker
    glPushMatrix();
    glTranslatef(coin[9].pos_x, coin[9].pos_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(striker_rad);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(coin[9].pos_x, coin[9].pos_y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawBall(striker_rad-0.05f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(coin[9].pos_x, coin[9].pos_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(striker_rad-0.08f);
    glPopMatrix();


    // Draw Holes
    glPushMatrix();
    glTranslatef(1.85f, 1.85f, 0.0f);
    glColor3f(0.1f, 0.0f, 0.0f);
    drawBall(hole_rad);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.85f, -1.85f, 0.0f);
    glColor3f(0.1f, 0.0f, 0.0f);
    drawBall(hole_rad);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.85f, 1.85f, 0.0f);
    glColor3f(0.1f, 0.0f, 0.0f);
    drawBall(hole_rad);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.85f, -1.85f, 0.0f);
    glColor3f(0.1f, 0.0f, 0.0f);
    drawBall(hole_rad);
    glPopMatrix();


    //Draw Coins
/*	coin[1].calla(1.0f);
	coin[2].calla(0.0f);
	coin[3].calla(1.0f);
	coin[4].calla(0.0f);
	coin[5].calla(1.0f);
	coin[6].calla(0.0f);
	coin[7].calla(1.0f);
	coin[8].calla(0.0f);*/
	coin[0].callo(0,9.0f);
	coin[1].callo(1.0f,1.0f);
	coin[2].callo(2.0f,0.0f);
	coin[3].callo(3.0f,1.0f);
	coin[4].callo(4.0f,0.0f);
	coin[5].callo(5.0f,1.0f);
	coin[6].callo(6.0f,0.0f);
	coin[7].callo(7.0f,1.0f);
	coin[8].callo(8.0f,0.0f);


/*    // Draw Triangle
    glPushMatrix();
    glTranslatef(tri_x, tri_y, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawTriangle();
    glPopMatrix();*/

    glPopMatrix();
    glutSwapBuffers();
}
float ball1x,ball1y,ballx,bally;
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
    timer=timer+1;
    if(timer==100){
        score-=1;
        timer=0;
    }
    if(score==0){
        timer2 += 1;
        if(timer2==100) exit(0);
    }
    //cout << c_count << endl;
    //cout << "entere";
	//cout << coin[1].vel_x;
    //cout << score << endl;

    // Handle ball collisions with box
 /*   if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;

    if(coin[9].pos_x + ball1_rad > box_len/2 || coin[9].pos_x - ball1_rad < -box_len/2)
        coin[9].vel_x *= -1;
    if(coin[9].pos_y + ball1_rad > box_len/2 || coin[9].pos_y - ball1_rad < -box_len/2)
        coin[9].vel_y *= -1;*/
    if(coin[9].pos_x + striker_rad > box_len/2)
        if(coin[9].vel_x > 0) coin[9].vel_x *= -1;
    if(coin[9].pos_x - striker_rad < -box_len/2)
        if(coin[9].vel_x < 0) coin[9].vel_x *= -1;
    if(coin[9].pos_y + striker_rad > box_len/2)
        if(coin[9].vel_y > 0) coin[9].vel_y *= -1;
    if(coin[9].pos_y - striker_rad < -box_len/2)
        if(coin[9].vel_y < 0) coin[9].vel_y *= -1;
    /*alpha = atan((ball_vely-coin[9].vel_y)/(ball_velx-coin[9].vel_x));
    sinx=sin(alpha);
    cosx=cos(alpha);*/



 /*   if((ball_x-coin[9].pos_x)*(ball_x-coin[9].pos_x)+(ball_y-coin[9].pos_y)*(ball_y-coin[9].pos_y) <= 4*ball_rad*ball_rad)
    {
		ball1x = ball_velx*cosx*cosx - ball_vely*sinx*cosx + coin[9].vel_x*sinx*sinx + coin[9].vel_y*cosx*sinx;
		ball1y = ball_vely*sinx*sinx - ball_velx*cosx*sinx + coin[9].vel_x*sinx*cosx + coin[9].vel_y*cosx*cosx;
		ballx = coin[9].vel_x*cosx*cosx - coin[9].vel_y*sinx*cosx + ball_velx*sinx*sinx + ball_vely*cosx*sinx;
		bally = coin[9].vel_y*sinx*sinx - coin[9].vel_x*cosx*sinx + ball_velx*sinx*cosx + ball_vely*cosx*cosx;
		coin[9].vel_x = ball1x;
		coin[9].vel_y = ball1y;
		ball_vely = bally;
		ball_velx = ballx;
    }*/

    call1(coin[0]);
    call1(coin[1]);
    call1(coin[2]);
    call1(coin[3]);
    call1(coin[4]);
    call1(coin[5]);
    call1(coin[6]);
    call1(coin[7]);
    call1(coin[8]);
    //call1(coin[9]);

    float fs=0.001f;
    float velocity;
    
    //updating positions of striker and coins
    for(int j=0;j<10;j++){

        velocity = sqrt(pow(coin[j].vel_x,2)+pow(coin[j].vel_y,2));

    	if(abs(coin[j].vel_x) > 0.001) coin[j].pos_x = coin[j].pos_x + (coin[j].vel_x = coin[j].vel_x - fs*(coin[j].vel_x/velocity));
    	if(abs(coin[j].vel_x) < 0.001) coin[j].vel_x = 0;
    	if(abs(coin[j].vel_y) > 0.001) coin[j].pos_y = coin[j].pos_y + (coin[j].vel_y = coin[j].vel_y - fs*(coin[j].vel_y/velocity));
    	if(abs(coin[j].vel_y) < 0.001) coin[j].vel_y = 0;
    }
    // Update position of ball
   // ball_x += ball_velx;
   // ball_y += ball_vely;
    //cout << coin[9].vel_y;
    //cout << "manish\n";

    //cout << flagu << endl;
    if(coin[9].vel_x == 0 && coin[9].vel_y == 0 && flagu==1){
        if(coin[0].vel_x==0 && coin[1].vel_x==0 && coin[2].vel_x==0 && coin[3].vel_x==0 && coin[4].vel_x==0 && coin[5].vel_x==0 && coin[6].vel_x==0 && coin[7].vel_x==0 && coin[8].vel_x==0 && coin[0].vel_y==0 && coin[1].vel_y==0 &&coin[2].vel_y==0 &&coin[3].vel_y==0 && coin[4].vel_y==0 && coin[5].vel_y==0 && coin[6].vel_y==0 && coin[7].vel_y==0 && coin[8].vel_y== 0){
            coin[9].pos_x = ball1_x; 
            coin[9].pos_y = ball1_y;
            theta=0;
            //cout<<"entered\n";
            flagu=0;
        }
    }
    //pocketing
    pocketing(coin[0]);
    pocketing(coin[1]);
    pocketing(coin[2]);
    pocketing(coin[3]);
    pocketing(coin[4]);
    pocketing(coin[5]);
    pocketing(coin[6]);
    pocketing(coin[7]);
    pocketing(coin[8]);
    pocketing(coin[9]);

   // coin[9].pos_x += coin[9].vel_x;
   // coin[9].pos_y += coin[9].vel_y;


    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
   
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawCircle(float rad) {
    
   glBegin(GL_LINE_LOOP);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.71f, 0.71f, 0.71f, 0.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if (key == 97)
    {
    	theta += 5;
	}
	if (key == 99)
    {
    	theta -= 5;
	}
    if (key == 32)
    {
        //cout << "entered\n";
        flagu=1;
    	coin[9].vel_x=(tri_y/100)*((-2)*sin(DEG2RAD(theta)));
    	coin[9].vel_y=(tri_y/100)*(2*cos(DEG2RAD(theta)));
    	/*cout << coin[9].vel_x << endl;
    	cout << coin[9].vel_y << endl;
    	cout << theta << endl;
    	cout << cos(theta) << endl;*/
	}	
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        if(coin[9].pos_x > -1.2f) coin[9].pos_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        if(coin[9].pos_x < 1.2f) coin[9].pos_x += 0.1;
    if (key == GLUT_KEY_UP)
    {
        if(tri_y < 7) tri_y += 0.2;
    	meter.callit(tri_y);
    }
    if (key == GLUT_KEY_DOWN)
    {
         if(tri_y > 0.6) tri_y -= 0.2;
        meter.callit(tri_y);
    }
}
/*
void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 5;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 5;
    }
}*/
