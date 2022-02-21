#include "cinq.h"
#pragma once

namespace cinq
{
	template<typename Collection>
	linq<Collection>::linq(Collection collection)
		: m_collection{ collection }
	{}

	template<typename Collection>
	linq<Collection>& linq<Collection>::select(value_type(*transform)(value_type))
	{
		for (auto& element : m_collection)
			element = transform(element);
		return *this;
	}

	template<typename Collection>
	Collection linq<Collection>::to_type() const
	{
		return m_collection;
	}

	template<typename Collection>
	linq<Collection> from(const Collection& collection)
	{
		return linq<Collection>{ collection };
	}
}