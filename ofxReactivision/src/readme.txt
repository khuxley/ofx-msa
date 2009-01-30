TUIO C++ LIBRARY AND DEMO
-------------------------
Copyright (c) 2005-2008 Martin Kaltenbrunner <mkalten@iua.upf.edu>
Developed at the Music Technology Group, UPF, Barcelona

This software is part of reacTIVision, an open source fiducial
tracking framework based on computer vision. 

http://reactivision.sourceforge.net/

Demo Applications:
------------------
This package contains two demo applications which are able
to receive TUIO messages from the reacTIVision engine.

* TuioDump prints the TUIO events directly to the console
* TuioDemo graphically draws the objects' state on the screen

You can use these demo applications for debugging purposes, 
and using them as a starting point for the development of you own
C++ applications implementing the TUIO protocol. Please refer to
the source code of the both examples and the following section.

Pressing F1 will toggle FullScreen mode with the TuioDemo,
pressing ESC or closing the Window will end the application.
Hitting the V key will print the TUIO events to the console.

Keep in mind to make your graphics scalable for the varying
screen and window resolutions. A reasonable TUIO application
will run in fullscreen mode, although the windowed mode might
be useful for debugging purposes or working with the Simulator.

Application Programming Interface:
----------------------------------
First you  need to create an instance of TuioClient. This class 
is listening to TUIO messages on the specified port and generates
higher level messages based on the object events. The method start(true)
will start the TuioClient in a blocking mode, simply calling start()
will start the TuioClient in the background. Call stop() in
order to stop listening to incoming TUIO messages. 

Your application needs to implement the TuioListener interface,
and has to be added to the TuioClient in order to receive messages.

A TuioListener needs to implement the following methods:

* addTuioObject(TuioObject *tobj):
  this is called when an object becomes visible
* removeTuioObject(TuioObject *tobj):
  an object was removed from the table
* updateTuioObject(TuioObject *tobj):
  an object was moved on the table surface
* addTuioCursor(TuioCursor *tcur):
  this is called when a new cursor is detected
* removeTuioCursor(TuioCursor *tcur):
  a cursor was removed from the table
* updateTuioCursor(TuioCursor *tcur):
  a cursor was moving on the table surface
* refresh(long timestamp):
  this method is called after each bundle,
  use it to repaint your screen for example
  the timestamp is in milliseconds since the client was started

Typically you will need just the following code to start with:

  MyTuioListener listener;	     // implements a TuioListener
  TuioClient client(port);	     // creates the TuioClient
  client.addTuioListener(&listener); // registers the TuioListener
  client.start();		     // starts the TuioClient

Each object or cursor is identified with a  unique session ID, that is maintained
over its lifetime. Additionally each object carries fiducial ID that corresponds
to its attached fiducial marker number. The finger ID of the cursor object is always
a number in the range of all currently detected cursor blobs.

The TuioObject and TuioCursor references are updated automatically by the TuioClient
and are always referencing the same instance over the object lifetime.
All the TuioObject and TuioCursor attributes are encapsulated and can be
accessed with methods such as getX(), getY() and getAngle() and so on.
TuioObject and TuioCursor also have some additional convenience methods
for the calculation of distances and angles between objects. The getPath()
method returns a Vector of TuioPoint representing the movement path of the object.

Alternatively the TuioClient class contains some methods for the polling
of the current object and cursor state. There are methods which return
either a list or individual object and cursor objects. The TuioObject and
TuioCursor classes have been added as a container which also can be used
by external classes. 

* getTuioObjects() returns a Vector<TuioObject*> of all currently present TuioObjects
* getTuioCursors() returns a Vector<TuioObject*> of all currently present TuioCursors
* getTuioObject(long s_id) returns a TuioObject* or NULL depending on its presence
* getTuioCursor(long s_id) returns a TuioCursor* or NULL depending on its presence

Building the Examples:
----------------------
This packeage includes a Visual Studio .NET 2003 project and a
Linux Makefile for building the two example applications.
The Win32 project already includes the necessary libraries.
To build the GUI example for Linux make sure you have the SDL,
OpenGL and GLUT libraries and header installed on your system.


License:
--------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

References:
-----------
This application uses the oscpack OpenSound Control library.
For more information and the source code see:
http://www.audiomulch.com/~rossb/code/oscpack/
