
/***********************************************************************************************************************************
 *	File : "KiLLVector.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Vector_H__
#define __KiLL_Vector_H__


namespace KiLL
{
/*=================================================================================================================================
 * --- 2D Float Vector ----------------------------------------------------------------------------------------------------------*/

	class F2Vector
	{
		public:

		float_t	X,
				Y;

		INL			F2Vector();
		INL			F2Vector(float_t p_fX, float_t p_fY) : X(p_fX), Y(p_fY) {}
		INL			F2Vector(const F2Vector& p_rf2Vec) : X(p_rf2Vec.X), Y(p_rf2Vec.Y) {}
		//INL		~_T2Vector() {} Because of the /EHsc command line option (in VSC) wich unwinds class in case of exeption
		//			throwing, it doesnt inline some fonctions of the class if that class has a specific custom destructor.


		INL void	operator = (const F2Vector& p_rf2vSrc);
		INL F2Vector	operator ~ () const;


		INL bool	operator >= (const F2Vector& p_rf2Vec) const;
		INL bool	operator <= (const F2Vector& p_rf2Vec) const;
		INL bool	operator > (const F2Vector& p_rf2Vec) const;
		INL bool	operator < (const F2Vector& p_rf2Vec) const;


		INL void		operator += (const F2Vector& p_rf2Vec);
		INL void		operator -= (const F2Vector& p_rf2Vec);
		friend INL F2Vector	operator + (const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
		{
			return F2Vector(	(p_rf2Vec1.X + p_rf2Vec2.X),
								(p_rf2Vec1.Y + p_rf2Vec2.Y) );
		}
		friend INL F2Vector	operator - (const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
		{
			return F2Vector(	(p_rf2Vec1.X - p_rf2Vec2.X),
								(p_rf2Vec1.Y - p_rf2Vec2.Y) );
		}

		INL void		operator *= (const F2Vector& p_rf2Vec);
		friend INL F2Vector	operator * (const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
		{
			return F2Vector(p_rf2Vec1.X*p_rf2Vec2.Y, p_rf2Vec1.Y*p_rf2Vec2.X);
		}


		INL void	operator *= (float_t p_fScalar);
		INL void	operator /= (float_t p_fScalar);
		INL F2Vector	operator * (float_t p_fScalar) const;
		friend INL F2Vector	operator * (float_t p_fScalar, const F2Vector& p_rf2Vec)
		{
			return F2Vector(p_rf2Vec.X*p_fScalar, p_rf2Vec.Y*p_fScalar);
		}
		INL F2Vector	operator / (float_t p_fScalar) const;


		friend INL float_t	operator | (const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2)
		{
			return (p_rf2Vec1.X*p_rf2Vec2.X + p_rf2Vec1.Y*p_rf2Vec2.Y);
		}

	};


	INL void		VecZero(F2Vector* p_pf2Zero);
	INL void		VecSet(F2Vector* p_pf2Dst, float_t p_fX, float_t p_fY);
	INL void		VecInvert(F2Vector* p_pf2Dst);

	INL void		VecCross(F2Vector* p_pf2Cross, const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2);
	INL void		VecDot(float_t* p_pfDot, const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2);

	INL void		VecNorm(float_t* p_pfNorm, const F2Vector& p_rf2Vec);

	INL bool		VecBitEqual(const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2);
	INL bool		VecSqrNormEqual(const F2Vector& p_rf2Vec1, const F2Vector& p_rf2Vec2, float_t p_fErr);




/*=================================================================================================================================
 * --- 4D Float Precision Vector ------------------------------------------------------------------------------------------------*/

	class ALIGN_16BYTE FVector			// fv, ptr: pfv, ref: rfv
	{
	public:

		float_t X, 
				Y,
				Z,
				W;

		INL			FVector() {};
		INL			FVector(float_t p_fX, float_t p_fY, float_t p_fZ) : X(p_fX), Y(p_fY), Z(p_fZ), W(g_fOne) {}
		INL			FVector(const FVector& p_rfvVec);
		//INL		~FVector() {}  Because of the /EHsc command line option (in VSC) wich unwinds class in case of exeption
		//			throwing, it doesnt inline some fonctions of the class if that class has a specific custom destructor.


		INL void	operator = (const FVector& p_rfvSrc);


		INL bool	operator >= (const FVector& p_rfvVec) const;
		INL bool	operator <= (const FVector& p_rfvVec) const;
		INL bool	operator > (const FVector& p_rfvVec) const;
		INL bool	operator < (const FVector& p_rfvVec) const;

		
		INL void	operator += (const FVector& p_rfvVec);
		INL void	operator -= (const FVector& p_rfvVec);
		friend INL FVector	operator + (const FVector& p_rfvVec1, const FVector& p_rfvVec2)
		{
			// return FVector(p_rfvVec1.X+p_rfvVec2.X, p_rfvVec1.Y+p_rfvVec2.Y, p_rfvVec1.Z+p_rfvVec2.Z);
			FVector fvAdd;
			__m128 _xmm0, _xmm1;
			_xmm0 = _mm_load_ps(&p_rfvVec1.X);
			_xmm1 = _mm_load_ps(&p_rfvVec2.X);
			_xmm0 = _mm_add_ps(_xmm0, _xmm1);
			_mm_store_ps(&fvAdd.X, _xmm0);
			return fvAdd;
		}
		friend INL FVector	operator - (const FVector& p_rfvVec1, const FVector& p_rfvVec2)
		{
			// return FVector(p_rfvVec1.X-p_rfvVec2.X, p_rfvVec1.Y-p_rfvVec2.Y, p_rfvVec1.Z-p_rfvVec2.Z);
			FVector fvSub;
			__m128 _xmm0, _xmm1;
			_xmm0 = _mm_load_ps(&p_rfvVec1.X);
			_xmm1 = _mm_load_ps(&p_rfvVec2.X);
			_xmm0 = _mm_sub_ps(_xmm0, _xmm1);
			_mm_store_ps(&fvSub.X, _xmm0);
			return fvSub;
		}

		INL void	operator *= (const FVector& p_rfvVec);
		friend INL FVector	operator * (const FVector& p_rfvVec1, const FVector& p_rfvVec2)
		{
			/*	return FVector((p_rfvVec1.Y * p_rfvVec2.Z) - (p_rfvVec1.Z * p_rfvVec2.Y),
								(p_rfvVec1.Z * p_rfvVec2.X) - (p_rfvVec1.X * p_rfvVec2.Z),
								(p_rfvVec1.X * p_rfvVec2.Y) - (p_rfvVec1.Y * p_rfvVec2.X) );	*/
			FVector fvCross;
			__m128 _xmm0, _xmm1, _xmm2, _xmm3;
			_xmm0 = _mm_load_ps(&p_rfvVec1.X);
			_xmm1 = _mm_load_ps(&p_rfvVec2.X);
			_xmm2 = _mm_shuffle_ps(_xmm1, _xmm1, 0xC9);
			_xmm2 = _mm_mul_ps(_xmm2, _xmm0);
			_xmm2 = _mm_shuffle_ps(_xmm2, _xmm2, 0xC9);
			_xmm3 = _mm_shuffle_ps(_xmm1, _xmm1, 0xD2);
			_xmm3 = _mm_mul_ps(_xmm3, _xmm0);
			_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xD2);
			_xmm0 = _mm_sub_ps(_xmm2, _xmm3);
			_mm_store_ps(&fvCross.X, _xmm0);
			return fvCross;
		}


		INL void	operator *= (const float_t p_fScalar);
		INL void	operator /= (const float_t p_fScalar);
		INL FVector	operator * (float_t p_fScalar) const;
		friend INL FVector	operator * (float_t p_fScalar, const FVector& p_rfv3Vec)
		{
			return FVector(p_rfv3Vec.X*p_fScalar, p_rfv3Vec.Y*p_fScalar, p_rfv3Vec.Z*p_fScalar);
		}
		INL FVector		operator / (float_t p_fScalar) const;


		friend INL float_t	operator | (const FVector& p_rfvVec1, const FVector& p_rfvVec2)
		{
			return (p_rfvVec1.X*p_rfvVec2.X + p_rfvVec1.Y*p_rfvVec2.Y + p_rfvVec1.Z*p_rfvVec2.Z);
		}

	};


	INL void		VecZero(FVector* p_pfvZero);
	INL void		VecSet(FVector* p_pfvDst, float_t p_fX, float_t p_fY, float_t p_fZ);
	INL void		VecInvert(FVector* p_pfvDst, const FVector& p_rfvVec);
	INL void		VecDoubleToFloat(FVector* p_pfvDst, const DVector& p_rdvSrc);

	INL void		VecUnit(FVector* p_pfvUnit, const FVector& p_rfvVec);
	INL void		VecCross(FVector* p_pfvCross, const FVector& p_rfvVec1, const FVector& p_rfvVec2);
	INL void		VecDot(float_t* p_pfDot, const FVector& p_rfvVec1, const FVector& p_rfvVec2);
	INL void		VecModulate(FVector* p_pfvMod, const FVector& p_rfvVec1, const FVector& p_rfvVec2);

	INL void		VecNorm(float_t* p_pfNorm, const FVector& p_rfvVec);
	INL void		VecSqrNorm(float_t* p_pfSqrNorm, const FVector& p_rfvVec);
	INL void		VecAngle(float_t* p_pfAngle, const FVector& p_rfvVec1, const FVector& p_rfvVec2);
	INL void		VecDistance(float_t* p_pfDist, const FVector& p_rfvVec1, const FVector& p_rfvVec2);

	INL bool		VecBitEqual(const FVector& p_rfvVec1, const FVector& p_rfvVec2);
	INL bool		VecSqrNormEqual(const FVector& p_rfvVec1, const FVector& p_rfvVec2, float_t p_fErr);
	
	void			VecReflect(FVector* p_pfvDirection, const FVector& p_rfvNorm);
	void			VecReflect(FVector* p_pfvReflection, const FVector& p_rfvDirection, const FVector& p_rfvNorm);
	void			VecReflect(FVector* p_pfvDirection, const FPlane& p_rfplPlane);
	void			VecReflect(FVector* p_pfvReflection, const FVector& p_rfvDirection, const FPlane& p_rfplPlane);

	void			VecRotate(FVector* p_pfvVec, const FMatrix& p_rfmxMx);
	void			VecRotate(FVector* p_pfvRot, const FVector& p_rfvVec, const FMatrix& p_rfmxMx);
	void			VecRotTransp(FVector* p_pfvVec, const FMatrix& p_rfmxMx);
	void			VecRotTransp(FVector* p_pfvRot, const FVector& p_rfvVec, const FMatrix& p_rfmxMx);




/*=================================================================================================================================
 * --- 4D Double Precision Vector -----------------------------------------------------------------------------------------------*/

	class ALIGN_16BYTE DVector			// dv, ptr: pdv, ref: rdv
	{
	public:

		double_t X, 
				 Y,
				 Z,
				 W;

		INL			DVector() {};
		INL			DVector(double_t p_dX, double_t p_dY, double_t p_dZ) : X(p_dX), Y(p_dY), Z(p_dZ), W(g_dOne) {}
		INL			DVector(const DVector& p_rdvVec);
		//INL		~DVector() {}  Because of the /EHsc command line option (in VSC) wich unwinds class in case of exeption
		//			throwing, it doesnt inline some fonctions of the class if that class has a specific custom destructor.


		INL void	operator = (const DVector& p_rdvSrc);


		INL bool	operator >= (const DVector& p_rdvVec) const;
		INL bool	operator <= (const DVector& p_rdvVec) const;
		INL bool	operator > (const DVector& p_rdvVec) const;
		INL bool	operator < (const DVector& p_rdvVec) const;

		
		INL void	operator += (const DVector& p_rdvVec);
		INL void	operator -= (const DVector& p_rdvVec);
		friend INL DVector	operator + (const DVector& p_rdvVec1, const DVector& p_rdvVec2)
		{
			// return DVector(p_rdvVec1.X+p_rdvVec2.X, p_rdvVec1.Y+p_rdvVec2.Y, p_rdvVec1.Z+p_rdvVec2.Z);
			DVector dvAdd;
			__m128d _xmm0, _xmm1;
			_xmm0 = _mm_load_pd(&p_rdvVec1.X);
			_xmm1 = _mm_load_pd(&p_rdvVec2.X);
			_xmm0 = _mm_add_pd(_xmm0, _xmm1);
			_mm_store_pd(&dvAdd.X, _xmm0);
			_xmm0 = _mm_load_sd(&p_rdvVec1.Z);
			_xmm1 = _mm_load_sd(&p_rdvVec2.Z);
			_xmm0 = _mm_add_sd(_xmm0, _xmm1);
			_mm_store_sd(&dvAdd.Z, _xmm0);
			dvAdd.W = g_dOne;
			return dvAdd;
		}
		friend INL DVector	operator - (const DVector& p_rdvVec1, const DVector& p_rdvVec2)
		{
			// return DVector(p_rdvVec1.X-p_rdvVec2.X, p_rdvVec1.Y-p_rdvVec2.Y, p_rdvVec1.Z-p_rdvVec2.Z);
			DVector dvSub;
			__m128d _xmm0, _xmm1;
			_xmm0 = _mm_load_pd(&p_rdvVec1.X);
			_xmm1 = _mm_load_pd(&p_rdvVec2.X);
			_xmm0 = _mm_sub_pd(_xmm0, _xmm1);
			_mm_store_pd(&dvSub.X, _xmm0);
			_xmm0 = _mm_load_sd(&p_rdvVec1.Z);
			_xmm1 = _mm_load_sd(&p_rdvVec2.Z);
			_xmm0 = _mm_sub_sd(_xmm0, _xmm1);
			_mm_store_sd(&dvSub.Z, _xmm0);
			dvSub.W = g_dOne;
			return dvSub;
		}

		INL void	operator *= (const DVector& p_rdvVec);
		friend INL DVector	operator * (const DVector& p_rdvVec1, const DVector& p_rdvVec2)
		{
			/*	return DVector((p_rdvVec1.Y * p_rdvVec2.Z) - (p_rdvVec1.Z * p_rdvVec2.Y),
								(p_rdvVec1.Z * p_rdvVec2.X) - (p_rdvVec1.X * p_rdvVec2.Z),
								(p_rdvVec1.X * p_rdvVec2.Y) - (p_rdvVec1.Y * p_rdvVec2.X) );	*/
			DVector dvCross;
			__m128d _xmm0, _xmm1, _xmm2, _xmm3;
			_xmm0 = _mm_load_pd(&p_rdvVec1.X);
			_xmm1 = _mm_load_pd(&p_rdvVec2.X);

			_xmm3 = _mm_shuffle_pd(_xmm1, _xmm1, 0x1);
			_xmm3 = _mm_mul_pd(_xmm3, _xmm0);
			_xmm2 = _mm_unpackhi_pd(_xmm3, _xmm3);
			_xmm3 = _mm_sub_pd(_xmm3, _xmm2);

			_xmm2 = _mm_load_sd(&p_rdvVec2.Z);
			_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
			_xmm0 = _mm_mul_pd(_xmm0, _xmm2);
			_xmm2 = _mm_load_sd(&p_rdvVec1.Z);
			_xmm2 = _mm_unpacklo_pd(_xmm2, _xmm2);
			_xmm1 = _mm_mul_pd(_xmm1, _xmm2);
			_xmm0 = _mm_sub_pd(_xmm0, _xmm1);
			_xmm1 = _mm_load_sd(&g_dNegZero);
			_xmm0 = _mm_xor_pd(_xmm0, _xmm1);
			_xmm0 = _mm_shuffle_pd(_xmm0, _xmm0, 0x1);

			_mm_store_pd(&dvCross.X, _xmm0);
			_mm_store_sd(&dvCross.Z, _xmm3);
			dvCross.W = g_dOne;

			return dvCross;
		}


		INL void	operator *= (const double_t p_dScalar);
		INL void	operator /= (const double_t p_dScalar);
		INL DVector	operator * (double_t p_dScalar) const;
		friend INL DVector	operator * (double_t p_dScalar, const DVector& p_rdvVec)
		{
			return DVector(p_rdvVec.X*p_dScalar, p_rdvVec.Y*p_dScalar, p_rdvVec.Z*p_dScalar);
		}
		INL DVector		operator / (double_t p_dScalar) const;


		friend INL double_t	operator | (const DVector& p_rdvVec1, const DVector& p_rdvVec2)
		{
			return (p_rdvVec1.X*p_rdvVec2.X + p_rdvVec1.Y*p_rdvVec2.Y + p_rdvVec1.Z*p_rdvVec2.Z);
		}

	};


	INL void		VecZero(DVector* p_pdvZero);
	INL void		VecSet(DVector* p_pdvDst, double_t p_dX, double_t p_dY, double_t p_dZ);
	INL void		VecInvert(DVector* p_pdvDst);
	INL void		VecFloatToDouble(DVector* p_pd3vDst, const FVector& p_rfvSrc);

	INL void		VecUnit(DVector* p_pdvUnit, const DVector& p_rdvVec);
	INL void		VecCross(DVector* p_pdvCross, const DVector& p_rdvVec1, const DVector& p_rdvVec2);
	INL void		VecDot(double_t* p_pdDot, const DVector& p_rdvVec1, const DVector& p_rdvVec2);
	INL void		VecModulate(DVector* p_pdvMod, const DVector& p_rdvVec1, const DVector& p_rdvVec2);

	INL void		VecNorm(double_t* p_pdNorm, const DVector& p_rdvVec);
	INL void		VecSqrNorm(double_t* p_pdSqrNorm, const DVector& p_rdvVec);
	INL void		VecAngle(double_t* p_pdDot, const DVector& p_rdvVec1, const DVector& p_rdvVec2);
	INL void		VecDistance(double_t* p_pdDist, const DVector& p_rdvVec1, const DVector& p_rdvVec2);

	INL bool		VecBitEqual(const DVector& p_rdvVec1, const DVector& p_rdvVec2);
	INL bool		VecSqrNormEqual(const DVector& p_rdvVec1, const DVector& p_rdvVec2, double_t p_dErr);

	void			VecReflect(DVector* p_pdvDirection, const DVector& p_rd3vNorm);
	void			VecReflect(DVector* p_pdvReflection, const DVector& p_rdvDirection, const DVector& p_rdvNorm);
	void			VecReflect(DVector* p_pdvDirection, const DPlane& p_rdplPlane);
	void			VecReflect(DVector* p_pdvReflection, const DVector& p_rdvDirection, const DPlane& p_rdplPlane);

	void			VecRotate(DVector* p_pdvVec, const DMatrix& p_rdmxMx);
	void			VecRotate(DVector* p_pdvRot, const DVector& p_rdvVec, const DMatrix& p_rdmxMx);
	void			VecRotTransp(DVector* p_pdvVec, const DMatrix& p_rdmxMx);
	void			VecRotTransp(DVector* p_pdvRot, const DVector& p_rdvVec, const DMatrix& p_rdmxMx);




/*=================================================================================================================================
 * --- Floating Number Vector Constants -----------------------------------------------------------------------------------------*/

	static const F2Vector	g_f2vZero(g_fZero, g_fZero);

	static const FVector	g_fvZero(g_fZero, g_fZero, g_fZero);
	static const FVector	g_fvInvert(g_fNegOne, g_fNegOne, g_fNegOne);

	static const DVector	g_dvZero(g_dZero, g_dZero, g_dZero);
	static const DVector	g_dvInvert(g_dNegOne, g_dNegOne, g_dNegOne);




} // namespace KiLL

#include "KiLLVector.inl"


#endif // __KiLL_Math_H__