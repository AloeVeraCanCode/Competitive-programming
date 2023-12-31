ll segmented_array[40000001];vector<ll> realarray;
void segmentation(int l,int r,int cur)
{
    if(l==r){segmented_array[cur]=realarray[r];return;}
    int mid=(l+r)/2;
    segmentation( l, mid, 2*cur);segmentation( mid+1, r, 2*cur+1);
    segmented_array[cur]=max(segmented_array[2*cur],segmented_array[2*cur+1]);
}
ll query(int l,int r,int ql,int qr,int cur)
{
    int mid=(l+r)/2;
    if((l==ql)&&(r==qr))return(segmented_array[cur]);
    else if(mid>=qr)
    {
        return(query( l, mid, ql, qr, 2*cur));
    }
    else if(mid<ql)
    {
        return(query( mid+1, r,ql, qr, 2*cur+1));
    }
    else
    {
        return(max(query(l,mid,ql,mid,2*cur),query(mid+1,r,mid+1,qr,2*cur+1)));
    }
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
    seg[i]=max(seg[2*i],seg[2*i+1]);
}
