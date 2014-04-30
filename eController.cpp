#include "eController.h"
#include <iostream>

Controller::Controller(){	
	//create cube
	//parser("sampleInput.txt", &faces);			// Will load a model from a file
	m = new Mesh();								// default a mesh
	selected = 0;								// Start with the zero-ith face selected
	d = new Display(10, 10, 800, 800, this);	// Create a new display window
	d->show();									// Show the window
	//d->select(selected);						// Let the browser know what was selected
	//d->updateBrowser();						// Update the browser and OpenGL window
	d->updateDrawing();
	//Fl::add_timeout(rate, callback, this);   // callback to rotate cube
}

Controller::~Controller(){};

const int Controller::isWireFrame() {			// is the mesh in wireframe mode?
	return m->getWireFrame();
}

const double Controller::getRate() {
	return rate;
}

const int Controller::numPolys(){				// Get the number of faces
	//return faces.size();
	return m->getNumPolys();
}

const mat4 Controller::getPoly(int i){			// Get a certain face
	//return faces[i]->getPoints();
	return m->getQuad(i);
}

const int Controller::getNumRows() {
	return m->getNumRows();
}

const int Controller::getNumCols() {
	return m->getNumCols();
}

const double Controller::getWidth() {
	return m->getRowWidth();
}

const double Controller::getDepth() {
	return m->getColDepth();
}

const double Controller::getRed() {
	return m->getRed();
}

const double Controller::getGreen() {
	return m->getGreen();
}

const double Controller::getBlue() {
	return m->getBlue();
}

const double Controller::getZ(int r, int c) {
	return ((vec4)m->getVertex(r, c))[2];
}

const vec4 Controller::getVertex(int r, int c) {
	return m->getVertex(r, c);
}

void Controller::setColor(double rgb[3]) {
	m->setColor(rgb);
}

void Controller::setVertex(int r, int c, vec4 v) {
	m->setVertex(r, c, v);
	d->updateDrawing();
}

const int Controller::getSelected(){			// Get which face has been selected
	return selected;
}

void Controller::setMesh(Mesh* mesh) {
	free(m);
	m = mesh;
	std::cout << "new mesh" << std::endl;
	d->updateDrawing();
}

void Controller::select(int i){								// Set the selected face
	selected = i; d->updateDrawing();
}

//void Controller::extrudeSelected(float depth){				// Do an extrusion
//	int sel = getSelected();
//	mat4 points = faces[sel]->getPoints();
//	Face *f = faces[sel];
//	faces.erase(faces.begin() + sel);
//	vec4 v1New = depth * f->getNormal() + points.getCol(0);
//	vec4 v2New = depth * f->getNormal() + points.getCol(1);
//	vec4 v3New = depth * f->getNormal() + points.getCol(2);
//	vec4 v4New = depth * f->getNormal() + points.getCol(3);
//	faces.push_back(new Face(points.getCol(0), points.getCol(1), v2New, v1New));
//	faces.push_back(new Face(points.getCol(1), points.getCol(2), v3New, v2New ));
//	faces.push_back(new Face(points.getCol(2), points.getCol(3), v4New, v3New ));
//	faces.push_back(new Face(points.getCol(3), points.getCol(0), v1New, v4New));
//	faces.push_back(new Face(v1New, v2New, v3New, v4New));
//	d->updateBrowser();
//	d->updateDrawing();
//	delete f;
//}

void Controller::printVertices() {
	m->printVertices();
}

void Controller::toggleWireFrame() {
	if (isWireFrame() != 0) {
		// wireframe is on, toggle off
		m->setWireFrame(0);
	}
	else {
		// wireframe is off, toggle on
		m->setWireFrame(1);
	}
	d->updateDrawing();
}

//void Controller::rotate_cube()
//{
//	Controller* control = this;
//	for (int i = 0; i < control->numPolys(); i++)
//	{
//		double r = control->rotation;
//		mat4 rotated = (mat4)control->faces[i]->getPoints() * rotation3D(axis, r);
//		control->faces[i]->setPoints(rotated);
//	}
//	control->d->updateDrawing();
//}
//
//void Controller::callback(void* data)
//{
//	Controller* control = (Controller*)data;  //expecting Controller type
//	control->rotate_cube();
//	Fl::repeat_timeout(control->getRate(), callback, data);
//}