#ifndef _DOLCESDK_PSP2_JSON_H_
#define _DOLCESDK_PSP2_JSON_H_

#define SCE_JSON_ERROR_PARSE_INVALID_CHAR		(-2137915135) // 0x80920101
#define SCE_JSON_ERROR_NOMEM					(-2137915134) // 0x80920102
#define SCE_JSON_ERROR_NOFILE					(-2137915133) // 0x80920103
#define SCE_JSON_ERROR_NOROOT					(-2137915132) // 0x80920104
#define SCE_JSON_ERROR_NOBUF					(-2137915131) // 0x80920105
#define SCE_JSON_ERROR_NOINIT					(-2137915120) // 0x80920110
#define SCE_JSON_ERROR_MULTIPLEINIT				(-2137915119) // 0x80920111
#define SCE_JSON_ERROR_INVALID_ARGUMENT			(-2137915118) // 0x80920112

#ifdef __cplusplus

#include <stdint.h>
#include <stddef.h>

namespace sce{
namespace Json{

typedef enum ValueType
{
	kValueTypeNull = 0,
	kValueTypeBoolean,
	kValueTypeInteger,
	kValueTypeUInteger,
	kValueTypeReal,
	kValueTypeString,
	kValueTypeArray,
	kValueTypeObject,
} ValueType;

class MemAllocator
{
public:
	MemAllocator();
	virtual ~MemAllocator();

#ifdef __psp2__
#pragma diag_push
#pragma diag_suppress 2261
#endif
	virtual void*	allocate(size_t size, void *userData) =0;
#ifdef __psp2__
#pragma diag_pop
#endif

	virtual void	deallocate(void *ptr, void *userData) =0;
	virtual void	notifyError (int32_t error, size_t size, void* userData );
};

class InitParameter
{
public:
	InitParameter()
		: allocator(0), userData(0), filebuffersize(0) {}

	InitParameter(MemAllocator *al, void *ud, size_t fbsiz)
		: allocator(al), userData(ud), filebuffersize(fbsiz) {}

	MemAllocator*	allocator;
	void*			userData;
	size_t			filebuffersize;
};

class Initializer
{
public:
	Initializer();
	~Initializer();
	int initialize(const InitParameter* initparam);
	int terminate();

	typedef void (*AllocatorInfoFunction)(int32_t infono, ValueType accesstype, void* context);
	static	int32_t setAllocatorInfoCallBack(AllocatorInfoFunction func, void* context);

private:
	bool			initstatus;
};

class Value;
class Parser;
class InputStream;
struct RootParam;
class ImplAccessor;

class String
{
public:
	String();
	String(const char*);
	String(const String&);
	~String();

	int32_t compare( const String& ) const;
	int32_t compare( const char* ) const;
	size_t size() const;
	size_t length() const;
	unsigned char at(size_t pos) const;
	bool empty() const;
	const char* c_str() const;

	String& append( const String& );
	String& append( const char* );
	String& append( const char*, size_t );

	void clear();

	size_t find (const String& str, size_t pos = 0) const;
	size_t find (const char* s, size_t pos = 0) const;
	size_t find (const char* s, size_t pos, size_t n) const;
	size_t find (char c, size_t pos = 0) const;
	size_t rfind (const String& str, size_t pos = npos) const;
	size_t rfind (const char* s, size_t pos = npos) const;
	size_t rfind (const char* s, size_t pos, size_t n) const;
	size_t rfind (char c, size_t pos = npos) const;
	void resize (size_t n);
	String substr (size_t pos = 0, size_t len = npos) const;

	bool operator==(const String&) const;
	bool operator==(const char*) const;

	String& operator=(const String&);
	String& operator+=(const char*);
	String& operator+=(unsigned char);

	static const size_t npos;

friend class ImplAccessor;
private:
	void* m_impl;
};

class Array
{

public:
	class iterator{
	public:
		iterator();
		iterator(const iterator&);
		~iterator();

		bool operator!= (iterator) const;
		Value* operator-> () const;
		Value& operator* () const;

		iterator& operator ++ ();
		iterator& operator ++ (int);

		void advance(size_t off);

		iterator& operator = (const iterator&);

	friend class ImplAccessor;
	private:
		void* m_itimpl;
	};

	typedef iterator const_iterator;

public:
	Array();
	Array(const Array&);
	~Array();

	iterator begin() const;
	iterator end() const ;
	iterator insert(const iterator&, const Value&);
	iterator erase(const iterator&);
	Value& back() const;

	void clear();
	size_t size() const ;
	void push_back( const Value &val );
	void pop_back();
	bool empty() const;



