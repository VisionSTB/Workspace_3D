#include "Display.h"
#include "eController.h"

Display::Display(int x, int y, int w, int h, Controller* c):Fl_Window(x, y, w, h, "Extrudor"){
		this->c = c;
		//browser = new Fl_Hold_Browser(0, 0, w/5, h/2);
		//browser->callback((void(*)(Fl_Widget*, void*))selectCB, (void*)c);
		win = new GLWindow(w/5, 0, 4*w/5, h);
		
		rowCounter = new Fl_Simple_Counter(0, 10, w / 5, 20, "Rows");
		rowCounter->callback((void(*)(Fl_Widget*, void*))rowCounterCB, (void*)c);
		rowCounter->value(c->getNumRows());
		rowCounter->step(1.0);
		rowCounter->range(1, 100);

		colCounter = new Fl_Simple_Counter(0, 50, w / 5, 20, "Columns");
		colCounter->callback((void(*)(Fl_Widget*, void*))colCounterCB, (void*)c);
		colCounter->value(c->getNumCols());
		colCounter->step(1.0);
		colCounter->range(1, 100);

		widthCounter = new Fl_Simple_Counter(0, 90, w / 5, 20, "Width");
		widthCounter->callback((void(*)(Fl_Widget*, void*))widthCounterCB, (void*)c);
		widthCounter->value(c->getWidth());
		widthCounter->range(0.1, 5.0);

		depthCounter = new Fl_Simple_Counter(0, 130, w / 5, 20, "Depth");
		depthCounter->callback((void(*)(Fl_Widget*, void*))depthCounterCB, (void*)c);
		depthCounter->value(c->getDepth());
		depthCounter->range(0.1, 5.0);

		newMeshB = new Fl_Button(0, 290, w / 5, 20, "New Mesh");
		newMeshB->callback((void(*)(Fl_Widget*, void*))newMeshCB, (void*)this);

		smoothB = new Fl_Button(0, 320, w / 5, 20, "Smooth Mesh");
		smoothB->callback((void(*)(Fl_Widget*, void*))smoothCB, (void*)c);

		rowVertexC = new Fl_Simple_Counter(0, 370, w / 10, 20, "Vertex Row");
		rowVertexC->callback((void(*)(Fl_Widget*, void*))vertexCB, (void*)this);
		rowVertexC->range(0, c->getNumRows()); //row zero is the 1st row
		rowVertexC->step(1);

		colVertexC = new Fl_Simple_Counter(w / 10, 370, w / 10, 20, "Vertex Column");
		colVertexC->callback((void(*)(Fl_Widget*, void*))vertexCB, (void*)this);
		colVertexC->range(0, c->getNumCols()); //column zero is the 1st column
		colVertexC->step(1);

		zValCounter = new Fl_Counter(0, 410, w / 5, 20, "Z");
		zValCounter->callback((void(*)(Fl_Widget*, void*))adjVertexCB, (void*)this);
		zValCounter->value(c->getZ(rowVertexC->value(), colVertexC->value()));

		pickColor = new Fl_Color_Chooser(0, 190, w / 5, 95, "new Mesh Color");
		pickColor->callback((void(*)(Fl_Widget*, void*))pickColorCB, (void*)this);
		pickColor->rgb(c->getRed(), c->getGreen(), c->getBlue());

		topViewB = new Fl_Button(0, h - 90, w / 10, 20, "Top View");
		topViewB->callback((void(*)(Fl_Widget*, void*))setViewCB, (void*)this);

		frontViewB = new Fl_Button(w / 10, h - 90, w / 10, 20, "Front View");
		frontViewB->callback((void(*)(Fl_Widget*, void*))setViewCB, (void*)this);

		slider = new Fl_Value_Slider(0, h-50, w/5, 20);
		slider->range(1, 10);
		slider->value(2);
		slider->type(FL_HORIZONTAL);
		
//		myButton = new Fl_Button(0, h-30, w/5, 20, "Extrude");
//		myButton->callback((void(*)(Fl_Widget*, void*))extrudeCB, (void*)c);
		
		wireB = new Fl_Button(0, h - 70, w / 5, 20, "Wireframe");
		wireB->callback((void(*)(Fl_Widget*, void*))wireCB, (void*)c);
		
		printB = new Fl_Button(0, h - 30, w / 5, 20, "Print");
		printB->callback((void(*)(Fl_Widget*, void*))printCB, (void*)c);
		
		this->end();
}

