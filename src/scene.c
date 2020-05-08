#include "scene.h"

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>


void init_scene(Scene* scene)
{
    load_model(&(scene->cat), "objects/cat.obj");
    scene->cat_texture_id = load_texture("textures/cat.jpg");

    scene->sky_texture_id = load_texture("textures/sky.jpg");
    scene->grass_texture_id = load_texture("textures/grass.jpg");

    load_model(&(scene->bee), "objects/bee.obj");
    scene->bee_texture_id = load_texture("textures/bee.png");


    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.2;

    scene->material.diffuse.red = 0.2;
    scene->material.diffuse.green = 0.2;
    scene->material.diffuse.blue = 0.2;

    scene->material.specular.red = 0.1;
    scene->material.specular.green = 0.1;
    scene->material.specular.blue = 0.1;

    scene->material.shininess = 5.0;

    scene->angle = 20.0;

    brightness = 1.0f;
}

void set_lighting(float number)
{
    brightness += number;
    if (brightness >= 1.2f)
    {
        brightness = 1.2f;
    }
    if (brightness <= -0.6f)
    {
        brightness = -0.6f;
    }

    float ambient_light[] = { brightness, brightness, brightness, 1.0 };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 2.0f, 2.0f, 2.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] =
    {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] =
    {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] =
    {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(0);
    //draw_origin();
    
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    draw_skybox();
    

    glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    draw_floor();


    if (cat_texture && cat && !opacity)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->cat_texture_id);
    }
    if (cat)
    {
        if (cat_texture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, scene->cat_texture_id);
        }
        else
        {
            glColor3f(1, 0.4, 0);

            if (opacity)
            {
                glEnable(GL_BLEND);
                glDepthMask(GL_FALSE);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(1, 0.4, 0, 0.4);
            }
        }
        
        draw_model(&(scene->cat));

        if (cat_texture)
        {
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            if (opacity)
            {
                glDepthMask(GL_TRUE);
                glDisable(GL_BLEND);
            }
            glColor3f(1, 1, 1);
        }
    }
    
   
    if (bee)
    {
        glTranslatef(0.0, 0.0, 2.0);

        if (animation)
        {
            animate_bee(scene);
        }

        if (bee_texture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, scene->bee_texture_id);
        }
        else
        {
            glColor3f(1, 1, 0.3);
        }

        draw_model(&(scene->bee));

        if (bee_texture)
        {
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            glColor3f(1, 1, 1);
        }
    }
    
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void animate_bee(Scene* scene)
{
    scene->angle += 10;
    glRotatef(scene->angle, 0.0, 0.0, -1.0);
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
}
