#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include "face.h"
#include "algebra3.h"

vec4 parsePoint(std::string point){		// get the x, y, z values of a vertex
	vec4 output(3);
	std::stringstream pointStream(point);
	pointStream.ignore(1, ' ');		// ignore spaces in the stream
	pointStream >> output[0];
	pointStream >> output[1];
	pointStream >> output[2];
	output[3] = 0;
	//std::cout<<"OUTPUT:  "<<output[0]<<" "<<output[1]<<" "<<output[2]<<"\n";
	return output;
}

Face* parseLine(std::string line){			// parse a line of the file
	std::stringstream lineStream(line);		
	std::string point;
	std::vector<vec4> faceHolder(4);
	char delim = ' ';
	int counter = 0;
	while(delim != ';'){					// parse line until a ';' is found
		getline(lineStream, point, '>');
		lineStream >> delim;
		faceHolder[counter] = parsePoint(point);	// parse the vertex
		counter++;
	}
	assert(counter == 4);					// make sure we parsed a quad
	Face *face = new Face(faceHolder[0], faceHolder[1],faceHolder[2],faceHolder[3]);
	return face;
}


void parser(const char* file, std::vector<Face*> *faces){	// parse faces from a file line by line
	std::string line;
	std::ifstream input(file);	// create an input stream and open the file

	if (input.is_open()){						// make sure the file was opened successfully
		while(!input.eof()){					// while not end of file
			getline(input, line);				// get a line of the file and store it in a string	
			//std::cout<<"Parsing: "<< line << std::endl; 
			if (line != "")						// if the line isn't empty, parse it
				faces->push_back(parseLine(line));
		}
	}
	else {
		std::cout<<"Error Reading File."<<std::endl;
	}
	input.close();		// close the file
}
