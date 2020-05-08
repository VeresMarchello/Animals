#include "draw.h"


void draw_model(const struct Model* model)
{
    draw_triangles(model);
}

void draw_triangles(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;
   
    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i)
	{
        for (k = 0; k < 3; ++k) 
		{
            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1-v);

            normal_index = model->triangles[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_floor()
{
    GLfloat width = 50.0f;
    
    if (floor_texture)
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glColor3f(0, 0.5, 0);
    }

    glBegin(GL_QUADS);

    GLfloat textCoord = width;

    glNormal3f(0, 1, 0);


    glTexCoord2d(0, 0);
    glVertex3f(-width, -width, 0);

    glTexCoord2d(0, textCoord);
    glVertex3f(-width, width, 0);

    glTexCoord2d(textCoord, textCoord);
    glVertex3f(width, width, 0);

    glTexCoord2d(textCoord, 0);
    glVertex3f(width, -width, 0);

    glEnd();

    if (floor_texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glColor3f(1, 1, 1);
    }
}

void draw_skybox()
{
    if (sky_texture)
    {
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glColor3f(0.5, 0.8, 1);
    }

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 120;
    n_stacks = 60;
    radius = 50;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i)
    {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k)
        {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

    if (sky_texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glColor3f(1, 1, 1);
    }
}
