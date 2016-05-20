#include "Render.hpp"
#include "toy/graph/OpenGL.hpp"



namespace Render{

void AddImage(const toy::Image &image)
{
	glTexImage2D(GL_TEXTURE_2D,0,3,image.getWidth(),image.getHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.getData());
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	float   rate;
	glViewport( 0, 0, 800, 600);
	rate = (float)800/(float)600;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45, rate, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

void DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode (GL_BACK, GL_LINE);

	glLoadIdentity();

	gluLookAt( 0, 0, 30.0, 0, 0, 0, 0, 1, 0);
//	glTranslatef( 0, 0, distance);
//	glRotatef( (float)rot_y + (float)record_y, 1.0, 0.0, 0.0);
//	glRotatef( (float)rot_x + (float)record_x, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
		glTexCoord2f(0,1);glVertex3f(-11, 11,0);
		glTexCoord2f(0,0);glVertex3f(-11,-11,0);
		glTexCoord2f(1,0);glVertex3f( 11,-11,0);
		glTexCoord2f(1,1);glVertex3f( 11, 11,0);
	glEnd();
}

void Resize(int w,int h)
{
	glViewport(0, 0, w, h);
}



}//namespace Render{
