Brandon Shea
CS351 Final Project
May 04, 2014

**** mini-modeling program with Catmull-Clark sub-division ****

The program creates a visualization of the current mesh object.  The vertices for the mesh
are stored in a Mesh class where they can be accessed and adjusted.  The attributes of the mesh
and accessed through the controller class which acts as the medium between the display class
and the mesh class.  The display creates and orientes all the widgets that control the program.  The glWindow takes the vertices and attributes of the Mesh class, and draws them on screen.
Currently, each mesh is drawn with Quads.


When the program opens, it will create and display a random mesh.  The user can set the number
of columns and rows, set their depth and width respectively, and create a new mesh based off
those settings.  The color can also be changes in real time.  The user can select the number of
sub-divisions, and press the 'Smooth this Mesh' button to use the Catmull-Clark sub-division
formula to smooth the mesh n number of times.  Each vertex can be selected by choosing the row
number and column number.  You can than adjust the z-value of that vertex.  To keep your changes
to the vertices, press the 'update vertex changes button'. Keep in mind, this will also save the
number of times it has been sub-divided.  If you do not update after changing vertices, smoothing the mesh will not consider your changes.  You can enable top and front views, as well as enable wireframe mode.  Print will display all the vertex values of the mesh in the console window.

Side-Note:
I wanted to challenge myself with the Catmull-Clark formula.  It is something I wanted badly to accomplish since Pixar uses it so I'm very happy that I was able to get this program to work.

Known Bugs:

1. Random isn't so random. Always seems to start with the same mesh.... Even though I set it to build a random mesh.

2. Don't Smooth too much. As expected, too much smoothing will take decades, so it is currently limited to 6 sub-divisions.

3. Exit button cuts off.  When you first open the program, the exit button is only half showing, but if you move the window, the rest appears.