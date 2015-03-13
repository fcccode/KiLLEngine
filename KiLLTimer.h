
/***********************************************************************************************************************************
 *	File : "KiLLTimer.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Timer_H__
#define __KiLL_Timer_H__


namespace KiLL
{

/*=================================================================================================================================
 * --- Timer --------------------------------------------------------------------------------------------------------------------*/

	class Timer
	{
	private:

		INL long_t		GetTicksPerSecond(double_t* p_pdTicksPerSecond);
		INL long_t		GetTick(long_t* p_plTick);

	public:

		INL				Timer() : m_lStartTick(0), m_dTicksPerSecond(0.0) {}

		INL void		Start();
		INL void		Stop();
		INL bool		Check(double_t p_dTime);
		INL double_t	GetTime();
		INL void		GetTime(double_t* p_pdTime);

	private:

		double_t		m_dTicksPerSecond;
		long_t			m_lStartTick;
	};




} // namespace KiLL

#include "KiLLTimer.inl"


#endif // __KiLL_Timer_H__