#include <vector>
#include <iostream>
#include "face.h"
#include "Display.h"
//#include "algebra3.h"
#include "Mesh.h"

void parser(const char* file, std::vector<Face*> *faces); // A function for loading faces from a file

class Controller{
	private:
		double rate = 0.5;
		double rotation = 10.0;
		vec3 axis = vec3(0, rate, 0);
		//std::vector<Face*> faces;	// Store all of the faces/polygons in the scene
		Mesh* m;					// a pointer to the mesh, which stores vertices
		int selected;				// Which face is currently selected
		Display* d;					// A pointer to the display mechanisms
	public:
		Controller(); 
		~Controller();

		const int isWireFrame();			// is the mesh in wireframe mode?
		const double getRate();				// Get the rate of rotation
		const int numPolys();				// Get the number of faces
		const mat4 getPoly(int i);			// Get a certain face
		const int getNumRows();				// Get the number of Rows
		const int getNumCols();				// Get the number of Columns
		const double getWidth();			// Get width of rows
		const double getDepth();			// Get depth of columns
		const double getRed();
		const double getGreen();
		const double getBlue();
		const double getZ(int r, int c);	// get z value of vertex at given row and col
		const vec4 getVertex(int r, int c);	// get vertex at r,c
		void setColor(double rgb[3]);
		void toggleWireFrame();				// toggle wireframe mode on/off
		void setPoly(mat4 m);				// set a face with new/edited vertices
		void setMesh(Mesh* mesh);			// set a new mesh
		void setVertex(int r, int c, vec4 v); // set a new vertex at row r and col c
		const int getSelected();			// Get which face has been selected
		void select(int i);					// Set the selected face
//		void extrudeSelected(float depth);	// Perform an extrusion
		void printVertices();				// print vertices of the mesh
		void smoothMesh(int n);				// smooth mesh with sub-division


		//void cb_startb(void) { Fl::add_timeout(0.5, rotatingCB); }
		void Controller::rotate_cube();		// rotate cube

		static void callback(void* data);	// Callback to rotate cube

};