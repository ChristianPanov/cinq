#pragma once

#include "cinq.h"

namespace cinq
{
	template<typename T>
	template<std::size_t Size>
	linq<T>::linq(const T(&arr)[Size])
		: m_storage{ std::begin(arr), std::end(arr) }
		, m_elements{ Size }
	{}

	template<typename T>
	template<std::size_t Size>
	linq<T>::linq(const std::array<T, Size>& arr)
		: m_storage{ arr.begin(), arr.end() }
		, m_elements{ Size }
	{}

	template<typename T>
	template<typename Allocator, template<typename, typename> typename Collection>
	linq<T>::linq(const Collection<T, Allocator>& collection)
		: m_storage{ collection.begin(), collection.end() }
		, m_elements{ collection.size() }
	{}

	template<typename T>
	linq<T>& linq<T>::select(T(*transform)(T))
	{
		for (auto& element : m_storage)
			element = transform(element);
		return *this;
	}

	template<typename T>
	linq<T>& linq<T>::where(bool(*predicate)(T))
	{
		std::vector<T> new_storage;
		for (auto& element : m_storage)
		{
			if (predicate(element) == true)
				new_storage.push_back(element);
			else m_elements--;
		}
		m_storage = new_storage;

		return *this;
	}

	template<typename T>
	linq<T>& linq<T>::take(std::size_t count)
	{
		std::vector<T> new_storage{ m_storage.begin(), 
			m_storage.begin() + count };
		m_storage = new_storage;
		return *this;
	}

	template<typename T>
	std::vector<T> linq<T>::to_vector() const
	{
		return m_storage;
	}

	template<typename T, std::size_t Size>
	linq<T> from(const T(&arr)[Size])
	{
		return linq<T>{ arr };
	}

	template<typename T, std::size_t Size>
	linq<T> from(const std::array<T, Size>& arr)
	{
		return linq<T>{ arr };
	}

	template<typename T, typename Allocator, template<typename, typename> typename Collection>
	linq<T> from(const Collection<T, Allocator>& collection)
	{
		return linq<T>{ collection };
	}
}