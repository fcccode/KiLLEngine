
/***********************************************************************************************************************************
 *	File : "KiLLArray.h"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Array_H__
#define __KiLL_Array_H__


namespace KiLL
{

/*=================================================================================================================================
 * --- Dynamic Array Class ------------------------------------------------------------------------------------------------------*/

	template <class _type>
	class TArray	// Must add check in insert() functions to see if current m_pdyArray is NULL
	{
	public:

		INL				TArray() : m_nCapacity(0), m_nElements(0), m_pdyArray(NULL) {}
		INL explicit	TArray(uint_t m_nCapacity);
		explicit		TArray(uint_t m_nCapacity, uint_t p_nElements, const _type *p_pSrc);
		explicit		TArray(const TArray<_type> &p_arraySrc);
		INL				~TArray();


		INL void		ZeroArray();


		INL uint_t		GetCapacity() const;
		INL uint_t		GetElementsNum() const;
		INL size_t		GetAllocSize() const;
		INL bool		IsEmpty() const;


		void			Initialize(uint_t p_nObjCap);
		void			Reserve(uint_t m_nCapacity);
		void			Create(uint_t m_nCapacity, uint_t p_nElements, const _type* p_pSrc);
		void			Clear();

		void			Assign(const TArray<_type> &p_arraySrc);

		INL bool		CheckInsert(uint_t p_nElements = 1);
		void			Insert(uint_t p_nIndex, const _type& p_Obj);
		void			Insert(uint_t p_nIndex, uint_t p_nElements, const _type* p_pSrc);
		void			Insert(uint_t p_nIndex, const TArray<_type>& p_arraySrc);

		INL void		Append(const _type& p_Obj);
		INL void		Append(uint_t p_nElements, const _type* p_pSrc);
		INL void		Append(const TArray<_type> &p_arraySrc);

		void			Erase(uint_t p_nIndex);
		void			Erase(uint_t p_nIndex, uint_t p_nElements);

		void			Overwrite(uint_t p_nIndex, const _type& p_Obj);


		INL _type*		Front() const;
		INL _type*		Back() const;
		INL _type*		GetPointer(uint_t p_nIndex) const;
		INL uint_t		GetIndex(pvoid_t p_pvdDst) const;


		INL void		PushBackAssign(const _type& p_Obj);
		INL void		PushBack(const _type& p_Obj);
		INL void		PopBack();


		INL _type&		operator [] (uint_t p_nIndex);


		void			operator = (const TArray<_type>& p_arraySrc);

	protected:

		_type*			m_pdyArray;
		uint_t			m_nElements;
		uint_t			m_nCapacity;
	};




} // namespace KiLL

#include "KiLLArray.inl"


#endif // __KiLL_Array_H__