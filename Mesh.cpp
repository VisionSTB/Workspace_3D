#include "Mesh.h"

Mesh::Mesh() {
	/* Constructor: initialize a default 3 x 3 mesh 
		w/ width/depth of 2.0	*/
	wireframe = 1;								//default wireframe off				
	numCols = numRows = 4;
	rowWidth = colDepth = 0.5;
	numPolys = numCols * numRows;
	color[0] = 0; color[1] = 0; color[2] = 1;	//default color blue
	buildVertices();
}

Mesh::Mesh(int c, int r, double w, double d, double rgb[3]) {
	/* Constructor based on give parameters */
	wireframe = 1;
	numCols = c;
	numRows = r;
	rowWidth = w;
	colDepth = d;
	numPolys = numCols * numRows;
	color[0] = rgb[0]; color[1] = rgb[1]; color[2] = rgb[2];
	buildVertices();
}

Mesh::~Mesh() {
	v.clear();
}

const int Mesh::getWireFrame() {
	return wireframe;
}

const int Mesh::getNumCols() {
	return numCols;
}

const int Mesh::getNumRows() {
	return numRows;
}

const int Mesh::getNumPolys() {
	return numPolys;
}

const double Mesh::getRowWidth() {
	return rowWidth;
}

const double Mesh::getColDepth() {
	return colDepth;
}

const double Mesh::getRed() {
	return color[0];
}
const double Mesh::getGreen() {
	return color[1];
}
const double Mesh::getBlue() {
	return color[2];
}

const mat4 Mesh::getQuad(int q) {
	/* get the face starting at origin i,j
		faces are in ascending order from left to right, up to down */
	int i = q / numRows;
	int j = q % numCols;
	return mat4(v[i][j], v[i][j + 1], v[i + 1][j + 1], v[i + 1][j]); 
}

const vec4 Mesh::getVertex(int r, int c) {
	return v[r][c];
}

std::vector<std::vector<vec4>> Mesh::getVertices() {
	return v;
}

void Mesh::setWireFrame(int n) {
	wireframe = n;
}

void Mesh::setNumCols(int n) {
	numCols = n;
}

void Mesh::setNumRows(int n) {
	numRows = n;
}

void Mesh::setRowWidth(double n) {
	rowWidth = n;
}

void Mesh::setColDepth(double n) {
	colDepth = n;
}

void Mesh::setColor(double rgb[3]) {
	color[0] = rgb[0];
	color[1] = rgb[1];
	color[2] = rgb[2];
}

void Mesh::setVertex(int r, int c, vec4 vertex) {
	v[r][c] = vertex;
}

void Mesh::setVertices(std::vector<std::vector<vec4>> newV) {
	v = newV;
}

void Mesh::buildVertices() {
	/* construct 2D array based on number of columns/rows
		and based off of row width / column depth 
		*/
	double adjX = (rowWidth * numCols / 2);
	double adjY = (colDepth * numRows / 2);
	mat4 trans = translation3D(vec3(adjX, adjY, 0));
	// resize 2D vector
	v.resize(numRows+1);
	for (int i = 0; i < numRows+1; i++)
		v[i].resize(numCols+1);
	// fill in with vertices
	for (int i = 0; i < numRows+1 ; i++) {
		for (int j = 0; j < numCols+1; j++) {
			double z = std::rand() % maxHeight;
			v[i][j] = vec4((double)i*rowWidth-((rowWidth*numCols)/2), 
							(double)j*colDepth-((colDepth*numRows)/2), 
							z, 0);
		}
	}
	v[0][0] = (vec4)v[0][0] * translation3D(vec3(-1, -1, 0));
}

void Mesh::printVertices() {
	std::cout << "Mesh Vertices are... " << std::endl;
	for (int i = 0; i < numRows + 1; i++) {
		for (int j = 0; j < numCols + 1; j++) {
			std::cout << "v[" << i << "][" << j << "] : " ;
			v[i][j].print();
		}
	}
}