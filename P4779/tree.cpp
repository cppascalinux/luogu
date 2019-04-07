#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define inf 0x7F7F7F7F7F7F7F7FLL
#define rg register int
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define lol long long
using namespace std;
char *p1,*p2,buffer[1000010];
int n,m,tot,s;
int head[100010],edge[200010],next[200010],len[200010];
int vist[100010];
lol dist[100010];
int l[400010],r[400010];
lol minn[4000010];
void read(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
}
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	minn[a]=inf;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void set(int a,int x,lol val)
{
	if(x<l[a]||x>r[a])
		return;
	if(l[a]==r[a])
	{
		minn[a]=val;
		return;
	}
	set(a<<1,x,val);
	set(a<<1|1,x,val);
	minn[a]=min(minn[a<<1],minn[a<<1|1]);
}
int find(int a,lol val)
{
	if(l[a]==r[a])
		return l[a];
	if(minn[a<<1]==val)
		return find(a<<1,val);
	return find(a<<1|1,val);
}
void dij()
{
	int x,num=0;
	memset(dist,0x7F,sizeof(dist));
	dist[s]=0;
	build(1,1,n);
	set(1,s,0);
	while(minn[1]^inf)
	{
		x=find(1,minn[1]);
		set(1,x,inf);
		vist[x]=1;
		for(int i=head[x];i;i=next[i])
			if(!vist[edge[i]]&&dist[edge[i]]>dist[x]+len[i])
			{
				dist[edge[i]]=dist[x]+len[i];
				set(1,edge[i],dist[edge[i]]);
			}
		if(++num>=n-1)
			break;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("heap.in","r",stdin);
	freopen("heap.out","w",stdout);
	#endif
	read(n);
	read(m);
	read(s);
	int a,b,c;
	for(rg i=1;i<=m;i++)
	{
		read(a);
		read(b);
		read(c);
		add(a,b,c);
	}
	dij();
	for(int i=1;i<=n;i++)
		printf("%lld ",dist[i]);
	return 0;
}