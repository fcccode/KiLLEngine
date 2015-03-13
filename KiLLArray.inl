
/***********************************************************************************************************************************
 *	File : "KiLLArray.inl"
 *
 *	KiLL Engine
 *	Copyright (C) 2009-2010 Alexandru Busila
 *
 *	This file is part of the "KiLL Engine".
 *	For conditions of use, see copyright notice in "KiLL Engine.h".
 **********************************************************************************************************************************/


#ifndef __KiLL_Array_INL__
#define __KiLL_Array_INL__


namespace KiLL
{

/*=================================================================================================================================
 * --- Dynamic Array Class ------------------------------------------------------------------------------------------------------*/

	template <class _type>
	INL				TArray<_type>::TArray(uint_t p_nCapacity)
	{
		Initialize(p_nCapacity);
	}
	template <class _type>
					TArray<_type>::TArray(uint_t p_nCapacity, uint_t p_nElements, const _type* p_pSrc)
	{
		// Check if incorrect parameters
		if (p_nCapacity < p_nElements) throw ARRAY_INCORRECTPARAM;

		// Check if array is wanted clear
		if (p_nCapacity == 0) {
			m_nCapacity = 0;
			m_nElements = 0;
			m_pdyArray = NULL;
			return;
		}

		// Copy from array
		m_nCapacity = p_nCapacity;
		m_pdyArray = new _type[m_nCapacity];
		if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
		memcpy(reinterpret_cast<void*>(m_pdyArray), reinterpret_cast<const void*>(p_pSrc),
					static_cast<size_t>(p_nElements*sizeof(_type)) );
		m_nElements = p_nElements;
	}
	template <class _type>
					TArray<_type>::TArray(const TArray<_type>& p_arraySrc)
	{
		// Check if @param array is clear
		if (p_arraySrc.m_nCapacity == 0) {
			m_nCapacity = 0;
			m_nElements = 0;
			m_pdyArray = NULL;
			return;
		}

		// Copy data
		if (p_arraySrc.m_pdyArray != NULL) {
			m_nCapacity = p_arraySrc.m_nCapacity;
			m_nElements = p_arraySrc.m_nElements;
			m_pdyArray = new _type[m_nCapacity];
			if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
			memcpy(reinterpret_cast<void*>(m_pdyArray), reinterpret_cast<const void*>(p_arraySrc.m_pdyArray),
						static_cast<size_t>(m_nCapacity*sizeof(_type)) );
		}
		else {
			m_nCapacity = 0;
			m_nElements = 0;
			m_pdyArray = NULL;
		}
	}
	template <class _type>
	INL				TArray<_type>::~TArray()
	{
		delete [] m_pdyArray;
	}

