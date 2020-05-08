#include "camera.h"


void init_camera(Camera* camera)
{
    camera->position.x = 3.0;
    camera->position.y = 3.0;
    camera->position.z = 3.0;
    camera->rotation.x = 337.0;
    camera->rotation.y = 3.0;
    camera->rotation.z = 228.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

void print_camera_info(struct Camera* camera)
{
    printf("Camera position:\n  x:%.6f \n  y:%.6f \n  z:%.6f \n", camera->position.x, camera->position.y, camera->position.z);
    printf("Camera rotation:\n  x:%.6f \n  y:%.6f \n  z:%.6f \n", camera->rotation.x, camera->rotation.y, camera->rotation.z);
    printf("\n");
}

void move_camera_forward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.z);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void move_camera_backward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.z);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
}

void step_camera_up(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.y + 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.z += sin(angle) * distance;
}

void step_camera_down(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.y - 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.z += sin(angle) * distance;
}

void step_camera_left(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.z + 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void step_camera_right(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->rotation.z - 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) 
    {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) 
    {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) 
    {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) 
    {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}