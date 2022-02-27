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
		template<typename Allocator, template<typename, typename> typename Collection>
		explicit linq(const Collection<T, Allocator>& collection);

	public:
		linq& select(T(*transform)(T));
		linq& where(bool(*predicate)(T));

	public:
		std::vector<T> to_vector() const;

	private:
		std::size_t m_elements;
		std::vector<T> m_collection;
	};

	template<typename T, typename Allocator, template<typename, typename> typename Collection>
	linq<T> from(const Collection<T, Allocator>& collection);
}

#include "cinq_impl.h"