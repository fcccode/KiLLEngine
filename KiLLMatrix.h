
/***********************************************************************************************************************************
 *	File : "KiLLMatrix.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Matrix_H__
#define __KiLL_Matrix_H__



namespace KiLL
{

/*=================================================================================================================================
 * --- 4D Float Matrix ----------------------------------------------------------------------------------------------------------*/

	class ALIGN_16BYTE FMatrix
	{
	public:

		float_t m11, m21, m31, m41;		// In fact the matrix is		m11 m12 m13 m14	<-- Translation X
		float_t m12, m22, m32, m42;		// programmed to be column		m21 m22 m23 m24	<-- Translation Y
		float_t m13, m23, m33, m43;		// major. So mathematicaly		m31 m32 m33 m34	<-- Translation Z
		float_t m14, m24, m34, m44;		// the matrix looks like this:	m41 m42 m43 m44			Each column is stored in a vector.

		INL			FMatrix() {};
		INL			FMatrix(const FMatrix &p_rfmxMx);
		INL			FMatrix(const ALIGN_16BYTE float_t* p_pfMatrix);
		INL			FMatrix(	float_t p_fm11, float_t p_fm12, float_t p_fm13, float_t p_fm14,
								float_t p_fm21, float_t p_fm22, float_t p_fm23, float_t p_fm24,
								float_t p_fm31, float_t p_fm32, float_t p_fm33, float_t p_fm34,
								float_t p_fm41, float_t p_fm42, float_t p_fm43, float_t p_fm44 );
		//INL		~FMatrix() {}  Because of the /EHsc command line option (in VSC) wich unwinds class in case of exeption
		//			throwing, it doesnt inline some fonctions of the class if that class has a specific custom destructor.


		INL void	operator = (const FMatrix& p_rfmxMx);


		INL void	operator *= (float_t p_fScalar);
		INL void	operator /= (float_t p_fScalar);
		friend INL FMatrix		operator * (float_t p_fScalar, const FMatrix& p_rfmxMx)
		{
			FMatrix fmxMx;
			__m128 _xmmScalar, _xmm0;

			_xmmScalar = _mm_load_ss(&p_fScalar);
			_xmmScalar = _mm_shuffle_ps(_xmmScalar, _xmmScalar, 0x00);
			_xmm0 = _mm_load_ps(&p_rfmxMx.m11);
			_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
			_mm_store_ps(&fmxMx.m11, _xmm0);
			_xmm0 = _mm_load_ps(&p_rfmxMx.m12);
			_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
			_mm_store_ps(&fmxMx.m12, _xmm0);
			_xmm0 = _mm_load_ps(&p_rfmxMx.m13);
			_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
			_mm_store_ps(&fmxMx.m13, _xmm0);
			_xmm0 = _mm_load_ps(&p_rfmxMx.m14);
			_xmm0 = _mm_mul_ps(_xmm0, _xmmScalar);
			_mm_store_ps(&fmxMx.m14, _xmm0);

			return fmxMx;
		}


		void				operator *= (const FMatrix& p_rfmxMx);
		friend FMatrix		operator * (const FMatrix& p_rfmxMx1, const FMatrix& p_rfmxMx2)
		{
			FMatrix fmxMx;
			/*
			fmxMx.m11 = p_rfmxMx1.m11*p_rfmxMx2.m11 + p_rfmxMx1.m12*p_rfmxMx2.m21 + p_rfmxMx1.m13*p_rfmxMx2.m31 + p_rfmxMx1.m14*p_rfmxMx2.m41;
			fmxMx.m12 = p_rfmxMx1.m11*p_rfmxMx2.m12 + p_rfmxMx1.m12*p_rfmxMx2.m22 + p_rfmxMx1.m13*p_rfmxMx2.m32 + p_rfmxMx1.m14*p_rfmxMx2.m42;
			fmxMx.m13 = p_rfmxMx1.m11*p_rfmxMx2.m13 + p_rfmxMx1.m12*p_rfmxMx2.m23 + p_rfmxMx1.m13*p_rfmxMx2.m33 + p_rfmxMx1.m14*p_rfmxMx2.m43;
			fmxMx.m14 = p_rfmxMx1.m11*p_rfmxMx2.m14 + p_rfmxMx1.m12*p_rfmxMx2.m24 + p_rfmxMx1.m13*p_rfmxMx2.m34 + p_rfmxMx1.m14*p_rfmxMx2.m44;

			fmxMx.m21 = p_rfmxMx1.m21*p_rfmxMx2.m11 + p_rfmxMx1.m22*p_rfmxMx2.m21 + p_rfmxMx1.m23*p_rfmxMx2.m31 + p_rfmxMx1.m24*p_rfmxMx2.m41;
			fmxMx.m22 = p_rfmxMx1.m21*p_rfmxMx2.m12 + p_rfmxMx1.m22*p_rfmxMx2.m22 + p_rfmxMx1.m23*p_rfmxMx2.m32 + p_rfmxMx1.m24*p_rfmxMx2.m42;
			fmxMx.m23 = p_rfmxMx1.m21*p_rfmxMx2.m13 + p_rfmxMx1.m22*p_rfmxMx2.m23 + p_rfmxMx1.m23*p_rfmxMx2.m33 + p_rfmxMx1.m24*p_rfmxMx2.m43;
			fmxMx.m24 = p_rfmxMx1.m21*p_rfmxMx2.m14 + p_rfmxMx1.m22*p_rfmxMx2.m24 + p_rfmxMx1.m23*p_rfmxMx2.m34 + p_rfmxMx1.m24*p_rfmxMx2.m44;

			fmxMx.m31 = p_rfmxMx1.m31*p_rfmxMx2.m11 + p_rfmxMx1.m32*p_rfmxMx2.m21 + p_rfmxMx1.m33*p_rfmxMx2.m31 + p_rfmxMx1.m34*p_rfmxMx2.m41;
			fmxMx.m32 = p_rfmxMx1.m31*p_rfmxMx2.m12 + p_rfmxMx1.m32*p_rfmxMx2.m22 + p_rfmxMx1.m33*p_rfmxMx2.m32 + p_rfmxMx1.m34*p_rfmxMx2.m42;
			fmxMx.m33 = p_rfmxMx1.m31*p_rfmxMx2.m13 + p_rfmxMx1.m32*p_rfmxMx2.m23 + p_rfmxMx1.m33*p_rfmxMx2.m33 + p_rfmxMx1.m34*p_rfmxMx2.m43;
			fmxMx.m34 = p_rfmxMx1.m31*p_rfmxMx2.m14 + p_rfmxMx1.m32*p_rfmxMx2.m24 + p_rfmxMx1.m33*p_rfmxMx2.m34 + p_rfmxMx1.m34*p_rfmxMx2.m44;

			fmxMx.m41 = p_rfmxMx1.m41*p_rfmxMx2.m11 + p_rfmxMx1.m42*p_rfmxMx2.m21 + p_rfmxMx1.m43*p_rfmxMx2.m31 + p_rfmxMx1.m44*p_rfmxMx2.m41;
			fmxMx.m42 = p_rfmxMx1.m41*p_rfmxMx2.m12 + p_rfmxMx1.m42*p_rfmxMx2.m22 + p_rfmxMx1.m43*p_rfmxMx2.m32 + p_rfmxMx1.m44*p_rfmxMx2.m42;
			fmxMx.m43 = p_rfmxMx1.m41*p_rfmxMx2.m13 + p_rfmxMx1.m42*p_rfmxMx2.m23 + p_rfmxMx1.m43*p_rfmxMx2.m33 + p_rfmxMx1.m44*p_rfmxMx2.m43;
			fmxMx.m44 = p_rfmxMx1.m41*p_rfmxMx2.m14 + p_rfmxMx1.m42*p_rfmxMx2.m24 + p_rfmxMx1.m43*p_rfmxMx2.m34 + p_rfmxMx1.m44*p_rfmxMx2.m44;
			*/
			__m128 _xmm0, _xmm1, _xmm2, _xmm3, _xmm4, _xmm5, _xmm6, _xmm7;
			__m128 _xmmMx11, _xmmMx12, _xmmMx13, _xmmMx14;

			_xmm0 = _mm_load_ps(&p_rfmxMx1.m11);
			_xmm1 = _mm_load_ps(&p_rfmxMx1.m12);
			_xmm2 = _mm_load_ps(&p_rfmxMx1.m13);
			_xmm3 = _mm_load_ps(&p_rfmxMx1.m14);
			_xmm4 = _mm_shuffle_ps(_xmm0, _xmm1, 0x44); // 01 00 01 00
			_xmm5 = _mm_shuffle_ps(_xmm2, _xmm3, 0x44); // 01 00 01 00
			_xmmMx11 = _mm_shuffle_ps(_xmm4, _xmm5, 0x88); // 10 00 10 00
			_xmmMx12 = _mm_shuffle_ps(_xmm4, _xmm5, 0xDD); // 11 01 11 01
			_xmm0 = _mm_shuffle_ps(_xmm0, _xmm1, 0xEE); // 11 10 11 10
			_xmm2 = _mm_shuffle_ps(_xmm2, _xmm3, 0xEE); // 11 10 11 10
			_xmmMx13 = _mm_shuffle_ps(_xmm0, _xmm2, 0x88); // 10 00 10 00
			_xmmMx14 = _mm_shuffle_ps(_xmm0, _xmm2, 0xDD); // 11 01 11 01

			_xmm0 = _mm_load_ps(&p_rfmxMx2.m11);
			_xmm1 = _mm_load_ps(&p_rfmxMx2.m12);
			_xmm2 = _mm_load_ps(&p_rfmxMx2.m13);
			_xmm3 = _mm_load_ps(&p_rfmxMx2.m14);

			_xmm4 = _mm_mul_ps(_xmm0, _xmmMx11);
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm5 = _mm_mul_ps(_xmm0, _xmmMx12);
			_xmm5 = _mm_hadd_ps(_xmm5, _xmm5);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0x44); // 01 00 01 00
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm6 = _mm_mul_ps(_xmm0, _xmmMx13);
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm7 = _mm_mul_ps(_xmm0, _xmmMx14);
			_xmm7 = _mm_hadd_ps(_xmm7, _xmm7);
			_xmm6 = _mm_shuffle_ps(_xmm6, _xmm7, 0x44); // 01 00 01 00
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm6, 0x44); // 01 00 01 00
			_mm_store_ps(&fmxMx.m11, _xmm4);

			_xmm4 = _mm_mul_ps(_xmm1, _xmmMx11);
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm5 = _mm_mul_ps(_xmm1, _xmmMx12);
			_xmm5 = _mm_hadd_ps(_xmm5, _xmm5);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0x44); // 01 00 01 00
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm6 = _mm_mul_ps(_xmm1, _xmmMx13);
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm7 = _mm_mul_ps(_xmm1, _xmmMx14);
			_xmm7 = _mm_hadd_ps(_xmm7, _xmm7);
			_xmm6 = _mm_shuffle_ps(_xmm6, _xmm7, 0x44); // 01 00 01 00
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm6, 0x44); // 01 00 01 00
			_mm_store_ps(&fmxMx.m12, _xmm4);

			_xmm4 = _mm_mul_ps(_xmm2, _xmmMx11);
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm5 = _mm_mul_ps(_xmm2, _xmmMx12);
			_xmm5 = _mm_hadd_ps(_xmm5, _xmm5);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0x44); // 01 00 01 00
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm6 = _mm_mul_ps(_xmm2, _xmmMx13);
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm7 = _mm_mul_ps(_xmm2, _xmmMx14);
			_xmm7 = _mm_hadd_ps(_xmm7, _xmm7);
			_xmm6 = _mm_shuffle_ps(_xmm6, _xmm7, 0x44); // 01 00 01 00
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm6, 0x44); // 01 00 01 00
			_mm_store_ps(&fmxMx.m13, _xmm4);

			_xmm4 = _mm_mul_ps(_xmm3, _xmmMx11);
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm5 = _mm_mul_ps(_xmm3, _xmmMx12);
			_xmm5 = _mm_hadd_ps(_xmm5, _xmm5);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm5, 0x44); // 01 00 01 00
			_xmm4 = _mm_hadd_ps(_xmm4, _xmm4);
			_xmm6 = _mm_mul_ps(_xmm3, _xmmMx13);
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm7 = _mm_mul_ps(_xmm3, _xmmMx14);
			_xmm7 = _mm_hadd_ps(_xmm7, _xmm7);
			_xmm6 = _mm_shuffle_ps(_xmm6, _xmm7, 0x44); // 01 00 01 00
			_xmm6 = _mm_hadd_ps(_xmm6, _xmm6);
			_xmm4 = _mm_shuffle_ps(_xmm4, _xmm6, 0x44); // 01 00 01 00
			_mm_store_ps(&fmxMx.m14, _xmm4);

			return fmxMx;
		}

		INL FVector	operator * (const FVector& p_rfvVec) const;

	};




