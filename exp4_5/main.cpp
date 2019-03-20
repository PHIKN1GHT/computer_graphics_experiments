//#include <bits/stdc++.h>
#include <GL/glut.h>
#include <list>

int iPointNum = 0, drawingMode = 0;
int px = 0, py = 0;
std::list<std::pair<GLint, GLint> > pointList;
int winWidth = 400, winHeight = 300;

void Initial() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		if (pointList.size() > 0) {
			for (std::pair<GLint, GLint> p : pointList) {
				if (p.first != -1) glVertex2i(p.first, p.second);
				else glEnd(), glBegin(GL_LINE_STRIP);
			}
			glVertex2i(px, py);
		}
		glEnd();
	glutSwapBuffers();
}


void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		pointList.push_back(std::pair<GLint, GLint> {xMouse, winHeight - yMouse});
		glutPostRedisplay();
	}
}


void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	px = xMouse, py = winHeight - yMouse;
	glutPostRedisplay();
}

void ProcessMenu(int value) {
	if (value == 1) pointList.clear();
}

void Key(unsigned char key, int x, int y) {
	switch(key) {
		case 'p': pointList.push_back(std::pair<GLint, GLint> {px, py}); break;
		case 'c': pointList.push_back(std::pair<GLint, GLint> {(GLint)-1, (GLint)-1}); break;
		default: break;
	}
}

int main(int argc,char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
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














