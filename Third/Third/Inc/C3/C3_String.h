#ifndef __C3_STRING_H__
#define __C3_STRING_H__

#define C3_STR_INIT_SIZE 32
#define C3_STR_GROW_SIZE 8

namespace C3 {

//-----------------------------------------------------------------------------
//==============================================================================
//
// String
//

class String {

public:

/// @name Con-/Destruction
//@{
	/// default constructor
	inline String()
		: _capacity(0), _chars(0) { resize(); }

	/// c-string construtor
    inline String(const char *c_str)
		: _capacity(0), _chars(0) { *this = c_str; }

	/// copy constructor
	inline String(const String &str)
		: _capacity(0), _chars(0) { *this = str; }

	/// virtual destructor
	virtual ~String() { if (_chars) delete [] _chars; }
//@}

/// @name Char Access
//@{
	/// returns const chars - use const_cast<char*>(chars()) for the evil stuff
	inline const char *chars() const { return _chars; }

	/// returns const reference to char #n - make sure to stay in range [0..length() or capacity())
	inline const char &operator[](unsigned int n) const { return _chars[n]; }

	/// returns reference to char #n - make sure to stay in range [0..length() or capacity())
	inline char &operator[](unsigned int n) { return _chars[n]; }
//@}

	/// returns actual number of chars (should equal strlen())
	inline unsigned int length() const { return (_chars)?len(_chars):0; }
	/// returns total capacity of chars including terminating zero
	inline unsigned int capacity() const { return _capacity; }

/// @name Capacity Adjustment
//@{
	/// resizes string's capacity to at least n chars
	unsigned int resize(unsigned int n = 0);

	/// grows string's capacity to at least n chars - no effect if n < capacity()
	inline unsigned int grow(unsigned int n) { return (n > capacity()) ? resize(n) : capacity(); }
//@}

/// @name Concatenation & Assignment
//@{
	const String operator+(const char *c_str);
	inline const String operator+(const String &str) { return *this + str.chars(); }

	const String &operator+=(const char *c_str);
	inline const String &operator+=(const String &str) { return *this += str.chars(); }

	const String &operator=(const char *c_str);
	inline const String &operator=(const String &str) { return *this = str.chars(); }
//@}

/// @name Comparison
//@{
	inline bool operator==(const char *c_str) const { return cmp(chars(), c_str) == 0; }
	inline bool operator==(const String &str) const { return *this == str.chars(); }

	inline bool operator!=(const char *c_str) const { return cmp(chars(), c_str) != 0; }
	inline bool operator!=(const String &str) const { return *this != str.chars(); }
//@}

/// @name Lexicographical Comparison
//@{
	inline bool operator<(const char *c_str) const { return cmp(chars(), c_str) < 0; }
	inline bool operator<(const String &str) const { return *this < str.chars(); }

	inline bool operator<=(const char *c_str) const { return cmp(chars(), c_str) <= 0; }
	inline bool operator<=(const String &str) const { return *this <= str.chars(); }

	inline bool operator>=(const char *c_str) const { return cmp(chars(), c_str) >= 0; }
	inline bool operator>=(const String &str) const { return *this >= str.chars(); }

	inline bool operator>(const char *c_str) const { return cmp(chars(), c_str) > 0; }
	inline bool operator>(const String &str) const { return *this > str.chars(); }
//@}

/// @name Standard C-String Methods
//@{
	/// should equal strlen()
	static inline unsigned int len(const char *c_str) {
		unsigned int i(0);
		while (c_str[i]) ++i;
		return i;
	}

	/// should equal strcmp()
	static inline int cmp(const char *c_str1, const char *c_str2) {
		unsigned int i(0);
		while (c_str1[i] && c_str2[i] && (c_str1[i] == c_str2[i])) ++i;
		return (int)((unsigned char)c_str1[i]) - ((unsigned char)c_str2[i]);
	}

	/// should equal strcpy()
	static inline void cpy(char *c_str1, const char *c_str2) {
		unsigned int i(0);
		do {
			c_str1[i] = c_str2[i];
			++i;
		} while (c_str1[i-1]);
	}
//@}

private:

	inline unsigned int align_capacity(unsigned int n) {
		// return max(min(initial size, n), initial size + next multiple of grow size)
		return (n<=C3_STR_INIT_SIZE)?C3_STR_INIT_SIZE:(((n/C3_STR_GROW_SIZE)+1)*C3_STR_GROW_SIZE);
	}

private:
    
	unsigned int _capacity; // including terminating '\0'
	char         *_chars;
};

//-----------------------------------------------------------------------------

}; // namespace C3

#endif __C3_STRING_H__
