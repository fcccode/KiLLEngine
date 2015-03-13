
/***********************************************************************************************************************************
 *	File : "KiLLTimer.inl"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Timer_INL__
#define __KiLL_Timer_INL__


namespace KiLL
{

/*=================================================================================================================================
 * --- Timer --------------------------------------------------------------------------------------------------------------------*/

#	ifdef _KILL_OS_WINDOWS
	INL long_t		Timer::GetTicksPerSecond(double_t* p_pdTicksPerSecond)
	{
		LARGE_INTEGER liTicksPerSecond;
		QueryPerformanceFrequency(&liTicksPerSecond);
		*p_pdTicksPerSecond = static_cast<double_t>(liTicksPerSecond.QuadPart);
	}
	INL long_t		Timer::GetTick(long_t* p_plTick)
	{
		LARGE_INTEGER liTick;
		QueryPerformanceCounter(&liTick);
		*p_plTick = static_cast<long_t>(liTick.QuadPart);
	}
#	endif

	INL void		Timer::Start()
	{
		GetTick(&m_lStartTick);
		GetTicksPerSecond(&m_dTicksPerSecond);
	}
	INL void		Timer::Stop()
	{
		m_lStartTick = 0;
	}
	INL bool		Timer::Check(double_t p_dSeconds)
	{
		if (m_lStartTick == 0) throw TIMER_NOTSTARTED;

		long_t lCurrentTick;
		GetTick(&lCurrentTick);

		return p_dSeconds <= (static_cast<double_t>(lCurrentTick-m_lStartTick) / m_dTicksPerSecond);
	}
	INL double_t	Timer::GetTime()
	{
		if (m_lStartTick == 0) throw TIMER_NOTSTARTED;

		long_t lCurrentTick;
		GetTick(&lCurrentTick);

		return (static_cast<double_t>(lCurrentTick-m_lStartTick) / m_dTicksPerSecond);
	}
	INL void		Timer::GetTime(double_t* p_pdTime)
	{
		if (m_lStartTick == 0) throw TIMER_NOTSTARTED;

		long_t lCurrentTick;
		GetTick(&lCurrentTick);

		*p_pdTime = static_cast<double_t>(lCurrentTick-m_lStartTick) / m_dTicksPerSecond;
	}




} // namespace KiLL


#endif // __KiLL_Timer_INL__