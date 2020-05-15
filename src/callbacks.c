#include "callbacks.h"
#include "al.h"
#include "alut.h"
#include "alc.h"
//#include "efx.h"
//#include "EFX-Util.h"
//#include "efx-creative.h"
//#include "xram.h"


#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0


struct
{
    int x;
    int y;
} mouse_position;

void print_info()
{
    glDisable(GL_LIGHTING);

    int c;
    FILE* file;

    file = fopen("info.txt", "r");

    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(0.2, 0.2, 0.2);
    glRasterPos2f(0.0f, -5.0f);

    if (file) 
    {
        float z = 17.0f;
        while ((c = getc(file)) != EOF)
        {
            if (c == '\n')
            {   
                glRasterPos3f(-4.0f, -15.0f, z);
                z -= 0.4f;
            }

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        fclose(file);
    }
    glPopAttrib();

    glEnable(GL_LIGHTING);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    
    set_view(&camera);
    if (show_info)
    {
        print_info();
    }
    draw_scene(&scene);
    
    glPopMatrix();
    

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	//printf("Window size: %d x %d\n", width, height);

	glViewport (0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
        move_camera_forward(&camera, 1.0);
    }
    else
    {
       move_camera_backward(&camera, 1.0);
    }

    return;
}

void keyboard(unsigned char c, int x, int y)
{
    if (c == 27)
    {
        exit(0); /* ESC-EXIT */
    }

    if (c == 'w')
    {
        move_camera_forward(&camera, 1.0); /* W */
    }

    if (c == 's')
    {
        move_camera_backward(&camera, 1.0); /* S */
    }

    if (c == 'a')
    {
        step_camera_left(&camera, 1.0); /* A */
    }

    if (c == 'd')
    {
        step_camera_right(&camera, 1.0); /* D */
    }

    if (c == 'm')
    {
        set_lighting(0.2f);
    }

    if (c == 'n')
    {
        set_lighting(-0.2f);
    }

    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_F1)
    {
        show_info = 1 - show_info;
        display();
    }

    if (key == GLUT_KEY_DOWN)
    {
        step_camera_down(&camera, 1.0); /* DOWN */
    }

    if (key == GLUT_KEY_UP)
    {
        step_camera_up(&camera, 1.0); /* UP */
    }

    if (key == GLUT_KEY_RIGHT)
    {
        step_camera_right(&camera, 1.0); /* RIGHT */
    }

    if (key == GLUT_KEY_LEFT)
    {
        step_camera_left(&camera, 1.0); /* LEFT */
    }

    glutPostRedisplay();
}

void motion(int x, int y)
{
    rotate_camera(&camera, (mouse_position.x - x), (mouse_position.y - y));

    //print_camera_info(&camera);

    mouse_position.x = x;
    mouse_position.y = y;

    glutPostRedisplay();
}

void idle()
{
	static int last_frame_time = 0;
    int current_time;
    double elapsed_time;

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}

void controls(int value)
{
    switch (value) 
    {
    case M_NONE:
        return;
    case M_MOTION:
        animation = 1 - animation;

        ALuint buffer, source;

        if (animation == 1 && bee == 1) 
        {
            alcMakeContextCurrent(1);
            alutInit(0, NULL);
            buffer = alutCreateBufferFromFile("sounds/bee.wav");
            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, buffer);
            alSourcePlay(source);

            glutIdleFunc(idle);
        }
        else
        {
            alSourceStop(source);
            alDeleteSources(1, &source);
            alDeleteBuffers(1, &buffer);
            alcMakeContextCurrent(NULL);

            glutIdleFunc(0);
        }
        break;
    case M_CAT:
        cat = 1 - cat;
        display();
        break;
    case M_BEE:
        bee = 1 - bee;
        if (!bee)
        {
            //PlaySound(NULL, NULL, 0);

            glutIdleFunc(0);
        }
        display();
        break;
    case M_FLOOR_TEXTURE:
        floor_texture = 1 - floor_texture;
        display();
        break;
    case M_SKY_TEXTURE:
        sky_texture = 1 - sky_texture;
        display();
        break;
    case M_CAT_TEXTURE:
        cat_texture = 1 - cat_texture;
        display();
        break;
    case M_BEE_TEXTURE:
        bee_texture = 1 - bee_texture;
        display();
        break;
    case M_OPACITY:
        opacity = 1 - opacity;
        display();
        break;
    case M_INFO:
        show_info = 1 - show_info;
        display();
        break;
        
    }
}

void set_callbacks()
{
	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

	glutCreateMenu(controls);

	glutAddMenuEntry("Toggle animation", M_MOTION);
	glutAddMenuEntry("-----------------------", M_NONE);
    glutAddMenuEntry("Toggle cat", M_CAT);
    glutAddMenuEntry("Toggle bee", M_BEE);
    glutAddMenuEntry("-----------------------", M_NONE);
	glutAddMenuEntry("Toggle floor texture", M_FLOOR_TEXTURE);
	glutAddMenuEntry("Toggle sky texture", M_SKY_TEXTURE);
    glutAddMenuEntry("Toggle cat texture", M_CAT_TEXTURE);
    glutAddMenuEntry("Toggle bee texture", M_BEE_TEXTURE);
    glutAddMenuEntry("-----------------------", M_NONE);
    glutAddMenuEntry("Toggle cat transparency", M_OPACITY);
    glutAddMenuEntry("-----------------------", M_NONE);
    glutAddMenuEntry("Show/Hide Info", M_INFO);
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
