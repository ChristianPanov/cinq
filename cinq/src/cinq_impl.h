#pragma once

#include "cinq.h"

namespace cinq
{
	template<typename T>
	template<std::size_t Size>
	linq<T>::linq(const std::array<T, Size>& arr)
		: m_collection{ std::begin(arr), std::end(arr) }
		, m_elements{ Size }
	{}

	template<typename T>
	template<typename Allocator, template<typename, typename> typename Collection>
	linq<T>::linq(const Collection<T, Allocator>& collection)
		: m_collection{ std::begin(collection), std::end(collection) }
		, m_elements{ std::size(collection) }
	{}

	template<typename T>
	linq<T>& linq<T>::select(T(*transform)(T))
	{
		for (auto& element : m_collection)
			element = transform(element);
		return *this;
	}

	template<typename T>
	linq<T>& linq<T>::where(bool(*predicate)(T))
	{
		std::vector<T> new_collection{};
		for (auto& element : m_collection)
		{
			if (predicate(element) == true)
				new_collection.push_back(element);
			else m_elements--;
		}
		m_collection = new_collection;

		return *this;
	}

	template<typename T>
	std::vector<T> linq<T>::to_vector() const
	{
		return m_collection;
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