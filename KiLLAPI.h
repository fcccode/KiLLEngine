
/***********************************************************************************************************************************
 *	File : "KiLLAPI.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_API_HPP__
#define __KiLL_API_HPP__



#undef _KILL_COMPILER_MVC
#undef _KILL_COMPILER_GNU
#undef _KILL_OS_WINDOWS
#undef _KILL_OS_LINUX
#undef _KILL_OS_APPLE



/*=================================================================================================================================
 * --- Compiler Check -----------------------------------------------------------------------------------------------------------*/

/* Microsoft Visual compiler ------------------------------------------------------*/
#if defined(_MSC_VER)
#	define _KILL_COMPILER_MVC		_MSC_VER
#	if !(_KILL_COMPILER_MVC >= 1600)
#		error "Microsoft Visual C++ compiler version is too old."
#	endif
#endif


/* GNUC Compiler ------------------------------------------------------------------*/
#if defined(__GNUC__)
#	define _KILL_COMPILER_GNU		__GNUC__
#	if !(_KILL_COMPILER_GNU >= 4)
#		error "GNU C++ compiler version is too old
#	endif
#endif


/* Compiler Error -----------------------------------------------------------------*/
#if !defined(_KILL_COMPILER_MVC) && !defined(_KILL_COMPILER_GNU)
#	error "Current compiler is not supported."
#elif defined(_KILL_COMPILER_MVC) && defined(_KILL_COMPILER_GNU)
#	error "Error with compiler preprocessor defines."
#endif





/*=================================================================================================================================
 * --- Compile time platform check ----------------------------------------------------------------------------------------------*/

/* Windows OS ---------------------------------------------------------------------*/
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)
#	define _KILL_OS_WINDOWS
#endif


/* Linux OS -----------------------------------------------------------------------*/
#if defined(linux) || defined(__linux) || defined(__linux__)
#	define _KILL_OS_LINUX
#endif


/* Apple OS -----------------------------------------------------------------------*/
#if defined(macintosh) || defined(__APPLE_CC__) || defined(__APPLE__) //
#	define _KILL_OS_APPLE
#endif


/* OS Error -----------------------------------------------------------------------*/
#if !defined(_KILL_OS_WINDOWS) && !defined(_KILL_OS_LINUX) && !defined(_KILL_OS_APPLE)
#	error "Current platform is not supported."
#elif defined(_KILL_OS_WINDOWS) && defined(_KILL_OS_LINUX) && defined(_KILL_OS_APPLE)
#	error "Error with compiler preprocessor defines."
#elif !defined(_KILL_OS_WINDOWS) && defined(_KILL_OS_LINUX) && defined(_KILL_OS_APPLE)
#	error "Error with compiler preprocessor defines."
#elif defined(_KILL_OS_WINDOWS) && !defined(_KILL_OS_LINUX) && defined(_KILL_OS_APPLE)
#	error "Error with compiler preprocessor defines."
#elif defined(_KILL_OS_WINDOWS) && defined(_KILL_OS_LINUX) && !defined(_KILL_OS_APPLE)
#	error "Error with compiler preprocessor defines."
#endif





/*=================================================================================================================================
 * --- KiLL Tech API ------------------------------------------------------------------------------------------------------------*/

/* External Dependencies ----------------------------------------------------------*/
#ifdef _KILL_OS_WINDOWS
#	include <windows.h>
#	include <emmintrin.h>
#	include <mmintrin.h>
#	include <intrin.h>
#	ifdef _D3DLIB
#		include <d3d10.h>
#		include <d3dx10.h>
#		pragma comment(lib, "d3d10.lib")
#		pragma comment(lib, "d3dx10.lib")
#	endif
#endif
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>




/* Microsoft Visual Compiler Settings ---------------------------------------------*/
#ifdef _KILL_COMPILER_MVC

#	define NULL 0

