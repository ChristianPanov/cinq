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
		template<typename Allocator, template<typename, typename> typename Container>
		explicit linq(const Container<T, Allocator>& collection);

	public:
		linq& select(T(*transform)(T));
		linq& where(bool(*predicate)(T));
		linq& take(std::size_t count);
		linq& take_while(bool(*predicate)(T));
		linq& skip(std::size_t count);
		linq& skip_while(bool(*predicate)(T));

	public:
		bool all(bool(*predicate)(T)) const;
		bool any(bool(*predicate)(T)) const;
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