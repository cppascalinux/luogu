//2019.04.15
//luoguP5284 [十二省联考2019]字符串问题 反串sam+后缀树优化建图+拓扑排序
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,na,nb,lst=1,tot=1,sme1,sme2,smv2;
char s[200009];
int o[400009][27],lnk[400009],len[400009],pos[200009];
int la[200009],ra[200009],lb[200009],rb[200009];
pii con[200009];
int hd1[400009],eg1[400009],nxt1[400009];//suffix tree
int hd2[1200009],eg2[1400009],nxt2[1400009];//the final graph
int v2[1200009],deg2[1200009];
ll f2[1200009];//the additional information
vector<pii> v[400009];//the substrings on a node
template<class T>
void clrv(vector<T> &v)
{
	vector<T> tmp;
	tmp.swap(v);
}
void clr()
{
	for(int i=1;i<=tot;i++)
	{
		memset(o[i],0,sizeof(o[i]));
		clrv(v[i]);
	}
	memset(hd1,0,(tot+1)<<2);
	memset(hd2,0,(smv2+1)<<2);
	memset(v2,0,(smv2+1)<<2);
	memset(deg2,0,(smv2+1)<<2);
	memset(f2,0,(smv2+1)<<3);
	lst=tot=1;
	sme1=sme2=smv2=0;
}
template<class T>
void rd(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int rds(char *s)
{
	char ch=0;
	int p=0;
	while(ch<'a'||ch>'z')
		ch=gc();
	while(ch>='a'&&ch<='z')
		s[++p]=ch-'a'+1,ch=gc();
	return p;
}
void ins(int a,int b,int &tot,int *hd,int *eg,int *nxt)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void add(int id,int c)
{
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	pos[id]=cur;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void input()
{
	n=rds(s);
	// for(int i=1;i<=n;i++)
	// 	printf("%c",s[i]+'a'-1);
	// printf("\n");
	for(int i=1;i<=n>>1;i++)
		swap(s[i],s[n-i+1]);
	rd(na);
	for(int i=1,a,b;i<=na;i++)
	{
		rd(a),rd(b);
		la[i]=n-b+1;
		ra[i]=n-a+1;
	}
	rd(nb);
	for(int i=1,a,b;i<=nb;i++)
	{
		rd(a),rd(b);
		lb[i]=n-b+1;
		rb[i]=n-a+1;
	}
	rd(m);
	for(int i=1;i<=m;i++)
		rd(con[i].fi),rd(con[i].se);
}
void dfs1(int x)
{
	o[x][0]=lnk[x];
	for(int i=1;i<=18;i++)
		o[x][i]=o[o[x][i-1]][i-1];
	for(int i=hd1[x];i;i=nxt1[i])
		dfs1(eg1[i]);
}
void buildsam()
{
	for(int i=1;i<=n;i++)
		add(i,s[i]);
	for(int i=2;i<=tot;i++)
		ins(lnk[i],i,sme1,hd1,eg1,nxt1);
	dfs1(1);
}
void dbg()
{
	for(int i=1;i<=tot;i++)
		printf("i:%d lnk:%d\n",i,lnk[i]);
}
int bin(int rp,int ln)
{
	int p=pos[rp];
	// printf("rp:%d stp:%d ln:%d ",rp,p,ln);
	for(int i=18;i>=0;i--)
		if(len[o[p][i]]>=ln)
			p=o[p][i];
	// printf("edp:%d lenp:%d \n",p,len[p]);
	return p;
}
void getpos()
{
	for(int i=1;i<=na;i++)
	{
		int p=bin(ra[i],ra[i]-la[i]+1);
		v[p].push_back(pii(ra[i]-la[i]+1,i+nb));
	}
	for(int i=1;i<=nb;i++)
	{
		int p=bin(rb[i],rb[i]-lb[i]+1);
		v[p].push_back(pii(rb[i]-lb[i]+1,i));
	}
}
void build2()
{
	smv2=na+nb+tot;
	for(int i=1;i<=tot;i++)
		sort(v[i].begin(),v[i].end());
	for(int i=2;i<=tot;i++)
	{
		int q=lnk[i];
		for(int j=0;j<(int)v[i].size()-1;j++)
		{
			smv2++;
			if(v[i][j].se<=nb)
				ins(v[i][j].se,smv2,sme2,hd2,eg2,nxt2);
			else
				ins(smv2,v[i][j].se,sme2,hd2,eg2,nxt2);
			ins(q<=tot?q+na+nb:q,smv2,sme2,hd2,eg2,nxt2);
			q=smv2;
		}
		if(v[i].size())
		{
			int p=(int)v[i].size()-1;
			// printf("from:%d to:%d\n",v[i][p].se,i+na+nb);
			if(v[i][p].se<=nb)
				ins(v[i][p].se,i+na+nb,sme2,hd2,eg2,nxt2);
			else
				ins(i+na+nb,v[i][p].se,sme2,hd2,eg2,nxt2);
		}
		ins(q<=tot?q+na+nb:q,i+na+nb,sme2,hd2,eg2,nxt2);
	}
	for(int i=1;i<=m;i++)
		ins(con[i].fi+nb,con[i].se,sme2,hd2,eg2,nxt2);
	// for(int i=1;i<=smv2;i++)
	// 	for(int j=hd2[i];j;j=nxt2[j])
			// printf("i;%d eg2:%d\n",i,eg2[j]);
}
void solve()
{
	for(int i=nb+1;i<=na+nb;i++)
		v2[i]=ra[i-nb]-la[i-nb]+1;
	for(int i=1;i<=smv2;i++)
		for(int j=hd2[i];j;j=nxt2[j])
			deg2[eg2[j]]++;
	queue<int> q;
	for(int i=1;i<=smv2;i++)
		if(!deg2[i])
			q.push(i);
	ll ans=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		f2[x]+=v2[x];
		ans=max(ans,f2[x]);
		for(int i=hd2[x];i;i=nxt2[i])
		{
			f2[eg2[i]]=max(f2[eg2[i]],f2[x]);
			if(!--deg2[eg2[i]])
				q.push(eg2[i]);
		}
	}
	for(int i=1;i<=smv2;i++)
		if(deg2[i])
		{
			printf("-1\n");
			return;
		}
	printf("%lld\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	int t;
	rd(t);
	while(t--)
	{
		input();
		buildsam();
		// dbg();
		getpos();
		build2();
		solve();
		clr();
	}
	return 0;
}