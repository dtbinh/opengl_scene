#include "Scene.h"
#include <GL/gl.h>
#include "opengl.h"
#include "Camera.h"

void draw_fire(const Scene& sc);

void draw_axes()
{
    glLineWidth(5);
    glBegin( GL_LINES );

    glColor3f( 1.f, 0.f, 0.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 1.f, 0.f, 0.f);

    glColor3f( 0.f, 1.f, 0.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 0.f, 1.f, 0.f);

    glColor3f( 0.f, 0.f, 1.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 0.f, 0.f, 1.f);

    glEnd();
}


void draw_grid()
{
    int i;
    glLineWidth(1);
    glColor3f( 1.f, 1.f, 1.f);

    glPushMatrix();
    glTranslatef( -5, 0, -5);

    glBegin( GL_LINES );

    for (i=0;i<=10;++i)
    {
        glVertex3f( i, 0, 0);
        glVertex3f( i, 0, 10);
    }

    for (i=0;i<=10;++i)
    {
        glVertex3f( 0, 0, i);
        glVertex3f( 10, 0, i);
    }

    glEnd();
    glPopMatrix();
}



void draw_cube()
{
    static float pt[8][3] = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1}, {0,1,0}, {1,1,0}, {1,1,1}, {0,1,1} };
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {1,5,6,2}, {0,3,7,4}, {3,2,6,7}, {0,4,5,1} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    static float uv[4][2] = { {0,0}, {1,0}, {1,1}, {0,1} };
    int i,j;

    glTranslatef(-0.5,-0.5,-0.5);
    glBegin(GL_QUADS);
    for (i=0;i<6;i++)
    {
        glNormal3f( n[ i ][0], n[ i ][1], n[ i ][2] );
        for (j=0;j<4;j++)
        {
            glTexCoord2f( uv[j][0], uv[j][1] );
            glVertex3f( pt[ f[i][j] ][0], pt[ f[i][j] ][1], pt[ f[i][j] ][2] );
        }
    }
    glEnd();
}

//-------------------------------------------- Procédures qui déssinent les formes de base --------------------------------------


void draw_sphere()
{
    float alpha1, alpha2, beta;
    //Nombre de divisions
    int divBeta=25, divAlpha=11;

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<divAlpha;i++)
    {
        alpha1 = -0.5*M_PI+float(i)*M_PI/divAlpha; //Pas pour dessiner la sph��re
        alpha2 = -0.5*M_PI+float(i+1)*M_PI/divAlpha;
        for (int j=0;j<divBeta;j++)
        {
            beta=float(j)*2*M_PI/divBeta;
            glNormal3f(cos(alpha1)*cos(beta),sin(alpha1),cos(alpha1)*sin(beta));
            glTexCoord2f(beta/(2*M_PI),0.5+(alpha1/M_PI));
            glVertex3f(cos(alpha1)*cos(beta),sin(alpha1),cos(alpha1)*sin(beta));
            glNormal3f(cos(alpha2)*cos(beta),sin(alpha2),cos(alpha2)*sin(beta));
            glTexCoord2f(beta/(2*M_PI),0.5+(alpha2/M_PI));
            glVertex3f(cos(alpha2)*cos(beta),sin(alpha2),cos(alpha2)*sin(beta));
        }
    }
    glEnd();
}



void draw_cylinder()
{
    int divAlpha=25;
    float alpha;
    float step=2*M_PI/divAlpha;

    glBegin(GL_TRIANGLE_STRIP);
        for(int i=0;i<=divAlpha;i++)
        {
            alpha=float(i)*step;
            glNormal3f(cos(alpha),0,sin(alpha));
            glTexCoord2f(float(i)/divAlpha,0);
            glVertex3f(cos(alpha),0,sin(alpha));
            glTexCoord2f(float(i)/divAlpha,1);
            glVertex3f(cos(alpha),1,sin(alpha));
        }
    glEnd();
}


void draw_cone()
{
    int divAlpha=25;
    float alpha;
    float step=2*M_PI/divAlpha;
    glBegin(GL_TRIANGLE_STRIP);
        for(int i=0;i<=divAlpha;i++)
        {
            alpha=float(i)*step;
            glNormal3f(cos(alpha),0,sin(alpha));
            glTexCoord2f(float(i)/divAlpha,1);
            glVertex3f(cos(alpha),0,sin(alpha));
            glTexCoord2f(0,0);
            glVertex3f(0,1,0);
        }
    glEnd();
}


