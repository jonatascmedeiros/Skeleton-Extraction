#ifndef __C3_ARRAY_H__
#define __C3_ARRAY_H__

#include <C3_Math.h>

namespace C3 {

//-----------------------------------------------------------------------------
//==============================================================================
//
// Array
//

template<typename T>
class Array {

public:

/// @name Con-/Destruction
//@{
	/// default constructor
	inline Array(unsigned int length = 0)
		: _length(0), _data(0) { resize(length); }

	/// copy constructor
	inline Array(const Array &a)
		: _length(0), _data(0) { *this = a; }

	/// virtual destructor
	virtual ~Array() { if (_data) delete [] _data; }
//@}

/// @name Content Access
//@{
	/// returns const T* - use const_cast<T*>(data()) for the evil stuff
	inline const T *data() const { return _data; }

	/// returns const reference to T #n - make sure to stay in range [0..length())
	inline const T &operator[](unsigned int n) const { return _data[n]; }

	/// returns reference to T #n - make sure to stay in range [0..length())
	inline T &operator[](unsigned int n) { return _data[n]; }
//@}

	inline unsigned int length() const { return _length; }

/// @name Length Adjustment
//@{
	/// resizes array to n items
	inline unsigned int resize(unsigned int n) {
		// allocate new items
		T *data = new T[n];
		// _data is normally nonzero, but we have
		// to check it, since we might get called
		// by some constructor...
		if (_data) {
			// compute number of items to retain
			unsigned int r(Math::min<unsigned int>(n, _length));
			// retain items
			for (unsigned int i(0); i < r; ++i) {
				data[i] = _data[i];
			}
			// dispose old items
			delete [] _data;
		}
		// assign new items
		_data = data;
		// assign new length & return it
		return _length = n;
	}

	/// grows array to n items - no effect if n <= length()
	inline unsigned int grow(unsigned int n) {
		return (n > _length) ? resize(n) : _length;
	}
//@}

/// @name Assignment
//@{
	inline const Array &operator=(const Array &a) {
		resize(a._length);
		for (unsigned int i = 0; i < _length; ++i) {
			_data[i] = a._data[i];
		}
		return *this;
	}
//@}

private:

	unsigned int _length;
	T            *_data;
};

//-----------------------------------------------------------------------------

}; // namespace C3

#endif __C3_ARRAY_H__
