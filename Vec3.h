#if !defined(_VEC3_H_)
#define _VEC3_H_

#if !defined(Assert)
#define Assert( _exp ) ((void)0)
#endif 

#if !defined(CHECK_VALID)
#define CHECK_VALID( _v)	Assert( (_v).isValid() )
#endif

 
#if defined (__GNUC__) || defined (__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined (_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

#include <iostream>
#include <cmath>

template <typename T>
class Vec3
{
public:
    
	union
	{
		T vecArray[3] __attribute__ ((aligned (16)));
		struct
		{
			T x;
			T y;
			T z;
		} vecStruct;
	} vecUnion;
	
	Vec3<T>(void);
    Vec3<T>(T i);
	Vec3<T>(T X, T Y, T Z);
	void Init(T ix = 0.f, T iy = 0.f, T iz = 0.f);
	FORCE_INLINE T 			operator[](int i) const;
	FORCE_INLINE T & 		operator[](int i);
    FORCE_INLINE Vec3<T> & 	operator++();
    FORCE_INLINE Vec3<T> 	operator++(int);
	FORCE_INLINE Vec3<T> & 	operator--();
    FORCE_INLINE Vec3<T> 	operator--(int);
	FORCE_INLINE bool 		operator==(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator!=(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator>(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator>(T s) const;
	FORCE_INLINE bool 		operator<(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator<(T s) const;
	FORCE_INLINE bool 		operator>=(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator>=(T s) const;
	FORCE_INLINE bool 		operator<=(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator<=(T s) const;
	FORCE_INLINE Vec3<T> &	operator+=(const Vec3<T> & v);
	FORCE_INLINE Vec3<T> &	operator+=(T fl);
	FORCE_INLINE Vec3<T> &	operator-=(const Vec3<T> & v);
	FORCE_INLINE Vec3<T> &	operator-=(T fl);
	FORCE_INLINE Vec3<T> &	operator*=(const Vec3<T> & v);
	FORCE_INLINE Vec3<T> &	operator*=(T s);
	FORCE_INLINE Vec3<T> &	operator/=(const Vec3<T> & v);
	FORCE_INLINE Vec3<T> &	operator/=(T s);
	FORCE_INLINE Vec3<T> & 	operator=(const Vec3<T> & vOther);
	FORCE_INLINE Vec3<T>	operator+(const Vec3<T> & v) const;
	FORCE_INLINE Vec3<T>	operator-(const Vec3<T> & v) const;
	FORCE_INLINE Vec3<T>	operator*(const Vec3<T> & v) const;
	FORCE_INLINE Vec3<T>	operator/(const Vec3<T> & v) const;
	FORCE_INLINE Vec3<T>	operator+(T fl) const;
	FORCE_INLINE Vec3<T>	operator-(T fl) const;
	FORCE_INLINE Vec3<T>	operator*(T fl) const;
	FORCE_INLINE Vec3<T>	operator/(T fl) const;
	FORCE_INLINE void	Zero();
	FORCE_INLINE bool	isValid() const;
	FORCE_INLINE T	Length() const;
	FORCE_INLINE T	LengthSqr(void) const;
	FORCE_INLINE bool	IsZero(const T tolerance = 0.01f) const;
	FORCE_INLINE void	NormalizeInPlace();
	FORCE_INLINE T	DistToSqr(const Vec3<T> & vOther) const;
	FORCE_INLINE T  DistTo(const Vec3<T> & vOther) const;
	FORCE_INLINE T	Dot(const Vec3<T> & vOther) const;
	FORCE_INLINE T	Length2D(void) const;
	FORCE_INLINE T	Length2DSqr(void) const;
	

    friend std::ostream & operator<<(std::ostream & os, const Vec3<T> & v) 
    {
        return os << v.vecUnion.vecStruct.x << ' ' << v.vecUnion.vecStruct.y << ' ' << v.vecUnion.vecStruct.z;
	}
	
};

template <typename T>
inline bool Vec3<T>::isValid() const
{
	return std::isfinite(vecUnion.vecStruct.x) && std::isfinite(vecUnion.vecStruct.y) && std::isfinite(vecUnion.vecStruct.z);
}


template <typename T>
inline void Vec3<T>::Init(T ix, T iy, T iz)
{
	vecUnion.vecStruct.x = ix; 
    vecUnion.vecStruct.y = iy; 
    vecUnion.vecStruct.z = iz;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z)
{
	vecUnion.vecStruct.x = X;
    vecUnion.vecStruct.y = Y; 
    vecUnion.vecStruct.z = Z;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T i)
{
	vecUnion.vecStruct.x = i; 
    vecUnion.vecStruct.y = i; 
    vecUnion.vecStruct.z = i;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(void)
{
	vecUnion.vecStruct.x = 0; 
    vecUnion.vecStruct.y = 0; 
    vecUnion.vecStruct.z = 0;
}

template <typename T>
inline void Vec3<T>::Zero()
{
    vecUnion.vecStruct.x = 0.f;
    vecUnion.vecStruct.y = 0.f; 
    vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline void Clear(Vec3<T>& a)
{
	a.vecUnion.vecStruct.x = 0.f;
    a.vecUnion.vecStruct.y = 0.f; 
    a.vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline Vec3<T> & Vec3<T>::operator++()
{
    ++vecUnion.vecStruct.x;
    ++vecUnion.vecStruct.y;
    ++vecUnion.vecStruct.z;
    return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator++(int)
{
    Vec3<T> temp = *this;
    ++vecUnion.vecStruct.x;
    ++vecUnion.vecStruct.y;
    ++vecUnion.vecStruct.z;
    return temp;
}

template <typename T>
inline Vec3<T> & Vec3<T>::operator--()
{
    --vecUnion.vecStruct.x;
    --vecUnion.vecStruct.y;
    --vecUnion.vecStruct.z;
    return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator--(int)
{
    Vec3<T> temp = *this;
    --vecUnion.vecStruct.x;
    --vecUnion.vecStruct.y;
    --vecUnion.vecStruct.z;
    return temp;
}

template <typename T>
inline Vec3<T>& Vec3<T>::operator=(const Vec3<T> &vOther)
{
	CHECK_VALID(vOther);
	vecUnion.vecStruct.x = vOther.vecUnion.vecStruct.x; 
	vecUnion.vecStruct.y = vOther.vecUnion.vecStruct.y; 
	vecUnion.vecStruct.z = vOther.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
inline T& Vec3<T>::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline T Vec3<T>::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.vecUnion.vecStruct.x == vecUnion.vecStruct.x) && (src.vecUnion.vecStruct.y == vecUnion.vecStruct.y) && (src.vecUnion.vecStruct.z == vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.vecUnion.vecStruct.x != vecUnion.vecStruct.x) && (src.vecUnion.vecStruct.y != vecUnion.vecStruct.y) && (src.vecUnion.vecStruct.z != vecUnion.vecStruct.z);
}

/*
	FORCE_INLINE bool 		operator>(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator>(T s) const;
	FORCE_INLINE bool 		operator<(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator<(T s) const;
	FORCE_INLINE bool 		operator>=(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator>=(T s) const;
	FORCE_INLINE bool 		operator<=(const Vec3<T> & v) const;
	FORCE_INLINE bool 		operator<=(T s) const;
*/

template <typename T>
inline bool Vec3<T>::operator>(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) > (src.vecUnion.vecStruct.x + src.vecUnion.vecStruct.y + src.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator>(T s) const
{
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) > s;
}

template <typename T>
inline bool Vec3<T>::operator<(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) < (src.vecUnion.vecStruct.x + src.vecUnion.vecStruct.y + src.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator<(T s) const
{
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) < s;
}

template <typename T>
inline bool Vec3<T>::operator>=(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) >= (src.vecUnion.vecStruct.x + src.vecUnion.vecStruct.y + src.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator>=(T s) const
{
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) >= s;
}

template <typename T>
inline bool Vec3<T>::operator<=(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) <= (src.vecUnion.vecStruct.x + src.vecUnion.vecStruct.y + src.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator<=(T s) const
{
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) <= s;
}

template <typename T>
FORCE_INLINE void Copy(const Vec3<T>& src, Vec3<T>& dst)
{
	CHECK_VALID(src);
	dst.vecUnion.vecStruct.x = src.vecUnion.vecStruct.x;
	dst.vecUnion.vecStruct.y = src.vecUnion.vecStruct.y;
	dst.vecUnion.vecStruct.z = src.vecUnion.vecStruct.z;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	vecUnion.vecStruct.x += v.vecUnion.vecStruct.x; vecUnion.vecStruct.y += v.vecUnion.vecStruct.y; vecUnion.vecStruct.z += v.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	vecUnion.vecStruct.x -= v.vecUnion.vecStruct.x; vecUnion.vecStruct.y -= v.vecUnion.vecStruct.y; vecUnion.vecStruct.z -= v.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(T fl)
{
	vecUnion.vecStruct.x *= fl;
	vecUnion.vecStruct.y *= fl;
	vecUnion.vecStruct.z *= fl;
	CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	vecUnion.vecStruct.x *= v.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y *= v.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z *= v.vecUnion.vecStruct.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator+=(T fl)
{
	vecUnion.vecStruct.x += fl;
	vecUnion.vecStruct.y += fl;
	vecUnion.vecStruct.z += fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator-=(T fl)
{
	vecUnion.vecStruct.x -= fl;
	vecUnion.vecStruct.y -= fl;
	vecUnion.vecStruct.z -= fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	vecUnion.vecStruct.x *= oofl;
	vecUnion.vecStruct.y *= oofl;
	vecUnion.vecStruct.z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.f && v.y != 0.f && v.z != 0.f);
	vecUnion.vecStruct.x /= v.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y /= v.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z /= v.vecUnion.vecStruct.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
inline T Vec3<T>::Length(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqsr = vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y + vecUnion.vecStruct.z*vecUnion.vecStruct.z;

	#if defined (__GNUC__) || defined (__clang__)
    __asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqsr));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}
	#else
	return sqrt(sqsr);
	#endif

	return root;
}

template <typename T>
FORCE_INLINE T Vec3<T>::LengthSqr(void) const
{
	CHECK_VALID(*this);
	return (vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y + vecUnion.vecStruct.z*vecUnion.vecStruct.z);
}
 
template <typename T>
FORCE_INLINE bool Vec3<T>::IsZero(T tolerance) const
{
	return (vecUnion.vecStruct.x > -tolerance && vecUnion.vecStruct.x < tolerance &&
		vecUnion.vecStruct.y > -tolerance && vecUnion.vecStruct.y < tolerance &&
		vecUnion.vecStruct.z > -tolerance && vecUnion.vecStruct.z < tolerance);
}

template <typename T>
inline T Vec3<T>::Length2D(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqst = vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y;

	#if defined (__GNUC__) || defined (__clang__)
	__asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqst));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}
	#else
	return std::sqrt(sqsr);
	#endif
 
	return root;
}
 
template <typename T>
inline T Vec3<T>::Length2DSqr(void) const
{
	return (vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y);
}

template <typename T>
inline Vec3<T> CrossProduct(const Vec3<T>& a, const Vec3<T>& b)
{
	return Vec3<T>(a.vecUnion.vecStruct.y*b.vecUnion.vecStruct.z - a.vecUnion.vecStruct.z*b.vecUnion.vecStruct.y, a.vecUnion.vecStruct.z*b.vecUnion.vecStruct.x - a.vecUnion.vecStruct.x*b.vecUnion.vecStruct.z, a.vecUnion.vecStruct.x*b.vecUnion.vecStruct.y - a.vecUnion.vecStruct.y*b.vecUnion.vecStruct.x);
}
 
template <typename T>
T Vec3<T>::DistToSqr(const Vec3<T> &vOther) const
{
	Vec3<T> delta;
 
	delta.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	delta.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;
	delta.vecUnion.vecStruct.z = vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z;
 
	return delta.LengthSqr();
}

template <typename T>
FORCE_INLINE T Vec3<T>::DistTo(const Vec3<T> &vOther) const
{
	CHECK_VALID(*this);
	return std::sqrt((vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x)*(vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x)
					+ (vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y)*(vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y)
					+ (vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z)*(vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z));

}
 
template <typename T>
inline void Vec3<T>::NormalizeInPlace()
{
	Vec3<T>& v = *this;
 
	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON
 
	v.vecUnion.vecStruct.x *= iradius;
	v.vecUnion.vecStruct.y *= iradius;
	v.vecUnion.vecStruct.z *= iradius;
    
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z + v.vecUnion.vecStruct.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z - v.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator+(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z + fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator-(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z - fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * v.vecUnion.vecStruct.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / v.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline T Vec3<T>::Dot(const Vec3<T>& vOther) const
{
	const Vec3<T>& a = *this;
 
	return(a.vecUnion.vecStruct.x*vOther.vecUnion.vecStruct.x + a.vecUnion.vecStruct.y*vOther.vecUnion.vecStruct.y + a.vecUnion.vecStruct.z*vOther.vecUnion.vecStruct.z);
}

#endif //_VEC3_H_