/*---------------------------- Procédures qui dessinent des objets un peu plus complexes ------------------------------*/

/*Fonction interm��diaire pour dessiner l'aile d'un avion*/
void draw_wing()
{
    glPushMatrix();
    glScalef(4,0.1,2);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.1,0);
    glScalef(0.4,0.4,2);
    draw_sphere();
    glPopMatrix();
}

//Dessin d'un avion
void draw_plane()
{
    //Dessin fuselage
    glPushMatrix();
    glScalef(1,1,5);
    draw_sphere();
    glPopMatrix();

    //Queue de l'avion
    glPushMatrix();
    glTranslatef(0,1,4);
    glScalef(0.3,2,2);
    draw_cube();
    glPopMatrix();

    //Ailes de l'avion
    glPushMatrix();
    glTranslatef(2.5,0.5,0);
    draw_wing();
    glPopMatrix();

    //Ailes de l'avion
    glPushMatrix();
    glTranslatef(-2.5,0.5,0);
    draw_wing();
    glPopMatrix();


}

//Dessin des turbines pour la fusée
void draw_turbine()
{
    glPushMatrix();
    glScalef(0.7,2,0.7);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2,0);
    glScalef(0.5,0.5,0.5);
    draw_cylinder();
    glPopMatrix();

}

//Dessin d'une fusée
void draw_rocket()
{
    //Dessin fuselage
    glPushMatrix();
    glScalef(1,5,1);
    draw_sphere();
    glPopMatrix();

    //Dessin des turbines
    glPushMatrix();
    glTranslatef(-1,-4,0);
    draw_turbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-4,0);
    draw_turbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-4,1);
    draw_turbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-4,-1);
    draw_turbine();
    glPopMatrix();
}

//Dessin des roues pour une voiture
void draw_tire()
{
    glPushMatrix();
    glColor3f(1,1,1);
    glRotatef(90,0,0,1);
    draw_cylinder();
    glPopMatrix();
}

//Dessin d'une voiture
void draw_car()
{
    glPushMatrix();
    glColor3f(1,0,0);
    glScalef(4,3,6);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,-0.5,-3);
    glScalef(4,2,6);
    draw_cube();
    glPopMatrix();

//Dessin des roues
    glPushMatrix();
    glTranslatef(2,-2,-3);
    draw_tire();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-2,2.1);
    draw_tire();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.1,-2,-3);
    draw_tire();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.1,-2,2.1);
    draw_tire();
    glPopMatrix();
}


/*-------------------------------------- Procédures pour le réalisation d'un terrain et d'un cubemap -------------------------------*/

//Initialise la structure scene avec les différentes textures
void sceneInit(Scene& sc)
{
    animInit( sc.anim, "data/anim1.ani" );
    sc.tex_tree = LoadGLTexture("data/billboard/arbre.ppm", true);
    imInitPPM(sc.terrain,"data/terrain/terrain.ppm");
    sc.tex_terrain = LoadGLTexture("data/terrain/terrain_texture.ppm", false);
    sc.cube_map[0] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_posx.ppm", false);
    sc.cube_map[1] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_negx.ppm", false);
    sc.cube_map[2] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_posy.ppm", false);
    sc.cube_map[3] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_negy.ppm", false);
    sc.cube_map[4] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_posz.ppm", false);
    sc.cube_map[5] = LoadGLTexture("data/cubemap/cubemap_opensea/opensea_negz.ppm", false);
    sc.cm = LoadGLTexture("data/cubemap/cubemap_BlueSkyRainbow.ppm",false);

    sc.water = LoadGLTexture("data/eau.ppm",true);
    sc.fire = LoadGLTexture("data/feu.ppm",true);
    sc.world = LoadGLTexture("data/monde.ppm",false);
    sc.cone = LoadGLTexture("data/cone.ppm",false);
}

