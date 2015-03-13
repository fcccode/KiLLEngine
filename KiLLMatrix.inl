
/***********************************************************************************************************************************
 *	File : "KiLLMatrix.inl"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Matrix_INL__
#define __KiLL_Matrix_INL__



namespace KiLL
{

/*=================================================================================================================================
 * --- 4D Float Matrix ----------------------------------------------------------------------------------------------------------*/

	INL		FMatrix::FMatrix(const FMatrix& p_rfmxMx)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(&p_rfmxMx.m11);
		_mm_store_ps(&m11, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m12);
		_mm_store_ps(&m12, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m13);
		_mm_store_ps(&m13, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m14);
		_mm_store_ps(&m14, _xmm0);
	}
	INL		FMatrix::FMatrix(const ALIGN_16BYTE float_t* p_pfMatrix)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(p_pfMatrix);
		_mm_store_ps(&m11, _xmm0);
		_xmm0 = _mm_load_ps(p_pfMatrix+16);
		_mm_store_ps(&m12, _xmm0);
		_xmm0 = _mm_load_ps(p_pfMatrix+32);
		_mm_store_ps(&m13, _xmm0);
		_xmm0 = _mm_load_ps(p_pfMatrix+48);
		_mm_store_ps(&m14, _xmm0);
	}
	INL		FMatrix::FMatrix(   float_t p_fm11, float_t p_fm12, float_t p_fm13, float_t p_fm14,
								float_t p_fm21, float_t p_fm22, float_t p_fm23, float_t p_fm24,
								float_t p_fm31, float_t p_fm32, float_t p_fm33, float_t p_fm34,
								float_t p_fm41, float_t p_fm42, float_t p_fm43, float_t p_fm44 )
	{
		m11 = p_fm11;	m12 = p_fm12;	m13 = p_fm13;	m14 = p_fm14;
		m21 = p_fm21;	m22 = p_fm22;	m23 = p_fm23;	m24 = p_fm24;
		m31 = p_fm31;	m32 = p_fm32;	m33 = p_fm33;	m34 = p_fm34;
		m41 = p_fm41;	m42 = p_fm42;	m43 = p_fm43;	m44 = p_fm44;
	}


	INL void	FMatrix::operator = (const FMatrix& p_rfmxMx)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(&p_rfmxMx.m11);
		_mm_store_ps(&m11, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m12);
		_mm_store_ps(&m12, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m13);
		_mm_store_ps(&m13, _xmm0);
		_xmm0 = _mm_load_ps(&p_rfmxMx.m14);
		_mm_store_ps(&m14, _xmm0);
	}


	INL void	FMatrix::operator *= (float_t p_fScalar)
	{
		__m128 _xmmScalar, _xmm0;

		_xmmScalar = _mm_load_ss(&p_fScalar);
		_xmmScalar = _mm_shuffle_ps(_xmmScalar, _xmmScalar, 0x00); // 00 00 00 00
		_xmm0 = _mm_load_ps(&m11);
		_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m11, _xmm0);
		_xmm0 = _mm_load_ps(&m12);
		_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m12, _xmm0);
		_xmm0 = _mm_load_ps(&m13);
		_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m13, _xmm0);
		_xmm0 = _mm_load_ps(&m14);
		_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m14, _xmm0);
	}
	INL void	FMatrix::operator /= (float_t p_fScalar)
	{
		__m128 _xmmScalar, _xmm0;

		_xmmScalar = _mm_load_ss(&p_fScalar);
		_xmm0 = _mm_load_ss(&g_fSPrc);
		if (_mm_comile_ss(_xmmScalar, _xmm0)) throw MATRIX_DIVIDEBYZERO;

		_xmmScalar = _mm_shuffle_ps(_xmmScalar, _xmmScalar, 0x00);
		_xmm0 = _mm_load_ps(&m11);
		_xmm0 = _mm_div_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m11, _xmm0);
		_xmm0 = _mm_load_ps(&m12);
		_xmm0 = _mm_div_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m12, _xmm0);
		_xmm0 = _mm_load_ps(&m13);
		_xmm0 = _mm_div_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m13, _xmm0);
		_xmm0 = _mm_load_ps(&m14);
		_xmm0 = _mm_div_ps(_xmm0, _xmmScalar);
		_mm_store_ps(&m14, _xmm0);
	}


	INL FVector	FMatrix::operator * (const FVector& p_rfvVec) const
	{	/*
		return FVector(p_rfvVec.X*m11 + p_rfvVec.Y*m12 + p_rfvVec.Z*m13 + m14,
						p_rfvVec.X*m21 + p_rfvVec.Y*m22 + p_rfvVec.Z*m23 + m24,
						p_rfvVec.X*m31 + p_rfvVec.Y*m32 + p_rfvVec.Z*m33 + m34 ); */
		FVector fvRet;
		__m128 _xmm0, _xmm1, _xmm2, _xmm3;

		_xmm0 = _mm_load_ps(&p_rfvVec.X);
		_xmm1 = _mm_shuffle_ps(_xmm0, _xmm0, 0x55); // 01 01 01 01
		_xmm2 = _mm_shuffle_ps(_xmm0, _xmm0, 0xAA); // 10 10 10 10
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x00); // 00 00 00 00

		_xmm3 = _mm_load_ps(&m11);
		_xmm0 = _mm_mul_ps(_xmm0, _xmm3);
		_xmm3 = _mm_load_ps(&m12);
		_xmm1 = _mm_mul_ps(_xmm1, _xmm3);
		_xmm3 = _mm_load_ps(&m13);
		_xmm2 = _mm_mul_ps(_xmm2, _xmm3);
		_xmm3 = _mm_load_ps(&m14);
		_xmm0 = _mm_add_ps(_xmm0, _xmm1);
		_xmm2 = _mm_add_ps(_xmm2, _xmm3);
		_xmm0 = _mm_add_ps(_xmm0, _xmm2);
		_mm_store_ps(&fvRet.X, _xmm0);
		fvRet.W = g_fOne;
		return fvRet;
	}




