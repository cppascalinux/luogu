#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot;
int hd[300009],eg[600009],nxt[600009],len[600009];
int dep[300009],dist[300009];
int fx[300009][21],fm[300009][21];
int getlca(int a,int b);
struct node
{
    int u,v,lca,suml;
    void callca()
    {
        lca=getlca(u,v);
    }
    void calsuml()
    {
        suml=dist[u]+dist[v]-2*dist[lca];
    }
    bool operator < (const node &o) const
    {
        return suml>o.suml;
    }
}q[300009];
void read(int &x)
{
    rc ch=0;
    x=0;
    while(ch<'0'||ch>'9')
        ch=gc();
    while(ch>='0'&&ch<='9')
        x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b,int c)
{
    eg[++tot]=b;
    len[tot]=c;
    nxt[tot]=hd[a];
    hd[a]=tot;
}
void dfs(int x,int fa,int flen)
{
    dep[x]=dep[fa]+1;
    dist[x]=dist[fa]+flen;
    fx[x][0]=fa;
    fm[x][0]=flen;
    for(rg i=1;i<=19;i++)
    {
        fx[x][i]=fx[fx[x][i-1]][i-1];
        fm[x][i]=max(fm[x][i-1],fm[fx[x][i-1]][i-1]);
    }
    for(int i=hd[x];i;i=nxt[i])
        if(eg[i]^fa)
            dfs(eg[i],x,len[i]);
}
int getlca(int a,int b)
{
    if(dep[a]<dep[b])
        swap(a,b);
    int dl=dep[a]-dep[b];
    for(rg i=0;i<=19;i++)
        if(dl&(1<<i))
            a=fx[a][i];
    if(a==b)
        return a;
    for(rg i=19;i>=0;i--)
        if(fx[a][i]^fx[b][i])
        {
            a=fx[a][i];
            b=fx[b][i];
        }
    return fx[a][0];
}
node getpath(node x,node y)
{
    node t;
    if(x.lca==y.lca)
    {
        if(getlca(x.u,y.u)==getlca(x.v,y.v))
            swap(y.u,y.v);
        t.u=getlca(x.u,y.u);
        t.v=getlca(x.v,y.v);
        t.lca=x.lca;
        t.calsuml();
        return t;
    }
//	return (node){0,0,0,0};
    if(dep[x.lca]>dep[y.lca])
        swap(x,y);
    if(getlca(x.u,y.u)==x.lca)
        swap(x.u,x.v);
    t.u=getlca(x.u,y.u);
    t.v=getlca(x.u,y.v);
    t.lca=y.lca;
    t.calsuml();
    if(t.u!=y.lca&&t.v!=y.lca)
        return (node){0,0,0,0};
    return t;
}
int getmax(node x)
{
    int ans=0;
    int a=x.u,b=x.v;
    int l1=dep[a]-dep[x.lca],l2=dep[b]-dep[x.lca];
    for(rg i=0;i<=19;i++)
        if(l1&(1<<i))
        {
            ans=max(ans,fm[a][i]);
            a=fx[a][i];
        }
    for(rg i=0;i<=19;i++)
        if(l2&(1<<i))
        {
            ans=max(ans,fm[b][i]);
            b=fx[b][i];
        }
    return ans;
}
int solve()
{
    sort(q+1,q+m+1);
    int ans=q[1].suml;
    node t=q[1];
    for(rg i=1;i<=m;i++)
    {
        t=getpath(t,q[i]);
        if(t.u)
            ans=min(ans,max(q[1].suml-getmax(t),q[i+1].suml));
        else
            break;
    }
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("transport.in","r",stdin);
    freopen("transport.out","w",stdout);
    #endif
    read(n);
    read(m);
    int a,b,c;
    for(rg i=1;i<=n-1;i++)
    {
        read(a);
        read(b);
        read(c);
        ins(a,b,c);
        ins(b,a,c);
    }
    dfs(1,0,0);
    for(rg i=1;i<=m;i++)
    {
        read(q[i].u);
        read(q[i].v);
        q[i].callca();
        q[i].calsuml();
    }
/*	for(rg i=1;i<=m;i++)
        for(rg j=1;j<=m;j++)
        {
            node t=getpath(q[i],q[j]);
            printf("i:%d j:%d u:%d v:%d lca:%d suml:%d\n",i,j,t.u,t.v,t.lca,t.suml);
        }*/
    printf("%d",solve());
    return 0;
}