#ifndef DISPLAY_H
#define DISPLAY_H
#include <Fl/Fl_Window.H>
//#include <Fl/Fl_Hold_Browser.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Value_Slider.H>
#include <FL/Fl_Simple_Counter.H>
#include <FL/Fl_Color_Chooser.H>
#include "GLWindow.h"
#include "algebra3.h"

class Controller;	// forward declaration

class Display: public Fl_Window{
private:
	Fl_Simple_Counter* rowCounter; // counter to increase/decrease num of rows
	Fl_Simple_Counter* colCounter; // counter to increase/decrease num of columns
	Fl_Simple_Counter* widthCounter; // counter to increase/decrease row width
	Fl_Simple_Counter* depthCounter; // counter to increase/decrease column depth
	Fl_Button* newMeshB;			// button to build new mesh 
	Fl_Button* smoothB;			// button to smooth out mesh with subdivision
	Fl_Button* topViewB;		// button to view mesh from above
	Fl_Button* frontViewB;		// button to view mesh from in front
	//Fl_Hold_Browser* browser;	// show a list of the faces to choose from
	Fl_Color_Chooser* pickColor;// select a color for the new mesh
	Fl_Value_Slider* slider;	// set the extrusion value
	GLWindow* win;				// the OpenGL window
//	Fl_Button* myButton;		// button to execute the extrusion
	Fl_Button* wireB;			// button to display the wireframe on/off
	Fl_Button* printB;			// button to print mesh vertices
	Controller* c;				// pointer back to the controller
public:
	Display(int x, int y, int w, int h, Controller* c);		// constructor
	//void updateBrowser();									// update the browser
	//void select(int selected){browser->value(selected+1);}// set the selection
	void updateDrawing(){win->redraw();}					// redraw the OpenGL window
	const int numPolys();									// get the number of faces
	mat4 getPoly(int i);									// get a face
	const int getSelected();								// get the index of the face selected
	const int isWireFrame();								// is the mesh in wireframe mode?
	const double getRed();
	const double getGreen();
	const double getBlue();
	//	const float getExtrude();							// get the length of the extraction

	static void rowCounterCB(Fl_Simple_Counter* w, Controller* d);
	static void colCounterCB(Fl_Simple_Counter* w, Controller* d);
	static void widthCounterCB(Fl_Simple_Counter* w, Controller* d);
	static void depthCounterCB(Fl_Simple_Counter* w, Controller* d);
	static void newMeshCB(Fl_Button* w, Display* d);
	static void smoothCB(Fl_Button* w, Controller* c);
	static void pickColorCB(Fl_Color_Chooser* w, Display* d);
	static void setViewCB(Fl_Button* w, Display* d);
	static void wireCB(Fl_Button* w, Controller* d);
	static void printCB(Fl_Button* w, Controller* d);
//	static void extrudeCB(Fl_Button* w, Controller* d);
	//static void selectCB(Fl_Hold_Browser* w, Controller* d);
};


#endif
