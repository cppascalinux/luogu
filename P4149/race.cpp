//utf-8 luogu4149 IOI2011 Race 点分治+桶+快读
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
int n,m,tot,ans=inf,mn,rt,top;
int hd[200009],eg[400009],len[400009],nxt[400009];
int sz[200009],vis[200009];
int disx[200009],disl[200009];
int buc[1000009];
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
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int sumx,int suml)
{
	disx[++top]=sumx;
	disl[top]=suml;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
			dfs(eg[i],x,sumx+1,suml+len[i]);
}
void cal(int x)
{
	buc[0]=0;
	int lst=1;
	top=0;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			dfs(eg[i],0,1,len[i]);
			for(rg j=lst;j<=top;j++)
				if(disl[j]<=m)
					ans=min(ans,buc[m-disl[j]]+disx[j]);
			for(rg j=lst;j<=top;j++)
				if(disl[j]<=m)
					buc[disl[j]]=min(buc[disl[j]],disx[j]);
			lst=top+1;
		}
	for(rg i=1;i<=top;i++)
		if(disl[i]<=m)
			buc[disl[i]]=inf;
}
void solve(int x,int siz)
{
	vis[x]=1;
	cal(x);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			mn=inf;
			int nsiz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			getrt(eg[i],0,nsiz);
			solve(rt,nsiz);
		}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	#endif
	read(n);
	read(m);
	int a,b,c;
	for(rg i=1;i<=n-1;i++)
	{
		read(a);
		read(b);
		read(c);
		a++;
		b++;
		ins(a,b,c);
		ins(b,a,c);
	}
	memset(buc,0x7F,sizeof(buc));
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	if(ans>=inf)
		printf("-1");
	else
		printf("%d",ans);
	return 0;
}