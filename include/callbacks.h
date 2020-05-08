#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdio.h>
#include "scene.h"


/* Scene */ 
Scene scene;

/* Camera */ 
Camera camera;

/* Call when need to display the graphical content */
void display();

/* Call after windows resizing */ 
void reshape(GLsizei width, GLsizei height);

/* Sets the Mouse callback for the current window */
void mouse(int button, int state, int x, int y);

/* Call after mouse wheel scroll */
void mouseWheel(int, int, int, int);

/* Call after normal key pressed */
void keyboard(unsigned char c, int x, int y);

/* Call after special key pressed */
void specialKeyboard(int key, int x, int y);

/* Sets the Motion callback for the current window */
void motion(int x, int y);

/* Call when there is no other event */ 
void idle();

/* Set values based on selected item */
void controls(int value);

/* Register GLUT callbacks */
void set_callbacks();

#endif 