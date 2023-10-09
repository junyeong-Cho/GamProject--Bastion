//Author: Junyeong Cho


#include "GLTexture.h"
#include <glCheck.h>
#include <stb_image.h>

GLTexture::~GLTexture() noexcept
{
	//delete_texture(); 함수를 이용해 GPU Texture가 해제되는지 확인
	delete_texture();
}


GLTexture::GLTexture(GLTexture&& other) noexcept
	: texture_handle{other.texture_handle},
	  width			{other.width},
	  height		{other.height},
	  filtering		{other.filtering},
	  wrapping		{ std::move(other.wrapping) }
{
	other.texture_handle = 0;
	other.width			 = 0;
	other.height		 = 0;
	other.filtering		 = Filtering::NearestPixel;
}


GLTexture& GLTexture::operator=(GLTexture&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	delete_texture();

	//move other's data to this
	texture_handle = other.texture_handle;
	width          = other.width;
	height         = other.height;
	filtering	   = other.filtering;
	wrapping	   = std::move(other.wrapping);

	//reset other
	other.texture_handle = 0;
	other.width			 = 0;
	other.height		 = 0;
	other.filtering		 = Filtering::NearestPixel;

	return *this;
}


bool GLTexture::LoadFromFileImage(const std::filesystem::path& image_filepath, bool flip_vertical) noexcept
{
	bool		   LoadImage;
	unsigned char* imageData;

	stbi_set_flip_vertically_on_load(flip_vertical);


	//stbi_load()함수는 image data를 unsigned char*로 반환하는데, 이것은 pixel data의 첫번째 byte를 가리키는 포인터이다.
	//여기서 4는 RGBA를 의미하며, (R,G,B,A)는 0 ~ 225 사이의 값을 가진다.
	imageData = stbi_load(image_filepath.string().c_str(), &width, &height, nullptr, 4);

	LoadImage = LoadFromMemory(width, height, reinterpret_cast<const RGBA*>(imageData));


	stbi_image_free(imageData);


	return LoadImage;
}


bool GLTexture::LoadFromMemory(int image_width, int image_height, const RGBA* colors) noexcept
{
	delete_texture();

	width  = image_width;
	height = image_height;

	//아래에서 glCreateTexture()함수는 4.5 버전 이후부터 추가된 요소이다.
	//이전에는 glGenTextures() + glBindTexture()를 사용해서, 1 / texture_handle값과 GL_TEXTURE_2D / texture_handle값을 각각 줬었다.
	GLuint texture;
	glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &texture));


	//glTextureStorage2D()는 각 텍셀에 대해 GL_RGBA8 내부 형식을 사용하여
	//width와 height에 의해 주어진 해상도로 모든 텍셀과 미피맵(mipmap) 레벨 1의 저장소 크기를 가진 2차원 텍스처 이미지에 대한 constexpr를 생성한다.
		
	#pragma region Mipmap Explain
	//Mipmap(Minimize aliasing maps)은 텍스처를 줄일 때 사용하는 기법이다.
	//이점
	/*
	  이점
	   1. Aliasing 감소
		-viewport에서 객체가 작게 표시될 때, mipmap은 낮은 해상도의 texture를 사용해, aliasing을 줄여준다.
		 여기서 aliasing은 signal processing분야에서, 신호를 샘플링할 때 생기는 문제를 의미한다.
		 즉 화면의 가장자리 부분이 매끄럽지 않게 계단처럼 보이는 그 현상이다.

	   2. 성능 향상
		 -mipmap은 렌더링할 때, 더 작은 텍스처를 사용하므로, 렌더링 성능이 향상된다.

	   3. 메모리 절약
	   4. 시각적 안정성
	*/

	//작동방식
	/*
	 mipmap의 레벨에 따라서 텍스처의 해상도가 달라진다(여기서는 ONE_TEXTURE_LEVEL).
	 0레벨 부터 시작하며 레벨이 증가할 때마다 텍스처의 해상도는 절반씩 줄어든다.
	*/

	#pragma endregion

	constexpr GLsizei ONE_TEXTURE_LEVEL = 1;
	glCheck(glTextureStorage2D(texture, ONE_TEXTURE_LEVEL, GL_RGBA8, width, height));


	constexpr GLint   FIRST_LEVEL = 0;
	constexpr GLsizei OFFSET_X = 0, OFFSET_Y = 0;
	glCheck(glTextureSubImage2D(texture, FIRST_LEVEL, OFFSET_X, OFFSET_Y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, colors));
	
	
	texture_handle = texture;


	SetFiltering(filtering);
	SetWrapping(wrapping[0], Coordinate::S);
	SetWrapping(wrapping[1], Coordinate::T);

	return true;
}

void GLTexture::UseForSlot(unsigned int texture_unit) const noexcept
{
	if (texture_handle == 0)
	{
		return;
	}
		

	glCheck(glActiveTexture(GL_TEXTURE0 + texture_unit));
	glCheck(glBindTexture(GL_TEXTURE_2D, texture_handle));
}


void GLTexture::SetFiltering(Filtering how_to_filter) noexcept
{
	if (texture_handle == 0)
	{
		return;
	}
		

	filtering = how_to_filter;


	glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filtering)));
	glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filtering)));
}


void GLTexture::SetWrapping(Wrapping how_to_wrap, Coordinate coord) noexcept
{
	if (texture_handle == 0)
	{
		return;
	}
		

	switch (coord)
	{
	case Coordinate::S:
		wrapping[0] = how_to_wrap;
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(how_to_wrap)));
		break;

	case Coordinate::T:
		wrapping[1] = how_to_wrap;
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(how_to_wrap)));
		break;

	case Coordinate::Both:
		wrapping[0] = wrapping[1] = how_to_wrap;
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(how_to_wrap)));
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(how_to_wrap)));
		break;
	}

}

void GLTexture::delete_texture() noexcept
{
	// invoke glDeleteTextures	
	texture_handle = 0;		//so we don't accidentally double it
	width		   = 0;
	height		   = 0;
}
