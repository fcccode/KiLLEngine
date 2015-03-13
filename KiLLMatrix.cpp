
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
 * --- 4D Float Matrix ----------------------------------------------------------------------------------------------------------*/

	void		FMatrix::operator *= (const FMatrix& p_rfmxMx)
	{
		__m128 _xmm0, _xmm1, _xmm2, _xmm3, _xmm4, _xmm5, _xmm6, _xmm7;
		__m128 _xmmMx11, _xmmMx12, _xmmMx13, _xmmMx14;

		_xmm0 = _mm_load_ps(&m11);
		_xmm1 = _mm_load_ps(&m12);
		_xmm2 = _mm_load_ps(&m13);
		_xmm3 = _mm_load_ps(&m14);

		_xmm4 = _mm_shuffle_ps(_xmm0, _xmm1, 0x44); // 01 00 01 00
		_xmm5 = _mm_shuffle_ps(_xmm2, _xmm3, 0x44); // 01 00 01 00
		_xmmMx11 = _mm_shuffle_ps(_xmm4, _xmm5, 0x88); // 10 00 10 00
		_xmmMx12 = _mm_shuffle_ps(_xmm4, _xmm5, 0xDD); // 11 01 11 01
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm1, 0xEE); // 11 10 11 10
		_xmm2 = _mm_shuffle_ps(_xmm2, _xmm3, 0xEE); // 11 10 11 10
		_xmmMx13 = _mm_shuffle_ps(_xmm0, _xmm2, 0x88); // 10 00 10 00
		_xmmMx14 = _mm_shuffle_ps(_xmm0, _xmm2, 0xDD); // 11 01 11 01

		_xmm0 = _mm_load_ps(&p_rfmxMx.m11);
		_xmm1 = _mm_load_ps(&p_rfmxMx.m12);
		_xmm2 = _mm_load_ps(&p_rfmxMx.m13);
		_xmm3 = _mm_load_ps(&p_rfmxMx.m14);

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
		_mm_store_ps(&m11, _xmm4);

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
		_mm_store_ps(&m12, _xmm4);

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
		_mm_store_ps(&m13, _xmm4);

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
		_mm_store_ps(&m14, _xmm4);
	}