//void Display::updateBrowser(){
//	for (int i = browser->size(); i<c->numPolys(); i++){
//		browser->add("Face");
//	}
//}

const int Display::numPolys(){
	return c->numPolys();
}

mat4 Display::getPoly(int i){
	return c->getPoly(i);
}

const int Display::getSelected(){
	return c->getSelected();
}

const int Display::isWireFrame() {
	return c->isWireFrame();
}

const double Display::getRed() {
	return c->getRed();
}
const double Display::getGreen() {
	return c->getGreen();
}
const double Display::getBlue() {
	return c->getBlue();
}
//const float Display::getExtrude(){
//	return slider->value();
//}

void Display::rowCounterCB(Fl_Simple_Counter* w, Controller* c) {
	/* not using atm */
}

void Display::colCounterCB(Fl_Simple_Counter* w, Controller* c) {
	/* not using atm */
}

void Display::widthCounterCB(Fl_Simple_Counter* w, Controller* c) {
	/* not using atm */
}

void Display::depthCounterCB(Fl_Simple_Counter* w, Controller* c) {
	/* not using atm */
}

void Display::vertexCB(Fl_Simple_Counter* w, Display* d) {
	//get vertex values
	vec4 v = d->c->getVertex(d->rowVertexC->value(), d->colVertexC->value());
	//display values
	d->zValCounter->value(v[2]);
}

void Display::adjVertexCB(Fl_Counter* w, Display* d) {
	double z = d->zValCounter->value();	// get new z value from widget
	int i = d->rowVertexC->value();			// get row location for vertex
	int j = d->colVertexC->value();			// get column location for vertex
	vec4 v = d->c->getVertex(i, j);	//might change
	v[2] = z;
	d->c->setVertex(i, j, v);		//might change to adjust x,y, and z
}

void Display::newMeshCB(Fl_Button* w, Display* d) {
	/* construct a new mesh based off user input from the counters 
		and adjust vertex selectors to new range					*/
	int numCols = d->colCounter->value();
	int numRows = d->rowCounter->value();
	double rowWidth = d->widthCounter->value();
	double colDepth = d->depthCounter->value();
	double color[3] = { 1, 0, 0 };
	d->rowVertexC->range(0, numRows);
	d->colVertexC->range(0, numCols);
	d->zValCounter->value(d->c->getZ(d->rowVertexC->value(), d->colVertexC->value()));
	Mesh* m = new Mesh(numCols, numRows, rowWidth, colDepth, color);
	d->c->setMesh(m);
}

void Display::smoothCB(Fl_Button* w, Controller* c) {
	/* use catmul-clark sub-division */
}

void Display::pickColorCB(Fl_Color_Chooser* w, Display* d) {
	double rgb[3];
	rgb[0] = w->r(); rgb[1] = w->g(); rgb[2] = w->b();
	d->c->setColor(rgb);
	d->updateDrawing();
}

void Display::setViewCB(Fl_Button* w, Display* d) {
	/* toggle pre-set view point based off which */
	Camera* view = d->win->getCamera();
	if (w->label() == "Top View") {
		//starting view is top view
		std::cout << "Top View enabled" << std::endl;
		view->setTheta(0);
		d->updateDrawing();
	}
	else if (w->label() == "Front View") {
		std::cout << "Front View enabled" << std::endl;
		view->setTheta(90);
		d->updateDrawing();
	}
}

void Display::wireCB(Fl_Button* w, Controller* c) {
	c->toggleWireFrame();
}

void Display::printCB(Fl_Button* w, Controller* c) {
	c->printVertices();
}

//void Display::extrudeCB(Fl_Button* w, Controller* c){
//	c->extrudeSelected(((Display*)(w->parent()))->getExtrude());
//}

//void Display::selectCB(Fl_Hold_Browser* w, Controller* c){
//	c->select(w->value()-1);
//}