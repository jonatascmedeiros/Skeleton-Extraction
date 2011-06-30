/*
=================================================
Mathematics.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	06/03/2009
=================================================
*/

#ifndef __MATHEMATICS_H
#define __MATHEMATICS_H

#include "definitions.h"
#include <cmath>

namespace RX
{
	class Math
	{
	public:
		// Constants
		static const int infinity;
		static const float pi;
		static const float epsilon;
		
		// Degrees/radians convertion
		static const float toDegrees(const float radians);
		static const float toRadians(const float degrees);

		// Sine/cosine
		static const float cosine(const float degrees);
		static const float sine(const float degrees);

		// Arcsine/arccosine
		static const float arccosine(const float sin, const float cos);
		static const float arcsine(const float sin, const float cos);
	};
};

#endif // __MATHEMATICS_H
