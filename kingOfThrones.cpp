#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>

#include <math.h>

#include <time.h>
#include <cstdlib>
using namespace std;
//g++ OpenGL2DTemplate.cpp -o gl -lGL -lGLU -lglut -lGLEW
void anim();
void calcY();
void resize(int, int);
void Key(unsigned char, int, int);
void KeyUp(unsigned char, int, int);
int isOnWall();
void setDelay();
void drawStep(double,double,double);
int getCurrentStep();
void setOnStep(int);
int onCurrentStep();
void drawGate();
int isInWinningArea();
void initAgain();
void addObstacle();
char intToChar(int);
void getTimeChars();
void getNumberOfLevels();
int isHit();
void restart();
int isHitStep();
double x = 0;
double y = 5.0001 ;
double yStart = 0 ;//start the jump.
double yMax = 0;//max height for the jump.
double squareWidth = 20;//the width of the moving body.
int yDirection = 1; // 0 for up and 1 for down.
int xDirection = 0; // 0 for right and 1 for left.
int status = 0; // 0 for on ground , 1 for jumping 2 for jumping on wall.
int windowWidth = 800;
int windowHeight = 500;
double step = 0.07;
timespec tim, tim2;
int myObstacles[300] = {800,0,0,370,0,50,400,420,100};
int obstaclesLength = 9;
int windowID;
int currentStepIndex = 0;
int generateDirectionX = 0; // 0 for generate on left and 1 on right
char currentTime[500];
int currentTimeLength = 1;
int numberOfLevels = 0;
char numberOfLevelString [500];
int numberOfLevelStringLength = 1 ;
int myBarriers[500] = {520,105};
int myBarriersLength = 2;
int restartedAt = 0;
void Display() {
	getTimeChars();
	getNumberOfLevels();
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(650, 470);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'I');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	for(int j = 0 ;j<currentTimeLength;j++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, currentTime[j]);
		}
	glRasterPos2i(300, 470);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'p');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'r');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'e');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 's');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 's');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 't');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'o');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'e');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'l');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'e');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'r');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 't');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'e');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ',');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 't');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'o');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 's');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'l');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'o');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'w');

	glRasterPos2i(0, 470);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	char t[]  = "Number of Gates reached = ";
	int k = 0;
	while(t[k]!='\0'){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[k]);
		k++;
	}
	if((numberOfLevels) == 0){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, intToChar(numberOfLevels));
	}else{
		for(int j = 0 ;j<numberOfLevelStringLength;j++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, numberOfLevelString[j]);
		}
	}
	int i = 0;
	while(i<obstaclesLength){
		drawStep(myObstacles[i],myObstacles[i+1],myObstacles[i+2]);
		i+=3;
	}
	drawGate();
	glBegin(GL_POLYGON);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(520, 105, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(520+10, 105, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(520, 105+20, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(520+10, 105+20, 0.0f);
	glEnd();
	glPushMatrix();
	glTranslated(x,y,0);
	//drawWheel();
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 20.f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(squareWidth, 20.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(squareWidth, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
	glFlush();
}

int main(int argc, char** argr) {
	glutInit(&argc, argr);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(150, 150);
	windowID = glutCreateWindow("MYPROJECT");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutIdleFunc(anim);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glutReshapeFunc(resize);
	glutMainLoop();
//		drawStep(windowWidth,0,0);
//				drawStep(400,0,50);
//				drawStep(400,windowWidth - 400,100);
//	for(int i = 0 ; i<mySteps.length(); i++){
//			cout << mySteps.get(i).width;
//			cout <<"-";
//			cout <<i;
//			cout <<"-";
//			cout <<mySteps.get(i).startY;
//			cout <<"\n";
//		}
	//glutMainLoop();
	return 0;
}
void Key(unsigned char key, int a, int b) {
	if(key == 'a' || key == 'A'){
		step+= 0.01;
		if(step>=0.5){
			step = 0.5;
		}
		return;
	}
	if(key == 's' || key == 'S'){
		step-= 0.01;
		if(step<= 0){
			step = 0;
		}
		return;
	}
	if(status==0){
		yStart = y;
		yDirection = 0;
		if(isOnWall()==1){
			status = 2;
			yMax = y+30;
		}else{
			status = 1;
			yMax = y+70;
		}
	}else if(status ==1){
		if(isOnWall()==1){
			status = 2;
			yDirection = 0;
			yMax = y+30;
		}

	}
	glutPostRedisplay();
}
void KeyUp(unsigned char key, int a, int b) {
  glutPostRedisplay();
}
void anim(){
//	if(y<=5){
//		y = 5.000000001;
//	}
	if( xDirection == 0 ){
		if(x >=windowWidth-squareWidth){
			xDirection = 1;
			if(status == 1){
				yDirection = 1;
			}
			setDelay();
		}else{
			x+= step;
			if(isHitStep()==1){
				yDirection = 1;
				//y-=step;
			}
			calcY();
		}
	}else{
		if(x<=0){
			xDirection = 0;
			if(status == 1){
				yDirection = 1;
			}
			setDelay();
		}else{
			x-= step;
			if(isHitStep()==1){
				yDirection = 1;
				//y-=step;
			}
			calcY();
		}
	}
	if (isHit() == 1){
		restart();
	}
	if(onCurrentStep()==0){
		yStart = 0;
		status = 1;
	}
	int stepIndex = getCurrentStep();
	if(currentStepIndex != stepIndex && stepIndex != -1){
		setOnStep(stepIndex);
	}
	if(isInWinningArea()==1){
		numberOfLevels++;
		setDelay();
		initAgain();
	}else{
		glutPostRedisplay();
	}
}
void resize(int width, int height) {
    glutReshapeWindow( windowWidth, windowHeight);
}
void calcY(){
	if(status != 0){
//		if(y>=yStart && y>0){
//			y+=2*sin(x);
//		}else{
//			if(y<0){
//				y=0;
//			}
//			status = 0;
//			yDirection = 1;
//		}
		if(yDirection == 0){
			if(y<=yMax){
				if(sin(x)<0){
					y+=step*sin(x)*-1;
				}else{
					y+=step*sin(x);
				}
//				y+=step;
				if(isHitStep()==1){
					yDirection = 1;
					//y-=step-0.2;

				}
			}else{
				yDirection = 1;
			}
		}else{
			if(y>yStart){
				if(sin(x)<0){
					y-=step*sin(x)*-1;
				}else{
					y-=step*sin(x);
				}
//				y-=step;

			}else{
				yDirection = 1;
				status = 0;
			}
		}
	}
}
//return 1 if body is on wall and 0 otherwise
int isOnWall(){
	if(x >=windowWidth-squareWidth || x<=0){
		return 1;
	}else{
		return 0;
	}
}
void setDelay(){
	tim.tv_sec  = 0;
	tim.tv_nsec = 200000000L;
	nanosleep(&tim , &tim2);
}

void drawStep(double width, double startX, double startY){
	glBegin(GL_POLYGON);
		glColor3f(0.9, 0.3, 0.2);
		glVertex3f(startX, startY, 0.0f);
		glColor3f(0.9, 0.3, 0.2);
		glVertex3f(startX, startY + 5, 0.0f);
		glColor3f(0.9, 0.3, 0.2);
		glVertex3f(startX + width, startY+5, 0.0f);
		glColor3f(0.9, 0.3, 0.2);
		glVertex3f(startX + width, startY, 0.0f);
	glEnd();
}
// return -1 if not on a step otherwise return the step number
int getCurrentStep(){
	int i = 0;
	while(i<obstaclesLength){
		int width = myObstacles[i];
		int startX = myObstacles[i+1];
		if(y  >= myObstacles[i+2]+5 && y <= myObstacles[i+2]+20){
			if((x >= startX-4 && x<=  startX+ width) || (x+squareWidth >= startX && x+squareWidth<= startX+width) ){
				return (i/3);
			}
		}
		i+=3;
	}
	return -1;
}
int isHitStep(){
	int i = 0;
		while(i<obstaclesLength){
			int width = myObstacles[i];
			int startX = myObstacles[i+1];
			if(y  <= myObstacles[i+2] && y >= myObstacles[i+2]-12){
				if((x >= startX && x<=  startX + width) || (x+squareWidth >= startX && x+squareWidth<= startX+width) ){
					return 1;
				}
			}
			i+=3;
		}
		return -0;
}
void setOnStep(int stepIndex){
	currentStepIndex = stepIndex;
	int i = stepIndex*3;
	y = myObstacles[i+2] + 5.0000001;
	yStart = y;
	status = 0;
	yDirection = 1;
}
int onCurrentStep(){
	int i = currentStepIndex*3;
	int startX = myObstacles[i+1];
	int width = myObstacles[i];
	if((x >= startX && x<=  startX+ width) || (x+squareWidth >= startX && x+squareWidth<= startX+width) ){
		return 1;
	}
	return 0;
}
void drawGate(){
	double endY = myObstacles[obstaclesLength-1]+5;
	double endX = myObstacles[obstaclesLength-2];
	double width =myObstacles[obstaclesLength-3];
	int startX;
	if(endX+width >= windowWidth){
		startX = windowWidth - 40;
	}else{
		startX = 40;

	}
	glBegin(GL_POLYGON);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startX, endY-20, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startX+40.0f, endY, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startX, endY+20, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startX-40, endY, 0.0f);
	glEnd();
}
int isInWinningArea(){
	double endY = myObstacles[obstaclesLength-1]+5;
	double endX = myObstacles[obstaclesLength-2];
	double width =myObstacles[obstaclesLength-3];
	int startX;
	if(endX+width >= windowWidth){
		startX = windowWidth - 40;
	}else{
		startX = 40;

	}
	if(y >= endY-15 && y <= endY+15){
		if(x>= startX - 40 && x<= startX + 40){
			return 1;
		}
	}
	return 0;

}

void initAgain(){
	x = 0;
	y = 5.00000001;
	yDirection = 1;
	xDirection = 0;
	status = 0;
	addObstacle();
}
void restart(){
	x = 0;
	y = 5.00000001;
	yDirection = 1;
	xDirection = 0;
	status = 0;
	generateDirectionX = 0;
	for(int i = 9;i<300;i++){
		myObstacles[i] = 0;
	}
	obstaclesLength = 9;
	numberOfLevels = 0;
	restartedAt = glutGet(GLUT_ELAPSED_TIME);
}
void addObstacle(){
	if(windowHeight - myObstacles[obstaclesLength-1] <= 80){
		for(int i = 9;i<300;i++){
			myObstacles[i] = 0;
		}
		obstaclesLength = 9;
	}else{
		int newX, newWidth;
		int newY = rand() % 20 + myObstacles[obstaclesLength-1]+40;
		if(generateDirectionX == 0){
			newX = 0;
			newWidth = rand() % 70 + (myObstacles[obstaclesLength-2] - 50);
			generateDirectionX = 1;

		}else{
			newX = rand() % 70 + (myObstacles[obstaclesLength-2] + 40);
			newWidth = windowWidth - newX;
			generateDirectionX = 0;
		}
		if(newWidth<90){
			newWidth = 90;
		}
		myObstacles[obstaclesLength] = newWidth;
		myObstacles[obstaclesLength+1] = newX;
		myObstacles[obstaclesLength+2] = newY;
		obstaclesLength+=3;
	}
}
char intToChar(int a){
	switch(a){
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	}
	return '0';
}
void getTimeChars(){
	int time = (glutGet(GLUT_ELAPSED_TIME)-restartedAt)/100;
	int i = 0;
	int temp = time;
	while(temp>0){
		temp /=10;
		i++;
	}
	currentTimeLength = i-1;
	temp = time;
	i--;
	while(i>=0){
		int m = temp%10;
		currentTime[i] = intToChar(m);
		temp /=10;
		i--;
	}
}
void getNumberOfLevels(){
	int temp = numberOfLevels;
	int i = 0;
	while(temp>0){
		i++;
		temp /= 10;
	}
	numberOfLevelStringLength = i;
	i--;
	temp = numberOfLevels;
	while(i>=0){
		numberOfLevelString[i] = intToChar(temp%10);
		temp/=10;
		i--;
	}
}
int isHit(){
	int i = 0;
	while(i<myBarriersLength){
		if(y>= myBarriers[i+1] && y <= myBarriers[i+1] + 20){
			if(x>=myBarriers[i] && x <= myBarriers[i] + 10){
				return 1;
			}
		}
		i+=2;
	}
	return 0;
}
