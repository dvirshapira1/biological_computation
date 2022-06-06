#include <iostream>
#include <vector>
using namespace std;

vector <int> graph[5];  //create the graph
vector <int> vis(5, 0);

void dfs(int u) //dfs algorithm
{
    if (vis[u])return;
    vis[u] = 1;

    for (auto v : graph[u])
    {
        dfs(v);
    }
}

void generateSubgraphs(int n, vector <pair<int, int>> edges) //the function to create the sub graphs
{

    int edgesCount = edges.size();
    int count = 0;

    vector <int> mask;
    count = 0;

    for (int i = 0; i < (1 << edgesCount); i++) //number of edges
    {

        int countSetBits = 0;
        for (int j = 1; j <= n; j++)
        {
            graph[j].clear(); //clear the graph in every round
            vis[j] = 0;
        }

        for (int j = 0; j < edgesCount; j++) 
        {
            if (i & (1 << j)) //if the result is 1 then we count it
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
        for (int j = 1; j <= n; j++) //check if the nodes were visited
        {
            if (vis[j] == 0)allVisited = false;
        }

        if (allVisited)  //if all the nodes were visited then add to the total number
        {
            mask.push_back(i);
            count += 1;
        }
    }
    cout << "n= "; //start to print
    cout << n << endl;
    cout << "count= ";
    cout << count << endl;
    int ctr = 1;
    for (int i = 0; i < mask.size(); i++)
    {
        vector<int> indices;
        cout << "#" << ctr++ << endl; //print the number of the sub graph
        for (int j = 0; j < edgesCount; j++)
        {
            if (mask[i] & (1 << j))
            {
                cout << edges[j].first << " " << edges[j].second << endl; //print the edges
            }
        }
    }
}

int main()
{
    int n;
    cout << "enter n:";
    cin >> n;
    cout << endl;

    vector <pair<int, int>> edges;
    cout << "enter number of edges:";
    int m; cin >> m;//number of edges
    cout << endl;

    for (int i = 1; i <= m; i++)  //get the edges
    {
        cout << "enter edge in the format (u v):";
        int u, v; cin >> u >> v;
        cout << endl;
        edges.push_back({ u,v });
    }

    generateSubgraphs(n, edges); //start the function

}