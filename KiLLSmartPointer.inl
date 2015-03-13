
/***********************************************************************************************************************************
 *	File : "KiLLSmartPointer.inl"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Smart_Pointer_INL__
#define __KiLL_Smart_Pointer_INL__


namespace KiLL
{

/*=================================================================================================================================
 * --- Storage Deallocation Protocols -------------------------------------------------------------------------------------------*/

	template <class _type>
	INL static void		TArrayProtocol<_type>::dealloc(_type* p_pdyObject)
	{
		delete [] p_pdyObject;
	}

	template <class _type>
	INL static void		TPointerProtocol<_type>::dealloc(_type* p_pdyObject)
	{
		delete p_pdyObject;
	}




/*=================================================================================================================================
 * --- Smart Pointer ------------------------------------------------------------------------------------------------------------*/

	template <class _type, class _deallocprotocol>
	INL		TSmartPointer<_type, _deallocprotocol>::TSmartPointer(_type* p_pdyObject)
	{
		m_pdyObject = p_pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL		TSmartPointer<_type, _deallocprotocol>::~TSmartPointer()
	{
		_deallocprotocol::dealloc(m_pdyObject);
	}

	template <class _type, class _deallocprotocol>
	INL _type*		TSmartPointer<_type, _deallocprotocol>::ReleasePtr()
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		_type* pdyObject = m_pdyObject;
		m_pdyObject = NULL;
		return pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL void		TSmartPointer<_type, _deallocprotocol>::ReleasePtrTo(_type** p_ppdyContainer)
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		*p_ppdyContainer = m_pdyObject;
		m_pdyObject = NULL;
	}

	template <class _type, class _deallocprotocol>
	INL _type&		TSmartPointer<_type, _deallocprotocol>::operator * ()
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return *m_pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL const _type&	TSmartPointer<_type, _deallocprotocol>::operator*() const
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return *m_pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL _type*		TSmartPointer<_type, _deallocprotocol>::operator -> ()
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return m_pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL const _type*	TSmartPointer<_type, _deallocprotocol>::operator->() const
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return m_pdyObject;
	}
	template <class _type, class _deallocprotocol>
	INL _type&		TSmartPointer<_type, _deallocprotocol>::operator [] (uint_t p_nIndex)
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return m_pdyObject[p_nIndex];
	}
	template <class _type, class _deallocprotocol>
	INL const _type &	TSmartPointer<_type, _deallocprotocol>::operator [] (uint_t p_nIndex)
	{
		if (m_pdyObject == NULL) throw SMPTR_RELEASED;
		return m_pdyObject[p_nIndex];
	}




} // namespace KiLL


#endif // __KiLL_Smart_Pointer_INL__