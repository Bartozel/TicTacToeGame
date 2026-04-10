#pragma once
#include <array>

template<typename type, std::size_t N>
class SquareMatrix
{
public:
	type& operator()(std::size_t r, std::size_t c);
	const type& operator()(std::size_t r, std::size_t c) const;

private:
	std::size_t _size = N;
	std::array<std::array<type, N>, N> _state;
};

template <typename type, std::size_t N>
type& SquareMatrix<type, N>::operator()(std::size_t r, std::size_t c)
{
	return _state[r][c];
}

template <typename type, std::size_t N>
const type& SquareMatrix<type, N>::operator()(std::size_t r, std::size_t c) const
{
	return  _state[r][c];
}
