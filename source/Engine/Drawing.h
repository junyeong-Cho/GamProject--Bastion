#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

#include "Engine/Normalization.h"
#include "Image2D.h"


struct GLFWwindow;


namespace ShaderDrawing
{

	enum class CoordinateSystem
	{
		ORGIN,
		LEFT_DOWN
	};

	enum class DrawOriginMode
	{
		ORIGN,
		LEFT_DOWN
	};


	class ShaderDraw
	{
	public:
		struct GLModel 
		{
			unsigned int primitive_type;
			unsigned int primitive_cnt;
			unsigned int shdr_pgm;
			unsigned int vaoid[2];
			unsigned int vboid[2];
			unsigned int draw_cnt;


            static unsigned int  compileShader(unsigned int shaderType, const char* sourceCode);
            static unsigned int  createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
            void                 reloadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		};
		
		struct Character 
		{
			unsigned int TextureID;  // ID handle of the glyph texture
			glm::ivec2   Size;       // Size of glyph
			glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
			unsigned int Advance;    // Offset to advance to next glyph
		};
		
		struct Font
        {
            std::map<char, Character> Characters;
            FT_Face                   face;
        };

		friend void EndWIndow();

		friend void draw_box(float x, float y, float width, float height);
		friend void draw_circle(int x, int y, int width, int height);
		friend void draw_image(ShaderDrawing::Image& image, int x, int y, int width, int height);
		friend void draw_image(ShaderDrawing::Image& image, int x, int y, int texelX, int texelY, int texelWidth, int texelHeight);
		friend void draw_image_freely(Image& image, int x, int y, int width, int height);

		friend void set_color(int red, int green, int blue, int alpha);
		friend void set_rectangle_mode(DrawOriginMode mode);
		friend void set_image_mode(DrawOriginMode mode);
		friend void set_coordinate_mode(CoordinateSystem mode);
		friend void set_fill(bool set);
		friend void set_line_color(int red, int green, int blue, int alpha);

		friend void draw_text(std::string text, float x, float y, float scale, float r, float g, float b, float a);
		friend void draw_text(std::string text, float x, float y, float scale, double radians, float r, float g, float b);

		void friend push();
		void friend pop();

		void friend translateView(float x, float y);
		void friend applyMatrix(float a, float b, float c, float d, float e, float f);
		static void init(SDL_Window* pWindow);
		static void initFont();
        static void initFont(const std::string& fontPath);

        static void setFont(const std::string& fontPath);

		static std::string readShaderFile(const std::string& filePath);

		static void updateShaders();



	private:
		static GLModel box;
		static GLModel textureBox;
		static GLModel circle;
		static GLModel fontBox;

		static bool isfill;
		static bool previous_isfill;
		static float ar;

		static glm::vec4 color;
		static glm::vec4 previous_color;

		static glm::vec4 outlineColor;
		static glm::vec4 previous_Outlinecolor;

		static glm::mat3 view_xform[2];
		static glm::mat3 privous_view_xform[2];

		static glm::mat3 reset_view_xform[2];

		static unsigned int current_image_mode;
		static unsigned int previous_image_mode;
		static unsigned int current_rectangle_mode;
		static unsigned int previous_rectangle_mode;
		static unsigned int current_coordinate_mode;
		static unsigned int previous_coordinate_mode;

		static glm::mat3 camwin_to_ndc_xform;
		static glm::mat3 world_to_ndc_xform;
		static glm::mat3 apply_Matrix;
		static glm::mat3 previous_Matrix;

		static void setBoxModel();
		static void setCircleModel();
		static void setTextureModel();

		static std::map<std::string, Font> Fonts;
        static std::string                 currentFont;


		//static std::map<char, Character> Characters;



	    struct ShaderFile
        {
            std::string                     path;
            std::filesystem::file_time_type lastWriteTime;
        };

        static ShaderFile vertexShaderBox;
        static ShaderFile fragmentShaderBox;
        static ShaderFile vertexShaderCircle;
        static ShaderFile fragmentShaderCircle;
        static ShaderFile vertexShaderTexture;
        static ShaderFile fragmentShaderTexture;
        static ShaderFile vertexShaderFont;
        static ShaderFile fragmentShaderFont;

        static void checkAndReloadShaders();
	};



	void push();
	void pop();

	void translateView(float x, float y);


	void draw_box(float x, float y, float width, float height);
	void draw_circle(int x, int y, int widht, int height);
	void draw_image(ShaderDrawing::Image& image, int x, int y, int width, int height);
	void draw_image(ShaderDrawing::Image& image, int x, int y, int texelX, int texelY, int texelWidth, int texelHeight);
	void draw_image_freely(Image& image, int x, int y, int width, int height);
	void set_color(int red, int green, int blue, int alpha);
	void applyMatrix(float a, float b, float c, float d, float e, float f);
	void set_rectangle_mode(DrawOriginMode mode);
	void set_image_mode(DrawOriginMode mode);
	void set_coordinate_mode(CoordinateSystem mode);
	void set_fill(bool set);
	void set_line_color(int red, int green, int blue, int alpha);
    void draw_text(std::string text, float x, float y, float scale, float r, float g, float b, float a = 1.0f);
	void draw_text(std::string text, float x, float y, float scale, double radians, float r, float g, float b);
	
	void EndWIndow();

}