#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
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
		template<typename Allocator, template<typename, typename> typename Container>
		explicit linq(const Container<T, Allocator>& collection);

	public:
		template<typename Callable> linq& select(Callable transform);
		template<typename Callable> linq& where(Callable predicate);
		template<typename Callable> linq& take_while(Callable predicate);
		template<typename Callable> linq& skip_while(Callable predicate);
		linq& take(std::size_t count);
		linq& skip(std::size_t count);

	public:
		template<typename Callable> bool all(Callable predicate) const;
		template<typename Callable> bool any(Callable predicate) const;
		bool any() const;

	public:
		std::vector<T> to_vector() const;

	private:
		std::vector<T> m_storage;
	};

	template<typename T, std::size_t Size>
	linq<T> from(const T(&arr)[Size]);

	template<typename T, std::size_t Size>
	linq<T> from(const std::array<T, Size>& arr);

	template<typename T, typename Allocator, template<typename, typename> typename Container>
	linq<T> from(const Container<T, Allocator>& collection);
}

#include "cinq_impl.h"