#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "model.h"
#include "load.h"
#include "draw.h"

typedef struct Scene
{
    Model cat;
    Model bee;
    Material material;
    GLuint cat_texture_id;
    GLuint bee_texture_id;
    GLuint sky_texture_id;
    GLuint grass_texture_id;
    GLfloat angle;
} Scene;

/* Menu items */
enum 
{
    M_NONE, M_MOTION, 
    M_SKY, M_CAT, M_BEE,
    M_FLOOR_TEXTURE, M_SKY_TEXTURE, M_CAT_TEXTURE, M_BEE_TEXTURE,
    M_OPACITY
};

float brightness;

/* Initialize the scene by loading models */
void init_scene(Scene* scene);

/* Set the lighting of the scene */
void set_lighting(float number);

/* Set the current material */
void set_material(const Material* material);

/* Draw the scene objects */
void draw_scene(Scene* scene);

/* Draw the origin of the world coordinate system */
void draw_origin();

/* Moves the bee in circle */
void animate_bee(Scene* scene);

#endif
