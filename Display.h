#ifndef DISPLAY_H
#define DISPLAY_H
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Hold_Browser.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Value_Slider.H>
#include "GLWindow.h"
#include "algebra3.h"

class Controller;	// forward declaration

class Display: public Fl_Window{
private:
	Fl_Hold_Browser* browser;	// show a list of the faces to choose from
	Fl_Value_Slider* slider;	// set the extrusion value
	GLWindow* win;				// the OpenGL window
	Fl_Button* myButton;		// button to execute the extrusion
	Controller* c;				// pointer back to the controller
public:
	Display(int x, int y, int w, int h, Controller* c);				// constructor
	void updateBrowser();											// update the browser
	void select(int selected){browser->value(selected+1);}			// set the selection
	void updateDrawing(){win->redraw();}							// redraw the OpenGL window
	const int numPolys();											// get the number of faces
	mat4 getPoly(int i);									// get a face
	const int getSelected();										// get the index of the face selected
	const float getExtrude();										// get the length of the extraction

	static void extrudeCB(Fl_Button* w, Controller* d);
	static void selectCB(Fl_Hold_Browser* w, Controller* d);
};


#endif
