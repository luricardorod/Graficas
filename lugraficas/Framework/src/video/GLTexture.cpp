#include <video/GLTexture.h>

#if defined(USING_OPENGL_ES20)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES30)
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL_ES31)
#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_OPENGL)
#include <GL/glew.h>
#else
#include <GL/glew.h>
#include <SDL/SDL.h>
#endif

void GLTexture::SetTextureParams()
{
	glBindTexture(GL_TEXTURE_2D, id);

	unsigned int glFiltering = 0;
	unsigned int glWrap = 0;

	glFiltering = GL_LINEAR_MIPMAP_LINEAR;
	glWrap = GL_CLAMP_TO_EDGE;

	if(params & TEXT_BASIC_PARAMS::MIPMAPS)
		glFiltering = GL_LINEAR_MIPMAP_LINEAR;

	if (params & TEXT_BASIC_PARAMS::CLAMP_TO_EDGE)
		glWrap = GL_CLAMP_TO_EDGE;

	if (params & TEXT_BASIC_PARAMS::TILED)
		glWrap = GL_REPEAT;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

	int Max = 1;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::GetFormatBpp(unsigned int &props, unsigned int &glFormat, unsigned int &bpp)
{

}

void GLTexture::LoadAPITexture(unsigned char* buffer)
{
	unsigned int glFormat = 0;
	unsigned int glChannel = GL_UNSIGNED_BYTE;
	unsigned int glTarget = GL_TEXTURE_2D;

	if (this->props&TEXT_BASIC_FORMAT::CH_ALPHA)
		glFormat = GL_ALPHA;
	else if (this->props&TEXT_BASIC_FORMAT::CH_RGB)
		glFormat = GL_RGB;
	else if (this->props&TEXT_BASIC_FORMAT::CH_RGBA)
		glFormat = GL_RGBA;

	glGenTextures(1, &id);
	glBindTexture(glTarget, id);

	if (this->x % 4 != 0)
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	else
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexImage2D(glTarget, 0, glFormat, this->x, this->y, 0, glFormat, glChannel, (void*)(buffer));

	glGenerateMipmap(glTarget);

	SetTextureParams();
}

void GLTexture::LoadAPITextureCompressed(unsigned char* buffer)
{

}

void GLTexture::DestroyAPITexture()
{
	glDeleteTextures(1,&id);
}