/*=================================================================================================================================
 * --- Matrix General Functions -------------------------------------------------------------------------------------------------*/

	/* 4D Float precision -------------------------------------------------------------*/
	INL void	MxIdentity(FMatrix* p_pfmxIdentity)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxIdentity->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxIdentity->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxIdentity->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxIdentity->m14, _xmm0);
	}
	INL void	MxSet(FMatrix* p_pfmxDst,	float_t p_fm11, float_t p_fm12, float_t p_fm13, float_t p_fm14,
											float_t p_fm21, float_t p_fm22, float_t p_fm23, float_t p_fm24,
											float_t p_fm31, float_t p_fm32, float_t p_fm33, float_t p_fm34,
											float_t p_fm41, float_t p_fm42, float_t p_fm43, float_t p_fm44 )
	{
		p_pfmxDst->m11 = p_fm11;	p_pfmxDst->m12 = p_fm12;	p_pfmxDst->m13 = p_fm13;	p_pfmxDst->m14 = p_fm14;
		p_pfmxDst->m21 = p_fm21;	p_pfmxDst->m22 = p_fm22;	p_pfmxDst->m23 = p_fm23;	p_pfmxDst->m24 = p_fm24;
		p_pfmxDst->m31 = p_fm31;	p_pfmxDst->m32 = p_fm32;	p_pfmxDst->m33 = p_fm33;	p_pfmxDst->m34 = p_fm34;
		p_pfmxDst->m41 = p_fm41;	p_pfmxDst->m42 = p_fm42;	p_pfmxDst->m43 = p_fm43;	p_pfmxDst->m44 = p_fm44;
	}
	INL float_t MxDeterminant(float_t* p_pfDet, const FMatrix& p_rfmxMx)
	{
		float_t fdet41 = g_fZero, fdet42 = g_fZero, fdet43 = g_fZero, fdet44;

		if (p_rfmxMx.m41 != g_fZero) {
			fdet41 = p_rfmxMx.m12*(p_rfmxMx.m23*p_rfmxMx.m34 - p_rfmxMx.m33*p_rfmxMx.m24) - p_rfmxMx.m22*(p_rfmxMx.m13*p_rfmxMx.m34 - p_rfmxMx.m33*p_rfmxMx.m14)
						+ p_rfmxMx.m32*(p_rfmxMx.m13*p_rfmxMx.m24 - p_rfmxMx.m23*p_rfmxMx.m14);
		}
		if (p_rfmxMx.m42 != g_fZero) {
			fdet42 = p_rfmxMx.m11*(p_rfmxMx.m23*p_rfmxMx.m24 - p_rfmxMx.m33*p_rfmxMx.m24) - p_rfmxMx.m21*(p_rfmxMx.m13*p_rfmxMx.m34 - p_rfmxMx.m33*p_rfmxMx.m14)
						+ p_rfmxMx.m31*(p_rfmxMx.m13*p_rfmxMx.m24 - p_rfmxMx.m23*p_rfmxMx.m14);
		}
		if (p_rfmxMx.m43 != g_fZero) {
			fdet43 = p_rfmxMx.m11*(p_rfmxMx.m22*p_rfmxMx.m34 - p_rfmxMx.m32*p_rfmxMx.m24) - p_rfmxMx.m21*(p_rfmxMx.m12*p_rfmxMx.m33 - p_rfmxMx.m32*p_rfmxMx.m14)
						+ p_rfmxMx.m31*(p_rfmxMx.m12*p_rfmxMx.m24 - p_rfmxMx.m22*p_rfmxMx.m14);
		}
		fdet44 = p_rfmxMx.m11*(p_rfmxMx.m22*p_rfmxMx.m33 - p_rfmxMx.m32*p_rfmxMx.m23) - p_rfmxMx.m21*(p_rfmxMx.m12*p_rfmxMx.m33 - p_rfmxMx.m32*p_rfmxMx.m13)
						+ p_rfmxMx.m31*(p_rfmxMx.m12*p_rfmxMx.m23 - p_rfmxMx.m22*p_rfmxMx.m13);

		*p_pfDet = -p_rfmxMx.m41*fdet41 + p_rfmxMx.m42*fdet42 - p_rfmxMx.m43*fdet43 + p_rfmxMx.m44*fdet44;
	}

	INL void	MxMakeRotX(FMatrix* p_pfmxDst, float_t p_fRad)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCosAng = Cos(p_fRad);
		float_t fSinAng = Sin(p_fRad);

		p_pfmxDst->m22 = fCosAng;
		p_pfmxDst->m23 = -fSinAng;
		p_pfmxDst->m32 = fSinAng;
		p_pfmxDst->m33 = fCosAng;
	}
	INL void	MxMakeRotY(FMatrix* p_pfmxDst, float_t p_fRad)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCosAng = Cos(p_fRad);
		float_t fSinAng = Sin(p_fRad);

		p_pfmxDst->m11 = fCosAng;
		p_pfmxDst->m13 = fSinAng;
		p_pfmxDst->m31 = -fSinAng;
		p_pfmxDst->m33 = fCosAng;
	}
	INL void	MxMakeRotZ(FMatrix* p_pfmxDst, float_t p_fRad)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCosAng = Cos(p_fRad);
		float_t fSinAng = Sin(p_fRad);

		p_pfmxDst->m11 = fCosAng;
		p_pfmxDst->m12 = -fSinAng;
		p_pfmxDst->m21 = fSinAng;
		p_pfmxDst->m22 = fCosAng;
	}

	INL void	MxMakeTranslation(FMatrix* p_pfmxDst, float_t p_fX, float_t p_fY, float_t p_fZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		p_pfmxDst->m14 = p_fX;		p_pfmxDst->m24 = p_fY;		p_pfmxDst->m34 = p_fZ;
	}
	INL void	MxMakeTranslation(FMatrix* p_pfmxDst, const FVector& p_rfvTrsl)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); // 11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); // 00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); // 10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		p_pfmxDst->m14 = p_rfvTrsl.X;	p_pfmxDst->m24 = p_rfvTrsl.Y;	p_pfmxDst->m34 = p_rfvTrsl.Z;
	}

	INL void	MxTranspose(FMatrix* p_pfmxMx)
	{
		__m128 _xmm0, _xmm1, _xmm2, _xmm3, _xmm4, _xmm5, _xmm6;

		_xmm0 = _mm_load_ps(&p_pfmxMx->m11);
		_xmm1 = _mm_load_ps(&p_pfmxMx->m12);
		_xmm2 = _mm_load_ps(&p_pfmxMx->m13);
		_xmm3 = _mm_load_ps(&p_pfmxMx->m14);

		_xmm4 = _mm_shuffle_ps(_xmm0, _xmm1, 0x44); // 01 00 01 00
		_xmm5 = _mm_shuffle_ps(_xmm2, _xmm3, 0x44); // 01 00 01 00
		_xmm6 = _mm_shuffle_ps(_xmm4, _xmm5, 0x88); // 10 00 10 00
		_mm_store_ps(&p_pfmxMx->m11, _xmm6);
		_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0xDD); // 11 01 11 01
		_mm_store_ps(&p_pfmxMx->m12, _xmm4);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm1, 0xEE); // 11 10 11 10
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm3, 0xEE); // 11 10 11 10
		_xmm1 = _mm_shuffle_ps(_xmm0, _xmm2, 0x88); // 10 00 10 00
		_mm_store_ps(&p_pfmxMx->m13, _xmm1);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm2, 0xDD); // 11 01 11 01
		_mm_store_ps(&p_pfmxMx->m14, _xmm0);
	}
	INL void	MxTransposeOf(FMatrix* p_pfmxDst, const FMatrix& p_rfmxMx)
	{
		__m128 _xmm0, _xmm1, _xmm2, _xmm3, _xmm4, _xmm5, _xmm6;

		_xmm0 = _mm_load_ps(&p_rfmxMx.m11);
		_xmm1 = _mm_load_ps(&p_rfmxMx.m12);
		_xmm2 = _mm_load_ps(&p_rfmxMx.m13);
		_xmm3 = _mm_load_ps(&p_rfmxMx.m14);

		_xmm4 = _mm_shuffle_ps(_xmm0, _xmm1, 0x44); // 01 00 01 00
		_xmm5 = _mm_shuffle_ps(_xmm2, _xmm3, 0x44); // 01 00 01 00
		_xmm6 = _mm_shuffle_ps(_xmm4, _xmm5, 0x88); // 10 00 10 00
		_mm_store_ps(&p_pfmxDst->m11, _xmm6);
		_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0xDD); // 11 01 11 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm4);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm1, 0xEE); // 11 10 11 10
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm3, 0xEE); // 11 10 11 10
		_xmm1 = _mm_shuffle_ps(_xmm0, _xmm2, 0x88); // 10 00 10 00
		_mm_store_ps(&p_pfmxDst->m13, _xmm1);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm2, 0xDD); // 11 01 11 01
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);
	}
} // namespace KiLL


#endif // __KiLL_Matrix_INL__