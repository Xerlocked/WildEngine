#pragma once

//~ Windows.h
#define _TCHAR_DEFINED  // TCHAR 재정의 에러 때문
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#undef max
#undef min

#ifdef TEXT             // Windows.h의 TEXT를 삭제
    #undef TEXT
#endif
//~ Windows.h

/**
* Windows specific types
**/
struct FWindowsPlatformTypes
{
#ifdef _WIN64
    typedef unsigned __int64	SIZE_T;
#else
    typedef unsigned long		SIZE_T;
#endif
};

#define USE_WIDECHAR 0

#if USE_WIDECHAR 
#define TEXT(x) L##x
#else
#define TEXT(x) x
#endif

typedef char ANSICHAR;
typedef wchar_t WIDECHAR;

#if USE_WIDECHAR
typedef WIDECHAR TCHAR;
#else
typedef ANSICHAR TCHAR;
#endif


// Unsigned base types.
typedef unsigned char 		uint8;		// 8-bit  unsigned.
typedef unsigned short int	uint16;		// 16-bit unsigned.
typedef unsigned int		uint32;		// 32-bit unsigned.
typedef unsigned long long	uint64;		// 64-bit unsigned.

// Signed base types.
typedef	signed char			int8;		// 8-bit  signed.
typedef signed short int	int16;		// 16-bit signed.
typedef signed int	 		int32;		// 32-bit signed.
typedef signed long long	int64;		// 64-bit signed.

// Character types.
typedef char				ANSICHAR;	// An ANSI character       -                  8-bit fixed-width representation of 7-bit characters.
typedef wchar_t				WIDECHAR;	// A wide character        - In-memory only.  ?-bit fixed-width representation of the platform's natural wide character set.  Could be different sizes on different platforms.
typedef uint8				CHAR8;		// An 8-bit character type - In-memory only.  8-bit representation.  Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint16				CHAR16;		// A 16-bit character type - In-memory only.  16-bit representation.  Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint32				CHAR32;		// A 32-bit character type - In-memory only.  32-bit representation.  Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).

// 컴파일러별 인라인 함수 강제 매크로
#if defined(_MSC_VER)
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCEINLINE inline __attribute__((always_inline))
#else
#define FORCEINLINE inline
#endif

#if PLATFORM_WINDOWS
#define RESTRICT __restrict
#elif defined(__GNUC__) || defined(__clang__)
#define RESTRICT __restrict__
#else
#define RESTRICT
#endif

// C++11 이상의 지원 여부에 따른 constexpr 정의
#if __cplusplus >= 201103L
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif