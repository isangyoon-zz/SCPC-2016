#include <iostream>

int T;
int dp[64];

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  for (int i = 1500; i > 0; --i)
  {
    int j = i;
    int length = 0;
    while (j != 1)
    {
      if (j & 1) j = j * 3 + 1, ++length;
      else while (!(j & 1)) { j >>= 1, ++length; };
    }

    if (length <= 63) dp[length] = i;
  }

  std::cin >> T;
  for (int TC = 1; TC <= T; ++TC)
  {
    int K;
    std::cin >> K;

    std::cout << "Case #" << TC << "\n" << dp[K] << " " << (1ULL << K) << "\n";
  }

  return 0;
}
