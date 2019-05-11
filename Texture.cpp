// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Texture.h"
#include "pngLoad.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture()
{

}

CTexture::~CTexture()
{

}

void CTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}


//only support BMP now...
bool CTexture::Load(const char *filename)
{
	bool Status=false;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	if(TextureImage[0] = LoadPNG(filename))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture);					// Create Three Textures

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
	else if (TextureImage[0]=LoadBMP(filename))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture);					// Create Three Textures

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])								// If Texture Exists
	{
		if (TextureImage[0]->data)						// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);							// Free The Image Structure
	}

	return Status;	
}

AUX_RGBImageRec * CTexture::LoadBMP(const char *Filename)
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL

}

AUX_RGBImageRec * CTexture::LoadPNG(const char *filename)
{
	unsigned char *image_data=0;
	unsigned long width,height;
	if (pngLoad((char *)filename,&width,&height,&image_data)==1)
	{
		AUX_RGBImageRec * image=new AUX_RGBImageRec;
		image->sizeX = width;
		image->sizeY = height;
		image->data = image_data;
		return image;
	}
	else
	{
		return 0;
	}
}
