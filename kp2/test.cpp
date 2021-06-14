//
// Created by ivan- on 29.04.2021.
//

#include <iostream>

template <int N>
struct binary {
  static const int value = (N % 10) + 2 * binary<N / 10>::value;
};

template <>
struct binary<0> {
  static const int value = 0;
};

template <int N>
constexpr int  binary_v = binary<N>::value;
template <int N>
constexpr int  BIN =  binary_v<N>;

int main()
{
  int b = BIN<110>;
  std::cout << std::hex << b << std::endl;
}
