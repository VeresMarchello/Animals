#ifndef DRAW_H
#define DRAW_H

#include <GL/glut.h>

#include "model.h"
#include "utils.h"

int animation;
int cat;
int bee;
int floor_texture;
int sky_texture;
int cat_texture;
int bee_texture;
int opacity;

/* Draw the model */
void draw_model(const struct Model* model);

/* Draw the triangles of the model */
void draw_triangles(const struct Model* model);

/* Draw the floor */
void draw_floor();

/* Draw the sky */
void draw_skybox();

#endif