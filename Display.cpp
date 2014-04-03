#include "Display.h"
#include "eController.h"

Display::Display(int x, int y, int w, int h, Controller* c):Fl_Window(x, y, w, h, "Extrudor"){
		this->c = c;
		browser = new Fl_Hold_Browser(0, 0, w/5, h-40);
		browser->callback((void(*)(Fl_Widget*, void*))selectCB, (void*)c);
		win = new GLWindow(w/5, 0, 4*w/5, h);
		slider = new Fl_Value_Slider(0, h-40, w/5, 20);
		slider->range(1, 10);
		slider->value(2);
		slider->type(FL_HORIZONTAL);
		myButton = new Fl_Button(0, h-20, w/5, 20, "Extrude");
		myButton->callback((void(*)(Fl_Widget*, void*))extrudeCB, (void*)c);
		this->end();
}

void Display::updateBrowser(){
	for (int i = browser->size(); i<c->numPolys(); i++){
		browser->add("Face");
	}
}

const int Display::numPolys(){
	return c->numPolys();
}

mat4 Display::getPoly(int i){
	return c->getPoly(i);
}

const int Display::getSelected(){
	return c->getSelected();
}

const float Display::getExtrude(){
	return slider->value();
}

void Display::extrudeCB(Fl_Button* w, Controller* c){
	c->extrudeSelected(((Display*)(w->parent()))->getExtrude());
}

void Display::selectCB(Fl_Hold_Browser* w, Controller* c){
	c->select(w->value()-1);
}