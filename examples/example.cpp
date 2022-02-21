#include "cinq.h"

#include <iostream>
#include <array>

int main()
{
	std::array src = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto& dst = cinq::from(src)
		.select([](auto x) { return x * 2; })
		.to_type();


	for (int i = 0; i < dst.size(); ++i)
	{
		std::cout << dst[i] << " ";
	}

	std::cout << '\n';

	return 0;
}