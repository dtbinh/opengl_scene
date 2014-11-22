// Informatique graphique LIF041 (Alexandre.Meyer -@- liris.cnrs.fr

#ifndef _OPENGL_HLIF041
#define _OPENGL_HLIF041

#if WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut-3.7.6-bin_win/glut.h"
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//! A appeller juste avant la boucle principale (Main Loop)
void GLInit(GLsizei Width, GLsizei Height);

//! Quand la fenetre est 'resizée'
void GLResize(GLsizei Width, GLsizei Height);

//! Pour changer la couleur du Ambiant/Diffus/Speculaire en même temps
void GLColor(const float r, const float g, const float b);

//! The main drawing function
void GLDraw(void);

//! Quand une touche est pressée
void keyPressed(unsigned char key, int x, int y);

//! The function called whenever a normal key is pressed
void specialKeyPressed(int key, int x, int y);

//! Load texture and return the GL identifier
unsigned int LoadGLTexture(const char* nomfichier, bool isTransparency);

#endif
