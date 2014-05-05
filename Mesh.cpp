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
	int i = q / numCols;
	int j = q % numCols;
	mat4 m = mat4(v[i][j], v[i][j + 1], v[i + 1][j + 1], v[i + 1][j]); 
	return m;
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
	numRows = newV.size() - 1;
	numCols = newV[0].size() - 1;
	numPolys = numRows * numCols;
	v.clear();
	// resize 2D vector
	v.resize(numRows + 1);
	for (int i = 0; i < numRows + 1; i++)
		v[i].resize(numCols + 1);
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
	v.resize(numRows + 1);
	original.resize(numRows + 1);
	for (int i = 0; i < numRows + 1; i++) {
		v[i].resize(numCols + 1);
		original[i].resize(numCols + 1);
	}
	// fill in with vertices
	for (int i = 0; i < numRows+1 ; i++) {
		for (int j = 0; j < numCols+1; j++) {
			double z = std::rand() % MAXHEIGHT;
			v[i][j] = vec4((double)i*rowWidth-((rowWidth*numCols)/2), 
							(double)j*colDepth-((colDepth*numRows)/2), 
							z, 0);
		}
	}
	v[0][0] = (vec4)v[0][0] * translation3D(vec3(-1, -1, 0));
	original = v;
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
	/* Implement Catmull-Clark subdivision on mesh */
	revertToOriginal(); // use original mesh, and subdivide it n times.
	while (n >= 1) {	// sub-divide n times
		int sub_numRows = 2 * numRows;
		int sub_numCols = 2 * numCols;
		std::vector<std::vector<vec4> > sub_Vert(sub_numRows + 1, std::vector<vec4>(sub_numCols + 1));
		/* for each new row(odd index), set center to Average of original face points */
		for (int i = 1; i <= sub_numRows; i = i + 2) {	// odd rows
			for (int j = 1; j <= sub_numCols; j = j + 2) {	// odd columns
				// get avg of 4 pts of quad, to get its center (face vertex)
				sub_Vert[i][j] = (v[(i - 1) / 2][(j - 1) / 2]		 // Top Left
								+ v[(i - 1) / 2][(j + 1) / 2]		 // Top Right
								+ v[(i + 1) / 2][(j - 1) / 2]		 // Bottom Left
								+ v[(i + 1) / 2][(j + 1) / 2]) / 4; // Bottom right, and avg
			}
		}
		/* for each edge, edge points = average of 2 neigbor face centers & 2 original points */
		// Horizontal edges
		for (int i = 0; i <= sub_numRows; i = i + 2) {	// even rows
			for (int j = 1; j <= sub_numCols; j = j + 2) {	// odd columns
				int n = 2;						// 2 edges, one to the left, one to the right, plus whatever face points that touch
				vec4 avgVertex = v[i / 2][(j - 1) / 2] + v[i / 2][(j + 1) / 2];
				if (i != 0) {					// if not top edge, look for face point above from the ones created
					avgVertex = avgVertex + sub_Vert[i - 1][j];
					n++;
				}
				if (i != sub_numRows) {			// if not bottom edge, look for face point below
					avgVertex = avgVertex + sub_Vert[i + 1][j];
					n++;
				}
				avgVertex = avgVertex / n;		// find average of n added vertices
				sub_Vert[i][j] = avgVertex;		// set edge point
			}
		}
		// Vertical edges
		for (int i = 1; i <= sub_numRows; i = i + 2) { // odd rows
			for (int j = 0; j <= sub_numCols; j = j + 2) { // even columns
				int n = 2;						// 2 edges, one above, one below, plus whatever face points that touch
				vec4 avgVertex = v[(i - 1) / 2][j / 2] + v[(i + 1) / 2][j / 2];
				if (j != 0) {					// if not left edge, look for face point to the left
					avgVertex = avgVertex + sub_Vert[i][j - 1];
					n++;
				}
				if (j != sub_numCols) {			// if not right edge, look for face point to the right
					avgVertex = avgVertex + sub_Vert[i][j + 1];
					n++;
				}
				avgVertex = avgVertex / n;		// find average of n added vertices
				sub_Vert[i][j] = avgVertex;		// set edge point
			}
		}
		/* for each original point P, average all adjacent face points
			than average all edge points touching P, and calculate new position of P
			// using formula at wikipedia //	*/
		for (int i = 0; i <= sub_numRows; i = i + 2) {	// even rows
			for (int j = 0; j <= sub_numCols; j = j + 2) { // even columns
				vec4 p = v[i / 2][j / 2];		// original point
				int nf = 0;						// face counter
				int ne = 0;						// edge counter
				vec4 f = vec4(0, 0, 0, 0);		// average of all face points created, touching P
				vec4 r = vec4(0, 0, 0, 0);		// average of all edge midpoints touching p
				if (i != 0 && j != 0) {					// can check upper left
					f = f + sub_Vert[i - 1][j - 1];
					nf++;
				}
				if (i != 0 && j != sub_numCols) {		// can check upper right
					f = f + sub_Vert[i - 1][j + 1];
					nf++;
				}
				if (i != sub_numRows && j != 0) {		// can check bottom left
					f = f + sub_Vert[i + 1][j - 1];
					nf++;
				}
				if (i != sub_numRows && j != sub_numCols) {	// can check bottom right
					f = f + sub_Vert[i + 1][j + 1];
					nf++;
				}
				if (i != 0) {							// can check up
					r = r + sub_Vert[i - 1][j];
					ne++;
				}
				if (i != sub_numRows) {					// can check down
					r = r + sub_Vert[i + 1][j];
					ne++;
				}
				if (j != 0) {							// can check left
					r = r + sub_Vert[i][j - 1];
					ne++;
				}
				if (j != sub_numCols) {					// can check right
					r = r + sub_Vert[i][j + 1];
					ne++;
				}
				f = f / nf;			// average faces
				r = r / ne;			// average edges
				int n = ne + nf;
				p = (f / n) + (2 * r / n) + ((p*(n - 3)) / n);
				sub_Vert[i][j] = p;
			}
		}
		setVertices(sub_Vert);		// assign the new vertices to Mesh
		n--;
	}
}

// revert back to original mesh
void Mesh::revertToOriginal() {
	setVertices(original);
}

// save current mesh as original
void Mesh::setOriginal() {
	original.resize(numRows + 1);
	for (int i = 0; i < numRows + 1; i++)
		original[i].resize(numCols + 1);
	original = v;
}