//Fonction qui calcule la normale pour l'illumination du terrain
Vec3f calc_norm(int i, int j, const Image& im)
{
    Vec3f v1, v2, n1;
    vecInit(v1,2,getPixConst(im,(i+1)%imGetDimX(im),j,2)-getPixConst(im,(i-1)%imGetDimX(im),j,2),0);
    vecInit(v2,0,getPixConst(im,i,(j+1)%imGetDimY(im),2)-getPixConst(im,i,(j-1)%imGetDimY(im),2),2);
    vecCross(n1,v2,v1);
    vecNormalize(n1);
    return n1;
}

//Dessin des bilboards avec les arbres
void pos_tree(const Scene& sc)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sc.tex_tree);
    glPushMatrix();
    glScalef(0.4,0.04,0.4);


    for (int i=1;i<imGetDimX(sc.terrain)-2;i++)
    {
        for (int j=1;j<imGetDimY(sc.terrain)-2;j++)
        {
            if (getPixConst(sc.terrain,i,j,2)>100 && getPixConst(sc.terrain,i,j,2)<125)
            {
                glPushMatrix();
                //Pour positionner les billboard dans le terrain et pour qu'ils soient orientés vers la caméra
                glTranslatef(i,getPixConst(sc.terrain,i,j,2),j);
                glRotatef(-cam.rotLeft,0,1,0);

                //Première face
                glBegin(GL_QUADS);
                glTexCoord2f(0,1);
                glVertex3f(0,0,0);
                glTexCoord2f(0,0);
                glVertex3f(0,20,0);
                glTexCoord2f(1,0);
                glVertex3f(1,20,0);
                glTexCoord2f(1,1);
                glVertex3f(1,0,0);
                glEnd();

                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}

//Dessin du terrain
void draw_field(const Image& im)
{
    Vec3f n, n1, n2;
    glPushMatrix();
    glScalef(0.4,0.04,0.4);

    for(int i=1;i<imGetDimX(im)-2;i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(int j=1;j<imGetDimY(im)-2;j++)
        {
            n1=calc_norm(i,j,im);
            glNormal3f(n1.x,n1.y,n1.z);
            glTexCoord2f(float(i)/imGetDimX(im), float(j)/imGetDimY(im));
            glVertex3f(i,getPixConst(im,i,j,2),j);

            n2=calc_norm(i+1,j,im);
            glNormal3f(n2.x,n2.y,n2.z);
            glTexCoord2f(float(i+1)/imGetDimX(im), float(j)/imGetDimY(im));
            glVertex3f(i+1,getPixConst(im,(i+1)%imGetDimX(im),j,2),j);
        }
        glEnd();
    }

    //glColor3f(1,0,0);
    for(int i=1;i<imGetDimX(im)-2;i++)
    {
        glBegin(GL_LINES);
        for(int j=1;j<imGetDimY(im)-2;j++)
        {
            n=calc_norm(i,j,im);
            glVertex3f(i,getPixConst(im,i,j,2),j);
            glVertex3f(n.x+i,n.y+getPixConst(im,i,j,2),n.z+j);
        }
    }
    glEnd();

    glPopMatrix();

}

//Dessine un plan, sera utilisé pour la première fonction cubemap
void draw_plan()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.999,0.999);
    glVertex3f(0,0,0);
    glTexCoord2f(0.001,0.999);
    glVertex3f(1,0,0);
    glTexCoord2f(0.001,0.001);
    glVertex3f(1,1,0);
    glTexCoord2f(0.999,0.001);
    glVertex3f(0,1,0);
    glEnd();
}

//Dessine un cubemap avec une texture par face
void draw_cubemap(const Scene& sc)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();

    //Pour centrer le cubemap et le faire grand
    //Pour qu'on ne sorte pas du cubemap
    if(cam.flyOrTrackball==0)
    {
        glTranslatef(cam.pos.x-75,cam.pos.y-75,cam.pos.z-75);
        glScalef(150,150,150);
    }
    else
    {
        glTranslatef(-75,-75,-75);
        glScalef(150,150,150);
    }

    //Initialisation des textures sur chaque face
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,sc.cube_map[4]);
    glRotatef(180,0,1,0);
    glTranslatef(-1,0,0);
    draw_plan();
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,sc.cube_map[1]);
    glRotatef(-90,0,1,0);
    draw_plan();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,sc.cube_map[2]);
    glPushMatrix();
    glTranslatef(0,1,0);
    glRotatef(90,1,0,0);
    draw_plan();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,sc.cube_map[3]);
    glPushMatrix();
    glRotatef(90,1,0,0);
    glRotatef(180,0,0,1);
    glTranslatef(-1,-1,0);
    draw_plan();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,sc.cube_map[0]);
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-1,0,1);
    draw_plan();
    glPopMatrix();


    glBindTexture(GL_TEXTURE_2D,sc.cube_map[5]);
    glPushMatrix();
    glTranslatef(0,0,1);
    draw_plan();
    glPopMatrix();

    glPopMatrix();


    //Pour que le cubemap soit reflété sur l'avion

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_GEN_S);

}

