
/***********************************************************************************************************************************
 *	File : "KiLLCPUID.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_CPUID_H__
#define __KiLL_CPUID_H__


namespace KiLL
{

/*=================================================================================================================================
 * --- CPUID --------------------------------------------------------------------------------------------------------------------*/

	enum ECPUVendor { UNKNOWN_CPU = 0, INTEL = 1, AMD = 2 };

	class CPUID
	{
	public:

				CPUID();
		bool	CheckSSE3();
		uint_t	CheckCores();

	//private:

		ascii_t m_szCPUVendor[13];
		ascii_t m_szCPUBrand[49];
		ECPUVendor m_eVendor;
		uint_t m_nCores;
		bool m_bSSE3;
		bool m_bIntelSSSE3;
		bool m_bIntelSSE41;
		bool m_bIntelSSE42;
		bool m_bAMDSSE3e;
		bool m_bAMDSSE41;
		bool m_bAMDSSE4A;
		bool m_bAMDSSE5;
	};


} // namespace KiLL


#endif // __KiLL_CPUID_H__