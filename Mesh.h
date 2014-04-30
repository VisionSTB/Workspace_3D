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
		int numCols;			// number of columns in terms of faces
		int numRows;			// number of rows in terms of faces
		int numPolys;			// number of faces
		double rowWidth;		// width of each row
		double colDepth;		// depth of each column
		int maxHeight = 3;	// maximun z value for height to the mesh
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
		const vec4 getVertex(int r, int c);			// get a vertex
		std::vector<std::vector<vec4>> getVertices();
		
		void setWireFrame(int n);					// toggle wireframe status
		void setNumCols(int n);						// set number of columns
		void setNumRows(int n);						// set number of rows
		void setRowWidth(double n);					// set width of each row
		void setColDepth(double n);					// set depth of each column
		void setColor(double rgb[3]);				// set color of the mesh
		void setVertex(int r, int c, vec4 vertex);	// change a vertex
		void setVertices(std::vector<std::vector<vec4>> newV);
		///////////////////////////
		// Other functions //////////////
		///////////////////////////
		void buildVertices();						// construct vertice based on fields
		void printVertices();						// print each vertice in the mesh
		void sub_divide(int n);						// sub-divide n times

};