#include "DrawShape.h"

#include <GL/glew.h>



void GAM200::DrawShape::DrawLine(int x1, int y1, int x2, int y2)
{


    float nx1 = Math::NormalizeX(x1, windowWidth);
    float ny1 = Math::NormalizeY(y1, windowHeight);
    float nx2 = Math::NormalizeX(x2, windowWidth);
    float ny2 = Math::NormalizeY(y2, windowHeight);

    glColor4fv(color);
    glLineWidth(lineWidth);

    glBegin(GL_LINES);
    glVertex2f(nx1, ny1);
    glVertex2f(nx2, ny2);
    glEnd();
}

void GAM200::DrawShape::DrawLine(Math::ivec2 start, Math::ivec2 end)
{
    DrawLine(start.x, start.y, end.x, end.y);
}



void GAM200::DrawShape::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    Engine::Instance().push();

    float nx1 = Math::NormalizeX(x1, windowWidth);
    float ny1 = Math::NormalizeY(y1, windowHeight);
    float nx2 = Math::NormalizeX(x2, windowWidth);
    float ny2 = Math::NormalizeY(y2, windowHeight);
    float nx3 = Math::NormalizeX(x3, windowWidth);
    float ny3 = Math::NormalizeY(y3, windowHeight);

    glColor4fv(color);           // Set the color

    glBegin(GL_TRIANGLES);      // Start drawing triangle
    glVertex2f(nx1, ny1);       // First vertex
    glVertex2f(nx2, ny2);       // Second vertex
    glVertex2f(nx3, ny3);       // Third vertex
    glEnd();                    // End drawing

    Engine::Instance().pop();
}


void GAM200::DrawShape::DrawTriangle(int x, int y, int width, int height)
{
    DrawTriangle(x, y, x + width, y, x + width / 2, y + height);
}



void GAM200::DrawShape::DrawRectangleWithPoints(int x1, int y1, int x2, int y2)
{
    Engine::Instance().push();

    float nx1 = Math::NormalizeX(x1, windowWidth);
    float ny1 = Math::NormalizeY(y1, windowHeight);
    float nx2 = Math::NormalizeX(x2, windowWidth);
    float ny2 = Math::NormalizeY(y2, windowHeight);

    glColor4fv(color);    // Set the color

    glBegin(GL_QUADS);    // Start drawing quadrilateral
    glVertex2f(nx1, ny1); // Bottom-left vertex
    glVertex2f(nx2, ny1); // Bottom-right vertex
    glVertex2f(nx2, ny2); // Top-right vertex
    glVertex2f(nx1, ny2); // Top-left vertex
    glEnd();              // End drawing

    Engine::Instance().pop();

}




void GAM200::DrawShape::DrawRectangle(int x, int y, int width, int height)
{
    DrawRectangleWithPoints(x, y, x + width, y + height);
}


/*
x, y, radius, points������ �Է��� �ּ���!
���⼭ points�� ���� �������� ������ �ǹ��մϴ�.
points�� Ŭ���� ���� �ε巯�����ϴ�. 100�� ������ �����ؿ�!!
*/
void GAM200::DrawShape::DrawCircle(int x, int y, int radius, int points)
{
    Engine::Instance().push(); 

    float normalizeX       = Math::NormalizeX(x, windowWidth);      
    float normalizeY       = Math::NormalizeY(y, windowHeight);    
    float normalizeRadiusX = radius / (float)windowWidth * 2.0f;                 
    float normalizeRadiusY = radius / (float)windowHeight * 2.0f; 

    glColor4fv(color);  

    glBegin(GL_TRIANGLE_FAN); 
    glVertex2f(normalizeX, normalizeY);

    for (int i = 0; i <= points; i++)
    {
        float angle = i * 2.0f * 3.14159f / (float)points;
        glVertex2f
        (
            normalizeX + (normalizeRadiusX * cosf(angle)),
            normalizeY + (normalizeRadiusY * sinf(angle))
        );
    }
    glEnd(); 

    Engine::Instance().pop(); 
}


/*
void GAM200::DrawShape::DrawCircle(int x, int y, int radius)
{
	glColor4fv(color); // Set the color

	glBegin(GL_TRIANGLE_FAN); // Start drawing triangle
	glVertex2i(x, y); // Center of circle
    for (int i = 0; i <= 20; i++)   // Last vertex same as first vertex
    {
        glVertex2i(
			(GLint)(x + (radius * cos(i * 2.0f * 3.14159 / 20))),
            (GLint)(y + (radius * sin(i * 2.0f * 3.14159 / 20)))
		);
	}
	glEnd(); // End drawing
}
*/



void GAM200::DrawShape::SetColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}


void GAM200::DrawShape::SetLineWidth(float width)
{
    lineWidth = width;
}
