#include <iostream>
#include <vector>

int T;
std::vector<std::vector<bool> > adj;
std::vector<bool> check;

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> T;

  for (int TC = 1; TC <= T; ++TC)
  {
    int K, L, N, M;
    std::cin >> K >> L >> N >> M;

    adj.assign(N + 1, std::vector<bool>(N + 1, false));
    check.assign(N + 1, false);

    while (M--)
    {
      int from, to;
      std::cin >> from >> to;

      adj[from][to] = adj[to][from] = true;
    }

    int V = N;
    while (true)
    {
      int i = 0;
      for (i = 1; i <= N; ++i)
      {
        if (check[i]) continue;

        int degree = 0;
        for (int j = 1; j <= N; ++j) degree += adj[i][j];

        if (degree < K || degree > (V - L - 1))
        {
          --V;
          check[i] = true;
          for (int j = 1; j <= N; ++j) adj[i][j] = adj[j][i] = false;

          break;
        }
      }

      if (i == (N + 1)) break;
    }

    int answer = 0;
    for (int i = 1; i <= N; ++i) if (check[i]) answer += i;

    std::cout << "Case #" << TC << "\n" << answer << "\n";
  }

  return 0;
}
