
#ifndef _SCENE_H
#define _SCENE_H

#include "Animation.h"
#include "Image.h"

//! The structure Scene stores all texture Id or images used by the sceneDraw fonction
struct Scene
{
    Animation anim;
	unsigned int tex_tree;

	Image terrain;
	unsigned int tex_terrain;

	unsigned int cube_map[6];

	unsigned int cm;

	unsigned int water;

	unsigned int fire;

	unsigned int world;

	unsigned int cone;
};


//! Init a Scene
void sceneInit(Scene& sc);

//! Draw the scene
void sceneDraw(const Scene& sc);


//! Draw a cube
void draw_cube();

//! Draw a cylinder
void draw_cylinder();

//! Draw a cone
void draw_cone();

//! Draw a sphere
void draw_sphere();

//! Draw the X,Y,Z axes
void draw_axes();

//! Draw a grid in the XZ plane
void draw_grid();


#endif
