#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

vector <int> graph[6];  //create the graph
vector <int> vis(6, 0);

void dfs(int u)  //dfs algorithm
{
    if (vis[u])return;
    vis[u] = 1;

    for (auto v : graph[u])
    {
        dfs(v);
    }
}

void generateSubgraphs(int n) //the function to create the sub graphs
{
    vector <pair<int, int>> edges; //create all the edges of the graph

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            edges.push_back({ i,j });
        }
    }

    int edgesCount = edges.size(); //number of edges
    int count = 0;

    vector <int> mask;
    count = 0;

    for (int i = 0; i < (1 << edgesCount); i++)
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

        if (allVisited)
        {
            mask.push_back(i);
            count += 1 << countSetBits; //if all the nodes were visited then count the total number
        }
    }

    cout << n << endl; //start to print to the file
    cout <<"count = "<< count << endl;
    int ctr = 1;
    for (int i = 0; i < mask.size(); i++)
    {
        vector<int> indices;
        for (int j = 0; j < edgesCount; j++)
        {
            if (mask[i] & (1 << j)) 
            {
                indices.push_back(j);
            }
        }

        for (int j = 0; j < (1 << indices.size()); j++)
        {
            cout << "#" << ctr++ << endl; //print the number of the sub graph
            for (int k = 0; k < indices.size(); k++)
            {
                if ((j & (1 << k)) == 0)
                    cout << edges[indices[k]].first << " " << edges[indices[k]].second << endl; //print the edges
                else
                {
                    cout << edges[indices[k]].first << " " << edges[indices[k]].second << endl;
                    cout << edges[indices[k]].second << " " << edges[indices[k]].first << endl;
                }
            }
        }
    }
}

int main() //the main function
{
    cout << "enter n:"; //get the n from user
    int n; cin >> n;
    cout << endl;


#ifndef	ONLINE_JUDGE
    freopen("output.txt", "w", stdout); //open the file
#endif

    
    generateSubgraphs(n); //start the function

}