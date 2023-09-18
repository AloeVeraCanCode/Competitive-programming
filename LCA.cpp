vector<int> graph[200001];
int dp[200001][23],height[200001];
void findPar(int j,int par,int h)
{
    dp[j][0]=par;height[j]=h;
    for(auto p:graph[j])
    {
        if(p!=par)
        {
            findPar(p,j,h+1);
        }
    }
}
void preProcessLca(int n)
{
    int j;
    for(j=1;j<23;j++)
    {
        for(int node=1;node<=n;node++)
        {
            dp[node][j]=-1;
            if(dp[node][j-1]==-1){continue;}
            dp[node][j]=dp[dp[node][j-1]][j-1];
        }
    }
}
int binaryLift(int x,int h)
{
    int bit=22;
    while(h>0)
    {
        if(h<(1<<bit)){bit--;continue;}
        else
        {
            h-=(1<<bit);x=dp[x][bit];
        }
        bit--;
    }
    return(x);
}
int findLca(int a,int b)
{
    if(a==b)return(a);
    if(height[a]<height[b])
    {
        swap(a,b);
    }
    a=binaryLift(a,height[a]-height[b]);
    if(a==b)return(a);
    int bit=22;
    while(bit>=0)
    {
        if(dp[a][bit]==dp[b][bit]){bit--;continue;}
        else
        {
           a=dp[a][bit];b=dp[b][bit];bit--;
        }
    }
    return(dp[a][0]);
}
int distance(int x,int y)
{
    int lca=findLca(x,y);return(height[x]+height[y]-2*height[lca]);
}
int main()
{
	findPar(1,-1,0);preProcessLca(n);
}