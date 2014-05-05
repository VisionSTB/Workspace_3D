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

Controller::~Controller(){
	delete(m);
	delete(d);
	m = NULL;
	d = NULL;
}

const int Controller::isWireFrame() {			// is the mesh in wireframe mode?
	return m->getWireFrame();
}

const double Controller::getRate() {
	return rate;
}

const int Controller::numPolys(){				// Get the number of faces
	return m->getNumPolys();
}

const mat4 Controller::getPoly(int i){			// Get a certain face
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
	delete(m);
	m = mesh;
	std::cout << "new mesh" << std::endl;
	d->updateDrawing();
}

void Controller::setOriginal() {
	m->setOriginal();
}

void Controller::select(int i){								// Set the selected face
	selected = i; d->updateDrawing();
}

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

void Controller::smoothMesh(int n) {
	m->sub_divide(n);
	d->updateDrawing();
}
