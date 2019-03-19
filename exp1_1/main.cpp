#include <GL/glut.h>

int iPointNum = 0, drawingMode = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
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
	if (iPointNum >= 1) {
		if (drawingMode == 0) {
			glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
			glEnd();
		} else {
			glRectf(x1, y1, x2, y2);
		}
		
	}
	glutSwapBuffers();
}


void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1; x1 = xMouse, y1 = winHeight - yMouse;
		} else {
			iPointNum = 2; x2 = xMouse, y2 = winHeight - yMouse;
			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0; glutPostRedisplay();
	}
}

void Key(unsigned char key, int x, int y) {
	switch(key) {
		case 'p': x1 = x, y1 = winHeight - y; iPointNum = 1; break;
		case 's':
			iPointNum = 2; x2 = x, y2 = winHeight - y;
			glutPostRedisplay(); break;
		default: break;
	}
}

void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	if(iPointNum == 1) {
		x2 = xMouse; y2 = winHeight - yMouse;
		glutPostRedisplay();
	}
}

void ProcessMenu(int value) {
	drawingMode = value - 1;
}

int main(int argc,char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Rectangle", 2);
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














