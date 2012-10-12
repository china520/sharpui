# ifndef _MULTISTR_H_
# define _MULTISTR_H_

#include <suicore/uicoreconfig.h>

class SUICORE_API Multistr
{
public:

  	typedef size_t size_type;

	static const size_type npos;

	Multistr();

	Multistr(const Multistr & copy);
	explicit Multistr(const char * copy);
    explicit Multistr(const wchar_t * copy, int code=1);
	explicit Multistr(const char * str, size_type len);

	~Multistr();

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

	Multistr& assign(const char* str, size_type len);
	Multistr& append(const char* str, size_type len);
	void swap (Multistr& other);

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

inline const char * Multistr::c_str() const 
{ 
    return _rep->str; 
}

inline const char * Multistr::data() const 
{ 
    return _rep->str; 
}

inline Multistr::size_type Multistr::length() const 
{ 
    return _rep->size; 
}

inline Multistr::size_type Multistr::size() const 
{ 
    return _rep->size; 
}

inline bool Multistr::empty() const 
{ 
    return _rep->size == 0; 
}

inline Multistr::size_type Multistr::capacity() const 
{ 
    return _rep->capacity; 
}

inline void Multistr::init(size_type sz) 
{ 
    init(sz, sz); 
}

inline void Multistr::set_size(size_type sz) 
{ 
    _rep->str[_rep->size=sz] = '\0'; 
}

inline char* Multistr::start() const 
{ 
    return _rep->str; 
}

inline char* Multistr::finish() const 
{ 
    return _rep->str + _rep->size; 
}

inline void Multistr::swap(Multistr& other)
{
    Rep* r = _rep;
    _rep = other._rep;
    other._rep = r;
}

#endif