//Deuxième procédure pour le dessin d'un cubemap, utilise une seule texture
void draw_cm2(const Scene& sc)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();

    //Pour centrer le cubemap et le faire grand
    //Pour qu'on ne sorte pas du cubemap
    //glTranslatef(cam.pos.x-25,cam.pos.y-25,cam.pos.z-25);
    //glScalef(50,50,50);


    //Initialisation des textures sur chaque face
    glBindTexture(GL_TEXTURE_2D,sc.cm);

    //Face d'en face
    glBegin(GL_QUADS);
    glTexCoord2f(0,0.66);
    glVertex3f(0,0,0);
    glTexCoord2f(0,0.33);
    glVertex3f(0,1,0);
    glTexCoord2f(0.25,0.33);
    glVertex3f(1,1,0);
    glTexCoord2f(0.25,0.66);
    glVertex3f(1,0,0);

    //Face de droite
    glTexCoord2f(0.25,0.66);
    glVertex3f(1,0,0);
    glTexCoord2f(0.25,0.33);
    glVertex3f(1,1,0);
    glTexCoord2f(0.5,0.33);
    glVertex3f(1,1,1);
    glTexCoord2f(0.5,0.66);
    glVertex3f(1,0,1);

    //Face du bas
    glTexCoord2f(0.25,1);
    glVertex3f(0,0,0);
    glTexCoord2f(0.25,0.66);
    glVertex3f(1,0,0);
    glTexCoord2f(0.5,0.66);
    glVertex3f(1,0,1);
    glTexCoord2f(0.5,1);
    glVertex3f(0,0,1);

    //Face du haut
    glTexCoord2f(0.25,0);
    glVertex3f(0,1,0);
    glTexCoord2f(0.25,0.33);
    glVertex3f(1,1,0);
    glTexCoord2f(0.5,0.33);
    glVertex3f(1,1,1);
    glTexCoord2f(0.5,0);
    glVertex3f(0,1,1);

    //Face de derrière
    glTexCoord2f(0.5,0.66);
    glVertex3f(1,0,1);
    glTexCoord2f(0.5,0.33);
    glVertex3f(1,1,1);
    glTexCoord2f(0.75,0.33);
    glVertex3f(0,1,1);
    glTexCoord2f(0.75,0.66);
    glVertex3f(0,0,1);

    //Face de gauche
    glTexCoord2f(1,0.66);
    glVertex3f(0,0,0);
    glTexCoord2f(1,0.33);
    glVertex3f(0,1,0);
    glTexCoord2f(0.75,0.33);
    glVertex3f(0,1,1);
    glTexCoord2f(0.75,0.66);
    glVertex3f(0,0,1);

    glEnd();

    glPopMatrix();
}