/*=================================================================================================================================
 * --- Matrix General Functions -------------------------------------------------------------------------------------------------*/

	/* 4D Float precision -------------------------------------------------------------*/
	void		MxMakeRotXYZ(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);
 
		p_pfmxDst->m11 = fCY*fCZ;
		p_pfmxDst->m12 = -fCY*fSZ;
		p_pfmxDst->m13 = fSY;
		p_pfmxDst->m21 = fCZ*fSX*fSY + fCX*fSZ;
		p_pfmxDst->m22 = fCX*fCZ - fSX*fSY*fSZ;
		p_pfmxDst->m23 = -fCY*fSX;
		p_pfmxDst->m31 = fSX*fSZ - fCX*fCZ*fSY;
		p_pfmxDst->m32 = fCZ*fSX + fCX*fSY*fSZ;
		p_pfmxDst->m33 = fCX*fCY;
	}
	void		MxMakeRotXZY(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);
 
		p_pfmxDst->m11 = fCY*fCZ;
		p_pfmxDst->m12 = -fSZ;
		p_pfmxDst->m13 = fCZ*fSY;
		p_pfmxDst->m21 = fSX*fSY + fCX*fCY*fCZ;
		p_pfmxDst->m22 = fCX*fCZ;
		p_pfmxDst->m23 = -fCY*fSX + fCX*fSY*fSZ;
		p_pfmxDst->m31 = -fCX*fSY + fCY*fSX*fSZ;
		p_pfmxDst->m32 = fCZ*fSX;
		p_pfmxDst->m33 = fCX*fCY + fSX*fSY*fSZ;
	}
	void		MxMakeRotYXZ(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);

		p_pfmxDst->m11 = fCY*fCZ + fSX*fSY*fSZ;
		p_pfmxDst->m12 = fCZ*fSX*fSY - fCY*fSZ;
		p_pfmxDst->m13 = fCX*fSY;
		p_pfmxDst->m21 = fCX*fSZ;
		p_pfmxDst->m22 = fCX*fCZ;
		p_pfmxDst->m23 = -fSX;
		p_pfmxDst->m31 = fCY*fSX*fSZ - fCZ*fSY;
		p_pfmxDst->m32 = fCY*fCZ*fSX + fSY*fSZ;
		p_pfmxDst->m33 = fCX*fCY;
	}
	void		MxMakeRotYZX(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);

		p_pfmxDst->m11 = fCY*fCZ;
		p_pfmxDst->m12 = fSX*fSY - fCX*fCY*fSZ;
		p_pfmxDst->m13 = fCX*fSY + fCY*fSX*fSZ;
		p_pfmxDst->m21 = fSZ;
		p_pfmxDst->m22 = fCX*fCZ;
		p_pfmxDst->m23 = -fCZ*fSX;
		p_pfmxDst->m31 = -fCZ*fSY;
		p_pfmxDst->m32 = fCY*fSX + fCX*fSY*fSZ;
		p_pfmxDst->m33 = fCX*fCY - fSX*fSY*fSZ;
	}
	void		MxMakeRotZXY(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);

		p_pfmxDst->m11 = fCY*fCZ - fSX*fSY*fSZ;
		p_pfmxDst->m12 = -fCX*fSZ;
		p_pfmxDst->m13 = fCZ*fSY + fCY*fSX*fSZ;
		p_pfmxDst->m21 = fCZ*fSX*fSY + fCY*fSZ;
		p_pfmxDst->m22 = fCX*fCZ;
		p_pfmxDst->m23 = -fCY*fCZ*fSX + fSY*fSZ;
		p_pfmxDst->m31 = -fCX*fSY;
		p_pfmxDst->m32 = fSX;
		p_pfmxDst->m33 = fCX*fCY;
	}
	void		MxMakeRotZYX(FMatrix* p_pfmxDst, float_t p_fRadX, float_t p_fRadY, float_t p_fRadZ)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCX, fSX,
				fCY, fSY,
				fCZ, fSZ;

		fCX = Cos(p_fRadX);
		fSX = Sin(p_fRadX);
		fCY = Cos(p_fRadY);
		fSY = Sin(p_fRadY);
		fCZ = Cos(p_fRadZ);
		fSZ = Sin(p_fRadZ);

		p_pfmxDst->m11 = fCY*fCZ;
		p_pfmxDst->m12 = fCZ*fSX*fSY- fCX*fSZ;
		p_pfmxDst->m13 = fCX*fCZ*fSY + fSX*fSZ;
		p_pfmxDst->m21 = fCY*fSZ;
		p_pfmxDst->m22 = fCX*fCZ + fSX*fSY*fSZ;
		p_pfmxDst->m23 = -fCZ*fSX + fCX*fSY*fSZ;
		p_pfmxDst->m31 = -fSY;
		p_pfmxDst->m32 = fCY*fSX;
		p_pfmxDst->m33 = fCX*fCY;
	}

	void		MxMakeAxisAngle(FMatrix* p_pfmxDst, const FVector& p_rfvAxis, float_t p_fRad)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		float_t fCos = Cos(p_fRad);
		float_t fSin = Sin(p_fRad);
		float_t fSum = 1.0f - fCos;
		float_t fSqrNorm;
		VecSqrNorm(&fSqrNorm, p_rfvAxis);
		FVector fvAxis = p_rfvAxis;

		if (!TRange<float_t>(fSqrNorm, g_fOne-g_fSPrc, g_fOne+g_fSPrc)) VecUnit(&fvAxis, fvAxis);

		p_pfmxDst->m11 = (p_rfvAxis.X * p_rfvAxis.X) * fSum + fCos;
		p_pfmxDst->m12 = (p_rfvAxis.X * p_rfvAxis.Y) * fSum - (p_rfvAxis.Z * fSin);
		p_pfmxDst->m13 = (p_rfvAxis.X * p_rfvAxis.Z) * fSum + (p_rfvAxis.Y * fSin);

		p_pfmxDst->m21 = (p_rfvAxis.Y * p_rfvAxis.X) * fSum + (p_rfvAxis.Z * fSin);
		p_pfmxDst->m22 = (p_rfvAxis.Y * p_rfvAxis.Y) * fSum + fCos ;
		p_pfmxDst->m23 = (p_rfvAxis.Y * p_rfvAxis.Z) * fSum - (p_rfvAxis.X * fSin);

		p_pfmxDst->m31 = (p_rfvAxis.Z * p_rfvAxis.X) * fSum - (p_rfvAxis.Y * fSin);
		p_pfmxDst->m32 = (p_rfvAxis.Z * p_rfvAxis.Y) * fSum + (p_rfvAxis.X * fSin);
		p_pfmxDst->m33 = (p_rfvAxis.Z * p_rfvAxis.Z) * fSum + fCos;
	}
	void		MxMakeQuaternion(FMatrix* p_pfmxDst, const FQuaternion& p_rfqtQuat)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		//m11 = 1.0f - 2.0f*(p_rfqtQt.Y*p_rfqtQt.Y + p_rfqtQt.Z*p_rfqtQt.Z);
		//m21 = 2.0f*(p_rfqtQt.X*p_rfqtQt.Y + p_rfqtQt.W*p_rfqtQt.Z);
		//m31 = 2.0f*(p_rfqtQt.X*p_rfqtQt.Z - p_rfqtQt.W*p_rfqtQt.Y);

		//m12 = 2.0f*(p_rfqtQt.X*p_rfqtQt.Y - p_rfqtQt.W*p_rfqtQt.Z);
		//m22 = 1.0f - 2.0f*(p_rfqtQt.X*p_rfqtQt.X + p_rfqtQt.Z*p_rfqtQt.Z);
		//m32 = 2.0f*(p_rfqtQt.Y*p_rfqtQt.Z + p_rfqtQt.W*p_rfqtQt.X);

		//m13 = 2.0f*(p_rfqtQt.X*p_rfqtQt.Z + p_rfqtQt.W*p_rfqtQt.Y);
		//m23 = 2.0f*(p_rfqtQt.Y*p_rfqtQt.Z - p_rfqtQt.W*p_rfqtQt.X);
		//m33 = 1.0f - 2.0f*(p_rfqtQt.X*p_rfqtQt.X + p_rfqtQt.Y*p_rfqtQt.Y);
	}
	void		MxMakeVec2Vec(FMatrix* p_pfmxDst, const FVector& p_rfvInitial, const FVector& p_rfvFinal)
	{
		__m128 _xmm0;

		_xmm0 = _mm_load_ps(g_fIdentityMatrix);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0xE1); //	11 10 00 01
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x10); //	00 01 00 00 
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_shuffle_ps(_xmm0, _xmm0, 0x80); //	10 00 00 00
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);

		FVector fvAxis;
		VecCross(&fvAxis, p_rfvInitial, p_rfvFinal);
		VecUnit(&fvAxis, fvAxis);
		float_t fRad;
		VecAngle(&fRad, p_rfvInitial, p_rfvFinal);

		float_t fCos = Cos(fRad);
		float_t fSin = Sin(fRad);
		float_t fSum = 1.0f - fCos;
		float_t fSqrNorm;
		VecSqrNorm(&fSqrNorm, fvAxis);

		if (!TRange<float_t>(fSqrNorm, g_fOne-g_fSPrc, g_fOne+g_fSPrc)) VecUnit(&fvAxis, fvAxis);

		p_pfmxDst->m11 = (fvAxis.X * fvAxis.X) * fSum + fCos;
		p_pfmxDst->m12 = (fvAxis.X * fvAxis.Y) * fSum - (fvAxis.Z * fSin);
		p_pfmxDst->m13 = (fvAxis.X * fvAxis.Z) * fSum + (fvAxis.Y * fSin);

		p_pfmxDst->m21 = (fvAxis.Y * fvAxis.X) * fSum + (fvAxis.Z * fSin);
		p_pfmxDst->m22 = (fvAxis.Y * fvAxis.Y) * fSum + fCos ;
		p_pfmxDst->m23 = (fvAxis.Y * fvAxis.Z) * fSum - (fvAxis.X * fSin);

		p_pfmxDst->m31 = (fvAxis.Z * fvAxis.X) * fSum - (fvAxis.Y * fSin);
		p_pfmxDst->m32 = (fvAxis.Z * fvAxis.Y) * fSum + (fvAxis.X * fSin);
		p_pfmxDst->m33 = (fvAxis.Z * fvAxis.Z) * fSum + fCos;
	}

	void		MxInverse(FMatrix* p_pfmxMx)
	{
		FMatrix fmxBuff;

		float_t f33444334 = p_pfmxMx->m33*p_pfmxMx->m44 - p_pfmxMx->m43*p_pfmxMx->m34;
		float_t f23444324 = p_pfmxMx->m23*p_pfmxMx->m44 - p_pfmxMx->m43*p_pfmxMx->m24;
		float_t f23343324 = p_pfmxMx->m23*p_pfmxMx->m34 - p_pfmxMx->m33*p_pfmxMx->m24;
		float_t f13444314 = p_pfmxMx->m13*p_pfmxMx->m44 - p_pfmxMx->m43*p_pfmxMx->m14;
		float_t f13343314 = p_pfmxMx->m13*p_pfmxMx->m34 - p_pfmxMx->m33*p_pfmxMx->m14;
		float_t f13242314 = p_pfmxMx->m13*p_pfmxMx->m24 - p_pfmxMx->m23*p_pfmxMx->m14;

		fmxBuff.m11 = p_pfmxMx->m22*f33444334 - p_pfmxMx->m32*f23444324 + p_pfmxMx->m42*f23343324;
		fmxBuff.m21 = p_pfmxMx->m12*f33444334 - p_pfmxMx->m32*f13444314 + p_pfmxMx->m42*f13343314;
		fmxBuff.m31 = p_pfmxMx->m12*f23444324 - p_pfmxMx->m22*f13444314 + p_pfmxMx->m42*f13242314;
		fmxBuff.m41 = p_pfmxMx->m12*f23343324 - p_pfmxMx->m22*f13343314 + p_pfmxMx->m32*f13242314;

		fmxBuff.m12 = p_pfmxMx->m21*f33444334 - p_pfmxMx->m31*f23444324 + p_pfmxMx->m41*f23343324;
		fmxBuff.m22 = p_pfmxMx->m11*f33444334 - p_pfmxMx->m31*f13444314 + p_pfmxMx->m41*f13343314;
		fmxBuff.m32 = p_pfmxMx->m11*f23444324 - p_pfmxMx->m21*f13444314 + p_pfmxMx->m41*f13242314;
		fmxBuff.m42 = p_pfmxMx->m11*f23343324 - p_pfmxMx->m21*f13343314 + p_pfmxMx->m31*f13242314;

		float_t f31424132 = p_pfmxMx->m31*p_pfmxMx->m42 - p_pfmxMx->m41*p_pfmxMx->m32;
		float_t f21424122 = p_pfmxMx->m21*p_pfmxMx->m32 - p_pfmxMx->m31*p_pfmxMx->m22;
		float_t f21323122 = p_pfmxMx->m21*p_pfmxMx->m32 - p_pfmxMx->m31*p_pfmxMx->m22;
		float_t f11424112 = p_pfmxMx->m11*p_pfmxMx->m42 - p_pfmxMx->m41*p_pfmxMx->m12;
		float_t f11222112 = p_pfmxMx->m11*p_pfmxMx->m22 - p_pfmxMx->m21*p_pfmxMx->m12;
		float_t f11323112 = p_pfmxMx->m11*p_pfmxMx->m32 - p_pfmxMx->m31*p_pfmxMx->m12;

		fmxBuff.m13 = p_pfmxMx->m24*f31424132 - p_pfmxMx->m34*f21424122 + p_pfmxMx->m44*f21323122;
		fmxBuff.m23 = p_pfmxMx->m14*f31424132 - p_pfmxMx->m34*f11424112 + p_pfmxMx->m44*f11323112;
		fmxBuff.m33 = p_pfmxMx->m14*f21424122 - p_pfmxMx->m24*f11424112 + p_pfmxMx->m44*f11222112;
		fmxBuff.m43 = p_pfmxMx->m14*f21323122 - p_pfmxMx->m24*f11323112 + p_pfmxMx->m34*f11222112;

		fmxBuff.m14 = p_pfmxMx->m23*f31424132 - p_pfmxMx->m33*f21424122 + p_pfmxMx->m43*f21323122;
		fmxBuff.m24 = p_pfmxMx->m13*f31424132 - p_pfmxMx->m33*f11424112 + p_pfmxMx->m43*f11323112;
		fmxBuff.m34 = p_pfmxMx->m13*f21424122 - p_pfmxMx->m23*f11424112 + p_pfmxMx->m43*f11222112;
		fmxBuff.m44 = p_pfmxMx->m13*f21323122 - p_pfmxMx->m23*f11323112 + p_pfmxMx->m33*f11222112;

		float_t fDet;
		MxDeterminant(&fDet, *p_pfmxMx);
		fmxBuff *= 1.0f / fDet;

		__m128 _xmm0;

		_xmm0 = _mm_load_ps(&fmxBuff.m11);
		_mm_store_ps(&p_pfmxMx->m11, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m12);
		_mm_store_ps(&p_pfmxMx->m12, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m13);
		_mm_store_ps(&p_pfmxMx->m13, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m14);
		_mm_store_ps(&p_pfmxMx->m14, _xmm0);
	}
	void		MxInverseOf(FMatrix* p_pfmxDst, const FMatrix& p_rfmxMx)
	{
		FMatrix fmxBuff;

		float_t f33444334 = p_rfmxMx.m33*p_rfmxMx.m44 - p_rfmxMx.m43*p_rfmxMx.m34;
		float_t f23444324 = p_rfmxMx.m23*p_rfmxMx.m44 - p_rfmxMx.m43*p_rfmxMx.m24;
		float_t f23343324 = p_rfmxMx.m23*p_rfmxMx.m34 - p_rfmxMx.m33*p_rfmxMx.m24;
		float_t f13444314 = p_rfmxMx.m13*p_rfmxMx.m44 - p_rfmxMx.m43*p_rfmxMx.m14;
		float_t f13343314 = p_rfmxMx.m13*p_rfmxMx.m34 - p_rfmxMx.m33*p_rfmxMx.m14;
		float_t f13242314 = p_rfmxMx.m13*p_rfmxMx.m24 - p_rfmxMx.m23*p_rfmxMx.m14;

		fmxBuff.m11 = p_rfmxMx.m22*f33444334 - p_rfmxMx.m32*f23444324 + p_rfmxMx.m42*f23343324;
		fmxBuff.m21 = p_rfmxMx.m12*f33444334 - p_rfmxMx.m32*f13444314 + p_rfmxMx.m42*f13343314;
		fmxBuff.m31 = p_rfmxMx.m12*f23444324 - p_rfmxMx.m22*f13444314 + p_rfmxMx.m42*f13242314;
		fmxBuff.m41 = p_rfmxMx.m12*f23343324 - p_rfmxMx.m22*f13343314 + p_rfmxMx.m32*f13242314;

		fmxBuff.m12 = p_rfmxMx.m21*f33444334 - p_rfmxMx.m31*f23444324 + p_rfmxMx.m41*f23343324;
		fmxBuff.m22 = p_rfmxMx.m11*f33444334 - p_rfmxMx.m31*f13444314 + p_rfmxMx.m41*f13343314;
		fmxBuff.m32 = p_rfmxMx.m11*f23444324 - p_rfmxMx.m21*f13444314 + p_rfmxMx.m41*f13242314;
		fmxBuff.m42 = p_rfmxMx.m11*f23343324 - p_rfmxMx.m21*f13343314 + p_rfmxMx.m31*f13242314;

		float_t f31424132 = p_rfmxMx.m31*p_rfmxMx.m42 - p_rfmxMx.m41*p_rfmxMx.m32;
		float_t f21424122 = p_rfmxMx.m21*p_rfmxMx.m32 - p_rfmxMx.m31*p_rfmxMx.m22;
		float_t f21323122 = p_rfmxMx.m21*p_rfmxMx.m32 - p_rfmxMx.m31*p_rfmxMx.m22;
		float_t f11424112 = p_rfmxMx.m11*p_rfmxMx.m42 - p_rfmxMx.m41*p_rfmxMx.m12;
		float_t f11222112 = p_rfmxMx.m11*p_rfmxMx.m22 - p_rfmxMx.m21*p_rfmxMx.m12;
		float_t f11323112 = p_rfmxMx.m11*p_rfmxMx.m32 - p_rfmxMx.m31*p_rfmxMx.m12;

		fmxBuff.m13 = p_rfmxMx.m24*f31424132 - p_rfmxMx.m34*f21424122 + p_rfmxMx.m44*f21323122;
		fmxBuff.m23 = p_rfmxMx.m14*f31424132 - p_rfmxMx.m34*f11424112 + p_rfmxMx.m44*f11323112;
		fmxBuff.m33 = p_rfmxMx.m14*f21424122 - p_rfmxMx.m24*f11424112 + p_rfmxMx.m44*f11222112;
		fmxBuff.m43 = p_rfmxMx.m14*f21323122 - p_rfmxMx.m24*f11323112 + p_rfmxMx.m34*f11222112;

		fmxBuff.m14 = p_rfmxMx.m23*f31424132 - p_rfmxMx.m33*f21424122 + p_rfmxMx.m43*f21323122;
		fmxBuff.m24 = p_rfmxMx.m13*f31424132 - p_rfmxMx.m33*f11424112 + p_rfmxMx.m43*f11323112;
		fmxBuff.m34 = p_rfmxMx.m13*f21424122 - p_rfmxMx.m23*f11424112 + p_rfmxMx.m43*f11222112;
		fmxBuff.m44 = p_rfmxMx.m13*f21323122 - p_rfmxMx.m23*f11323112 + p_rfmxMx.m33*f11222112;

		float_t fDet;
		MxDeterminant(&fDet, p_rfmxMx);
		fmxBuff *= 1.0f / fDet;

		__m128 _xmm0;

		_xmm0 = _mm_load_ps(&fmxBuff.m11);
		_mm_store_ps(&p_pfmxDst->m11, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m12);
		_mm_store_ps(&p_pfmxDst->m12, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m13);
		_mm_store_ps(&p_pfmxDst->m13, _xmm0);
		_xmm0 = _mm_load_ps(&fmxBuff.m14);
		_mm_store_ps(&p_pfmxDst->m14, _xmm0);
	}

	void		MxMakeObjectLookAt(FMatrix* p_pfmxDst, const FVector& p_rfvEye, const FVector& p_rfvLookAt, const FVector& p_rfvUp);
	void		MxMakeCameraLookAt(FMatrix* p_pfmxDst, const FVector& p_rfvEye, const FVector& p_rfvLookAt, const FVector& p_rfvUp);




} // namespace KiLL