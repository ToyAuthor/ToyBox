
#include <toy/graph/OpenGL.hpp>
#include <toy/scene/CameraConfig.hpp>
#include "Render.hpp"


static toy::scene::CameraConfig    CameraConfig;

namespace Render{

void AddImage(const toy::Image &image)
{
	glTexImage2D(GL_TEXTURE_2D,0,3,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.data());
	glEnable(GL_TEXTURE_2D);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	float   rate;
	glViewport( 0, 0, 800, 600);
	//rate = (float)800/(float)600;
	rate = (float)600/(float)800;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	CameraConfig.perspect(45, rate, 1.0, 500.0);


	glLoadMatrixf((float*)CameraConfig.projection().data);


	//gluPerspective( 45, rate, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

void DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// In OpenGL ES, GL_FILL is the only available polygon mode.
	//glPolygonMode (GL_BACK, GL_LINE);

	glLoadIdentity();

	CameraConfig.lookat( toy::math::Vector3<float>(0, 0, 30.0), toy::math::Vector3<float>(0, 0, 0), toy::math::Vector3<float>(0, 1, 0));

	glLoadMatrixf((float*)CameraConfig.modelview().data);

	//gluLookAt( 0, 0, 30.0, 0, 0, 0, 0, 1, 0);
//	glTranslatef( 0, 0, distance);
//	glRotatef( (float)rot_y + (float)record_y, 1.0, 0.0, 0.0);
//	glRotatef( (float)rot_x + (float)record_x, 0.0, 1.0, 0.0);

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	float    texCoord[8]={0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f};
	float    vertex[12]={-11,-11,0,11,-11,0,-11, 11,0,11, 11,0};

	glTexCoordPointer( 2, GL_FLOAT, sizeof(float)*2, texCoord );
	glVertexPointer( 3, GL_FLOAT, sizeof(float)*3, vertex );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
}

void Resize(int w,int h)
{
	glViewport(0, 0, w, h);
}



}//namespace Render{