	template <class _type>
	INL void		TArray<_type>::ZeroArray()
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		memset(reinterpret_cast<void*>(m_pdyArray), 0, static_cast<size_t>(m_nCapacity*sizeof(_type)));
	}


	template <class _type>
	INL uint_t		TArray<_type>::GetCapacity() const
	{
		return m_nCapacity;
	}
	template <class _type>
	INL uint_t		TArray<_type>::GetElementsNum() const
	{
		return m_nElements;
	}
	template <class _type>
	INL size_t		TArray<_type>::GetAllocSize() const
	{
		return static_cast<size_t>(sizeof(_type)*m_nCapacity);
	}
	template <class _type>
	INL bool	TArray<_type>::IsEmpty() const
	{
		return (m_nElements == 0);
	}


	template <class _type>
	void	TArray<_type>::Initialize(uint_t p_nCapacity)
	{
		// Is array already used?
		if (m_pdyArray != NULL) delete [] m_pdyArray;

		// Check if array is wanted cleared
		if (p_nCapacity == 0) {
			m_nCapacity = 0;
			m_nElements = 0;
			m_pdyArray = NULL;
			return;
		}

		m_pdyArray = new _type[p_nCapacity];
		if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
		m_nCapacity = p_nCapacity;
		m_nElements = 0;
	}
	template <class _type>
	void	TArray<_type>::Reserve(uint_t p_nCapacity)
	{
		// Is current buffer big enough?
		if (p_nCapacity <= m_nCapacity) return;

		// Reallocate new capacity
		_type* pdyBuffer = new _type[p_nCapacity];
		if (pdyBuffer == NULL) throw ARRAY_ALLOCFAIL;
		if (p_pdyArray != NULL) {
				memcpy(reinterpret_cast<void*>(pdyBuffer), reinterpret_cast<const void*>(m_pdyArray),
							static_cast<size_t>(p_nCapacity*sizeof(_type)));
				delete [] m_pdyArray;
			}
		m_pdyArray = pdyBuffer;
		m_nCapacity = p_nCapacity;
	}
	template <class _type>
	void	TArray<_type>::Create(uint_t p_nCapacity, uint_t p_nElements, const _type* p_pSrc)
	{
		// Check if incorrect parameters
		if ((p_nCapacity < p_nElements) || (p_pSrc == NULL)) throw ARRAY_INCORRECTPARAM;

		// Check if array is wanted cleared
		if (p_nCapacity == 0) {
			m_nCapacity = 0;
			m_nElements = 0;
			delete [] m_pdyArray;
			m_pdyArray = NULL;
			return;
		}

		// If array is used free the memory
		delete [] m_pdyArray;

		// Assign new capacity and copy data from @param
		m_pdyArray = new _type[p_nCapacity];
		if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
		memcpy(reinterpret_cast<void*>(m_pdyArray), reinterpret_cast<const void*>(p_pSrc),
					static_cast<size_t>(p_nElements*sizeof(_type)));

		m_nCapacity = p_nCapacity;
		m_nElements = p_nElements;
	}
	template <class _type>
	void	TArray<_type>::Clear()
	{
		delete [] m_pdyArray;
		m_pdyArray = NULL;
		m_nCapacity = 0;
		m_nElements = 0;
	}	

	template <class _type>
	void	TArray<_type>::Assign(const TArray<_type>& p_arraySrc)
	{
		// Empty current array
		if (m_pdyArray != NULL) {
			delete [] m_pdyArray;
			m_pdyArray = NULL;
			m_nCapacity = 0;
			m_nElements = 0;
		}

		// Check if @param is an empty array
		if (p_arraySrc.m_nCapacity == 0) return;

		// Copy data from @param
		m_nCapacity = p_arraySrc.m_nCapacity;
		m_nElements = p_arraySrc.m_nElements;
		m_pdyArray = new _type[m_nCapacity];
		if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
		memcpy(reinterpret_cast<void*>(m_pdyArray), reinterpret_cast<const void*>(p_arraySrc.m_pdyArray),
					static_cast<size_t>(m_nElements*sizeof(_type)) );
	}

	template <class _type>
	INL bool	TArray<_type>::CheckInsert(uint_t p_nElements = 1)
	{
		return ((m_nElements + p_nElements) <= m_nCapacity);
	}
	template <class _type>
	void	TArray<_type>::Insert(uint_t p_nIndex, const _type& p_Obj)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// If index too big throw error
		if (p_nIndex > m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		// Check if new size is bigger than allocated capacity
		if ((m_nElements + 1) > m_nCapacity) Reserve(m_nElements + 1);

		// Move the array objects by 1 offset upper if index is in middle
		memmove(reinterpret_cast<void*>(m_pdyArray + ((p_nIndex+1)*sizeof(_type))),
					reinterpret_cast<const void *>(m_pdyArray + (p_nIndex*sizeof(_type))),
					static_cast<size_t>((m_nElements - p_nIndex)*sizeof(_type)) );

		// Copy @param object inside
		memcpy(reinterpret_cast<void*>(m_pdyArray+(p_nIndex*sizeof(_type))),
					reinterpret_cast<const void *>(&p_Obj), sizeof(_type));
		m_nElements += 1;
	}
	template <class _type>
	void	TArray<_type>::Insert(uint_t p_nIndex, uint_t p_nElements, const _type* p_pSrc)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// End if nothing to copy
		if (p_nElements == 0) return;
		if (p_pSrc == NULL) return;

		// If index too big throw error
		if (p_nIndex > m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		// Check if when inserting inside overflows the size
		if ((m_nElements + p_nElements) > m_nCapacity) Reserve(m_nElements + p_nElements);

		// Moving objects inside array to offset upper
		memmove(reinterpret_cast<void*>(m_pdyArray + ((p_nIndex + p_nElements)*sizeof(_type))),
					reinterpret_cast<const void *>(m_pdyArray + (p_nIndex*sizeof(_type))),
					static_cast<size_t>((m_nElements - p_nIndex)*sizeof(_type)) );

		// Copy @param objects inside
		memcpy(reinterpret_cast<void*>(m_pdyArray + p_nIndex*sizeof(_type)),
					reinterpret_cast<const void *>(p_pSrc), p_nElements*sizeof(_type));

		m_nElements += p_nElements;
	}
	template <class _type>
	void	TArray<_type>::Insert(uint_t p_nIndex, const TArray<_type>& p_arraySrc)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// If index too big throw error
		if (p_nIndex > m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		// End if nothing to copy
		if (p_arraySrc.m_nElements == 0) return;

		// Check if current capacity is zero if yes allocate to the size of @param.m_nElements
		if (m_nCapacity == 0) Initialize(p_arraySrc.m_nElements);

		// Check if when inserting inside overflows the capacity
		if ((m_nElements + p_arraySrc.m_nElements) > m_nCapacity) Reserve(m_nElements + p_arraySrc.m_nElements);

		// Moving objects inside array to offset
		memmove(reinterpret_cast<void*>(m_pdyArray+((p_nIndex+p_arraySrc.m_nElements)*sizeof(_type))),
					reinterpret_cast<const void*>(m_pdyArray+(p_nIndex*sizeof(_type))),
					static_cast<size_t>(p_arraySrc.m_nElements*sizeof(_type)) );

		// Moving new objects inside
		memcpy(reinterpret_cast<void*>(m_pdyArray+(p_nIndex*sizeof(_type))),
					reinterpret_cast<const void *>(p_arraySrc.m_pdyArray), static_cast<size_t>(p_arraySrc.m_nElements*sizeof(_type))  );

		m_nElements += p_arraySrc.m_nElements;
	}

	template <class _type>
	INL void	TArray<_type>::Append(const _type &p_Obj)
	{
		Insert(m_nElements, p_Obj);
	}
	template <class _type>
	INL void	TArray<_type>::Append(uint_t p_nElements, const _type* p_pSrc)
	{
		Insert(m_nElements, p_nElements, p_pSrc);
	}
	template <class _type>
	INL void	TArray<_type>::Append(const TArray<_type>& p_arraySrc)
	{
		Insert(m_nElements, p_arraySrc);
	}

	template <class _type>
	void	TArray<_type>::Erase(uint_t p_nIndex)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// If index too big throw error
		if (p_nIndex => m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		// Move upper data to 1 offset lower
		if (static_cast<int_t>(m_nElements - p_nIndex - 1) > 0) {
			memmove(reinterpret_cast<void*>(m_pdyArray + (p_nIndex*sizeof(_type))),
						reinterpret_cast<const void*>(m_pdyArray + ((p_nIndex+1)*sizeof(_type))),
						static_cast<size_t>(m_nElements - p_nIndex - 1) );
		}

		m_nElements -= 1;
	}
	template <class _type>
	void	TArray<_type>::Erase(uint_t p_nIndex, uint_t p_nElements)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// End if nothing to erase
		if (p_nElements == 0) return;

		// Check if index is out of range
		if ((p_nIndex + p_nElements) > m_nElements) throw ARRAY_INCORRECTPARAM;

		// Check if too many obj erased
		if (static_cast<int_t>(m_nElements - p_nIndex - p_nElements) < 0) throw ARRAY_INCORRECTPARAM;

		// Move upper data to offset lower
		if (static_cast<uint_t>(m_nElements - p_nIndex - p_nElements) > 0) {
			memmove(reinterpret_cast<void*>(m_pdyArray + (p_nIndex*sizeof(_type))),
						reinterpret_cast<const void*>(m_pdyArray + ((p_nIndex+p_nElements)*sizeof(_type))),
						static_cast<size_t>(m_nElements - p_nIndex - p_nElements) );
		}

		m_nElements -= p_nElements;
	}

	template <class _type>
	void	TArray<_type>::Overwrite(uint_t p_nIndex, const _type& p_Obj)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// If index too big throw error
		if (p_nIndex >= m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		// Overwrite data
		memcpy(reinterpret_cast<void*>(m_pdyArray + (p_nIndex*sizeof(_type))),
					reinterpret_cast<const void*>(&p_Obj), sizeof(_type) );
	}


	template <class _type>
	INL _type*	TArray<_type>::Front() const
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		return m_pdyArray;
	}
	template <class _type>
	INL _type*	TArray<_type>::Back() const
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		return (m_pdyArray + (sizeof(_type)*m_nElements));
	}
	template <class _type>
	INL _type*	TArray<_type>::GetPointer(uint_t p_nIndex) const
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// If index too big throw error
		if (p_nIndex > m_nElements) throw ARRAY_INDEXOUTOFRANGE;

		return (m_pdyArray + (p_nIndex*sizeof(_type)));
	}
	template <class _type>
	INL uint_t	TArray<_type>::GetIndex(pvoid_t p_pDst) const
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// Check if index pointer is incorrect
		if ((p_pvdDst < m_pdyArray) || (p_pvdDst > (m_nElements*sizeof(_type)+m_pdyArray))) throw ARRAY_INDEXPOINTEROUTOFRANGE;

		// Check if index pointer doesnt point to a bad class
		//if (((p_pObj - m_pdyArray) % sizeof(_type)) > 0) throw KILL_ARRAY_INCORRECTPARAMETERS;

		return static_cast<uint_t>((m_pdyArray - p_pvdDst) / sizeof(_type) + 1);
	}


	template <class _type>
	INL void	TArray<_type>::PushBackAssign(const _type& p_Obj)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// Check if enough space for new Obj
		if (m_nElements == m_nCapacity) Reserve(m_nElements + 1);
	
		// Copy element with a = operator, Obj must have an overloaded = operator so this can work
		m_pdyArray[m_nElements] = p_Obj;
		m_nElements += 1;
	}
	template <class _type>
	INL void	TArray<_type>::PushBack(const _type& p_Obj)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// Check if enough space for new Obj
		if (m_nElements == m_nCapacity) Reserve(m_nElements + 1);
	
		// Copy data
		memcpy(reinterpret_cast<void*>(m_pdyArray + (m_nElements*sizeof(_type))),
					reinterpret_cast<const void*>(&p_Obj), static_cast<size_t>(sizeof(_type)));
		m_nElements += 1;
	}
	template <class _type>
	INL void	TArray<_type>::PopBack()
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// Check if array has no more obj
		if (m_nElements == 0) throw ARRAY_IMPOSSIBLEPOPBACK;

		m_nElements -= 1;
	}


	template <class _type>
	INL _type&	TArray<_type>::operator [] (uint_t p_nIndex)
	{
		// Check if pointer to data is NULL
		if (m_pdyArray == NULL) throw ARRAY_NULLPTR;

		// Check if index is out of range
		if (p_nIndex >= m_nElements) throw ARRAY_INDEXOUTOFRANGE;
		
		return m_pdyArray[p_nIndex];
	}


	template <class _type>
	void	TArray<_type>::operator = (const TArray<_type>& p_arraySrc)
	{
		// Empty current array
		delete [] m_pdyArray;
		m_pdyArray = NULL;
		m_nCapacity = 0;
		m_nElements = 0;

		// Check if @param is an empty array
		if (p_arraySrc.m_nCapacity == 0) {
			return;
		}

		// Copy data
		m_nCapacity = p_arraySrc.m_nCapacity;
		m_nElements = p_arraySrc.m_nElements;
		m_pdyArray = new _type[m_nCapacity];
		if (m_pdyArray == NULL) throw ARRAY_ALLOCFAIL;
		if (m_nElements > 0) {
			memcpy(reinterpret_cast<void*>(m_pdyArray), reinterpret_cast<const void*>(p_arraySrc.m_pdyArray),
						static_cast<size_t>(m_nElements*sizeof(_type)));
		}
	}




} // namespace KiLL


#endif // __KiLL_Array_INL__