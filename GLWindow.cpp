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

		if (i == d->getSelected())
			glColor3f(1, 0, 0);
		else 
			glColor3f(0, 0, 1);

		vec4 v1 = ((mat4)(d->getPoly(i)))[0];
		vec4 v2 = ((mat4)(d->getPoly(i)))[1];
		vec4 v3 = ((mat4)(d->getPoly(i)))[2];
		vec4 v4 = ((mat4)(d->getPoly(i)))[3];
			
		glBegin(GL_QUADS);
			glVertex3f(v1[0], v1[1], v1[2]);
			glVertex3f(v2[0], v2[1], v2[2]);
			glVertex3f(v3[0], v3[1], v3[2]);
			glVertex3f(v4[0], v4[1], v4[2]);
		glEnd();

		glColor3f(1, 1, 1);			// outline the faces so that they are easier to see
		glBegin(GL_LINE_LOOP);
			glVertex3f(v1[0], v1[1], v1[2]);
			glVertex3f(v2[0], v2[1], v2[2]);
			glVertex3f(v3[0], v3[1], v3[2]);
			glVertex3f(v4[0], v4[1], v4[2]);
		glEnd();
	}
}

int GLWindow::handle(int event){		// handle keyboard events
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
	return Fl_Gl_Window::handle(event);
}