	Array& operator=(const Array&);

friend class ImplAccessor;
private:
	void* m_impl;


};

class Object;
class Value
{
	friend class Parser;

private:
	Value*			m_parent;
	RootParam*		m_rootparam;
	union {
		bool		m_boolean;
		int64_t		m_integer;
		uint64_t	m_uinteger;
		double		m_real;
		String*		m_string;
		Array*		m_array;
		Object*		m_object;
	};
	char _padding[4];
	ValueType		m_type;
public:
	~Value();
	Value();
	Value(ValueType type);
	Value(bool b);
	Value(int64_t l);
	Value(uint64_t ul);
	Value(double n);
	Value(const String& s);
	Value(const Array& a);
	Value(const Object& o);
	Value(const Value& x);

	Value& operator=(const Value& x);
	operator bool() const;

	String toString() const
	{
		String str;
		toString(str);
		return str;
	}
	void toString(String& dst) const;

	typedef const Value& (*NullAccessFunction)(ValueType accesstype, const Value* parent, void* context);
	typedef int32_t (*DataReceiveFunction)(String& buf, void* userdata);
	int32_t serialize(String& buf, DataReceiveFunction func, void *userdata);
	int32_t serialize(String& dst);

	void swap(Value& rhs);
	void clear();

	void set(ValueType type);
	void set(bool b);
	void set(int64_t l);
	void set(uint64_t ul);
	void set(double n);
	void set(const String& s);
	void set(const Array& a);
	void set(const Object& o);
	void set(const Value& x);

	static const String* s_nullstring;
	static const Array* s_nullarray;
	static const Object* s_nullobject;
	static const int64_t s_nullinteger;
	static const uint64_t s_nulluinteger;
	static const double s_nullreal;
	static const bool s_nullbool;

	ValueType		getType() const;

	String*			referString();
	Array*			referArray();
	Object*			referObject();
	int64_t*		referInteger();
	uint64_t*		referUInteger();
	double*			referReal();
	bool*			referBoolean();

	Value*			referValue(size_t index);
	Value*			referValue(const String& key);

	const String&	getString() const;
	const Array&	getArray() const;
	const Object&	getObject() const;
	const int64_t&	getInteger() const;
	const uint64_t&	getUInteger() const;
	const double&	getReal() const;
	const bool&		getBoolean() const;

	const Value&	getValue(size_t index) const;
	const Value&	getValue(const String& key) const;
	const Value&	operator[](size_t index) const;
	const Value&	operator[](const String& key) const;
	const Value&	operator[](const char *key) const;

	int32_t	count() const;

	int32_t setNullAccessCallBack(NullAccessFunction func, void* context);

private:
	void setParent(const Value* parent);
	const Value* getRoot() const;
	int32_t serialize_internal(String& buf, DataReceiveFunction func, void *userdata, Value* parent=NULL);
};


class Object
{
public:
	class Pair{
	public:
		Pair();
		Pair(const String& srcstr, const Value& srcval);
		~Pair();

	public:
		String	first;
		char _padding[4];
		Value	second;
	};

	class iterator{
	public:
		iterator();
		iterator(const iterator&);
		~iterator();

		bool operator == (iterator) const;
		bool operator != (iterator) const;

		iterator& operator ++ ();
		iterator& operator ++ (int);

		Pair* operator -> () const;
		Pair& operator * () const;

		iterator& operator = (const iterator&);

		void advance(size_t off);

	friend class ImplAccessor;
	private:
		void* m_itimpl;
	};

	typedef iterator const_iterator;

public:
	Object();
	Object(const Object&);

	~Object();

	size_t size() const;

	iterator begin() const ;
	iterator end() const ;
	iterator find(const String& key) const ;
	iterator insert(const Pair& objpair);
	void erase(const String& key);
	void clear();
	bool empty() const;

	Value& operator[] (const String& key);
	Object& operator=(const Object&);

friend class ImplAccessor;
private:
	void* m_impl;
};

class Parser
{
public:
	typedef int32_t (*DataProvideFunction)(char& data, void* userdata);
	static int32_t parse(Value& dst, DataProvideFunction func, void *userdata);
	static int32_t parse(Value& dst, const char *src, size_t siz_src);
	static int32_t parse(Value& dst, const char *path);

private:
	static int  parseQuadHex(InputStream& is);
	static bool parseCodePoint(String& str, InputStream& is);
	static bool parseString(String& s, InputStream& is);
	static bool parseArray(Value& v, InputStream& is, Value* parent);
	static bool parseObject(Value& v, InputStream& is, Value* parent);
	static bool parseString(Value& v, InputStream& is, Value* parent);
	static bool parseNumber(Value& v, InputStream& is, Value* parent);
	static bool parseValue(Value& v, InputStream& is, Value* parent);

};

} // namespace Json
} // namespace sce

#endif /* __cplusplus */

#endif // _DOLCESDK_PSP2_JSON_H_
