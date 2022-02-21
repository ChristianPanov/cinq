#pragma once

namespace cinq
{
	template<typename Collection>
	class linq
	{
		using value_type = typename Collection::value_type;

	public:
		explicit linq(Collection collection);
		linq& select(value_type (*transform)(value_type));

	public:
		Collection to_type() const;

	private:
		Collection m_collection;
	};

	template<typename Collection>
	linq<Collection> from(const Collection& collection);
}

#include "cinq_impl.h"