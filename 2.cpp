#include <iostream>
#include <vector>
using namespace std;

vector <int> graph[5];
vector <int> vis(5, 0);

void dfs(int u)
{
    if (vis[u])return;
    vis[u] = 1;

    for (auto v : graph[u])
    {
        dfs(v);
    }
}

void generateSubgraphs(int n, vector <pair<int, int>> edges)
{

    int edgesCount = edges.size();
    int count = 0;

    vector <int> mask;
    count = 0;

    for (int i = 0; i < (1 << edgesCount); i++)
    {

        int countSetBits = 0;
        for (int j = 1; j <= n; j++)
        {
            graph[j].clear();
            vis[j] = 0;
        }

        for (int j = 0; j < edgesCount; j++)
        {
            if (i & (1 << j))
            {
                countSetBits++;
                int u = edges[j].first;
                int v = edges[j].second;

                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }

        dfs(1);
        int allVisited = true;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] == 0)allVisited = false;
        }

        if (allVisited)
        {
            mask.push_back(i);
            count += 1;
        }
    }

    cout << n << endl;
    cout << count << endl;
    int ctr = 1;
    for (int i = 0; i < mask.size(); i++)
    {
        vector<int> indices;
        cout << "#" << ctr++ << endl;
        for (int j = 0; j < edgesCount; j++)
        {
            if (mask[i] & (1 << j))
            {
                cout << edges[j].first << " " << edges[j].second << endl;
            }
        }
    }
}

int main()
{
    int n; cin >> n;

    vector <pair<int, int>> edges;
    int m; cin >> m;//number of edges
    for (int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        edges.push_back({ u,v });
    }

    generateSubgraphs(n, edges);

}