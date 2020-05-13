#include "callbacks.h"
#include "init.h"
#include <stdio.h>
/* Main function */
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	
    int window = glutCreateWindow("Animals");
    glutSetWindow(window);
	
	animation = 0;
	
	cat = 1;
	bee = 1;

	floor_texture = 1;
	sky_texture = 1;
	cat_texture = 1;
	bee_texture = 1;

	opacity = 0;

	show_info = 0;

	init_opengl();
	init_scene(&scene);
	init_camera(&camera);
	set_callbacks();
	
    glutMainLoop();

    return 0;
}




