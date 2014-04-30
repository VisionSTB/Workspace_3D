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

void Mesh::sub_divide(int n) {
	/* sub-divide mesh n times */
	// make a new 2D vector to hold sub-divided mesh
	int sub_numRows = 2 * numRows;
	int sub_numCols = 2 * numCols;
	std::vector<std::vector<vec4> > subMesh(sub_numRows + 1,
						std::vector<vec4>(sub_numCols + 1));
	std::cout << "old mesh vertex count: " << v.size() << std::endl;
	std::cout << "new mesh vertex count: " << subMesh.size() << std::endl;
	for (int i = 0; i < sub_numRows + 1; i++) {
		if (i % 2 == 0) {	// original row
			for (int j = 0; j < sub_numCols + 1; j++) {
				if (i % 2 == 0) {	
					// assign original vertex
					subMesh[i][j] = v[i / 2][j / 2];
				}
				else {
					// assign new vertex between originals (avg)
					subMesh[i][j] = vec4((v[i][j / 2 + 1][0] + v[i][j / 2 - 1][0]) / 2, // average x
						(v[i][j / 2 + 1][1] + v[i][j / 2 - 1][1]) / 2,	// average y
						(v[i][j / 2 + 1][2] + v[i][j / 2 - 1][2]) / 2,	// average z
						0);
				}
			}
		}
		else {				// new row between originals
			for (int j = 0; j < sub_numCols + 1; j++) {
				if (i % 2 == 0) {	
					// assign vertex between original prev. row and next row
					subMesh[i][j] = vec4((v[i / 2 + 1][j / 2][0] + v[i / 2 - 1][j / 2][0]) / 2,	//average x
						(v[i / 2 + 1][j / 2][1] + v[i / 2 - 1][j / 2][1]) / 2,	//average y
						(v[i / 2 + 1][j / 2][2] + v[i / 2 - 1][j / 2][2]) / 2,	//average z
						0);
				}
				else {
					// get avg of 4 pts of quad, to get its center

				}
			}
		}
	}
}