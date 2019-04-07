#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define inf 0x7F7F7F7F7F7F7F7FLL;
#define ll long long
using namespace std;
char *p1,*p2,buffer[1000000];
int n,m,tot,s;
int head[100010],edge[200010],next[200010],len[200010];
ll dist[100010];
int vist[100010];
int h[200010],pos[100010],top;
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
void read(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
}
void up(int now)
{
	while(now>1&&dist[h[now]]<dist[h[now>>1]])
	{
		swap(pos[h[now]],pos[h[now>>1]]);
		swap(h[now],h[now>>1]);
		now>>=1;
	}
}
void down(int now)
{
	int t;
	while(min(dist[h[now<<1]],dist[h[now<<1|1]])<dist[h[now]])
	{
		t=dist[h[now<<1]]<=dist[h[now<<1|1]]?now<<1:now<<1|1;
		swap(pos[h[now]],pos[h[t]]);
		swap(h[now],h[t]);
		now=t;
	}
}
void add(int x)
{
	h[++top]=x;
	pos[x]=top;
	up(pos[x]);
}
void del(int x)
{
	if(pos[x]==0||top==0)
		return;
	if(top==1)
	{
		h[top--]=0;
		return;
	}
	int now=pos[x];
	swap(pos[x],pos[h[top]]);
	swap(h[now],h[top]);
	h[top--]=0;
	down(now);
	up(now);
}
void dij(int s)
{
	memset(dist,0x7F,sizeof(dist));
	dist[s]=0;
	add(s);
	int x;
	while(top)
	{
		x=h[1];
		del(x);
		vist[x]=1;
		for(int i=head[x];i;i=next[i])
			if(!vist[edge[i]]&&dist[edge[i]]>dist[x]+len[i])
			{
				dist[edge[i]]=dist[x]+len[i];
				del(edge[i]);
				add(edge[i]);
			}
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
	int x,y,z;
	for(int i=1;i<=m;i++)
	{
		read(x);
		read(y);
		read(z);
		add(x,y,z);
	}
	dij(s);
	for(int i=1;i<=n;i++)
		printf("%lld ",dist[i]);
	return 0;
}