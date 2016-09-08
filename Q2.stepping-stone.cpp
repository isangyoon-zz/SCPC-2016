#include <iostream>
#include <cstring> // using std::memset
#include <vector>

const int MOD = 1000000009;

int T;
int answer[50001];
int dp[50001][101]; // dp[N][K] = N번째 징검다리로 K거리 만큼 점프했을 때 개울을 건너는 방법 수

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> T;

  for (int TC = 1; TC <= T; ++TC)
  {
    int N, K, L;
    std::cin >> N >> K >> L;

    std::vector<bool> mines(N + 1, false);
    for (int i = 1, x; i <= L; ++i) std::cin >> x, mines[x] = true;

    std::memset(dp, 0, sizeof(dp));
    dp[0][0] = answer[0] = 1;

    for (int i = 1; i <= N; ++i)
    {
      answer[i] = 0;
      if (mines[i]) continue;

      for (int j = 1; j <= K && (i >= j); ++j) dp[i][j] = ((answer[i - j] + MOD) - dp[i - j][j]) % MOD, answer[i] = (answer[i] + dp[i][j]) % MOD;
    }

    std::cout << "Case #" << TC << "\n" << answer[N] << "\n";
  }

  return 0;
}
