#include <vector>
#include <iostream>
#include "face.h"
#include "Display.h"
#include "algebra3.h"

void parser(const char* file, std::vector<Face*> *faces); // A function for loading faces from a file

class Controller{
	private:
		std::vector<Face*> faces;	// Store all of the faces/polygons in the scene
		int selected;				// Which face is currently selected
		Display* d;					// A pointer to the display mechanisms
	public:
		Controller(); 
		~Controller();

		const int numPolys();				// Get the number of faces
		const mat4 getPoly(int i);			// Get a certain face
		const int getSelected();			// Get which face has been selected
		void select(int i);					// Set the selected face
		void extrudeSelected(float depth);	// Perform an extrusion
};