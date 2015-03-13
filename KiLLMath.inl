
/***********************************************************************************************************************************
 *	File : "KiLLMath.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Math_INL__
#define __KiLL_Math_INL__


namespace KiLL
{

/*=================================================================================================================================
 * --- Floating Number General Math Functions -----------------------------------------------------------------------------------*/

	INL float_t	Sqrt(float_t p_fNbr)
	{
		__m128 _xmm0;
		_xmm0 = _mm_load_ss(&p_fNbr);
		_xmm0 = _mm_sqrt_ss(_xmm0);
		return _xmm0.m128_f32[0];
		//return static_cast<float_t>(sqrt(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	Pow(float_t p_fNbr, float_t p_fPow)
	{
		return static_cast<float_t>(pow(static_cast<double_t>(p_fNbr), static_cast<double_t>(p_fPow)));
	}
	INL float_t	FMod(float_t p_fNumerator, float_t p_fDenominator)
	{
		return static_cast<float_t>(fmod(static_cast<double_t>(p_fNumerator), static_cast<double_t>(p_fDenominator)));
	}
	INL float_t	FAbs(float_t p_fNbr)
	{
		return static_cast<float_t>(fabs(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	Ceil(float_t p_fNbr)
	{
		return static_cast<float_t>(ceil(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	Floor(float_t p_fNbr)
	{
		return static_cast<float_t>(floor(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	Sin(float_t p_fTheta)
	{
		return static_cast<float_t>(sin(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	Cos(float_t p_fTheta)
	{
		return static_cast<float_t>(cos(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	Tan(float_t p_fTheta)
	{
		return static_cast<float_t>(tan(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	Sinh(float_t p_fTheta)
	{
		return static_cast<float_t>(sinh(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	Cosh(float_t p_fTheta)
	{
		return static_cast<float_t>(cosh(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	Tanh(float_t p_fTheta)
	{
		return static_cast<float_t>(tanh(static_cast<double_t>(p_fTheta)));
	}
	INL float_t	ArcSin(float_t p_fNbr)
	{
		return static_cast<float_t>(asin(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	ArcCos(float_t p_fNbr)
	{
		return static_cast<float_t>(acos(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	ArcTan(float_t p_fNbr)
	{
		return static_cast<float_t>(atan(static_cast<double_t>(p_fNbr)));
	}
	INL float_t	ArcTan2(float_t p_fY, float_t p_fX)
	{
		return static_cast<float_t>(atan2(static_cast<double_t>(p_fY), static_cast<double_t>(p_fX)));
	}


	INL double_t	Sqrt(double_t p_dNbr)
	{
		__m128d _xmm0;
		_xmm0 = _mm_load_sd(&p_dNbr);
		_xmm0 = _mm_sqrt_sd(_xmm0, _xmm0);
		return _xmm0.m128d_f64[0];
		//return sqrt(p_dNbr);
	}
	INL double_t	Pow(double_t p_dNbr, double_t p_dPow)
	{
		return pow(p_dNbr, p_dPow);
	}
	INL double_t	FMod(double_t p_dNumerator, double_t p_dDenominator)
	{
		return fmod(p_dNumerator, p_dDenominator);
	}
	INL double_t	FAbs(double_t p_dNbr)
	{
		return fabs(p_dNbr);
	}
	INL double_t	Ceil(double_t p_dNbr)
	{
		return ceil(p_dNbr);
	}
	INL double_t	Floor(double_t p_dNbr)
	{
		return floor(p_dNbr);
	}
	INL double_t	Sin(double_t p_dTheta)
	{
		return sin(p_dTheta);
	}
	INL double_t	Cos(double_t p_dTheta)
	{
		return cos(p_dTheta);
	}
	INL double_t	Tan(double_t p_dTheta)
	{
		return tan(p_dTheta);
	}
	INL double_t	Sinh(double_t p_dTheta)
	{
		return sinh(p_dTheta);
	}
	INL double_t	Cosh(double_t p_dTheta)
	{
		return cosh(p_dTheta);
	}
	INL double_t	Tanh(double_t p_dTheta)
	{
		return tanh(p_dTheta);
	}
	INL double_t	ArcSin(double_t p_dNbr)
	{
		return asin(p_dNbr);
	}
	INL double_t	ArcCos(double_t p_dNbr)
	{
		return acos(p_dNbr);
	}
	INL double_t	ArcTan(double_t p_dNbr)
	{
		return atan(p_dNbr);
	}
	INL double_t	ArcTan2(double_t p_dY, double_t p_dX)
	{
		return atan2(p_dY, p_dX);
	}


	INL float_t	Deg2Rad(float_t p_fTheta)
	{
		return (p_fTheta * 0.01745329251994f);
	}
	INL float_t	Rad2Deg(float_t p_fTheta)
	{
		return (p_fTheta * 57.295779513082f);
	}


	INL double_t	Deg2Rad(double_t p_dTheta)
	{
		return (p_dTheta * 0.017453292519943295);
	}
	INL double_t	Rad2Deg(double_t p_dTheta)
	{
		return (p_dTheta * 57.295779513082321);
	}

	
	template <class _type>
	INL _type		TMax(_type p_var1, _type p_var2)
	{
		return ( (p_var1 > p_var2) ? p_var1 : p_var2 );
	}
	template <class _type>
	INL _type		TMin(_type p_var, _type p_min, _type p_max)
	{
		return ( (p_var1 < p_var2) ? p_var1 : p_var2 );
	}



	template <class _type>
	INL bool		TRange(_type p_var, _type p_min, _type p_max)
	{
		return ( (p_var >= p_min) && (p_var <= p_max) );
	}
	template <class _type>
	INL _type		TClamp(_type p_var, _type p_min, _type p_max)
	{
		return ( p_var < p_min ? p_min : (p_var > p_max ? p_max : p_var) );
	}




} // namespace KiLL


#endif // __KiLL_Math_INL__