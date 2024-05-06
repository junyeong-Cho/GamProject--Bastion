#pragma once

#ifndef IMAGE2D_H
#define IMAGE2D_H

#include "stb_image.h"

#include <glm/gtc/type_ptr.hpp>


namespace ShaderDrawing
{
	class Image
	{
	public:
		Image(const char* filename);
		Image() 
		{
			iwidth = 0;
			iheight = 0;
			ichannels = 0;
			image = nullptr;
		};

		friend void draw_image(ShaderDrawing::Image& image, int x, int y, int width, int height);
		friend void draw_image(ShaderDrawing::Image& image, int x, int y, int texelX, int texelY, int texelWidth, int texelHeight);
		friend void draw_image_freely(Image& image, int x, int y, int width, int height);
		int GetWidth()
		{
			return iwidth;
		}
		int GetHeight()
		{
			return iheight;
		}

		void DeleteTexture();
		unsigned int GetTextureID() const { return textureID; }

		void SetTextureID(unsigned int id) { textureID = id; }

		unsigned char* image;


	private:
		int iwidth, iheight, ichannels;
		unsigned int textureID;

	};
}
#endif
