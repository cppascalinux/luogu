#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x3F3F3F3F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char buffer[10000009],*p1,*p2;
int n,m,k,mod,tot,tot2;
int head[100009],edge[200009],len[200009],nxt[200009];
int head2[100009],edge2[200009],len2[200009],nxt2[200009];
int in[100009];
int vist[100009],dist[100009],dist2[100009];
int mn[400009],mx[400009],l[400009],r[400009];
int sq[100009],top;
int f[59][100009];
struct node
{
	int id,dis;
	node(){}
	node(int a,int b)
	{
		id=a;
		dis=b;
	}
	bool operator < (const node &o) const
	{
		return dis>o.dis;
	}
};
void clr()
{
	tot=tot2=top=0;
	memset(head,0,sizeof(head));
	memset(head2,0,sizeof(head2));
	memset(in,0,sizeof(in));
	memset(f,0,sizeof(f));
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
void ins(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	nxt[tot]=head[a];
	head[a]=tot;
}
void ins2(int a,int b,int c)
{
	edge2[++tot2]=b;
	len2[tot2]=c;
	nxt2[tot2]=head2[a];
	head2[a]=tot2;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	mn[a]=inf;
	mx[a]=ll;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void set(int a,int x,int val)
{
	if(l[a]==r[a])
	{
		mn[a]=val;
		return;
	}
	x<=r[a<<1]?set(a<<1,x,val):set(a<<1|1,x,val);
	mn[a]=min(mn[a<<1],mn[a<<1|1]);
	mx[a]=mn[a<<1]<mn[a<<1|1]?mx[a<<1]:mx[a<<1|1];
}
void dij(int s)
{
	memset(dist,0x3F,100009<<2);
	memset(vist,0,sizeof(vist));
	dist[s]=0;
	rg x,lp;
	set(1,s,0);
	while(mn[1]^inf)
	{
		x=mx[1];
		lp=mn[1];
		vist[x]=1;
		set(1,x,inf);
		for(rg i=head[x];i;i=nxt[i])
			if(!vist[edge[i]]&&dist[edge[i]]>lp+len[i])
			{
				dist[edge[i]]=lp+len[i];
				set(1,edge[i],dist[edge[i]]);
			}
	}
}
void dij2(int s)
{
	memset(dist2,0x3F,100009<<2);
	memset(vist,0,sizeof(vist));
	dist2[s]=0;
	rg x,lp;
	set(1,s,0);
	while(mn[1]^inf)
	{
		x=mx[1];
		lp=mn[1];
		vist[x]=1;
		set(1,x,inf);
		for(rg i=head2[x];i;i=nxt2[i])
			if(!vist[edge2[i]]&&dist2[edge2[i]]>lp+len2[i])
			{
				dist2[edge2[i]]=lp+len2[i];
				set(1,edge2[i],dist2[edge2[i]]);
			}
	}
}
int dp()
{
	queue<int> q;
	rg x;
	for(rg i=1;i<=n;++i)
		for(rg j=head[i];j;j=nxt[j])
			if(dist[i]+len[j]==dist[edge[j]])
				in[edge[j]]++;
	f[0][1]=1;
	for(rg i=1;i<=n;++i)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		sq[++top]=x;
		for(rg i=head[x];i;i=nxt[i])
			if(dist[x]+len[i]==dist[edge[i]])
			{
				--in[edge[i]];
				!in[edge[i]]?(q.push(edge[i]),0):0;
			}
	}
	// for(rg i=1;i<=n;++i)
	// 	printf("i:%d dist:%d f:%d sq:%d\n",i,dist[i],f[i][0],sq[i]);
	for(rg i=1;i<=n;++i)
		if(in[i]&&dist[i]+dist2[i]<=dist[n]+k)
			return -1;
	for(int l=0;l<=k;++l)
	{
		for(rg i=1;i<=n;++i)
			for(rg j=head[i];j;j=nxt[nxt[j]])
			{
				int t=dist[i]+len[j]-dist[edge[j]];
				rg p=nxt[j];
				if(t<=l&&t>=1)
				{
					// printf("in i:%d j:%d l:%d left:%d\n",i,edge[j],l,l-(dist[i]+len[j]-dist[edge[j]]));
					f[l][edge[j]]+=f[l-t][i];
					f[l][edge[j]]>=mod?f[l][edge[j]]-=mod:0;
				}
				if(p)
				{
					int tp=dist[i]+len[p]-dist[edge[p]];
					if(tp<=l&&tp>=1)
					{
						f[l][edge[p]]+=f[l-tp][i];
						f[l][edge[p]]>=mod?f[l][edge[p]]-=mod:0;
					}
				}
			}
		for(rg i=1;i<=top;++i)
			for(rg j=head[sq[i]];j;j=nxt[nxt[j]])
			{
				rg p=nxt[j];
				if(dist[sq[i]]+len[j]==dist[edge[j]])
				{
					f[l][edge[j]]+=f[l][sq[i]];
					f[l][edge[j]]>=mod?f[l][edge[j]]-=mod:0;
				}
				if(p)
					if(dist[sq[i]]+len[p]==dist[edge[p]])
					{
						f[l][edge[p]]+=f[l][sq[i]];
						f[l][edge[p]]>=mod?f[l][edge[p]]-=mod:0;
					}
			}
	}
	int sum=0;
	for(rg i=0;i<=k;++i)
	{
		sum+=f[i][n];
		sum>=mod?sum-=mod:0;
	}
	return sum;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	#endif
	int t;
	read(t);
	while(t--)
	{
		read(n);
		build(1,1,n);
		read(m);
		read(k);
		read(mod);
		int a,b,c;
		for(rg i=1;i<=m;++i)
		{
			read(a);
			read(b);
			read(c);
			ins(a,b,c);
			ins2(b,a,c);
		}
		dij(1);
		dij2(n);
		// for(rg i=1;i<=n;++i)
		// 	printf("i:%d dist:%d\n",i,dist[i]);
		printf("%d\n",dp());
		// for(rg i=1;i<=n;++i)
		// 	for(rg j=0;j<=k;++j)
		// 		printf("i:%d j:%d f:%d\n",i,j,f[i][j]);
		clr();
	}
	return 0;
}