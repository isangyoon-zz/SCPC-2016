#include <iostream>
#include <algorithm> // using std::fill
#include <vector>

const int SOURCE = 0;
const int SINK = 401;

struct ford_fulkerson
{
  struct edge
  {
    int to;
    int capacity;
    edge* reverse;

    edge(int to, int capacity) : to(to), capacity(capacity) {}
  };

  std::size_t n;
  int source, sink;
  std::vector<std::vector<edge*> > adj;
  std::vector<bool> visited;

  ford_fulkerson(std::size_t n, int source, int sink) : n(n), source(source), sink(sink)
  {
    adj.resize(n);
    visited.resize(n);
  }

  void add_edge(int u, int v, int capacity)
  {
    edge* forward = new edge(v, capacity);
    edge* backward = new edge(u, 0);

    forward->reverse = backward;
    backward->reverse = forward;

    adj[u].push_back(forward);
    adj[v].push_back(backward);
  }

  void add_edge_from_source(int v, int capacity)
  {
    add_edge(source, v, capacity);
  }

  void add_edge_to_sink(int u, int capacity)
  {
    add_edge(u, sink, capacity);
  }

  int dfs(int u, int c)
  {
    if (visited[u]) return 0;
    visited[u] = true;

    if (u == sink) return c;

    for (unsigned int i = 0; i < adj[u].size(); ++i)
    {
      if (adj[u][i]->capacity > 0)
      {
        int capacity = adj[u][i]->capacity;
        if (c != 0 && c < capacity) capacity = c;

        int flow = dfs(adj[u][i]->to, capacity);
        if (flow)
        {
          adj[u][i]->capacity -= flow;
          adj[u][i]->reverse->capacity += flow;

          return flow;
        }
      }
    }

    return 0;
  }

  int flow()
  {
    int answer = 0;
    while (true)
    {
      std::fill(visited.begin(), visited.end(), false);

      int f = dfs(source, 0);
      if (f == 0) break;

      answer += f;
    }

    return answer;
  }
};

int T;
int N, K;

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> T;

  for (int TC = 1; TC <= T; ++TC)
  {
    std::cin >> N >> K;

    int total = 0;
    ford_fulkerson maximum_flow(402, SOURCE, SINK);
    for (int i = 1, a, f, p; i <= N; ++i)
    {
      std::cin >> a >> f >> p;

      total += p;

      for (int j = a + 1; j <= f; ++j) maximum_flow.add_edge(j + 100, i + 200, 1);
      maximum_flow.add_edge_to_sink(i + 200, p);
    }

    for (int i = 1, s, e; i <= K; ++i)
    {
      std::cin >> s >> e;

      maximum_flow.add_edge_from_source(i, e - s);
      for (int j = s + 1; j <= e; ++j) maximum_flow.add_edge(i, j + 100, 1);
    }

    int answer = maximum_flow.flow();
    std::cout << "Case #" << TC << "\n" << (answer == total) << "\n";
  }

  return 0;
}
