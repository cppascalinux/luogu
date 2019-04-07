#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
#define inf 0x7F7F7F7F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,tot,q,k,s,tots;
int head[400009],edge[800009],nxt[800009],l[800009];
int vist[200009],dist[200009];
int fat[400009],val[400009];
int f[400009][21],mn[400009];
struct node
{
	int id,len;
	node(){}
	node(int a,int b)
	{
		id=a;
		len=b;
	}
	bool operator < (const node &o) const
	{
		return len>o.len;
	}
};
struct edge
{
	int u,v,he;
	bool operator < (const edge &o) const
	{
		return he>o.he;
	}
}e[400009];
void clr()
{
	memset(head,0,sizeof(head));
	tot=0;
}
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x*10)+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void ins(int a,int b,int c)
{
	edge[++tot]=b;
	l[tot]=c;
	nxt[tot]=head[a];
	head[a]=tot;
}
int find(int x)
{
	if(x==fat[x])
		return x;
	return fat[x]=find(fat[x]);
}
void dij()
{
	rg x,pl;
	node t;
	priority_queue<node> pq;
	memset(vist,0,sizeof(vist));
	memset(dist,inf,sizeof(dist));
	dist[1]=0;
	pq.push(node(1,0));
	while(!pq.empty())
	{
		t=pq.top();
		pq.pop();
		if(vist[t.id])
			continue;
		x=t.id;
		pl=t.len;
		vist[x]=1;
		for(rg i=head[x];i;i=nxt[i])
			if(!vist[edge[i]]&&dist[edge[i]]>pl+l[i])
			{
				dist[edge[i]]=pl+l[i];
				pq.push(node(edge[i],dist[edge[i]]));
			}
	}
}
void init()
{
	memset(head,0,sizeof(head));
	tot=0;
	sort(e+1,e+m+1);
	int fa,fb;
	tots=n;
	memset(val+1,inf,n<<2);
	val[0]=-1;
	for(rg i=1;i<=n*2;++i)
		fat[i]=i;
	for(rg i=1;i<=m;++i)
	{
		fa=find(e[i].u);
		fb=find(e[i].v);
		if(fa^fb)
		{
			++tots;
			fat[fa]=tots;
			fat[fb]=tots;
			ins(tots,fa);
			ins(tots,fb);
			val[tots]=e[i].he;
		}
	}
}
void dfs(int x,int fa)
{
	f[x][0]=fa;
	for(rg i=1;i<=20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	if(x<=n)
		mn[x]=dist[x];
	else
		mn[x]=inf;
	for(int i=head[x];i;i=nxt[i])
	{
		dfs(edge[i],x);
		mn[x]=min(mn[x],mn[edge[i]]);
	}
}
int solve(int a,int b)
{
	for(rg i=20;i>=0;--i)
		if(val[f[a][i]]>b)
			a=f[a][i];
	return mn[a];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
	#endif
	int t;
	read(t);
	while(t--)
	{
		read(n);
		read(m);
		int a,b,c,d;
		for(rg i=1;i<=m;++i)
		{
			read(a);
			read(b);
			read(c);
			read(d);
			e[i].u=a;
			e[i].v=b;
			e[i].he=d;
			ins(a,b,c);
			ins(b,a,c);
		}
		dij();
		init();
		dfs(tots,0);
		read(q);
		read(k);
		read(s);
		int last=0;
		for(rg i=1;i<=q;++i)
		{
			read(a);
			read(b);
			a=(a+k*last-1)%n+1;
			b=(b+(ll)k*last)%(s+1);
			last=solve(a,b);
			printf("%d\n",last);
		}
		clr();
	}
	return 0;
}