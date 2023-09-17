#include<iomanip>
#include <iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<set>
#include<deque>
#include<math.h>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<string.h>
#include<queue>
#define ll long long int

//ll p=999998727899999;
ll prime=998244353;
ll INF=1000000000000000000;
using namespace std;
vector<int> graph[200001],decomposed[200001],volume(200001,0),parent(200001,-1),visited(200001,0);int head=-1;
void dfs(int j,int par)
{
    volume[j]=0;
    for(auto p:graph[j])
    {
        if(p!=par&&!visited[p])
        {
            dfs(p,j);volume[j]+=volume[p];
        }
    }
    volume[j]+=1;
}
int findCentroid(int cur,int par,int &s)
{
    for(auto p:graph[cur])
    {
        if(!visited[p]&&p!=par)
        {
            if(volume[p]*2>s)return(findCentroid(p,cur,s));
        }
    }
    return(cur);
}
void centroid_decomposition(int root,int par)
{
    dfs(root,-1);
    int centroid=findCentroid(root,-1,volume[root]);
    if(par!=-1)
    {
        decomposed[par].push_back(centroid);
        decomposed[centroid].push_back(par);
    }
    else
    {
        head=centroid;
    }
    visited[centroid]=1;
    for(auto p:graph[centroid])
    {
        if(!visited[p])centroid_decomposition(p,centroid);
    }
}
map<int,char> ans;
void finaldfs(int j,int par,char s)
{
    ans[j]=s;
    for(auto p:decomposed[j])
    {
        if(p!=par)
        {
            finaldfs(p,j,s+1);
        }
    }
}
int main()
{
    int t;t=1;//cin>>t;
     while(t--)
	{
       
        centroid_decomposition(1,-1);
	}
	return(0);
}