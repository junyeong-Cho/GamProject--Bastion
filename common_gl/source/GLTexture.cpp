//Author: Junyeong Cho


#include "GLTexture.h"
#include <glCheck.h>
#include <stb_image.h>

GLTexture::~GLTexture() noexcept
{
	//delete_texture(); �Լ��� �̿��� GPU Texture�� �����Ǵ��� Ȯ��
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


	//stbi_load()�Լ��� image data�� unsigned char*�� ��ȯ�ϴµ�, �̰��� pixel data�� ù��° byte�� ����Ű�� �������̴�.
	//���⼭ 4�� RGBA�� �ǹ��ϸ�, (R,G,B,A)�� 0 ~ 225 ������ ���� ������.
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

	//�Ʒ����� glCreateTexture()�Լ��� 4.5 ���� ���ĺ��� �߰��� ����̴�.
	//�������� glGenTextures() + glBindTexture()�� ����ؼ�, 1 / texture_handle���� GL_TEXTURE_2D / texture_handle���� ���� �����.
	GLuint texture;
	glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &texture));


	//glTextureStorage2D()�� �� �ؼ��� ���� GL_RGBA8 ���� ������ ����Ͽ�
	//width�� height�� ���� �־��� �ػ󵵷� ��� �ؼ��� ���Ǹ�(mipmap) ���� 1�� ����� ũ�⸦ ���� 2���� �ؽ�ó �̹����� ���� constexpr�� �����Ѵ�.
		
	#pragma region Mipmap Explain
	//Mipmap(Minimize aliasing maps)�� �ؽ�ó�� ���� �� ����ϴ� ����̴�.
	//����
	/*
	  ����
	   1. Aliasing ����
		-viewport���� ��ü�� �۰� ǥ�õ� ��, mipmap�� ���� �ػ��� texture�� �����, aliasing�� �ٿ��ش�.
		 ���⼭ aliasing�� signal processing�о߿���, ��ȣ�� ���ø��� �� ����� ������ �ǹ��Ѵ�.
		 �� ȭ���� �����ڸ� �κ��� �Ų����� �ʰ� ���ó�� ���̴� �� �����̴�.

	   2. ���� ���
		 -mipmap�� �������� ��, �� ���� �ؽ�ó�� ����ϹǷ�, ������ ������ ���ȴ�.

	   3. �޸� ����
	   4. �ð��� ������
	*/

	//�۵����
	/*
	 mipmap�� ������ ���� �ؽ�ó�� �ػ󵵰� �޶�����(���⼭�� ONE_TEXTURE_LEVEL).
	 0���� ���� �����ϸ� ������ ������ ������ �ؽ�ó�� �ػ󵵴� ���ݾ� �پ���.
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
