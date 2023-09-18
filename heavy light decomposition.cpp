vector<int> graph[200001],parent(200001,0),visited(200001,0),s(200001,0),cost(200001,0),height(200001,0),head(200001,0);
unordered_map<int,int> ind;int number=0;
unordered_map<int,ll> revcost;
ll query(int l,int r,int x,int y,int i,vector<ll> &seg);
void sizedfs(int j,int h=0)
{
    visited[j]=1;height[j]=h;
    for(auto p:graph[j])
    {
        if(!visited[p])
        {
            sizedfs(p,h+1);s[j]+=s[p];
        }
    }
    s[j]++;
}
void decompose(int j,int h,int par)
{
    ind[j]=++number;parent[j]=par;revcost[number]=cost[j];
    head[j]=h;int big=0,v=-1;
    for(auto p:graph[j])
    {
        if(p!=par)
        {
            if(s[p]>big)
            {
                v=p;big=s[p];
            }
        }
    }
    for(auto p:graph[j])
    {
        if(p!=par)
        {
            if(p==v)
            {
                decompose(p,head[j],j);
            }
        }
    }
    for(auto p:graph[j])
    {
        if(p!=par)
        {
            if(p!=v)
            {
                decompose(p,p,j);
            }
        }
    }
}
ll heavylightquery(int a,int b,int n)
{
    if(height[a]>height[b]){swap(a,b);}
    ll ans=0;
    for(;head[b]!=head[a];b=parent[head[b]])
    {
        ans+=query(1,n,ind[head[b]],ind[b],1,sum);
    }
    ans+=query(1,n,ind[a],ind[b],1,sum);
    return(ans);
}
void segmentation(int l,int r,int i,vector<ll> &seg)
{
    if(l==r){seg[i]=revcost[l];return;}
    int mid=(l+r)>>1;
    segmentation(l,mid,2*i,seg);
    segmentation(mid+1,r,2*i+1,seg);
    seg[i]=(seg[2*i]+seg[2*i+1]);
}
void update(int l,int r,int ind,int i,ll tar,vector<ll> &seg)
{
    //cout<<i<<" ";
    if(l==r){seg[i]=tar;return;}
    int mid=(l+r)>>1;
    if(ind<=mid)
    update(l,mid,ind,2*i,tar,seg);
    else 
    update(mid+1,r,ind,2*i+1,tar,seg);
    seg[i]=(seg[2*i]+seg[2*i+1]);
}
ll query(int l,int r,int x,int y,int i,vector<ll> &seg)
{
    if(l==x&&r==y){return(seg[i]);}
    int mid=(l+r)>>1;
    if(y<=mid)
    return(query(l,mid,x,y,2*i,seg));
    else if(x>mid)
    return(query(1+mid,r,x,y,2*i+1,seg));
    else
    return((query(l,mid,x,mid,2*i,seg)+query(1+mid,r,mid+1,y,2*i+1,seg)));
}
int main()
{
	sizedfs(1);decompose(1,1,-1);segmentation(1,n,1,sum);
}