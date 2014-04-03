#include "eController.h"
#include <iostream>

Controller::Controller(){	
	//create cube
	parser("sampleInput.txt", &faces);			// Will load a model from a file
	selected = 0;								// Start with the zero-ith face selected
	d = new Display(10, 10, 600, 600, this);	// Create a new display window
	d->show();									// Show the window
	d->select(selected);						// Let the browser know what was selected
	d->updateBrowser();							// Update the browser and OpenGL window
	d->updateDrawing();
}

Controller::~Controller(){};

const int Controller::numPolys(){							// Get the number of faces
	return faces.size();
}
const mat4 Controller::getPoly(int i){					// Get a certain face
	return faces[i]->getPoints();
}
const int Controller::getSelected(){						// Get which face has been selected
	return selected;
}
void Controller::select(int i){								// Set the selected face
	selected = i; d->updateDrawing();
}

void Controller::extrudeSelected(float depth){				// Do an extrusion
	int sel = getSelected();
	mat4 points = faces[sel]->getPoints();
	Face *f = faces[sel];
	faces.erase(faces.begin() + sel);
	vec4 v1New = depth * f->getNormal() + points.getCol(0);
	vec4 v2New = depth * f->getNormal() + points.getCol(1);
	vec4 v3New = depth * f->getNormal() + points.getCol(2);
	vec4 v4New = depth * f->getNormal() + points.getCol(3);
	faces.push_back(new Face(points.getCol(0), points.getCol(1), v2New, v1New));
	faces.push_back(new Face(points.getCol(1), points.getCol(2), v3New, v2New ));
	faces.push_back(new Face(points.getCol(2), points.getCol(3), v4New, v3New ));
	faces.push_back(new Face(points.getCol(3), points.getCol(0), v1New, v4New));
	faces.push_back(new Face(v1New, v2New, v3New, v4New));
	d->updateBrowser();
	d->updateDrawing();
	delete f;
}