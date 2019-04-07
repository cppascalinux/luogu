#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,totq;
int head[300009],edge[600009],nxt[600009];
int stq[300009],numq[600009],idq[600009],nxtq[600009];
int f[300009],vist[300009];
int w[300009],dep[300009];
int buc1[600009],buck[600009];
int *buc2=buck+300005;
int ans[300009];
struct node
{
    int s,t,lca;
}q[300009];
struct query
{
    int typ,x,val;
    query(){}
    query(int a,int b,int c)
    {
        typ=a;
        x=b;
        val=c;
    }
};
vector<query> v[300009];
void read(int &x)
{
    rc ch=0;
    x=0;
    while(ch<'0'||ch>'9')
        ch=gc();
    while(ch>='0'&&ch<='9')
        x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
    edge[++tot]=b;
    nxt[tot]=head[a];
    head[a]=tot;
}
void addq(int a,int b,int c)
{
    numq[++totq]=b;
    idq[totq]=c;
    nxtq[totq]=stq[a];
    stq[a]=totq;
}
int find(int x)
{
    if(x==f[x])	
        return x;
    return f[x]=find(f[x]);
}
void dfs1(int x,int fa)
{
    dep[x]=dep[fa]+1;
    for(int i=head[x];i;i=nxt[i])
        if(edge[i]^fa)
            dfs1(edge[i],x);
    for(rg i=stq[x];i;i=nxtq[i])
    {
        if(vist[idq[i]])
            q[idq[i]].lca=find(numq[i]);
        vist[idq[i]]=1;
    }
    f[find(x)]=find(fa);
}
void init()
{
    for(rg i=1;i<=m;i++)
    {
        v[q[i].s].push_back(query(0,dep[q[i].s],1));
        v[q[i].lca].push_back(query(0,dep[q[i].s],-1));
        v[q[i].t].push_back(query(1,dep[q[i].s]-2*dep[q[i].lca],1));
        v[q[i].lca].push_back(query(1,dep[q[i].s]-2*dep[q[i].lca],-1));
    }
}
void dfs2(int x,int fa)
{
    int sub=buc1[w[x]+dep[x]]+buc2[w[x]-dep[x]];
    for(int i=head[x];i;i=nxt[i])
        if(edge[i]^fa)
            dfs2(edge[i],x);
    for(rg i=0;i<v[x].size();i++)
    {
        query t=v[x][i];
        if(t.val==1)
        {
            if(t.typ==0)
                buc1[t.x]++;
            else
                buc2[t.x]++;
        }
    }
    for(rg i=0;i<v[x].size();i++)
    {
        query t=v[x][i];
        if(t.val==-1)
        {
            if(t.typ==0&&t.x==w[x]+dep[x])
                sub++;
        //	else if(t.typ==1&&t.x==w[x]-dep[x])
        //		sub++;
        }
    }
    ans[x]=buc1[w[x]+dep[x]]+buc2[w[x]-dep[x]]-sub;
    for(rg i=0;i<v[x].size();i++)
    {
        query t=v[x][i];
        if(t.val==-1)
        {
            if(t.typ==0)
                buc1[t.x]--;
            else
                buc2[t.x]--;
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("running.in","r",stdin);
    freopen("running.out","w",stdout);
    #endif
    read(n);
    read(m);
    int a,b;
    for(rg i=1;i<=n-1;i++)
    {
        read(a);
        read(b);
        ins(a,b);
        ins(b,a);
    }
    for(rg i=1;i<=n;i++)
    {
        f[i]=i;
        read(w[i]);
    }
    for(rg i=1;i<=m;i++)
    {
        read(q[i].s);
        read(q[i].t);
        addq(q[i].s,q[i].t,i);
        addq(q[i].t,q[i].s,i);
    }
    dfs1(1,0);
    init();
    dfs2(1,0);
    for(rg i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}