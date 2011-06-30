#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <QQueue>
#include <QStack>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QFileInfoList>
#include <QTime>

#ifdef _MSC_VER
#undef min
#undef max
#endif

// Common Utilities
namespace Utils
{
	inline const QString TimeStamp() { return QTime::currentTime().toString("hh:mm:ss.zzz"); }
	const QDir SeekDir(const QString &dirname, unsigned int upLevels);
}

// Math Utilities
namespace MathUtils
{
	// Defines
	const double epsilon = 0.0001;
	const double pi = 3.14159265359;

	// Trigonometry
	const float toDegrees(const float radians);
	const float toRadians(const float degrees);
	const float cosine(float angle, bool radians);
	const float sine(float angle, bool radians);

};

#endif // __UTILITIES_H
