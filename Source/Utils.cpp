#include <cmath>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include "Utils.h"

// Common Utilities
const QDir Utils::SeekDir(const QString &dirName, unsigned int upLevels) 
{
	QDir dir(QCoreApplication::applicationDirPath());
	for (unsigned int i = 0; i < upLevels && !dir.cd(dirName); ++i, dir.cdUp());
	return (dir.dirName() == dirName) ? dir : QDir(dirName);
}

// Trigonometry
const float MathUtils::toDegrees(const float radians)
{
	return radians * 180.0f / pi;
}
const float MathUtils::toRadians(const float degrees)
{
	return degrees * pi / 180.0f;
}

// Sine/cosine
const float MathUtils::cosine(float angle, bool radians)
{
	if(radians)
	{
		return cos(angle);
	}
	else
	{
		return cos(toRadians(angle));
		/*
		angle -= ((int)angle/360)*360; // -360.0 - 360.0 (float mod)
		if(angle < 0.0f) angle += 360.0f; // 0 - 360.0

		// cos function works with radians, and only for the first quadrant
		int sig = 1;

		// quad2
		if((angle > 90.0f)&&(angle <= 180.0f)) {
			sig = -1;
			angle = (180.0f - angle);
		}
		// quad3
		if((angle > 180.0f)&&(angle <= 270.0f)) {
			sig = -1;
			angle = (angle - 180.0f);
		}
		// quad4
		if((angle > 270.0f)&&(angle <= 360.0f)) angle = (360.0f - angle);

		return (float)(sig*cos(toRadians(angle)));
		*/
	}
}

const float MathUtils::sine(float angle, bool radians)
{
	if(radians)
	{
		return sin(angle);
	}
	else
	{
		return sin(toRadians(angle));
		/*
		angle -= ((int)angle/360)*360; // -360.0 - 360.0 (float mod)
		if(angle < 0.0f) angle += 360.0f; // 0 - 360.0

		// sin function works with radians, and only for the first quadrant
		int sig = 1;

		// quad2
		if((angle > 90.0f)&&(angle <= 180.0f)) angle = (180.0f - angle);
		// quad3
		if((angle > 180.0f)&&(angle <= 270.0f)) {
			sig = -1;
			angle = (angle - 180.0f);
		}
		// quad4
		if((angle > 270.0f)&&(angle <= 360.0f)) {
			sig = -1;
			angle = (360.0f - angle);
		}

		return (float)(sig*sin(toRadians(angle)));
		*/
	}
}