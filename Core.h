
/***********************************************************************************************************************************
 *	File : "Core.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Core_H__
#define __KiLL_Core_H__


// Compiler and platform check. Basic datatypes and function decorations defined.
#include "KiLLAPI.h"


#define TIMER_NOTCREATED							0x0000000000000000
#define TIMER_NOTSTARTED							0x0000000000000000

#define SMPTR_RELEASED								0x0000000000000000

#define ARRAY_INCORRECTPARAM						0x0000000000000000
#define ARRAY_ALLOCFAIL								0x0000000000000000
#define ARRAY_INDEXOUTOFRANGE						0x0000000000000000
#define ARRAY_IMPOSSIBLEPOPBACK						0x0000000000000000
#define ARRAY_INDEXPOINTEROUTOFRANGE				0x0000000000000000
#define ARRAY_NULLPTR								0x0000000000000000

#define VECTOR_DIVIDEBYZERO							0x0000000000000000

#define MATRIX_DIVIDEBYZERO							0x0000000000000000


#define _ALIGN_VAR_2(x)								(((x) + 1) &	0xFFFFFFFFFFFFFFFE)
#define _ALIGN_VAR_4(x)								(((x) + 3) &	0xFFFFFFFFFFFFFFFC)
#define _ALIGN_VAR_8(x)								(((x) + 7) &	0xFFFFFFFFFFFFFFF8)
#define _ALIGN_VAR_16(x)							(((x) + 15) &	0xFFFFFFFFFFFFFFF0)
#define _ALIGN_VAR_2048(x)							(((x) + 2047) & 0xFFFFFFFFFFFFF000)
#define _ALIGN_VAR_2336(x)							(((x) + 2335) % 2336)
#define _ALIGN_VAR(x, y)							(((x) + (y) - 1) % (y))



namespace KiLL
{

/*=================================================================================================================================
 * --- General Optimizations ----------------------------------------------------------------------------------------------------*

	extern "C" dword_t		_inKiLL_64EndSwapDW(dword_t p_dwVar);
	extern "C" qword_t		_inKiLL_64EndSwapQW(qword_t p_qwVar);

#	define _EndSwapDW(dwVar)	(KiLL::_inKiLL_64EndSwapDW(dwVar))
#	define _EndSwapQW(qwVar)	(KiLL::_inKiLL_64EndSwapQW(qwVar))
*/
} // namespace KiLL


// Error exception and log
//#include "KiLLError.h"

// CPUID instructions check class
#include "KiLLCPUID.h"

// Timer class
#include "KiLLTimer.h"

// Smart pointer (end life auto garbage)
#include "KiLLSmartPointer.h"

// Dynamic array container
#include "KiLLArray.h"

// Dynamic linked node container
//#include "KiLLLink.h"

// Advanced string object
//#include "KiLLString.h"

// Basic tree object with search and sort
//#include "KiLLTree.h"  // not sure if should be included

/* Include the Memory Manager, Memory Pool and Array Chunk container.
 * Uses own memory array for using memory from the memory pool.
 * Better performance for allocating memory than   new and delete   or   malloc() and free().
 */
//#include "KiLLMemory.h"

// General 3D math library
#include "KiLLMath.h"



#endif // __KiLL_Core_H__