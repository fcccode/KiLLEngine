
/***********************************************************************************************************************************
 *	File : "KiLLMatrix.cpp"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#include "Core.h"


namespace KiLL
{

/*=================================================================================================================================
 * --- 4D Float Precision Vector ------------------------------------------------------------------------------------------------*/

	void		VecReflect(FVector* p_pfvDirection, const FVector& p_rfvNorm)
	{	// *p_pfvDirection = (p_rfvNorm * ((p_rfvDirection | p_rfvNorm) * (-2.0f)) + p_rfvDirection);
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_ps(&p_pfvDirection->X);
		_xmm1 = _mm_load_ps(&p_rfvNorm.X);
		_xmm2 = _mm_mul_ps(_xmm0, _xmm1);
		_xmm3 = _xmm2;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_sub_ps(_xmm2, _xmm3);

		_xmm3 = _mm_load_ss(&g_fNegTwo);
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0x00); // 00 00 00 00
		_xmm2 = _mm_mul_ps(_xmm2, _xmm3);

		_xmm2 = _mm_mul_ps(_xmm2, _xmm1);
		_xmm2 = _mm_add_ps(_xmm2, _xmm0);
		_mm_store_ps(&p_pfvDirection->X, _xmm2);
		p_pfvDirection->W = g_fOne;
	}
	void		VecReflect(FVector* p_pfvReflection, const FVector& p_rfvDirection, const FVector& p_rfvNorm)
	{
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_ps(&p_rfvDirection.X);
		_xmm1 = _mm_load_ps(&p_rfvNorm.X);
		_xmm2 = _mm_mul_ps(_xmm0, _xmm1);
		_xmm3 = _xmm2;
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0xFF); // 11 11 11 11
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_hadd_ps(_xmm2, _xmm2);
		_xmm2 = _mm_sub_ps(_xmm2, _xmm3);

		_xmm3 = _mm_load_ss(&g_fNegTwo);
		_xmm3 = _mm_shuffle_ps(_xmm3, _xmm3, 0x00); // 00 00 00 00
		_xmm2 = _mm_mul_ps(_xmm2, _xmm3);

		_xmm2 = _mm_mul_ps(_xmm2, _xmm1);
		_xmm2 = _mm_add_ps(_xmm2, _xmm0);
		_mm_store_ps(&p_pfvReflection->X, _xmm2);
		p_pfvReflection->W = g_fOne;
	}
	void		VecReflect(FVector* p_pfvDirection, const FPlane& p_rfplPlane);
	void		VecReflect(FVector* p_pfvReflection, const FVector& p_rfvDirection, const FPlane& p_rfplPlane);

	void		VecRotate(FVector* p_pfvVec, const FMatrix& p_rfmxMx);
	void		VecRotate(FVector* p_pfvRot, const FVector& p_rfvVec, const FMatrix& p_rfmxMx);
	void		VecRotTransp(FVector* p_pfvVec, const FMatrix& p_rfmxMx);
	void		VecRotTransp(FVector* p_pfvRot, const FVector& p_rfvVec, const FMatrix& p_rfmxMx);




/*=================================================================================================================================
 * --- 4D Double Precision Vector -----------------------------------------------------------------------------------------------*/

	void		VecReflect(DVector* p_pdvDirection, const DVector& p_rdvNorm)
	{
		double_t dDot = ((*p_pdvDirection) | p_rdvNorm) * (-2.0);
		p_pdvDirection->X = p_rdvNorm.X * dDot  + p_pdvDirection->X;
		p_pdvDirection->Y = p_rdvNorm.Y * dDot  + p_pdvDirection->Y;
		p_pdvDirection->Z = p_rdvNorm.Z * dDot  + p_pdvDirection->Z;
	}
	void		VecReflect(DVector* p_pdvReflection, const DVector& p_rdvDirection, const DVector& p_rdvNorm)
	{
		double_t dDot = (p_rdvDirection | p_rdvNorm) * (-2.0);
		p_pdvReflection->X = p_rdvNorm.X * dDot  + p_rdvDirection.X;
		p_pdvReflection->Y = p_rdvNorm.Y * dDot  + p_rdvDirection.Y;
		p_pdvReflection->Z = p_rdvNorm.Z * dDot  + p_rdvDirection.Z;
	}
	void		VecReflect(DVector* p_pdvDirection, const DPlane& p_rdplPlane);
	void		VecReflect(DVector* p_pdvReflection, const DVector& p_rdvDirection, const DPlane& p_rdplPlane);

	void		VecRotate(DVector* p_pdvVec, const DMatrix& p_rdmxMx);
	void		VecRotate(DVector* p_pdvRot, const DVector& p_rdvVec, const DMatrix& p_rdmxMx);
	void		VecRotTransp(DVector* p_pdvVec, const DMatrix& p_rdmxMx);
	void		VecRotTransp(DVector* p_pdvRot, const DVector& p_rdvVec, const DMatrix& p_rdmxMx);




} // namespace KiLL