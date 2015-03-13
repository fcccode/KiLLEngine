
/***********************************************************************************************************************************
 *	File : "KiLLSmartPointer.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Smart_Pointer_H__
#define __KiLL_Smart_Pointer_H__


namespace KiLL
{

/*=================================================================================================================================
 * --- Storage Deallocation Protocols -------------------------------------------------------------------------------------------*/

	template <class _type>
	class TArrayProtocol
	{
		INL static void		dealloc(_type* p_pdyObject);
	};

	template <class _type>
	class TPointerProtocol
	{
		INL static void		dealloc(_type* p_pdyObject);
	};




/*=================================================================================================================================
 * --- Smart Pointer ------------------------------------------------------------------------------------------------------------*/

	template <class _type, class _deallocprotocol = TPointerProtocol<_type>>
	class TSmartPointer
	{
	public:

		INL		TSmartPointer(_type* p_pdyObject);
		INL		~TSmartPointer();

		INL _type*		ReleasePtr();
		INL void		ReleasePtrTo(_type** p_ppdyContainer);

		INL _type&		operator * ();
		INL const _type&	operator*() const;
		INL _type*		operator -> ();
		INL const _type*	operator -> () const;
		INL _type&		operator [] (uint_t p_nIndex);
		INL const _type&	operator [] (uint_t p_nIndex);

	private:

		_type*		m_pdyObject;
	};




} // namespace KiLL

#include "KiLLSmartPointer.inl"


#endif // __KiLL_Smart_Pointer_INL__