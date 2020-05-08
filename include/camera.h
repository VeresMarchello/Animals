#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

#include "utils.h"
#include <stdio.h>

/* GLSL-like three dimensional vector */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

/* Initialize the camera to the start position */
void init_camera(Camera* camera);

/* Print camera position and rotation */
void print_camera_info(Camera* camera);

/* Moves camera upward */
void step_camera_up(struct Camera* camera, double distance);

/* Moves camera downwards */
void step_camera_down(struct Camera* camera, double distance);

/* Moves camera left */
void step_camera_left(struct Camera* camera, double distance);

/* Moves camera right */
void step_camera_right(struct Camera* camera, double distance);

/* Moves camera forward */
void move_camera_forward(struct Camera* camera, double distance);

/* Moves camera backward */
void move_camera_backward(struct Camera* camera, double distance);

/* Update the position of the camera */
void update_camera(Camera* camera, double time);

/* Apply the camera settings to the view transformation */
void set_view(const Camera* camera);

/* Set the horizontal and vertical rotation of the view angle */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/* Set the speed of forward and backward motion */
void set_camera_speed(Camera* camera, double speed);

/* Set the speed of left and right side steps */
void set_camera_side_speed(Camera* camera, double speed);

#endif