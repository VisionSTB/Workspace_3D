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

		depthCounter = new Fl_Simple_Counter(0, 130, w / 5, 20, "Depth");
		depthCounter->callback((void(*)(Fl_Widget*, void*))depthCounterCB, (void*)c);
		depthCounter->value(c->getDepth());

		newMeshB = new Fl_Button(0, 170, w / 5, 20, "New Mesh");
		newMeshB->callback((void(*)(Fl_Widget*, void*))newMeshCB, (void*)this);

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

}

void Display::colCounterCB(Fl_Simple_Counter* w, Controller* c) {

}

void Display::widthCounterCB(Fl_Simple_Counter* w, Controller* c) {

}

void Display::depthCounterCB(Fl_Simple_Counter* w, Controller* c) {

}

void Display::newMeshCB(Fl_Button* w, Display* d) {
	/* construct a new mesh based off user input from the counters */
	int numCols = d->colCounter->value();
	int numRows = d->rowCounter->value();
	double rowWidth = d->widthCounter->value();
	double colDepth = d->depthCounter->value();
	double color[3] = { 1, 0, 0 };
	Mesh* m = new Mesh(numCols, numRows, rowWidth, colDepth, color);
	d->c->setMesh(m);
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