//L'objet anim�� est dessin��
void anim_plane(const Scene& sc)
{
    glPushMatrix();
    Vec3f pos,dir,dir1,codir,vecy,d;
    float px,py,pz,dx,dy,dz;
    float t = temps();
    int temps_entier = int(t);
    int temps_entier_ok = temps_entier % sc.anim.nbp ;

    //Calcul des interpolations pour un mouvement plus fluide
    px = sc.anim.P[temps_entier_ok].x+(sc.anim.P[(temps_entier_ok+1)%sc.anim.nbp].x-sc.anim.P[temps_entier_ok].x)*(t-temps_entier);
    py = sc.anim.P[temps_entier_ok].y+(sc.anim.P[(temps_entier_ok+1)%sc.anim.nbp].y-sc.anim.P[temps_entier_ok].y)*(t-temps_entier);
    pz = sc.anim.P[temps_entier_ok].z+(sc.anim.P[(temps_entier_ok+1)%sc.anim.nbp].z-sc.anim.P[temps_entier_ok].z)*(t-temps_entier);
    vecInit(pos,px,py,pz);

    //Calcul de l'interpolation de rotation
    vecInit(vecy,0,1,0);
    vecSub(dir,sc.anim.P[(temps_entier_ok+1)%sc.anim.nbp],pos);
    vecSub(dir1,sc.anim.P[(temps_entier_ok+2)%sc.anim.nbp],pos);
    vecNormalize(dir);
    vecNormalize(dir1);
    dx=dir.x+(dir1.x-dir.x)*(t-temps_entier);
    dy=dir.y+(dir1.y-dir.y)*(t-temps_entier);
    dz=dir.z+(dir1.z-dir.z)*(t-temps_entier);
    vecInit(d,dx,dy,dz);
    vecCross(codir,d,vecy);

    //Matrice de rotation et de translation
    float mat[16]={d.x,d.y,d.z,0,
                    0,1,0,0,
                    codir.x,codir.y,codir.z,0,
                    pos.x,pos.y,pos.z,1};
    glMultMatrixf(mat);

    //Pour que l'avion soit affiché dans la bonne position et plus petit
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.5,0.5);

    glEnable (GL_BLEND);
    draw_plane();
    glDisable (GL_BLEND);
    glPopMatrix();
}

//Dessin de l'eau du terrain avec simulation de vagues
void draw_water(const Scene& sc)
{
    glBindTexture(GL_TEXTURE_2D, sc.water);
    glPushMatrix();
    //On fait correspondre par rapport au cubemap
    if(cam.flyOrTrackball==0)
    {
        glTranslatef(cam.pos.x-75,getPixConst(sc.terrain,1,1,1)/500-4,cam.pos.z-75);
        glScalef(150,1,150);
    }
    else
    {
        glTranslatef(-75,getPixConst(sc.terrain,1,1,1)/500-4,-75);
        glScalef(150,1,150);
    }
    glRotatef(90,1,0,0);
    //Simulation des vagues de l'eau
    glTranslatef(0,0,0.1*sin(2*temps()));
    //Transparence pour faire l'effet de l'eau
    glColor4f(1,1,1,0.7);
    draw_plan();
    glPopMatrix();
}

//Dessin du feu au dessus de la montagne
void draw_fire(const Scene& sc)
{
    //Pour avoir une image un peu plus réaliste
    float t = temps()*24;
    int temps_entier = int(t);
    int t_ok = temps_entier % 16;

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, sc.fire);
    glPushMatrix();
    glTranslatef(3,5,14);
    glScalef(3,3,3);
    glRotatef(-cam.rotLeft,0,1,0);
    glColor4f(1,1,1,0.7);

    //Dessin de la première face
    glBegin(GL_QUADS);
    glTexCoord2f(float(t_ok)/16,1);
    glVertex3f(0,0,0);
    glTexCoord2f(float(t_ok)/16,0);
    glVertex3f(0,1,0);
    glTexCoord2f(float(t_ok)/16+0.0625,0);
    glVertex3f(1,1,0);
    glTexCoord2f(float(t_ok)/16+0.0625,1);
    glVertex3f(1,0,0);

    //Dessin de la deuxième face

    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}


void sceneDraw(const Scene& sc)
{
    //Dessin du cubemap
    glEnable(GL_TEXTURE_2D);
    draw_cm2(sc);
    draw_cubemap(sc);

    //Animation de l'objet
    anim_plane(sc);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    //Dessin du terrain
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(-30,-5,-35);
    glBindTexture(GL_TEXTURE_2D, sc.tex_terrain);
    draw_field(sc.terrain);
    pos_tree(sc);
    glPopMatrix();

    //Dessin de l'eau. Transparence pour l'eau activée
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw_water(sc);
    glDisable(GL_BLEND);

    draw_fire(sc);

    //Dessin des formes de base
    glBindTexture(GL_TEXTURE_2D,sc.world);
    glPushMatrix();
    glTranslatef(0,5,0);
    glRotatef(180,1,0,0);
    draw_sphere();
    glTranslatef(4,0,0);
    draw_cylinder();
    glTranslatef(-8,0,0);
    draw_cone();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
