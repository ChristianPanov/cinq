#pragma once

#include "cinq.h"

namespace cinq
{
	template<typename T>
	template<std::size_t Size>
	linq<T>::linq(const T(&arr)[Size])
		: m_storage{ std::begin(arr), std::end(arr) }
	{}

	template<typename T>
	template<std::size_t Size>
	linq<T>::linq(const std::array<T, Size>& arr)
		: m_storage{ arr.begin(), arr.end() }
	{}

	template<typename T>
	template<typename Allocator, template<typename, typename> typename Container>
	linq<T>::linq(const Container<T, Allocator>& collection)
		: m_storage{ collection.begin(), collection.end() }
	{}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::order_by(Callable key)
	{
		std::sort(m_storage.begin(), m_storage.end(),
			[key](T lhs, T rhs)
			{
				return key(lhs) < key(rhs);
			}
		);
		return *this;
	}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::order_by_descending(Callable key)
	{
		std::sort(m_storage.begin(), m_storage.end(),
			[key](T lhs, T rhs)
			{
				return key(lhs) > key(rhs);
			}
		);
		return *this;
	}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::select(Callable transform)
	{
		for (auto& element : m_storage)
			element = transform(element);
		return *this;
	}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::where(Callable predicate)
	{
		std::vector<T> new_storage;
		for (auto& element : m_storage)
		{
			if (predicate(element))
				new_storage.push_back(element);
		}
		m_storage = new_storage;

		return *this;
	}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::take_while(Callable predicate)
	{
		std::size_t count{};
		for (auto& element : m_storage)
		{
			if (predicate(element)) count++;
			else break;
		}

		std::vector<T> new_storage{ m_storage.begin(),
			m_storage.begin() + count };

		m_storage = new_storage;
		return *this;
	}

	template<typename T>
	template<typename Callable>
	linq<T>& linq<T>::skip_while(Callable predicate)
	{
		std::size_t count{};
		for (auto& element : m_storage)
		{
			if (predicate(element)) count++;
			else break;
		}

		std::vector<T> new_storage{ m_storage.begin() + count,
			m_storage.end() };

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
	linq<T>& linq<T>::skip(std::size_t count)
	{
		std::vector<T> new_storage{ m_storage.begin() + count,
			m_storage.end() };
		m_storage = new_storage;
		return *this;
	}

	template<typename T>
	template<typename... Items, typename>
	linq<T>& linq<T>::append(Items&&... items)
	{
		(m_storage.push_back(items), ...);
		return *this;
	}

	template<typename T>
	template<typename... Items, typename>
	linq<T>& linq<T>::prepend(Items&&... items)
	{
		std::initializer_list<T> temp{ items... };
		m_storage.insert(m_storage.begin(), temp);
		return *this;
	}

	template<typename T>
	template<typename Callable>
	bool linq<T>::all(Callable predicate) const
	{
		for (const auto& element : m_storage)
			if (!predicate(element)) return false;
		return true;
	}

	template<typename T>
	template<typename Callable>
	bool linq<T>::any(Callable predicate) const
	{
		for (const auto& element : m_storage)
			if (predicate(element)) return true;
		return false;
	}

	template<typename T>
	bool linq<T>::any() const
	{
		return !m_storage.empty();
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

	template<typename T, typename Allocator, template<typename, typename> typename Container>
	linq<T> from(const Container<T, Allocator>& collection)
	{
		return linq<T>{ collection };
	}
}