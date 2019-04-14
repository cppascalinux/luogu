//2019.04.14
//luoguSP8093 JZPGYZ - Sevenk Love Oimaster ac自动机+fail树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,cnt,tot,tme;
char t[360009];
int o[360009][27],fail[360009];
int sm[360009],out[60009];
int hd[360009],eg[360009],nxt[360009];
int f[360009][19];
int dfn[360009],dep[360009];
vector<char> s[10009];
vector<int> id[360009];
pii st[100009];
void add(int x)
{
	int l=strlen(t+1);
	int p=0;
	for(int i=1;i<=l;i++)
		t[i]-='a'-1;
	for(int i=1;i<=l;i++)
	{
		if(!o[p][t[i]])
			o[p][t[i]]=++cnt;
		p=o[p][t[i]];
	}
	id[p].push_back(x);
}
void build()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(o[x][i])
			{
				if(x)
					fail[o[x][i]]=o[fail[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[fail[x]][i];
	}
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x)
{
	f[x][0]=fail[x];
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	dfn[x]=++tme;
	dep[x]=dep[fail[x]]+1;
	for(int i=hd[x];i;i=nxt[i])
		dfs1(eg[i]);
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	// printf("a:%d b:%d depa:%d depb:%d\n",a,b,dep[a],dep[b]);
	int l=dep[a]-dep[b];
	for(int i=0;i<=18;i++)
		if(l&(1<<i))
			a=f[a][i];
	if(a==b)
		return a;
	// printf("notreturn\n");
	for(int i=18;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
void solve(int x)
{
	int p=0,tp=0;
	vector<char> &q=s[x];
	for(int i=0;i<(int)q.size();i++)
	{
		p=o[p][q[i]];
		st[++tp]=pii(dfn[p],p);
		sm[p]++;
	}
	sort(st+1,st+tp+1);
	// for(int i=1;i<=tp;i++)
	// 	printf("i:%d p:%d lca:%d\n",i,st[i].se,i>1?getlca(st[i].se,st[i-1].se):0);
	for(int i=2;i<=tp;i++)
		sm[getlca(st[i].se,st[i-1].se)]--;
}
void dfs2(int x)
{
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs2(eg[i]);
		sm[x]+=sm[eg[i]];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("ac.in","r",stdin);
	freopen("ac.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",t+1);
		int l=strlen(t+1);
		for(int j=1;j<=l;j++)
			s[i].push_back(t[j]-'a'+1);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",t+1);
		add(i);
	}
	build();
	// for(int i=1;i<=cnt;i++)
	// 	printf("i:%d fail:%d\n",i,fail[i]);
	for(int i=1;i<=cnt;i++)
		ins(fail[i],i);
	dfs1(0);
	for(int i=1;i<=n;i++)
	{
		// printf("i:%d----------------------------------\n",i);
		solve(i);
		// for(int j=1;j<=cnt;j++)
		// 	printf("\tj:%d sm:%d\n",j,sm[j]);
	}
	dfs2(0);
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<(int)id[i].size();j++)
			out[id[i][j]]=sm[i];
	for(int i=1;i<=m;i++)
		printf("%d\n",out[i]);
	return 0;
}