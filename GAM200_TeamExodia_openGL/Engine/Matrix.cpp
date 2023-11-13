/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.cpp
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October  3, 2023
Updated:    November 1, 2023
*/


#include <cmath>

#include "Matrix.h"


#pragma region TransformationMatrix

Math::TransformationMatrix::TransformationMatrix()
{
    Reset();
}

void Math::TransformationMatrix::Reset()
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == col)
            {
                matrix[row][col] = 1;
            }
            else
            {
                matrix[row][col] = 0;
            }
        }
    }
}


Math::TransformationMatrix Math::TransformationMatrix::operator * (TransformationMatrix m) const
{
    TransformationMatrix result;

    result.matrix[0][0] = matrix[0][0] * m[0][0] + matrix[0][1] * m[1][0] + matrix[0][2] * m[2][0];
    result.matrix[0][1] = matrix[0][0] * m[0][1] + matrix[0][1] * m[1][1] + matrix[0][2] * m[2][1];
    result.matrix[0][2] = matrix[0][0] * m[0][2] + matrix[0][1] * m[1][2] + matrix[0][2] * m[2][2];
    result.matrix[1][0] = matrix[1][0] * m[0][0] + matrix[1][1] * m[1][0] + matrix[1][2] * m[2][0];
    result.matrix[1][1] = matrix[1][0] * m[0][1] + matrix[1][1] * m[1][1] + matrix[1][2] * m[2][1];
    result.matrix[1][2] = matrix[1][0] * m[0][2] + matrix[1][1] * m[1][2] + matrix[1][2] * m[2][2];
    result.matrix[2][0] = matrix[2][0] * m[0][0] + matrix[2][1] * m[1][0] + matrix[2][2] * m[2][0];
    result.matrix[2][1] = matrix[2][0] * m[0][1] + matrix[2][1] * m[1][1] + matrix[2][2] * m[2][1];
    result.matrix[2][2] = matrix[2][0] * m[0][2] + matrix[2][1] * m[1][2] + matrix[2][2] * m[2][2];

    return result;
}

Math::TransformationMatrix& Math::TransformationMatrix::operator *= (Math::TransformationMatrix m)
{
    (*this) = (*this) * m;
    return (*this);
}

Math::vec2 Math::TransformationMatrix::operator * (vec2 v) const
{
    Math::vec2 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2];
    return result;
}

#pragma endregion


#pragma region TranslationMatrix

Math::TranslationMatrix::TranslationMatrix(ivec2 translate)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == col)
            {
                matrix[row][col] = 1;
            }
            else if (row == 0 && col == 2)
            {
                matrix[row][col] = translate.x;
            }
            else if (row == 1 && col == 2)
            {
                matrix[row][col] = translate.y;
            }
            else
            {
                matrix[row][col] = 0;
            }

        }
    }
}


Math::TranslationMatrix::TranslationMatrix(vec2 translate)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == col)
            {
                matrix[row][col] = 1;
            }
            else if (row == 0 && col == 2)
            {
                matrix[row][col] = translate.x;
            }
            else if (row == 1 && col == 2)
            {
                matrix[row][col] = translate.y;
            }
            else
            {
                matrix[row][col] = 0;
            }

        }
    }
}

#pragma endregion


#pragma region ScaleMatrix

Math::ScaleMatrix::ScaleMatrix(double scale)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == 0 && col == 0)
            {
                matrix[row][col] = scale;
            }
            else if (row == 1 && col == 1)
            {
                matrix[row][col] = scale;
            }
            else if (row == 2 && col == 2)
            {
                matrix[row][col] = 1;
            }
            else
            {
                matrix[row][col] = 0;
            }
        }
    }
}


Math::ScaleMatrix::ScaleMatrix(vec2 scale)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == 0 && col == 0)
            {
                matrix[row][col] = scale.x;
            }
            else if (row == 1 && col == 1)
            {
                matrix[row][col] = scale.y;
            }
            else if (row == 2 && col == 2)
            {
                matrix[row][col] = 1;
            }
            else
            {
                matrix[row][col] = 0;
            }

        }
    }
}

Math::RotationMatrix::RotationMatrix(double theta)
{
    
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (row == 0 && col == 0)
            {
                matrix[row][col] = cos(theta);
            }
            else if (row == 0 && col == 1)
            {
                matrix[row][col] = -sin(theta);
            }
            else if (row == 1 && col == 0)
            {
                matrix[row][col] = sin(theta);
            }
            else if (row == 1 && col == 1)
            {
                matrix[row][col] = cos(theta);
            }
            else if (row == 2 && col == 2)
            {
                matrix[row][col] = 1;
            }
            else
            {
                matrix[row][col] = 0;
            }
        }
    }
    

}

#pragma endregion
