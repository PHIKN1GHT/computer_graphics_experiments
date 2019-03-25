//#include <bits/stdc++.h>
#include <GL/glut.h>
#include <list>
#include <vector>
#include <iostream>
#include <cstring>

struct rect {
	GLuint name;
	std::pair<std::pair<GLint, GLint>, std::pair<GLint, GLint> > pos;
	std::vector<float> color;
};

GLuint id = 0;
int iPointNum = 0, drawingMode = 1;
int px = 0, py = 0;
std::list<rect> rectList;
std::pair<GLint, GLint> lp; std::vector<float> lc;
int winWidth = 400, winHeight = 300;

void Initial() {
	srand(2333);
	lc.push_back(0); lc.push_back(0); lc.push_back(0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}



void DrawRect() {
	if (rectList.size() > 0)
			for (auto r : rectList) {
				if (!drawingMode) glPushName(r.name);
				glColor3f(r.color[0], r.color[1], r.color[2]),
				glRectf(r.pos.first.first, r.pos.first.second, r.pos.second.first, r.pos.second.second);
			}
	if (iPointNum) {
		glColor3f(lc[0], lc[1], lc[2]),
		glRectf(lp.first, lp.second, px, py);
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
	DrawRect();
	glFlush();
}

GLuint pickBuffer[255];
void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (drawingMode) {
			if (iPointNum == 0) lp = std::pair<GLint, GLint> {xMouse, winHeight - yMouse},
				lc[0] = (rand() % 100) / 100.0, lc[1] = (rand() % 100) / 100.0, lc[2] = (rand() % 100) / 100.0;
				else rectList.push_back(rect{id++, std::pair<std::pair<GLint, GLint>, std::pair<GLint, GLint> >
					{std::pair<GLint, GLint>{lp.first, lp.second}, std::pair<GLint, GLint>{xMouse, winHeight - yMouse}},
					std::vector<float>{lc[0], lc[1], lc[2]}
					});
			iPointNum = 1 - iPointNum;
		} else {
			memset(pickBuffer, 0, sizeof(pickBuffer));
			glSelectBuffer(255, pickBuffer);
			glRenderMode(GL_SELECT);
			glInitNames();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			GLint vp[4];
			glGetIntegerv(GL_VIEWPORT, vp);
			gluPickMatrix(GLdouble(xMouse), GLdouble(winHeight - yMouse), 10, 10, vp);
			gluOrtho2D(0.0, winWidth, 0.0, winHeight);
			DrawRect();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glFlush();
			//
			int nPicks = glRenderMode(GL_FEEDBACK);
			glRenderMode(GL_RENDER);
			if (nPicks) {
				std::cout << "You Pick No. ";
				GLuint* buffer = pickBuffer;
				for (int i = 0; i < nPicks; i++) {
					GLuint name = *buffer; buffer += 3; buffer += name - 1;
					std::cout << buffer[0] << ", "; buffer++;
				}
				std::cout << std::endl;
			}
		}
		glutPostRedisplay();
	}
}


void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	px = xMouse, py = winHeight - yMouse;
	glutPostRedisplay();
}

void ProcessMenu(int value) {
	if (value == 1) rectList.clear();
}

void Key(unsigned char key, int x, int y) {
	switch(key) {
		case 'c': drawingMode = 1 - drawingMode; break;
		default: break;
	}
}

int main(int argc,char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Clear", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}














