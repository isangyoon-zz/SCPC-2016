#include <iostream>
#include <functional>
#include <vector>
#include <queue>

const long long INF = 9223372036854775807LL;

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  std::cin >> T;

  for (int TC = 1; TC <= T; ++TC)
  {
    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<std::pair<int, int> > > adj(N + 1);
    for (int i = 1, from, to, cost; i <= M; ++i)
    {
      std::cin >> from >> to >> cost;

      adj[from].push_back(std::make_pair(to, cost));
      adj[to].push_back(std::make_pair(from, cost));
    }

    std::vector<int> shelters(N + 1, 0);
    std::vector<long long> distance(N + 1, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;
    for (int i = 1, shelter; i <= K; ++i)
    {
      std::cin >> shelter;

      distance[shelter] = 0;
      shelters[shelter] = shelter;
      pq.push(std::make_pair(0, shelter));
    }

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();

      for (unsigned int i = 0; i < adj[u].size(); ++i)
      {
        int v = adj[u][i].first;

        if (distance[v] > distance[u] + adj[u][i].second)
        {
          shelters[v] = shelters[u];
          pq.push(std::make_pair((distance[v] = distance[u] + adj[u][i].second), v));
        }
        else if ((distance[v] == distance[u] + adj[u][i].second) && (shelters[v] > shelters[u]))
        {
          shelters[v] = shelters[u];
          pq.push(std::make_pair(distance[v], v));
        }
      }
    }

    std::pair<long long, long long> answers(0LL, 0LL);
    for (int i = 1; i <= N; ++i)
    {
      answers.first += distance[i];
      answers.second += shelters[i];
    }

    std::cout << "Case #" << TC << "\n" << answers.first << "\n" << answers.second << "\n";
  }

  return 0;
}
