#include <math.h>
#include "algebra3.h"
#include <iostream>

// A class for storing camera transforms
class Camera{
	private:
		mat4 rot;			// Current rotation matrix 
		vec4 up;			// Current up vector
		vec4 eye;			// Current eye/camera position
	public:
		Camera(float r, float phi, float theta); 
		void increasePhi(float inc);		// increase the phi angle. Note a negative value will decrease it. 
		void increaseTheta(float inc);		// increase the theta angle
		void increaseRad(float inc);		// increase the radius
		vec4 getEye();		// get the current eye position
		vec4 getUp();		// get the current up vector
		void setPhi(float inc);				// set the phi angle. use for default camera views
		void setTheta(float inc);			// set the theta angle.
		void setRad(float inc);
};