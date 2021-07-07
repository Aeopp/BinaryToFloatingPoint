#include <iostream>
#include <numeric>
#include <limits>
#include <cmath>
#include <array>

template<uint64_t Exponent>
constexpr uint64_t Pow2()
{
	return 2 * Pow2<Exponent - 1>();
};

template<>
constexpr uint64_t Pow2<0>()
{
	return 1;
};

bool IsBitOn(const int32_t BinaryNumber,
	const int32_t BitNth)
{
	return BinaryNumber & (1 << BitNth);
}

template<int32_t BinaryNumber,
	int32_t BitNth>
	constexpr bool IsBitOn()
{
	return BinaryNumber & (1 << BitNth);
};

template<int64_t BinaryNumber>
constexpr float FloatingNumber()
{
	static constexpr int64_t Bias = -127;
	int64_t _Exponent = Bias;

	for (int32_t i = 23; i < 31; ++i)
	{
		if (IsBitOn(BinaryNumber, i))
			_Exponent += std::pow<int64_t>(2,i-23);
	}

	if (_Exponent == Bias)
	{
		return 0.0f;
	}
	else if (_Exponent == 128)
	{
		return std::numeric_limits<float>::infinity();
	}

	float Mantissa = 1.f;

	for (int32_t i = 0; i < 23; ++i)
	{
		if (IsBitOn(BinaryNumber, i))
			Mantissa +=  std::pow<int64_t>(2, i - 23);
	}

	constexpr float Sign = IsBitOn<BinaryNumber, 31>() ? -1.f : 1.f;

	return Mantissa * (std::pow(2, _Exponent)) * Sign;
};


int main()
{
	constexpr int32_t BiNumber = 0b11000110101101111011001111111111;

	std::cout.precision(100);

	float Number = FloatingNumber<BiNumber>();
	int32_t* Ptr = reinterpret_cast<int32_t*> (&Number);
	std::cout << "내가 변환한 숫자 : " << Number << std::endl;
	
	return 0;
}