/*=================================================================================================================================
 * --- Matrix General Functions -------------------------------------------------------------------------------------------------*/

	/* 4D Float precision -------------------------------------------------------------*/
	//void		MxDoubleToFloat(FMatrix* p_pfmxDst, const DMatrix& p_rdmxSrc);
	INL void	MxIdentity(FMatrix* p_pfmxIdentity);
	INL void	MxSet(FMatrix* p_pfmxDst,	float_t p_fm11, float_t p_fm12, float_t p_fm13, float_t p_fm14,
											float_t p_fm21, float_t p_fm22, float_t p_fm23, float_t p_fm24,
											float_t p_fm31, float_t p_fm32, float_t p_fm33, float_t p_fm34,
											float_t p_fm41, float_t p_fm42, float_t p_fm43, float_t p_fm44 );
	INL float_t MxDeterminant(float_t* p_pfDet, const FMatrix& p_rfmxMx);

	INL void	MxMakeRotX(FMatrix* p_pfmxDst, float_t p_fRad);
	INL void	MxMakeRotY(FMatrix* p_pfmxDst, float_t p_fRad);
	INL void	MxMakeRotZ(FMatrix* p_pfmxDst, float_t p_fRad);
	void		MxMakeRotXYZ(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);
	void		MxMakeRotXZY(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);
	void		MxMakeRotYXZ(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);
	void		MxMakeRotYZX(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);
	void		MxMakeRotZXY(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);
	void		MxMakeRotZYX(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ);

	void		MxMakeAxisAngle(FMatrix* p_pfmxDst, const FVector& p_rfvAxis, float_t p_fRad);
	void		MxMakeQuaternion(FMatrix* p_pfmxDst, const FQuaternion& p_rfqtQuat);
	void		MxMakeVec2Vec(FMatrix* p_pfmxDst, const FVector& p_rfvInitial, const FVector& p_rfvFinal);

	INL void	MxMakeTranslation(FMatrix* p_pfmxDst, float_t p_fX, float_t p_fY, float_t p_fZ);
	INL void	MxMakeTranslation(FMatrix* p_pfmxDst, const FVector& p_rfvTrsl);

	INL void	MxTranspose(FMatrix* p_pfmxMx);
	INL void	MxTransposeOf(FMatrix* p_pfmxDst, const FMatrix& p_rfmxMx);

	void		MxInverse(FMatrix* p_pfmxMx);
	void		MxInverseOf(FMatrix* p_pfmxDst, const FMatrix& p_rfmxMx);

	void		MxMakeObjectLookAt(FMatrix* p_pfmxDst, const FVector& p_rfvEye, const FVector& p_rfvLookAt, const FVector& p_rfvUp);
	void		MxMakeCameraLookAt(FMatrix* p_pfmxDst, const FVector& p_rfvEye, const FVector& p_rfvLookAt, const FVector& p_rfvUp);

	//void		MxMakeBillboard(FMatrix* p_fmxDst, const FVector &p_rfvEye, const FVector &p_rfvDir, const FVector &p_rfvUp);

	//void		MxSetOrthogonal(FMatrix* p_pfmxDst, float_t p_fWidth, float_t p_fHeight, float_t p_fZScale, float_t p_fZOffset);
	void		MxSetPerspectiveGL(FMatrix* p_pfmxDst, float_t p_fRadFOV, float_t p_fAspect, float_t p_fZNear, float_t p_fZFar);
	void		MxSetPerspectiveDXLH(FMatrix* p_pfmxDst, float_t p_fRadFOV, float_t p_fAspect, float_t p_fZNear, float_t p_fZFar);
	void		MxSetPerspectiveDXRH(FMatrix* p_pfmxDst, float_t p_fRadFOV, float_t p_fAspect, float_t p_fZNear, float_t p_fZFar);


	/* 4D Double precision ------------------------------------------------------------*/
	//void		MxFloatToDouble(DMatrix* p_pdmxDst, const FMatrix& p_rfmxSrc);





} // namespace KiLL

#include "KiLLMatrix.inl"


#endif // __KiLL_Matrix_H__