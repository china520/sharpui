# ifndef _MULTISTR_H_
# define _MULTISTR_H_

#include <suic/uicoreconfig.h>

class SUICORE_API AsciiStr
{
public:

  	typedef unsigned int size_type;

    static const size_type npos;

	AsciiStr();
	AsciiStr(const AsciiStr & copy);

	AsciiStr(const char * copy);
    AsciiStr(const wchar_t * copy, int code = 1);
	AsciiStr(const char * str, size_type len);

	~AsciiStr();

    void SetCode(int code);
    int GetCode() const;

	const char* c_str() const;
	const char* data() const;
	size_type length() const;
	size_type size() const;
	bool empty() const;
	size_type capacity() const;

	char& operator[](size_type index) const
	{
		assert(index < length());
		return _rep->str[index];
	}

	size_type find(char lookup) const;
	size_type find(char tofind, size_type offset) const;

	void clear();

	void reserve(size_type cap);

	AsciiStr& assign(const char* str, size_type len);
	AsciiStr& append(const char* str, size_type len);

	void swap (AsciiStr& other);

private:

	void init(size_type sz);
	void set_size(size_type sz);
	char* start() const;
	char* finish() const;

	void init(size_type sz, size_type cap);
	void quit();

private:

    struct Rep
    {
        size_type size;
        size_type capacity;
        char str[1];
    };

    int _code;
	Rep * _rep;
	static Rep _nullrep;
};

inline const char * AsciiStr::c_str() const 
{ 
    return _rep->str; 
}

inline const char * AsciiStr::data() const 
{ 
    return _rep->str; 
}

inline AsciiStr::size_type AsciiStr::length() const 
{ 
    return _rep->size; 
}

inline AsciiStr::size_type AsciiStr::size() const 
{ 
    return _rep->size; 
}

inline bool AsciiStr::empty() const 
{ 
    return _rep->size == 0; 
}

inline AsciiStr::size_type AsciiStr::capacity() const 
{ 
    return _rep->capacity; 
}

inline void AsciiStr::init(size_type sz) 
{ 
    init(sz, sz); 
}

inline void AsciiStr::set_size(size_type sz) 
{ 
    _rep->str[_rep->size=sz] = '\0'; 
}

inline char* AsciiStr::start() const 
{ 
    return _rep->str; 
}

inline char* AsciiStr::finish() const 
{ 
    return _rep->str + _rep->size; 
}

inline void AsciiStr::swap(AsciiStr& other)
{
    Rep* r = _rep;
    _rep = other._rep;
    other._rep = r;
}

#endif

