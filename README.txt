Simple FLTK Application Template
--------------------------------
  Version  1.02 
  by Fabien COSTANTINI

What is it ?
------------
This template will allows you to start and compile a new FLTK App in less than 1 minute with xcode. 
It will allow you to compile fluid (.fl) files automatically with proper dependencies and preconfigured custom builds.
It will create a simple main FLTK window as the one you get in the the fluid wizard but encapsulated in a separated UserInterface class and instanciated automatically in the main() function.

You can also use this template to port your existing projects easily.

How to USE
----------

1. Copy the uncompressed archive main folder to :
  ~/Library/Application Support/Apple/Developer Tools/Project Templates/Application,
	(if some sub-directories do not exist : create them).
2. copy the flc bash script file located at the root of the distribution to a directory in your path 
	(i.e: /usr/bin)    and make sure it has the +x (executable) flag
3. Open XCode, select New Project and in the Application thumbnail, select Simple FLTK App
4. Compile, Test, Add your own code and enjoy !

If you plan to use OpenGL or the image libs , just add them in the Target Build config where you 'll already find the fltk static lib in the LD_OTHER_FLAGS variable.

Important Note:
---------------
You MUST install the fltk libs and headersin a path that the compiler can find.
 (i.e: in /usr/local/lib and /usr/local/include) 

It is a good idea to install the fltk distrib as follows:

In a terminal window, in the root fltk dir; type the 3 following commands: 
	./configure
	make
	sudo make install

This will make and install fltk libs and include to /usr/local 

		-------------------------------------


Disclaimer: This fltk application template is supplied to you by F. Costantini on an "AS IS" basis.
	USE IT AT YOUR OWN RISK. 
	
YOU CAN USE, MODIFY AND DISTRIBUTE THIS TEMPLATE AS YOU NEED
    provided that you keep the Copyright info in the distribution.

For more information on the Fast Light Toolkit (Copyright Bill Spitzak and others), 
please refer to this link : wwww.fltk.org

