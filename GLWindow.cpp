#include "GLWindow.h"
#include "Display.h"
#include "algebra3.h"

GLWindow::GLWindow(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	c= new Camera(4, 0, 0);	// create a camera
}

void GLWindow::init(){	// initialize the required OpenGL transforms
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 10);		// experiment with these settings to see their effects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void GLWindow::draw(){
	if (!valid()){
		init();				// make sure the OpenGL settings are completed once before drawing
		valid(1);
	}
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	gluLookAt(c->getEye()[0], c->getEye()[1], c->getEye()[2],	// set the camera
			  0, 0, 0,
			  c->getUp()[0], c->getUp()[1], c->getUp()[2]);
	
	Fl_Group *g = this->parent();	// get a pointer to the FL display window
	Display *d = (Display*)(g);
	for (int i = 0; i < d->numPolys(); i++){
		//if (i == d->getSelected())
		//	glColor3f(1, 0, 0);
		//else 
		glColor3f(d->getRed(), d->getGreen(), d->getBlue());

		vec4 v1 = ((mat4)(d->getPoly(i)))[0];
		vec4 v2 = ((mat4)(d->getPoly(i)))[1];
		vec4 v3 = ((mat4)(d->getPoly(i)))[2];
		vec4 v4 = ((mat4)(d->getPoly(i)))[3];
		
		if (d->isWireFrame() != 0) {
			glBegin(GL_QUADS);
				if (v1[2] > 1)
					glColor3f(1, 1, 1);
				else
					glColor3f(d->getRed(), d->getGreen(), d->getBlue());
				glVertex3f(v1[0], v1[1], v1[2]);

				if (v2[2] > 1)
					glColor3f(1, 1, 1);
				else
					glColor3f(d->getRed(), d->getGreen(), d->getBlue());
				glVertex3f(v2[0], v2[1], v2[2]);

				if (v3[2] > 1)
					glColor3f(1, 1, 1);
				else
					glColor3f(d->getRed(), d->getGreen(), d->getBlue());
				glVertex3f(v3[0], v3[1], v3[2]);

				if (v4[2] > 1)
					glColor3f(1, 1, 1);
				else
					glColor3f(d->getRed(), d->getGreen(), d->getBlue());
				glVertex3f(v4[0], v4[1], v4[2]);
			glEnd();
		}

		glColor3f(1, 1, 1);			// outline the faces so that they are easier to see
		glBegin(GL_LINE_LOOP);
			glVertex3f(v1[0], v1[1], v1[2]);
			glVertex3f(v2[0], v2[1], v2[2]);
			glVertex3f(v3[0], v3[1], v3[2]);
			glVertex3f(v4[0], v4[1], v4[2]);
		glEnd();
	}
}

int GLWindow::handle(int event){		// handle keyboard and mouse events
	double start_x = 0, start_y = 0;
	if (event == FL_KEYUP){				// when the key is released, check for an event and handle it
		if (Fl::event_key() == 'a'){
			c->increasePhi(-7);
			redraw();
		}
		if (Fl::event_key() == 'd'){
			c->increasePhi(7);
			redraw();
		}
		if (Fl::event_key() == 'w'){
			c->increaseTheta(-7);
			redraw();
		}
		if (Fl::event_key() == 's'){
			c->increaseTheta(7);
			redraw();
		}
		if (Fl::event_key() == 'e'){
			c->increaseRad(-.5);					
			redraw();
		}
		if (Fl::event_key() == 'f'){
			c->increaseRad(.5);					
			redraw();
		}
	}
	////3D picking from given example
	//if (event == FL_PUSH) // in Fl_Gl_Window handle method 
	//{
	//	float x = Fl::event_x();
	//	float y = Fl::event_y();
	//	std::cout << "Someone clicked " << x << ", " << y << std::endl;
	//	// change to normalized device coordinates 
	//	//y = h() – y; ? ? ? ?
	//	x = x / this->w();
	//	y = y / this->h();

	//	// coordinate of eye 
	//	vec4 eye = vec4(c->getEye()[0], c->getEye()[1], c->getEye()[2], 0);
	//	// up vector 
	//	vec4 up = vec4(c->getUp()[0], c->getUp()[1], c->getUp()[2], 0);
	//	// get viewing vector 
	//	vec4 center = vec4(0, 0, 0, 0); // different if center moves 
	//	vec4 G = center - eye;
	//	// half viewing angles depend on perspective setup 
	//	float fi = 30.0 * 3.14159 / 180.0;
	//	float theda = 30.0 * 3.14159 / 180.0;
	//	vec4 A = G^up;
	//	vec4 B = A^G;
	//	vec4 M = eye + G;

	//	vec4 H = (A*(G.length()*tan(theda))) / A.length();
	//	vec4 V = (B*(G.length()*tan(fi))) / B.length();

	//	vec4 P = M + (2 * x - 1)*H + (2 * y - 1)*V;
	//	std::cout << "The point is " << P[0] << ", " << P[1] << ", " << P[2] << std::endl;

	//	// The ray is: where t goes from 0 to infinity 
	//	double t = 2;
	//	vec4 R = eye + t*(P - eye) / (P - eye).length();
	//}
	//if (event == FL_PUSH){
	//	if (Fl::event_button() == FL_RIGHT_MOUSE){
	//		std::cout << "Right Mouse Pushed" << std::endl;
	//		start_x = Fl::event_x();
	//		start_y = Fl::event_y();
	//		//while (Fl::event_state() == FL_DRAG){
	//		//	std::cout << "Right Mouse dragging" << std::endl;
	//		//	double move_x = Fl::event_x() - start_x;
	//		//	double move_y = Fl::event_y() - start_y;
	//		//	c->increasePhi(move_x);
	//		//	c->increaseTheta(move_y);
	//		//}
	//	}
	//}
	//if (event == FL_DRAG){
	//	std::cout << "Right Mouse dragging" << std::endl;
	//	//double move_x = Fl::event_x() - start_x;
	//	//double move_y = Fl::event_y() - start_y;
	//	//c->increasePhi(move_x);
	//	//c->increaseTheta(move_y);
	//	if (Fl::event_x() > 0){
	//		c->increasePhi(Fl::event_x());
	//		redraw();
	//	}
	//}
	return Fl_Gl_Window::handle(event);
}

Camera* GLWindow::getCamera() {
	return c;
}