#include <GL/glut.h>
#include <utility>
#include <list>
#include <cstdlib>
#include <cstdio>

typedef std::pair<int,int> p2i;
typedef std::pair<p2i,p2i> p4i;

int iPointNum = 0, clipMode = 0;
int winWidth = 400, winHeight = 300;
std::list<p4i> lines, clipped;
p2i startPoint, endPoint;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (auto line : lines)
		glVertex2i(line.first.first, line.first.second),
		glVertex2i(line.second.first, line.second.second);
	glEnd();
	if (iPointNum >= 1) {
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(2);
		glBegin(GL_LINES);
		for (auto line : clipped)
			glVertex2i(line.first.first, line.first.second),
			glVertex2i(line.second.first, line.second.second);
		glEnd();
		glLineWidth(1);
	}

	switch (clipMode) {
		case 0 : 
			glBegin(GL_LINE_STRIP);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(startPoint.first, startPoint.second);
			glVertex2i(startPoint.first, endPoint.second);
			glVertex2i(endPoint.first, endPoint.second);
			glVertex2i(endPoint.first, startPoint.second);
			glVertex2i(startPoint.first, startPoint.second);
			glEnd();
		break;

		case 1 :
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(0, startPoint.second);
			glVertex2i(winWidth, startPoint.second);
			glVertex2i(0, endPoint.second);
			glVertex2i(winWidth, endPoint.second);
			glEnd();
		break;

		case 2 :
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(startPoint.first, 0);
			glVertex2i(startPoint.first, winHeight);
			glVertex2i(endPoint.first, 0);
			glVertex2i(endPoint.first, winHeight);
			glEnd();
		break;

		default: break;
	}
	glutSwapBuffers();
}


void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1; startPoint = {xMouse, winHeight - yMouse};
		} else {
			iPointNum = 2; endPoint = {xMouse, winHeight - yMouse};
			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0; glutPostRedisplay();
	}
}

void gen_lines() {
	srand(2333);
	lines.clear();
	for (int i = 0; i < 20; i++) {
		lines.push_back(p4i{p2i{rand() % winWidth, rand() % winWidth}, 
					p2i{rand() % winHeight, rand() % winHeight}});
	}
}

int lb_clip_test(double p, double q, double &umax, double &umin) {
	double r = q / p;
	if (p < 0.0) {
		if (r > umin) return 0; else if (r > umax) umax = r;
	} else if (p > 0.0) {
		if (r < umax) return 0; else if (r < umin) umin = r;
	} else if (q < 0.0) return 0;
	return 1;
}

int lb_clip(p4i line) {
	int l, r, b, t;
	switch (clipMode) {
		case 0 : 
			l = std::min(startPoint.first, endPoint.first);
			r = std::max(startPoint.first, endPoint.first);
			b = std::min(startPoint.second, endPoint.second);
			t = std::max(startPoint.second, endPoint.second);
		break;

		case 1 :
			l = 0;
			r = winWidth;
			b = std::min(startPoint.second, endPoint.second);
			t = std::max(startPoint.second, endPoint.second);
		break;

		case 2 :
			l = std::min(startPoint.first, endPoint.first);
			r = std::max(startPoint.first, endPoint.first);
			b = 0;
			t = winHeight;
		break;

		default: break;
	}

	double x1, y1, x2, y2;
	x1 = line.first.first, y1 = line.first.second;
	x2 = line.second.first, y2 = line.second.second;
	double umax = 0, umin = 1,
	dx = x2 - x1, 
	dy = y2 - y1;
	if (lb_clip_test(-dx, x1 - l, umax, umin))
		if (lb_clip_test(dx, r - x1, umax, umin))
			if (lb_clip_test(-dy, y1 - b, umax, umin))
				if (lb_clip_test(dy, t - y1, umax, umin)) {
					x1 = line.first.first + umax * dx + 0.5;
					y1 = line.first.second + umax * dy + 0.5;
					x2 = line.first.first + umin * dx + 0.5;
					y2 = line.first.second + umin * dy + 0.5;
					clipped.push_back(p4i{p2i{x1, y1}, p2i{x2, y2}});
				}
	return 0;
}

void Update() {
	clipped.clear();
	for (auto line : lines)
		lb_clip(line);
	glutPostRedisplay();
}

void Initial() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void PassiveMouseMove (GLint xMouse, GLint yMouse) {
	if(iPointNum == 1) {
		endPoint = {xMouse, winHeight - yMouse};
		Update();
	}
}

void ProcessMenu(int value) {
	clipMode = value - 1;
	Update();
}

void ChangeSize(int w, int h) {
	winWidth = w; winHeight = h;
	gen_lines();
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

int main(int argc,char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Diagonal", 1);
	glutAddMenuEntry("Horizontal", 2);
	glutAddMenuEntry("Vertical", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}