#	define UNIQUE __restrict
#	define INL __forceinline
#	define DLIB_EXP __declspec(dllexport)
#	define DLIB_IMP __declspec(dllimport)

#	define ALIGN_BYTE(x) __declspec(align(x))
#	define ALIGN_2BYTE __declspec(align(2))
#	define ALIGN_4BYTE __declspec(align(4))
#	define ALIGN_8BYTE __declspec(align(8))
#	define ALIGN_16BYTE __declspec(align(16))
#	define ALIGN_32BYTE __declspec(align(32))
#	define ALIGN_64BYTE __declspec(align(64))
#	define ALIGN_128BYTE __declspec(align(128))

typedef unsigned __int8		byte_t;		// by; ptr: pby
typedef unsigned __int16	word_t;		// w; ptr: pw
typedef unsigned __int32	dword_t;	// dw; ptr: pdw
typedef unsigned __int64	qword_t;	// qw; ptr: pqw

typedef __int8				int8_t;		// i8; ptr: pi8
typedef unsigned __int8		uint8_t;	// n8; ptr: pn8
typedef __int16				int16_t;	// i16; ptr: pi16
typedef unsigned __int16	uint16_t;	// n16; ptr: pn16
typedef __int32				int32_t;	// i32; ptr: pi32
typedef unsigned __int32	uint32_t;	// ui32; ptr: pn32
typedef __int64				int64_t;	// i64; ptr: pi64
typedef unsigned __int64	uint64_t;	// n64; ptr: pn64

typedef __int16				short_t;	// sh; ptr: psh
typedef unsigned __int16	ushort_t;	// sn; ptr: psn
typedef __int32				int_t;		// i; ptr: pi
typedef unsigned __int32	uint_t;		// n; ptr: pn
typedef __int64				long_t;		// l; ptr: pl
typedef unsigned __int64	ulong_t;	// ln; ptr: pln

typedef float				float_t;	// f; ptr: pf
typedef double				double_t;	// d; ptr: pd

typedef char				ascii_t;	// ch, sz;
typedef char*				pascii_t;	// pc, psz;
typedef unsigned __int8		u8_t;		// u8ch, u8sz;
typedef unsigned __int8*	pu8_t;		// pu8c, pu8sz;
typedef wchar_t				u16_t;		// wch, wsz;
typedef wchar_t*			pu16_t;		// pwc, pwsz;
typedef unsigned __int32	u32_t;		// uch, usz;
typedef unsigned __int32*	pu32_t;		// puc, pusz;

typedef unsigned __int64	sizeb_t;		// sb; ptr: psb
typedef void*				pvoid_t;		// pvd;
typedef void* UNIQUE		upvoid_t;		// upvd; u stands for unique (the value of the pointer)

#endif


/* GNUC Compiler Settings ---------------------------------------------------------*/
#ifdef _KILL_COMPILER_GNU

#	define FORCE_INLINE __attribute__((always_inline))
#	define DLIB_EXP __attribute__((dllexport))
#	define DLIB_IMP __attribute__((dllimport))

#	define ALIGN_2BYTE __attribute__((aligned(2)))
#	define ALIGN_4BYTE __attribute__((aligned(4)))
#	define ALIGN_8BYTE __attribute__((aligned(8)))
#	define ALIGN_16BYTE __attribute__((aligned(16)))
#	define ALIGN_32BYTE __attribute__((aligned(32)))


#endif


/* Forward Class Declaration ------------------------------------------------------*/
namespace KiLL
{
	class Timer;
	class SmartTimer;
	enum ECPUVendor;
	class CPUID;
	/*
	enum EAllocType;
	template <class _tobj> class _TMalloc_Alloc;
	template <class _tobj> class _TNew_Alloc;
	template <class _tobj, class _talloc> class _TArray;
	*/
	class FVector;
	class DVector;
	class FMatrix;
	class DMatrix;
	class FQuaternion;
	class FPlane;
}



#endif // _KiLL_Tech_API_HPP_