/* 
	Mesh.h
	Mesh will store the vertices(vec4's) in a 2D vector.  There will be a
	default set of vertices, but the user can change the number of columns
	and rows.  The user can also change the width of each row.  The 
	vertices will be used to draw the faces in a mesh 

	Use algebra3 to store xyz coordinates as vec4 objects
*/

#include "algebra3.h"
#include <vector>

class Mesh {
	private:
		int wireframe;			// toggle wireframe = 1
		int numCols;
		int numRows;
		int numPolys;			// number of faces
		double rowWidth;		// width of each row
		double colDepth;		// depth of each column
		double color[3];		// rgb color
		std::vector<std::vector<vec4> > v;  /* vector of vectors, sub-vectors 
											  hold vertices for a row */
	public:
		//	constructors   ////////
		Mesh();													// default a mesh
		Mesh(int c, int r, double w, double d, double rgb[3]);	//constructor with parameters for mesh
		~Mesh();												// deconstructor
		///////////////////////////
		// Getters and Setters ////
		const int getWireFrame();					// return wireframe status
		const int getNumCols();
		const int getNumRows();
		const int getNumPolys();
		const double getRowWidth();
		const double getColDepth();				
		const double getRed();						// return red value
		const double getGreen();					// return green value
		const double getBlue();						// return blue value
		const mat4 getQuad(int q);					// get a Quad from vertices
		std::vector<std::vector<vec4>> getVertices();
		
		void setWireFrame(int n);					// toggle wireframe status
		void setNumCols(int n);						// set number of columns
		void setNumRows(int n);						// set number of rows
		void setRowWidth(double n);					// set width of each row
		void setColDepth(double n);					// set depth of each column
		void setColor(double rgb[3]);				// set color of the mesh
		void setVertices(std::vector<std::vector<vec4>> newV);
		///////////////////////////
		// functions //////////////
		///////////////////////////
		void buildVertices();						// construct vertice based on fields
		void printVertices();

};