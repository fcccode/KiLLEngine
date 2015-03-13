
/***********************************************************************************************************************************
 *	File : "KiLLMath.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Math_H__
#define __KiLL_Math_H__

#ifdef X
#	undef X
#endif
#ifdef Y
#	undef Y
#endif
#ifdef Z
#	undef Z
#endif
#ifdef W
#	undef W
#endif


namespace KiLL
{

/*=================================================================================================================================
 * --- Floating Number Constants ------------------------------------------------------------------------------------------------*/

	static const float_t g_fZero = 0.0f;
	static const float_t g_fNegZero = -0.0f;
	static const float_t g_fOne = 1.0f;
	static const float_t g_fNegOne = 1.0f;
	static const float_t g_fNegTwo = -2.0f;

	static const float_t g_fPi = 3.14159265359f;
	static const float_t g_f2Pi = 6.28318530718f;
	static const float_t g_fHalgPi = 1.570796326795f;
	static const float_t g_fQuartPi = 0.7853981634f;
	static const float_t g_fInvPi = 0.3183098862f;
	static const float_t g_fInv2Pi = 0.1591549367f;

	static const float_t g_fBPrc = 0.001f;
	static const float_t g_fNPrc = 0.0001f;
	static const float_t g_fSPrc = 0.00001f;

	static const ALIGN_16BYTE float_t g_fIdentityMatrix[4] = { 1.0f, 0.0f, 0.0f, 0.0f };


	static const double_t g_dZero = 0.0;
	static const double_t g_dNegZero = -0.0;
	static const double_t g_dOne = 1.0f;
	static const double_t g_dNegOne = 1.0f;
	static const double_t g_dNegTwo = -2.0;

	static const double_t g_dPi = 3.14159265358979323846;
	static const double_t g_d2Pi = 6.28318530717958647692;
	static const double_t g_dHalfPi = 1.57079632679489661923;
	static const double_t g_dQuartPi = 0.78539816339744830962;
	static const double_t g_dInvPi = 0.31830988618379069;
	static const double_t g_dInv2Pi = 0.15915494309189535;

	static const double_t g_dBPrc = 0.0001;
	static const double_t g_dNPrc = 0.00001;
	static const double_t g_dSPrc = 0.000001;

	static const ALIGN_16BYTE double_t g_dIdentityMatrix[4] = { 1.0, 0.0, 0.0, 0.0 };




/*=================================================================================================================================
 * --- Floating Number General Math Functions -----------------------------------------------------------------------------------*/


	INL float_t		Sqrt(float_t p_fNbr);
	INL float_t		Pow(float_t p_fNbr, float_t p_fPow);
	INL float_t		FMod(float_t p_fNbr1, float_t p_fNbr2);
	INL float_t		FAbs(float_t p_fNbr);
	INL float_t		Ceil(float_t p_fNbr);
	INL float_t		Floor(float_t p_fNbr);
	INL float_t		Sin(float_t p_fTheta);
	INL float_t		Cos(float_t p_fTheta);
	INL float_t		Tan(float_t p_fTheta);
	INL float_t		Sinh(float_t p_fTheta);
	INL float_t		Cosh(float_t p_fTheta);
	INL float_t		Tanh(float_t p_fTheta);
	INL float_t		ArcSin(float_t p_fNbr);
	INL float_t		ArcCos(float_t p_fNbr);
	INL float_t		ArcTan(float_t p_fNbr);
	INL float_t		ArcTan2(float_t p_fY, float_t p_fX);


	INL double_t	Sqrt(double_t p_dNbr);
	INL double_t	Pow(double_t p_dNbr, double_t p_dPow);
	INL double_t	FMod(double_t p_dNbr1, double_t p_dNbr2);
	INL double_t	FAbs(double_t p_dNbr);
	INL double_t	Ceil(double_t p_dNbr);
	INL double_t	Floor(double_t p_dNbr);
	INL double_t	Sin(double_t p_dTheta);
	INL double_t	Cos(double_t p_dTheta);
	INL double_t	Tan(double_t p_dTheta);
	INL double_t	Sinh(double_t p_dTheta);
	INL double_t	Cosh(double_t p_dTheta);
	INL double_t	Tanh(double_t p_dTheta);
	INL double_t	ArcSin(double_t p_dNbr);
	INL double_t	ArcCos(double_t p_dNbr);
	INL double_t	ArcTan(double_t p_dNbr);
	INL double_t	ArcTan2(double_t p_dY, double_t p_dX);


	INL float_t		Deg2Rad(float_t p_fTheta);
	INL float_t		Rad2Deg(float_t p_fTheta);


	INL double_t	Deg2Rad(double_t p_dTheta);
	INL double_t	Rad2Deg(double_t p_dTheta);

	
	template <class _type>
	INL _type		TMax(_type p_var1, _type p_var2);
	template <class _type>
	INL _type		TMin(_type p_var, _type p_min, _type p_max);



	template <class _type>
	INL bool		TRange(_type p_var, _type p_min, _type p_max);
	template <class _type>
	INL _type		TClamp(_type p_var, _type p_min, _type p_max);




} // namespace KiLL

#include "KiLLMath.inl"


#include "KiLLVector.h"
#include "KiLLMatrix.h"
//#include "KiQuaternion.h"


#endif // __KiLL_Math_H__