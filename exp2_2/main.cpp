//#include <bits/stdc++.h>
#include <GL/glut.h>
#include <list>

int iPointNum = 0;
int px = 0, py = 0;
std::list<std::pair<GLint, GLint> > pointList;
std::pair<GLint, GLint> startPoint;
std::pair<GLint, GLint> endPoint;
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
	glBegin(GL_POINTS);
	if (pointList.size() > 0)
		for (std::pair<GLint, GLint> p : pointList)
			glVertex2i(p.first, p.second);
	glEnd();
	glutSwapBuffers();
}


void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (!iPointNum)
			startPoint = std::pair<GLint, GLint> {xMouse, winHeight - yMouse},
			iPointNum = 1;
		else
			endPoint = std::pair<GLint, GLint> {xMouse, winHeight - yMouse},
			iPointNum = 0;
		glutPostRedisplay();
	}
}

void GenerateCircle() {
	int r = std::max(abs((endPoint.first - startPoint.first) / 2), abs((endPoint.second - startPoint.second ) / 2));
	std::pair<GLint, GLint> center = std::pair<GLint, GLint> {
		startPoint.first + (endPoint.first - startPoint.first > 0 ? 1 : -1)  * r,
		startPoint.second + (endPoint.second - startPoint.second > 0 ? 1 : -1) * r
	};
	int x = 0, y = r, d = 1 - r;
	std::list<std::pair<GLint, GLint> > circle;
	while (x <= y) {
		circle.push_back(std::pair<GLint, GLint> {x, y});
		if (d >= 0)
			d += 2 * (x - y) + 5, y--;
		else
			d += 2 * x + 3;
		x++;
	}

	for (std::pair<GLint, GLint> p : circle)
		pointList.push_back(std::pair<GLint, GLint> {p.first + center.first, p.second + center.second}),
		pointList.push_back(std::pair<GLint, GLint> {p.first + center.first, center.second - p.second}),
		pointList.push_back(std::pair<GLint, GLint> {center.first - p.first, p.second + center.second}),
		pointList.push_back(std::pair<GLint, GLint> {center.first - p.first, center.second - p.second}),
		pointList.push_back(std::pair<GLint, GLint> {p.second + center.first, p.first + center.second}),
		pointList.push_back(std::pair<GLint, GLint> {center.first - p.second, p.first + center.second}),
		pointList.push_back(std::pair<GLint, GLint> {p.second + center.first, center.second - p.first}),
		pointList.push_back(std::pair<GLint, GLint> {center.first - p.second, center.second - p.first});
}


void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	if (iPointNum)
		endPoint = std::pair<GLint, GLint> {xMouse, winHeight - yMouse},
		pointList.clear(), GenerateCircle();
	glutPostRedisplay();
}

void ProcessMenu(int value) {
	if (value == 1) pointList.clear();
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
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}














