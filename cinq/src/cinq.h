#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <set>
#include <list>
#include <deque>
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
		template<typename Callable> linq& order_by(Callable key);
		template<typename Callable> linq& order_by_descending(Callable key);
		template<typename Callable> linq& select(Callable transform);
		template<typename Callable> linq& where(Callable predicate);
		template<typename Callable> linq& take_while(Callable predicate);
		template<typename Callable> linq& skip_while(Callable predicate);
		linq& take(std::size_t count);
		linq& skip(std::size_t count);

	public:
		template<typename... Items, typename = std::enable_if_t<(std::is_same_v<T, Items>, ...)>> 
		linq& append(Items&&... items);
		template<typename... Items, typename = std::enable_if_t<(std::is_same_v<T, Items>, ...)>>
		linq& prepend(Items&&... items);

	public:
		template<typename Callable> bool all(Callable predicate) const;
		template<typename Callable> bool any(Callable predicate) const;
		bool any() const;

	public:
		std::set<T> to_set() const;
		std::list<T> to_list() const;
		std::deque<T> to_deque() const;
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