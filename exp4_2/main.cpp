//#include <bits/stdc++.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include <list>
#include <map>

int iPointNum = 0, ploygonMode = 0;
int px = 0, py = 0;
std::list<std::pair<GLint, GLint> > pointList;
std::pair<GLint, GLint> startPoint;
std::pair<GLint, GLint> endPoint;
int winWidth = 400, winHeight = 300;
char mask[32][32];
int maskSize = 32;

void Initial() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	memset(mask, 0, sizeof(mask));
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++)
			mask[i][j] = ((i % maskSize) ^ (j % maskSize)) < (maskSize >> 1);
}

void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

std::map<int, int> lp, rp;
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	lp.clear(), rp.clear();
	if (pointList.size() > 0)
		for (std::pair<GLint, GLint> p : pointList) 
			glVertex2i(p.first, p.second),
			lp[p.second] = lp.count(p.second) ? std::min(lp[p.second] == 0 ? 0x3fffffff : lp[p.second], p.first) : p.first,
			rp[p.second] = lp.count(p.second) ? std::max(rp[p.second], p.first) : p.first;
	glEnd();
	glBegin(GL_POINTS);
	if (!ploygonMode) {
		for (auto k : lp)
			for (int i = k.second; i < rp[k.first]; i++)
				if (mask[i % 32][k.first % 32]) glVertex2i(i, k.first);
	}
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

void GenerateEclipse() {
	long long a = abs((endPoint.first - startPoint.first) / 2), b = abs((endPoint.second - startPoint.second ) / 2);
	std::pair<GLint, GLint> center = std::pair<GLint, GLint> {
		startPoint.first + (endPoint.first - startPoint.first) / 2,
		startPoint.second + (endPoint.second - startPoint.second ) / 2
	};
	long double d; long long x = 0, y = b;

	d = b * b + a * a * (y - 0.5);
	while (b * b * (x + 1) < a * a * (y - 0.5)) {
		if (d <= 0)
			d += b * b * (2*x+3), x++;
		else
			d += b * b * (2*x+3) + a * a * (-2 * y + 2), x++, y--;
		pointList.push_back(std::pair<GLint, GLint>{center.first + x, center.second + y});
		pointList.push_back(std::pair<GLint, GLint>{center.first + x, center.second - y});
		pointList.push_back(std::pair<GLint, GLint>{center.first - x, center.second + y});
		pointList.push_back(std::pair<GLint, GLint>{center.first - x, center.second - y});
	}

	d = b * b * (x+0.5)*(x+0.5)+a*a*(y-1) * (y-1)-a*a*b*b;
	while (y > 0) {
		if (d <= 0)
			d += b * b * (2*x+2)+a * a * (-2 * y + 3), x++, y--;
		else
			d += a * a * (-2 * y + 3), y--;
		pointList.push_back(std::pair<GLint, GLint>{center.first + x, center.second + y});
		pointList.push_back(std::pair<GLint, GLint>{center.first + x, center.second - y});
		pointList.push_back(std::pair<GLint, GLint>{center.first - x, center.second + y});
		pointList.push_back(std::pair<GLint, GLint>{center.first - x, center.second - y});
	}
}


void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	if (iPointNum)
		endPoint = std::pair<GLint, GLint> {xMouse, winHeight - yMouse},
		pointList.clear(), GenerateEclipse();
	glutPostRedisplay();
}

void ProcessMenu(int value) {
	ploygonMode = value;
}

int main(int argc,char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Mask", 0);
	glutAddMenuEntry("NoMask", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}
