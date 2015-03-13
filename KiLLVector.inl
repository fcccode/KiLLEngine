
/***********************************************************************************************************************************
 *	File : "KiLLVector.inl"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Vector_INL__
#define __KiLL_Vector_INL__



namespace KiLL
{
/*=================================================================================================================================
 * --- 2D Float Vector ----------------------------------------------------------------------------------------------------------*/

	INL void	F2Vector::operator = (const F2Vector& p_rf2vSrc)
	{
		X = p_rf2vSrc.X;	Y = p_rf2vSrc.Y;
	}
	INL F2Vector	F2Vector::operator ~ () const
	{
		return F2Vector( -X, -Y);
	}


	INL bool	F2Vector::operator >= (const F2Vector& p_rf2Vec) const
	{
		return ( (X*X + Y*Y) >= (p_rf2Vec.X*p_rf2Vec.X + p_rf2Vec.Y*p_rf2Vec.Y) );
	}
	INL bool	F2Vector::operator <= (const F2Vector& p_rf2Vec) const
	{
		return ( (X*X + Y*Y) <= (p_rf2Vec.X*p_rf2Vec.X + p_rf2Vec.Y*p_rf2Vec.Y) );
	}
	INL bool	F2Vector::operator > (const F2Vector& p_rf2Vec) const
	{
		return ( (X*X + Y*Y) > (p_rf2Vec.X*p_rf2Vec.X + p_rf2Vec.Y*p_rf2Vec.Y) );
	}
	INL bool	F2Vector::operator < (const F2Vector& p_rf2Vec) const
	{
		return ( (X*X + Y*Y) < (p_rf2Vec.X*p_rf2Vec.X + p_rf2Vec.Y*p_rf2Vec.Y) );
	}


	INL void	F2Vector::operator += (const F2Vector& p_rf2Vec)
	{
		X += p_rf2Vec.X;	Y += p_rf2Vec.Y;
	}
	INL void	F2Vector::operator -= (const F2Vector& p_rf2Vec)
	{
		X -= p_rf2Vec.X;	Y -= p_rf2Vec.Y;
	}

	INL void	F2Vector::operator *= (const F2Vector& p_rf2Vec)
	{
		X *= p_rf2Vec.Y;	Y *= p_rf2Vec.X;
	}


	INL void	F2Vector::operator *= (float_t p_fScalar)
	{
		X *= p_fScalar;		Y *= p_fScalar;
	}
	INL void	F2Vector::operator /= (float_t p_fScalar)
	{
		X /= p_fScalar;		Y /= p_fScalar;
	}
	INL F2Vector	F2Vector::operator * (float_t p_fScalar) const
	{
		return F2Vector(X*p_fScalar, Y*p_fScalar);
	}
	INL F2Vector	F2Vector::operator / (float_t p_fScalar) const
	{
		return F2Vector(X/p_fScalar, Y/p_fScalar);
	}


	INL void		VecZero(F2Vector* p_pf2Zero)
	{
		p_pf2Zero->X = g_fZero;	p_pf2Zero->Y = g_fZero;
	}
	INL void		VecSet(F2Vector* p_pf2Dst, float_t p_fX, float_t p_fY)
	{
		p_pf2Dst->X = p_fX;	p_pf2Dst->Y = p_fY;
	}
	INL void		VecInvert(F2Vector* p_pf2Dst)
	{
		p_pf2Dst->X *= g_fNegOne;	p_pf2Dst->Y *= g_fNegOne;
	}

	INL void		VecCross(F2Vector* p_pf2Cross, const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
	{
		p_pf2Cross->X = p_rf2Vec1.X*p_rf2Vec2.Y;
		p_pf2Cross->Y = p_rf2Vec1.Y*p_rf2Vec2.X;
	}
	INL void		VecDot(float_t* p_pfDot, const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
	{
		*p_pfDot = p_rf2Vec1.X*p_rf2Vec2.X + p_rf2Vec1.Y*p_rf2Vec2.Y;
	}

	INL void		VecUnit(float_t* p_pfNorm, const F2Vector& p_rf2Vec)
	{
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ss(&p_rf2Vec.X);
		_xmm1 = _mm_load_ss(&p_rf2Vec.Y);
		*p_pfNorm = _mm_sqrt_ss(_mm_mul_ss(_xmm0, _xmm1)).m128_f32[0];
	}

	INL bool		VecBitEqual(const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
	{
		return ((p_rf2Vec1.X == p_rf2Vec2.X) && (p_rf2Vec1.Y == p_rf2Vec2.Y));
	}
	INL bool		VecSqrNormEqual(const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2, float_t p_fErr)
	{
		float_t fVec1SL = p_rf2Vec1.X*p_rf2Vec1.X + p_rf2Vec1.Y*p_rf2Vec1.Y;
		float_t fVec2SL = p_rf2Vec2.X*p_rf2Vec2.X + p_rf2Vec2.Y*p_rf2Vec2.Y;
		return ( TRange<float_t>(fVec1SL, fVec2SL-p_fErr, fVec2SL+p_fErr) ? true : false );
	}




/*=================================================================================================================================
 * --- 4D Float Precision Vector ------------------------------------------------------------------------------------------------*/

	INL		FVector::FVector(const FVector& p_rfvVec)
	{
		__m128 _xmm0;
		_xmm0 = _mm_load_ps(&p_rfvVec.X);
		_mm_store_ps(&X, _xmm0);
	}


	INL void	FVector::operator = (const FVector& p_rfvSrc)
	{
		__m128 _xmm0;
		_xmm0 = _mm_load_ps(&p_rfvSrc.X);
		_mm_store_ps(&X, _xmm0);
	}


	INL bool	FVector::operator >= (const FVector& p_rfvVec) const
	{	// return ( (X*X + Y*Y + Z*Z) >= (p_rfvVec.X*p_rfvVec.X + p_rfvVec.Y*p_rfvVec.Y + p_rfvVec.Z*p_rfvVec.Z) );
		__m128 _xmm0, _xmm1, _xmm2;

		_xmm0 = _mm_load_ps(&X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm2 = _xmm0;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm2);
		
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm2 = _xmm1;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm2);

		return (_mm_comige_ss(_xmm0, _xmm1) != 0);
	}
	INL bool	FVector::operator <= (const FVector& p_rfvVec) const
	{	// return ( (X*X + Y*Y + Z*Z) <= (p_rfvVec.X*p_rfvVec.X + p_rfvVec.Y*p_rfvVec.Y + p_rfvVec.Z*p_rfvVec.Z) );
		__m128 _xmm0, _xmm1, _xmm2;
		
		_xmm0 = _mm_load_ps(&X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm2 = _xmm0;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm2);
		
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm2 = _xmm1;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm2);

		return (_mm_comile_ss(_xmm0, _xmm1) != 0);
	}
	INL bool	FVector::operator > (const FVector& p_rfvVec) const
	{	// return ( (X*X + Y*Y + Z*Z) > (p_rfvVec.X*p_rfvVec.X + p_rfvVec.Y*p_rfvVec.Y + p_rfvVec.Z*p_rfvVec.Z) );
		__m128 _xmm0, _xmm1, _xmm2;
		
		_xmm0 = _mm_load_ps(&X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm2 = _xmm0;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm2);
		
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm2 = _xmm1;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm2);

		return (_mm_comigt_ss(_xmm0, _xmm1) != 0);
	}
	INL bool	FVector::operator < (const FVector& p_rfvVec) const
	{	// return ( (X*X + Y*Y + Z*Z) < (p_rfvVec.X*p_rfvVec.X + p_rfvVec.Y*p_rfvVec.Y + p_rfvVec.Z*p_rfvVec.Z) );
		__m128 _xmm0, _xmm1, _xmm2;
		
		_xmm0 = _mm_load_ps(&X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm2 = _xmm0;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm2);
		
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm2 = _xmm1;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm2);

		return (_mm_comilt_ss(_xmm0, _xmm1) != 0);
	}


	INL void	FVector::operator += (const FVector& p_rfvVec)
	{	// X += p_rfvVec.X;	Y += p_rfvVec.Y;	Y += p_rfvVec.Y;
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&X);
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm0 = _mm_add_ps(_xmm0, _xmm1);
		_mm_store_ps(&X, _xmm0);
		W = g_fOne;
	}
	INL void	FVector::operator -= (const FVector& p_rfvVec)
	{	// X -= p_rfvVec.X;	Y -= p_rfvVec.Y;	Y -= p_rfvVec.Y;
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&X);
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_mm_store_ps(&X, _xmm0);
		W = g_fOne;
	}

	INL void	FVector::operator *= (const FVector& p_rfvVec)
	{	// *this = FVector((Y*p_rfvVec.Z)-(Z*p_rfvVec.Y), (Z*p_rfvVec.X)-(X * p_rfvVec.Z), (X*p_rfvVec.Y)-(Y*p_rfvVec.X));
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;
		_xmm0 = _mm_load_ps(&X);
		_xmm1 = _mm_load_ps(&p_rfvVec.X);
		_xmm2 = _mm_shuffle_ps(_xmm1, _xmm1, 0xC9); // 11 00 10 01
		_xmm2 = _mm_mul_ps(_xmm2, _xmm0);
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xC9); // 11 00 10 01
		_xmm3 = _mm_shuffle_ps(_xmm1, _xmm1, 0xD2); // 11 01 00 10
		_xmm3 = _mm_mul_ps(_xmm3, _xmm0);
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xD2); // 11 01 00 10
		_xmm0 = _mm_sub_ps(_xmm2, _xmm3);
		_mm_store_ps(&X, _xmm0);
		W = g_fOne;
	}


	INL void	FVector::operator *= (const float_t p_fScalar)
	{
		X *= p_fScalar;	Y *= p_fScalar;	Z *= p_fScalar;
	}
	INL void	FVector::operator /= (const float_t p_fScalar)
	{
		X /= p_fScalar;	Y /= p_fScalar;	Z /= p_fScalar;
	}
	INL FVector	FVector::operator * (float_t p_fScalar) const
	{
		return FVector(X*p_fScalar, Y*p_fScalar, Z*p_fScalar);
	}
	INL FVector	FVector::operator / (float_t p_fScalar) const
	{
		return FVector(X/p_fScalar, Y/p_fScalar, Z/p_fScalar);
	}


	INL void		VecZero(FVector* p_pfvZero)
	{
		__m128 _xmm0;
		_xmm0 = _mm_load_ps(&g_fvZero.X);
		_mm_store_ps(&p_pfvZero->X, _xmm0);
	}
	INL void		VecSet(FVector* p_pfvDst, float_t p_fX, float_t p_fY, float_t p_fZ)
	{
		p_pfvDst->X = p_fX;		p_pfvDst->Y = p_fY;		p_pfvDst->Z = p_fZ;		p_pfvDst->W = g_fOne;
	}
	INL void		VecInvert(FVector* p_pfvDst, const FVector& p_rfvVec)
	{
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_load_ps(&g_fvInvert.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm1);
		_mm_store_ps(&p_pfvDst->X, _xmm0);
	}
	INL void		VecDoubleToFloat(FVector* p_pfvDst, const DVector& p_rdvSrc)
	{	/*	p_pfvDst->X = static_cast<float_t>(p_rdvSrc.X);
			p_pfvDst->Y = static_cast<float_t>(p_rdvSrc.Y);
			p_pfvDst->Z = static_cast<float_t>(p_rdvSrc.Z);
			p_pfvDst->W = static_cast<float_t>(p_rdvSrc.Z); */
		__m128d _xmm0, _xmm1;
		__m128 _xmm2, _xmm3;

		_xmm0 = _mm_load_pd(&p_rdvSrc.X);
		_xmm1 = _mm_load_pd(&p_rdvSrc.Z);
		_xmm2 = _mm_cvtpd_ps(_xmm0);
		_xmm3 = _mm_cvtpd_ps(_xmm1);
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm3, 0x44); // 01 00 01 00
		_mm_store_ps(&p_pfvDst->X, _xmm2);
	}

	INL void		VecUnit(FVector* p_pfvNorm, const FVector& p_rfvVec)
	{
		__m128 _xmm0, _xmm1, _xmm2;

		_xmm1 = _mm_load_ps(&(p_rfvVec.X));
		_xmm0 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm2 = _xmm0;
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm2);
		_xmm0 = _mm_sqrt_ss(_xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x00); // 00 00 00 00
		_xmm1 = _mm_div_ps(_xmm1, _xmm0);
		_mm_store_ps(&p_pfvNorm->X, _xmm1);
		p_pfvNorm->W = g_fOne;
	}
	INL void		VecCross(FVector* p_pfvCross, const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{	/*	p_pfvCross->X = p_rfvVec1.Y * p_rfvVec2.Z - p_rfvVec1.Z * p_rfvVec2.Y;
			p_pfvCross->Y = p_rfvVec1.Z * p_rfvVec2.X - p_rfvVec1.X * p_rfvVec2.Z;
			p_pfvCross->Z = p_rfvVec1.X * p_rfvVec2.Y - p_rfvVec1.Y * p_rfvVec2.X; */
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm2 = _mm_shuffle_ps(_xmm1, _xmm1, 0xC9); // 11 00 10 01
		_xmm2 = _mm_mul_ps(_xmm2, _xmm0);
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xC9); // 11 00 10 01
		_xmm3 = _mm_shuffle_ps(_xmm1, _xmm1, 0xD2); // 11 01 00 10
		_xmm3 = _mm_mul_ps(_xmm3, _xmm0);
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xD2); // 11 01 00 10
		_xmm0 = _mm_sub_ps(_xmm2, _xmm3);
		_mm_store_ps(&p_pfvCross->X, _xmm0);
		p_pfvCross->W = g_fOne;
	}
	INL void		VecDot(float_t* p_pfDot, const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{	/*	*p_pfDot = p_rfvVec1.X*p_rfvVec2.X + p_rfvVec1.Y*p_rfvVec2.Y + p_rfvVec1.Z*p_rfvVec2.Z; */
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm1);
		_xmm1 = _xmm0;
		_xmm1 = _mm_shuffle_ps(_xmm1, _xmm1, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_mm_store_ss(p_pfDot, _xmm0);
	}
	INL void		VecModulate(FVector* p_pfvMod, const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm1);
		_mm_store_ps(&p_pfvMod->X, _xmm0);
		p_pfvMod->W = g_fOne;
	}

	INL void		VecNorm(float_t* p_pfNorm, const FVector& p_rfvVec)
	{	/*	*p_pfNorm = Sqrt(X*X + Y*Y + Z*Z); */
		__m128 _xmm0, _xmm1;
		_mm_load_ps(&p_rfvVec.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm1 = _xmm0;
		_xmm1 = _mm_shuffle_ps(_xmm1, _xmm1, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_xmm0 = _mm_sqrt_ss(_xmm0);
		_mm_store_ss(p_pfNorm, _xmm0);
	}
	INL void		VecSqrNorm(float_t* p_pfSqrNorm, const FVector& p_rfvVec)
	{	/*	*p_pfNorm = X*X + Y*Y + Z*Z; */
		__m128 _xmm0, _xmm1;
		_mm_load_ps(&p_rfvVec.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm1 = _xmm0;
		_xmm1 = _mm_shuffle_ps(_xmm1, _xmm1, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_mm_store_ss(p_pfSqrNorm, _xmm0);
	}
	INL void		VecAngle(float_t* p_pfAngle, const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{	/*	float_t f2Norm = (Sqrt(p_rfvVec1.X*p_rfvVec1.X + p_rfvVec1.Y*p_rfvVec1.Y + p_rfvVec1.Z*p_rfvVec1.Z) *
								Sqrt(p_rfvVec2.X*p_rfvVec2.X + p_rfvVec2.Y*p_rfvVec2.Y + p_rfvVec2.Z*p_rfvVec2.Z) );
			if (f2Norm < g_fSPrc) throw KILL_VECTOR_DIVIDEBYZERO;
			*p_pfAngle = ArcCos( (p_rfvVec1.X*p_rfvVec2.X + p_rfvVec1.Y*p_rfvVec2.Y + p_rfvVec1.Z*p_rfvVec2.Z) / f2Norm ); */
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;
		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm2 = _mm_mul_ps(_xmm0, _xmm1);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm3 = _xmm0;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm3);
		_xmm0 = _mm_sqrt_ss(_xmm0);
		_xmm3 = _xmm1;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm3);
		_xmm1 = _mm_sqrt_ss(_xmm1);
		_xmm0 = _mm_mul_ss(_xmm0, _xmm1);
		_xmm1 = _mm_load_ss(&g_fSPrc);
		if (_mm_comilt_ss(_xmm0, _xmm1)) throw VECTOR_DIVIDEBYZERO;
		_xmm3 = _xmm2;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_sub_ps(_xmm2, _xmm3);
		_xmm2 = _mm_div_ss(_xmm2, _xmm0);
		*p_pfAngle = ArcCos(_xmm2.m128_f32[0]);
	}
	INL void		VecDistance(float_t* p_pfDist, const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{	/*	return (Sqrt(	(p_rfvVec1.X-p_rfvVec2.X)*(p_rfvVec1.X-p_rfvVec2.X) +
							(p_rfvVec1.Y-p_rfvVec2.Y)*(p_rfvVec1.Y-p_rfvVec2.Y) +
							(p_rfvVec1.Z-p_rfvVec2.Z)*(p_rfvVec1.Z-p_rfvVec2.Z)) ); */
		__m128 _xmm0, _xmm1;
		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm1 = _xmm0;
		_xmm1 = _mm_shuffle_ps(_xmm1, _xmm1, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
		_xmm0 = _mm_sqrt_ss(_xmm0);
		_mm_store_ss(p_pfDist, _xmm0);
	}

	INL bool		VecBitEqual(const FVector& p_rfvVec1, const FVector& p_rfvVec2)
	{
		return ((p_rfvVec1.X == p_rfvVec2.X) && (p_rfvVec1.Y == p_rfvVec2.Y) && (p_rfvVec1.Z == p_rfvVec2.Z));
	}
	INL bool		VecSqrNormEqual(const FVector& p_rfvVec1, const FVector& p_rfvVec2, float_t p_fErr)
	{
		/*	float_t fVec1SL = p_rfvVec1.X*p_rfvVec1.X + p_rfvVec1.Y*p_rfvVec1.Y + p_rfvVec1.Z*p_rfvVec1.Z;
			float_t fVec2SL = p_rfvVec2.X*p_rfvVec2.X + p_rfvVec2.Y*p_rfvVec2.Y + p_rfvVec2.Z*p_rfvVec2.Z;
			return TRange<float_t>(fVec1SL, fVec2SL-p_fErr, fVec2SL+p_fErr);	*/
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;
		_xmm0 = _mm_load_ps(&p_rfvVec1.X);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm0);
		_xmm3 = _xmm0;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_hadd_ps(_xmm0, _xmm0);
		_xmm0 = _mm_sub_ps(_xmm0, _xmm3);
		_xmm1 = _mm_load_ps(&p_rfvVec2.X);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm1);
		_xmm3 = _xmm1;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_hadd_ps(_xmm1, _xmm1);
		_xmm1 = _mm_sub_ps(_xmm1, _xmm3);
		_xmm2 = _mm_load_ss(&p_fErr);
		_xmm3 = _xmm1;
		_xmm3 = _mm_add_ss(_xmm3, _xmm2);
		_xmm1 = _mm_sub_ss(_xmm1, _xmm2);
		return (_mm_comige_ss(_xmm0, _xmm1) && _mm_comile_ss(_xmm0, _xmm3));
	}




/*=================================================================================================================================
 * --- 4D Double Precision Vector -----------------------------------------------------------------------------------------------*/

	INL		DVector::DVector(const DVector& p_rdvVec)
	{
		__m128d _xmm0;
		_xmm0 = _mm_load_pd(&p_rdvVec.X);
		_mm_store_pd(&X, _xmm0);
		_xmm0 = _mm_load_pd(&p_rdvVec.Z);
		_mm_store_pd(&Z, _xmm0);
	}


	INL void	DVector::operator = (const DVector& p_rdvSrc)
	{	//	X = p_rdvSrc.X;		Y = p_rdvSrc.Y;		Z = p_rdvSrc.Z;
		__m128d _xmm0;
		_xmm0 = _mm_load_pd(&p_rdvSrc.X);
		_mm_store_pd(&X, _xmm0);
		_xmm0 = _mm_load_pd(&p_rdvSrc.Z);
		_mm_store_pd(&Z, _xmm0);
	}


	INL bool	DVector::operator >= (const DVector& p_rdvVec) const
	{	//	return ( (X*X + Y*Y + Z*Z) >= (p_rdvVec.X*p_rdvVec.X + p_rdvVec.Y*p_rdvVec.Y + p_rdvVec.Z*p_rdvVec.Z) );
		__m128d _xmm0, _xmm1, _xmm2;
		_xmm1 = _mm_load_pd(&X);
		_xmm0 = _mm_load_sd(&Z);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm1);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_add_pd(_xmm1, _xmm0);
		_xmm1 = _mm_hadd_pd(_xmm1, _xmm1);

		_xmm2 = _mm_load_pd(&p_rdvVec.X);
		_xmm0 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_mul_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm2 = _mm_add_pd(_xmm2, _xmm0);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);

		return (_mm_comige_sd(_xmm1, _xmm2) != 0);
	}
	INL bool	DVector::operator <= (const DVector& p_rdvVec) const
	{	//	return ( (X*X + Y*Y + Z*Z) <= (p_rdvVec.X*p_rdvVec.X + p_rdvVec.Y*p_rdvVec.Y + p_rdvVec.Z*p_rdvVec.Z) );
		__m128d _xmm0, _xmm1, _xmm2;
		_xmm1 = _mm_load_pd(&X);
		_xmm0 = _mm_load_sd(&Z);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm1);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_add_pd(_xmm1, _xmm0);
		_xmm1 = _mm_hadd_pd(_xmm1, _xmm1);

		_xmm2 = _mm_load_pd(&p_rdvVec.X);
		_xmm0 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_mul_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm2 = _mm_add_pd(_xmm2, _xmm0);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);

		return (_mm_comile_sd(_xmm1, _xmm2) != 0);
	}
	INL bool	DVector::operator > (const DVector& p_rdvVec) const
	{	//	return ( (X*X + Y*Y + Z*Z) > (p_rdvVec.X*p_rdvVec.X + p_rdvVec.Y*p_rdvVec.Y + p_rdvVec.Z*p_rdvVec.Z) );
		__m128d _xmm0, _xmm1, _xmm2;
		_xmm1 = _mm_load_pd(&X);
		_xmm0 = _mm_load_sd(&Z);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm1);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_add_pd(_xmm1, _xmm0);
		_xmm1 = _mm_hadd_pd(_xmm1, _xmm1);

		_xmm2 = _mm_load_pd(&p_rdvVec.X);
		_xmm0 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_mul_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm2 = _mm_add_pd(_xmm2, _xmm0);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);

		return (_mm_comigt_sd(_xmm1, _xmm2) != 0);
	}
	INL bool	DVector::operator < (const DVector& p_rdvVec) const
	{	//	return ( (X*X + Y*Y + Z*Z) < (p_rdvVec.X*p_rdvVec.X + p_rdvVec.Y*p_rdvVec.Y + p_rdvVec.Z*p_rdvVec.Z) );
		__m128d _xmm0, _xmm1, _xmm2;
		_xmm1 = _mm_load_pd(&X);
		_xmm0 = _mm_load_sd(&Z);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm1);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_add_pd(_xmm1, _xmm0);
		_xmm1 = _mm_hadd_pd(_xmm1, _xmm1);

		_xmm2 = _mm_load_pd(&p_rdvVec.X);
		_xmm0 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_mul_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm2 = _mm_add_pd(_xmm2, _xmm0);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);

		return (_mm_comilt_sd(_xmm1, _xmm2) != 0);
	}


	INL void	DVector::operator += (const DVector& p_rdvVec)
	{
		X += p_rdvVec.X;	Y += p_rdvVec.Y;	Y += p_rdvVec.Y;
	}
	INL void	DVector::operator -= (const DVector& p_rdvVec)
	{
		X -= p_rdvVec.X;	Y -= p_rdvVec.Y;	Y -= p_rdvVec.Y;
	}

	INL void	DVector::operator *= (const DVector& p_rdvVec)
	{	/*	*this = DVector(	(Y * p_rdvVec.Z) - (Z * p_rdvVec.Y),
								(Z * p_rdvVec.X) - (X * p_rdvVec.Z),
								(X * p_rdvVec.Y) - (Y * p_rdvVec.X) ); */
		__m128d _xmm0, _xmm1, _xmm2, _xmm3;
		_xmm0 = _mm_load_pd(&X);
		_xmm1 = _mm_load_pd(&p_rdvVec.X);

		_xmm3 = _mm_shuffle_pd(_xmm1, _xmm1, 0x1);
		_xmm3 = _mm_mul_pd(_xmm3, _xmm0);
		_xmm2 = _mm_unpackhi_pd(_xmm3, _xmm3);
		_xmm3 = _mm_sub_pd(_xmm3, _xmm2);

		_xmm2 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm2);
		_xmm2 = _mm_load_sd(&Z);
		_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm2);
		_xmm0 = _mm_sub_pd(_xmm0, _xmm1);
		_xmm1 = _mm_load_sd(&g_dNegZero);
		_xmm0 = _mm_xor_pd(_xmm0, _xmm1);
		_xmm0 = _mm_shuffle_pd(_xmm0, _xmm0, 0x1);

		_mm_store_pd(&X, _xmm0);
		_mm_store_pd(&Z, _xmm3);
		W = g_dOne;
	}


	INL void	DVector::operator *= (const double_t p_dScalar)
	{
		X *= p_dScalar;	Y *= p_dScalar;	Z *= p_dScalar;
	}
	INL void	DVector::operator /= (const double_t p_dScalar)
	{
		X /= p_dScalar;	Y /= p_dScalar;	Z /= p_dScalar;
	}
	INL DVector	DVector::operator * (double_t p_dScalar) const
	{
		return DVector(X*p_dScalar, Y*p_dScalar, Z*p_dScalar);
	}
	INL DVector	DVector::operator / (double_t p_dScalar) const
	{
		return DVector(X/p_dScalar, Y/p_dScalar, Z/p_dScalar);
	}


	INL void		VecZero(DVector* p_pdvZero)
	{
		__m128d _xmm0;
		_xmm0 = _mm_load_pd(&g_dvZero.X);
		_mm_store_pd(&p_pdvZero->X, _xmm0);
		_xmm0 = _mm_load_pd(&g_dvZero.Z);
		_mm_store_pd(&p_pdvZero->Z, _xmm0);
	}
	INL void		VecSet(DVector* p_pdvDst, double_t p_dX, double_t p_dY, double_t p_dZ)
	{
		p_pdvDst->X = p_dX;		p_pdvDst->Y = p_dY;		p_pdvDst->Z = p_dZ;		p_pdvDst->W = g_dOne;
	}
	INL void		VecInvert(DVector* p_pdvDst)
	{	// X = -X;		Y = -Y;		Z = -Z;
		__m128d _xmm0, _xmm1;
		_xmm0 = _mm_load_pd(&p_pdvDst->X);
		_xmm1 = _mm_load_pd(&g_dvInvert.X);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm1);
		_mm_store_pd(&p_pdvDst->X, _xmm0);
		_xmm0 = _mm_load_sd(&g_dvZero.Z);
		_xmm0 = _mm_mul_sd(_xmm0, _xmm1);
		_mm_store_sd(&p_pdvDst->Z, _xmm0);
		p_pdvDst->W = g_dOne;
	}
	INL void		VecFloatToDouble(DVector* p_pdvDst, const FVector& p_rfvSrc)
	{	/*	p_pdvDst->X = static_cast<double_t>(p_rfvSrc.X);
			p_pdvDst->Y = static_cast<double_t>(p_rfvSrc.Y);
			p_pdvDst->Z = static_cast<double_t>(p_rfvSrc.Z);
			p_pdvDst->W = static_cast<double_t>(p_rfvSrc.W); */
		__m128 _xmm0;
		__m128d _xmm1;

		_xmm0 = _mm_load_ps(&p_rfvSrc.X);
		_xmm1 = _mm_cvtps_pd(_xmm0);
		_mm_store_pd(&p_pdvDst->X, _xmm1);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x1E); // 00 01 11 10
		_xmm1 = _mm_cvtps_pd(_xmm0);
		_mm_store_pd(&p_pdvDst->Z, _xmm1);
	}

	INL void		VecUnit(DVector* p_pdvUnit, const DVector& p_rdvVec)
	{	/*	*p_pdvUnit = p_rdvVec / p_rdvVec.length(); */
		__m128d _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_pd(&p_rdvVec.X);
		_xmm1 = _mm_load_sd(&p_rdvVec.Z);
		_xmm2 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm3 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm2 = _mm_add_pd(_xmm2, _xmm3);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);
		_xmm2 = _mm_sqrt_sd(_xmm2, _xmm2);
		_xmm2 = _mm_shuffle_pd(_xmm2, _xmm2, 0x0);
		_xmm0 = _mm_div_pd(_xmm0, _xmm2);
		_xmm1 = _mm_div_sd(_xmm1, _xmm2);
		_mm_store_pd(&p_pdvUnit->X, _xmm0);
		_mm_store_sd(&p_pdvUnit->Z, _xmm1);
		p_pdvUnit->W = g_dOne;
	}
	INL void		VecCross(DVector* p_pdvCross, const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{	/*	p_pdvCross->X = p_rdvVec1.Y * p_rdvVec2.Z - p_rdvVec1.Z * p_rdvVec2.Y;
			p_pdvCross->Y = p_rdvVec1.Z * p_rdvVec2.X - p_rdvVec1.X * p_rdvVec2.Z;
			p_pdvCross->Z = p_rdvVec1.X * p_rdvVec2.Y - p_rdvVec1.Y * p_rdvVec2.X;	*/
		__m128d _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_pd(&p_rdvVec2.X);

		_xmm3 = _mm_shuffle_pd(_xmm1, _xmm1, 0x1);
		_xmm3 = _mm_mul_pd(_xmm3, _xmm0);
		_xmm2 = _mm_unpackhi_pd(_xmm3, _xmm3);
		_xmm3 = _mm_sub_pd(_xmm3, _xmm2);

		_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
		_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_sd(_xmm0, _xmm2);
		_xmm2 = _mm_load_pd(&p_rdvVec1.Z);
		_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm2);
		_xmm0 = _mm_sub_pd(_xmm0, _xmm1);
		_xmm1 = _mm_load_sd(&g_dNegZero);
		_xmm0 = _mm_xor_pd(_xmm0, _xmm1);
		_xmm0 = _mm_shuffle_pd(_xmm0, _xmm0, 0x1);

		_mm_store_pd(&p_pdvCross->X, _xmm0);
		_mm_store_sd(&p_pdvCross->Z, _xmm3);
		p_pdvCross->W = g_dOne;
	}
	INL void		VecDot(double_t* p_pdDot, const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{	// *p_pdDot = p_rdvVec1.X*p_rdvVec2.X + p_rdvVec1.Y*p_rdvVec2.Y + p_rdvVec1.Z*p_rdvVec2.Z;
		__m128d _xmm0, _xmm1, _xmm2;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_pd(&p_rdvVec2.X);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm1);
		_xmm1 = _mm_load_sd(&p_rdvVec1.Z);
		_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm2);
		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);
		_mm_store_sd(p_pdDot, _xmm0);
	}
	INL void		VecModulate(DVector* p_pdvMod, const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{	/*	p_pdvMod->X = p_rdvVec1.X*p_rdvVec2.X;
			p_pdvMod->Y = p_rdvVec1.Y*p_rdvVec2.Y;
			p_pdvMod->Z = p_rdvVec1.Z*p_rdvVec2.Z;	*/
		__m128d _xmm0, _xmm1, _xmm2;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_pd(&p_rdvVec2.X);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm1);
		_xmm1 = _mm_load_sd(&p_rdvVec1.Z);
		_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm2);
		_mm_store_pd(&p_pdvMod->X, _xmm0);
		_mm_store_sd(&p_pdvMod->Z, _xmm1);
		p_pdvMod->W = g_dOne;
	}

	INL void		VecNorm(double_t* p_pdNorm, const DVector& p_rdvVec)
	{	// *p_pdNorm = Sqrt(X*X + Y*Y + Z*Z);
		__m128d _xmm0, _xmm1;

		_xmm0 = _mm_load_pd(&p_rdvVec.X);
		_xmm1 = _mm_load_sd(&p_rdvVec.Z);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);
		_xmm0 = _mm_sqrt_sd(_xmm0, _xmm0);
		_mm_store_sd(p_pdNorm, _xmm0);
	}
	INL void		VecSqrNorm(double_t* p_pdSqrNorm, const DVector& p_rdvVec)
	{	// *p_pdNorm = X*X + Y*Y + Z*Z;
		__m128d _xmm0, _xmm1;

		_xmm0 = _mm_load_pd(&p_rdvVec.X);
		_xmm1 = _mm_load_sd(&p_rdvVec.Z);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);
		_mm_store_sd(p_pdSqrNorm, _xmm0);
	}
	INL void		VecAngle(double_t* p_pdDot, const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{	/*	double_t d2Norm = ( Sqrt(p_rdvVec1.X*p_rdvVec1.X + p_rdvVec1.Y*p_rdvVec1.Y + p_rdvVec1.Z*p_rdvVec1.Z) *
								Sqrt(p_rdvVec2.X*p_rdvVec2.X + p_rdvVec2.Y*p_rdvVec2.Y + p_rdvVec2.Z*p_rdvVec2.Z) );
			if (d2Norm < g_dSPrc) throw VECTOR_DIVIDEBYZERO;
			*p_pdDot = ArcCos( (p_rdvVec1.X*p_rdvVec2.X + p_rdvVec1.Y*p_rdvVec2.Y + p_rdvVec1.Z*p_rdvVec2.Z) / d2Norm );	*/
		__m128d _xmm0, _xmm1, _xmm2, _xmm3, _xmm4, _xmm5;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_sd(&p_rdvVec1.Z);
		_xmm2 = _mm_load_pd(&p_rdvVec2.X);
		_xmm3 = _mm_load_sd(&p_rdvVec2.Z);

		_xmm4 = _mm_mul_pd(_xmm0, _xmm2);
		_xmm5 = _mm_mul_sd(_xmm1, _xmm3);

		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm2 = _mm_mul_pd(_xmm2, _xmm2);
		_xmm3 = _mm_mul_sd(_xmm3, _xmm3);

		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);
		_xmm0 = _mm_sqrt_sd(_xmm0, _xmm0);
		_xmm2 = _mm_add_pd(_xmm2, _xmm3);
		_xmm2 = _mm_hadd_pd(_xmm2, _xmm2);
		_xmm2 = _mm_sqrt_sd(_xmm2, _xmm2);
		_xmm0 = _mm_mul_sd(_xmm0, _xmm2);

		_xmm1 = _mm_load_sd(&g_dSPrc);
		if (_mm_comile_sd(_xmm0, _xmm1)) throw VECTOR_DIVIDEBYZERO;
		_xmm4 = _mm_add_pd(_xmm4, _xmm5);
		_xmm4 = _mm_hadd_pd(_xmm4, _xmm4);
		_xmm4 = _mm_div_sd(_xmm4, _xmm0);

		*p_pdDot = ArcCos(_xmm4.m128d_f64[0]);
	}
	INL void		VecDistance(double_t* p_pdDist, const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{	/*	return (Sqrt(	(p_rdvVec1.X-p_rdvVec2.X)*(p_rdvVec1.X-p_rdvVec2.X) +
							(p_rdvVec1.Y-p_rdvVec2.Y)*(p_rdvVec1.Y-p_rdvVec2.Y) +
							(p_rdvVec1.Z-p_rdvVec2.Z)*(p_rdvVec1.Z-p_rdvVec2.Z)) );	*/
		__m128d _xmm0, _xmm1, _xmm2;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_pd(&p_rdvVec2.X);
		_xmm0 = _mm_sub_pd(_xmm0, _xmm1);
		_xmm1 = _mm_load_sd(&p_rdvVec1.Z);
		_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
		_xmm1 = _mm_sub_sd(_xmm1, _xmm2);

		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);
		_xmm0 = _mm_sqrt_sd(_xmm0, _xmm0);
		_mm_store_sd(p_pdDist, _xmm0);
	}

	INL bool		VecBitEqual(const DVector& p_rdvVec1, const DVector& p_rdvVec2)
	{
		return ((p_rdvVec1.X == p_rdvVec2.X) && (p_rdvVec1.Y == p_rdvVec2.Y) && (p_rdvVec1.Z == p_rdvVec2.Z));
	}
	INL bool		VecSqrNormEqual(const DVector& p_rdvVec1, const DVector& p_rdvVec2, double_t p_dErr)
	{	/*	double_t dVec1SL = p_rdvVec1.X*p_rdvVec1.X + p_rdvVec1.Y*p_rdvVec1.Y + p_rdvVec1.Z*p_rdvVec1.Z;
			double_t dVec2SL = p_rdvVec2.X*p_rdvVec2.X + p_rdvVec2.Y*p_rdvVec2.Y + p_rdvVec2.Z*p_rdvVec2.Z;
			return TRange<double_t>(dVec1SL, dVec2SL-p_dErr, dVec2SL+p_dErr); */
		__m128d _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_pd(&p_rdvVec1.X);
		_xmm1 = _mm_load_sd(&p_rdvVec1.Z);
		_xmm0 = _mm_mul_pd(_xmm0, _xmm0);
		_xmm1 = _mm_mul_sd(_xmm1, _xmm1);
		_xmm0 = _mm_add_pd(_xmm0, _xmm1);
		_xmm0 = _mm_hadd_pd(_xmm0, _xmm0);

		_xmm1 = _mm_load_pd(&p_rdvVec2.X);
		_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
		_xmm1 = _mm_mul_pd(_xmm1, _xmm1);
		_xmm2 = _mm_mul_sd(_xmm2, _xmm2);
		_xmm1 = _mm_add_pd(_xmm1, _xmm2);
		_xmm1 = _mm_hadd_pd(_xmm1, _xmm1);

		_xmm3 = _mm_load_sd(&p_dErr);
		_xmm2 = _xmm1;
		_xmm2 = _mm_sub_sd(_xmm2, _xmm3);
		_xmm3 = _mm_add_sd(_xmm3, _xmm1);
		return (_mm_comige_sd(_xmm0, _xmm2) && _mm_comile_sd(_xmm0, _xmm3));
	}

	


} // namespace KiLL


#endif // __KiLL_Vector_INL__