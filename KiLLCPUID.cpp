
/***********************************************************************************************************************************
 *	File : "KiLLCPUID.cpp"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#include "Core.h"



#define CPUREG_BASEMODEL			0x000000F0
#define CPUREG_BASEMODELSTEP		4
#define CPUREG_BASEFAMILY			0x00000F00
#define CPUREG_BASEFAMILYSTEP		8
#define CPUREG_EXTMODEL				0x000F0000
#define CPUREG_EXTMODELSTEP			16
#define CPUREG_EXTFAMILY			0x0FF00000
#define CPUREG_EXTFAMILYSTEP		20


#define CPU_FLAG_MASK				0x00000001

#define CPU_INTEL_ECX_SSE3_STEP		0
#define CPU_INTEL_ECX_SSSE3_STEP	9
#define CPU_INTEL_ECX_SSE41_STEP	19
#define CPU_INTEL_ECX_SSE42_STEP	20

#define CPU_AMD_ECX1_SSE3_STEP		0
#define CPU_AMD_ECX1_SSE3E_STEP		9
#define CPU_AMD_ECX1_SSE41_STEP		19
#define CPU_AMD_ECX81_SSE4A_STEP	6
#define CPU_AMD_ECX81_SSE5_STEP		11



namespace KiLL
{

/*=================================================================================================================================
 * --- CPUID --------------------------------------------------------------------------------------------------------------------*/

			CPUID::CPUID()
	{
		memset(this, 0, sizeof(CPUID));
		int_t iReg[4];
		int_t iMaxEAX;

		__cpuid(iReg, 0);
		iMaxEAX = iReg[0];
		reinterpret_cast<int_t*>(m_szCPUVendor)[0] = iReg[1];
		reinterpret_cast<int_t*>(m_szCPUVendor)[1] = iReg[3];
		reinterpret_cast<int_t*>(m_szCPUVendor)[2] = iReg[2];
		m_szCPUVendor[12] = '\0';
		if (strcmp(m_szCPUVendor, "GenuineIntel\0") == 0) m_eVendor = INTEL;
		if (strcmp(m_szCPUVendor, "AuthenticAMD\0") == 0) m_eVendor = AMD;

		__cpuid(iReg, 0x80000002);
		reinterpret_cast<int_t*>(m_szCPUBrand)[0] = iReg[0];
		reinterpret_cast<int_t*>(m_szCPUBrand)[1] = iReg[1];
		reinterpret_cast<int_t*>(m_szCPUBrand)[2] = iReg[2];
		reinterpret_cast<int_t*>(m_szCPUBrand)[3] = iReg[3];
		__cpuid(iReg, 0x80000003);
		reinterpret_cast<int_t*>(m_szCPUBrand)[4] = iReg[0];
		reinterpret_cast<int_t*>(m_szCPUBrand)[5] = iReg[1];
		reinterpret_cast<int_t*>(m_szCPUBrand)[6] = iReg[2];
		reinterpret_cast<int_t*>(m_szCPUBrand)[7] = iReg[3];
		__cpuid(iReg, 0x80000004);
		reinterpret_cast<int_t*>(m_szCPUBrand)[8] = iReg[0];
		reinterpret_cast<int_t*>(m_szCPUBrand)[9] = iReg[1];
		reinterpret_cast<int_t*>(m_szCPUBrand)[10] = iReg[2];
		reinterpret_cast<int_t*>(m_szCPUBrand)[11] = iReg[3];
		m_szCPUBrand[48] = '\0';

		if (m_eVendor == INTEL) {
			long_t lInstr;
			__cpuid(iReg, 0x01);
			lInstr = iReg[2];	//_inKiLL_64GetCPUrcx01hInstructions()
			m_bSSE3 = static_cast<bool>((lInstr >> CPU_INTEL_ECX_SSE3_STEP) & CPU_FLAG_MASK);
			m_bIntelSSSE3 = static_cast<bool>((lInstr >> CPU_INTEL_ECX_SSSE3_STEP) & CPU_FLAG_MASK);
			m_bIntelSSE41 = static_cast<bool>((lInstr >> CPU_INTEL_ECX_SSE41_STEP) & CPU_FLAG_MASK);
			m_bIntelSSE42 = static_cast<bool>((lInstr >> CPU_INTEL_ECX_SSE42_STEP) & CPU_FLAG_MASK);
		}
		if (m_eVendor == AMD) {
			long_t lInstr;
			__cpuid(iReg, 0x01);
			lInstr = iReg[2];	//_inKiLL_64GetCPUrcx01hInstructions()
			m_bSSE3 = static_cast<bool>((lInstr >> CPU_AMD_ECX1_SSE3_STEP) & CPU_FLAG_MASK);
			m_bAMDSSE3e = static_cast<bool>((lInstr >> CPU_AMD_ECX1_SSE3E_STEP) & CPU_FLAG_MASK);
			m_bAMDSSE41 = static_cast<bool>((lInstr >> CPU_AMD_ECX1_SSE41_STEP) & CPU_FLAG_MASK);
			__cpuid(iReg, 0x80000001);
			lInstr = iReg[2];	//_inKiLL_64GetCPUrcx81hInstructions()
			m_bAMDSSE4A = static_cast<bool>((lInstr >> CPU_AMD_ECX81_SSE4A_STEP) & CPU_FLAG_MASK);
			m_bAMDSSE5 = static_cast<bool>((lInstr >> CPU_AMD_ECX81_SSE5_STEP) & CPU_FLAG_MASK);
		}

		if (m_eVendor == INTEL) {
			__cpuid(iReg, 0x04);
			m_nCores = (iReg[0] >> 26) + 1;
		}
		if (m_eVendor == AMD) {
			__cpuid(iReg, 0x80000008);
			m_nCores = (iReg[2] & 0x0000007F) + 1;
		}
	}

	bool		CPUID::CheckSSE3()
	{
		return m_bSSE3;
	}

	uint_t		CPUID::CheckCores()
	{
		return m_nCores;
	}


} // namespace KiLL