#ifndef DISPLAY_H
#define DISPLAY_H
#include <Fl/Fl_Window.H>
//#include <Fl/Fl_Hold_Browser.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Value_Slider.H>
#include <FL/Fl_Simple_Counter.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Box.H>
#include "GLWindow.h"
#include "algebra3.h"

class Controller;	// forward declaration

class Display: public Fl_Window{
private:
	const int maxSD = 6;		// max number of sub-divisions
	Fl_Box* meshBox;			// box to display mesh things
	Fl_Simple_Counter* rowCounter; // counter to increase/decrease num of rows
	Fl_Simple_Counter* colCounter; // counter to increase/decrease num of columns
	Fl_Simple_Counter* widthCounter; // counter to increase/decrease row width
	Fl_Simple_Counter* depthCounter; // counter to increase/decrease column depth
	Fl_Button* newMeshB;			// button to build new mesh 
	Fl_Simple_Counter* smoothCounter; // counter to increase/decrease the number of sub-divisions
	Fl_Button* smoothB;			// button to smooth out mesh with subdivision
	Fl_Box* vertBox;			// box to display vertex things
	Fl_Simple_Counter* rowVertexC;	// counter to select a row for a vertex
	Fl_Simple_Counter* colVertexC;	// counter to select a vertex by column in the row
	Fl_Counter* zValCounter;	// counter to adjust the z value of a vertex
	Fl_Button* saveOriginalB;	// save current mesh as the new original
	Fl_Button* topViewB;		// button to view mesh from above
	Fl_Button* frontViewB;		// button to view mesh from in front
	//Fl_Hold_Browser* browser;	// show a list of the faces to choose from
	Fl_Color_Chooser* pickColor;// select a color for the new mesh
	GLWindow* win;				// the OpenGL window
	Fl_Button* wireB;			// button to display the wireframe on/off
	Fl_Button* printB;			// button to print mesh vertices
	Fl_Button* exitB;			// button to exit the program
	Controller* c;				// pointer back to the controller
public:
	Display(int x, int y, int w, int h, Controller* c);		// constructor
	~Display();												// deconstructor
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
	static void smoothCB(Fl_Button* w, Display* d);
	static void pickColorCB(Fl_Color_Chooser* w, Display* d);
	static void vertexCB(Fl_Simple_Counter* w, Display* d);
	static void adjVertexCB(Fl_Counter* w, Display* d);
	static void saveOriginalCB(Fl_Button* w, Display* d);
	static void setViewCB(Fl_Button* w, Display* d);
	static void wireCB(Fl_Button* w, Controller* c);
	static void printCB(Fl_Button* w, Controller* c);
	static void exitCB(Fl_Button* w, Controller* c);
	//static void selectCB(Fl_Hold_Browser* w, Controller* d);
};


#endif
