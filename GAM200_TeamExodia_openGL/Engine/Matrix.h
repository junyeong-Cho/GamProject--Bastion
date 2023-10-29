/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 3, 2023
*/

#pragma once

#include "Vec2.h"

namespace Math
{
	class TransformationMatrix
	{
	public:
		TransformationMatrix();

		const double* operator[](int index) const { return matrix[index]; }

		TransformationMatrix  operator *  (TransformationMatrix m) const;
		TransformationMatrix& operator *= (TransformationMatrix m);

		Math::vec2 operator*(vec2 v) const;

		void Reset();

		const GLfloat* ToGLfloatArray() const
		{
			static GLfloat result[16];
			memset(result, 0, sizeof(result));

			
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					result[i * 4 + j] = (GLfloat)matrix[i][j];
				}
			}
				
				
			result[15] = 1.0f;  

			return result;
		}

	protected:
		double matrix[3][3];

	};

	class TranslationMatrix : public TransformationMatrix
	{
	public:
		TranslationMatrix(ivec2 translate);
		TranslationMatrix(vec2  translate);
	};


	class ScaleMatrix : public TransformationMatrix
	{
	public:
		ScaleMatrix(double scale);
		ScaleMatrix(vec2   scale);
	};


	class RotationMatrix : public TransformationMatrix
	{
	public:
		RotationMatrix(double theta);
	};

}