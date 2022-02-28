#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

namespace cinq
{
	template<typename T>
	class linq
	{
	public:
		template<std::size_t Size>
		explicit linq(const T(&arr)[Size]);
		template<std::size_t Size>
		explicit linq(const std::array<T, Size>& arr);
		template<typename Allocator, template<typename, typename> typename Collection>
		explicit linq(const Collection<T, Allocator>& collection);

	public:
		linq& select(T(*transform)(T));
		linq& where(bool(*predicate)(T));
		linq& take(std::size_t count);
		linq& skip(std::size_t count);

	public:
		std::vector<T> to_vector() const;

	private:
		std::size_t m_elements;
		std::vector<T> m_storage;
	};

	template<typename T, std::size_t Size>
	linq<T> from(const T(&arr)[Size]);

	template<typename T, std::size_t Size>
	linq<T> from(const std::array<T, Size>& arr);

	template<typename T, typename Allocator, template<typename, typename> typename Collection>
	linq<T> from(const Collection<T, Allocator>& collection);
}

#include "cinq_impl.h"