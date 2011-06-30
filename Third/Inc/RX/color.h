/*
=================================================
color.h
-------------------------------------------------
Author:			Rosália Galiazzi Schneider
Last Modified:	13/05/2009
=================================================
*/

#ifndef __COLOR_H
#define __COLOR_H

#include <iostream>
#include <cmath>
#include "mat4.h"

namespace RX
{

class color
{
public:
	// Create/destroy
	color();
	color(float r, float g, float b);
	color(const vec3 &v);
	color(const color &c);

	// Addition/Subtraction/Copy
	color operator+(const color &v) const;
	color operator+=(const color &v);
	color operator-(const color &v) const;
	color operator-=(const color &v);
	color operator=(const color &v);

	// Multiplication by scalar
	color operator*=(const float &f);

	// Gets
	float const *floats() const { return &r; }
	float operator[](int id) const;

	// Color conversion matrices
	// from RGB to XYZ (white reference D65)
	static const mat4 gRGBtoXYZ;
	static const mat4 gXYZtoRGB;

	// from RGB to XYZ specified by Judd-Vos (1878)
	static const mat4 gRGBtoXYZ_Judd_Vos_1978;
	static const mat4 gXYZtoRGB_Judd_Vos_1978;

	// from RGB to YUV
	static const mat4 gRGBtoYUV;
	static const mat4 gYUVtoRGB;

	// from RGB to YIQ
	static const mat4 gRGBtoYIQ;
	static const mat4 gYIQtoRGB;

	// from RGB to YCbCr
	static const mat4 gRGBtoYCbCr;
	static const mat4 gYCbCrToRGB;

	// from RGB to YPQ specified by Grundland and Dogson (2007)
	static const mat4 gRGBtoYPQ_Grundland_2007;
	static const mat4 gYPQtoRGB_Grundland_2007;

	// from RGB to LMS specified by Brettel et al. (1997)
	static const mat4 gRGBtoLMS_Brettel_1997;
	static const mat4 gLMStoRGB_Brettel_1997;

	// from RGB to LMS specified by Reinhaerd et al. (2001)
	static const mat4 gRGBtoLMS_Reinhard_2001;
	static const mat4 gLMStoRGB_Reinhard_2001;

	// from LMS to LAlphaBeta specified by Ruderman et al. (1998)
	static const mat4 gLMStoLAlphaBeta_Ruderman_1998;
	static const mat4 gLAlphaBetaToLMS_Ruderman_1998;

public:
	float r, g, b;
};

};

#endif // __vec4_H

