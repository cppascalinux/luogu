//2019.04.12
//luoguP3649 [APIO2014]回文串 后缀自动机+倍增+manacher
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n,lst=1,cnt=1,tot;
ll ans;
char s[300009],ps[600009];
int o[600009][27],lnk[600009],len[600009],sz[600009],pos[300009];
int hd[600009],eg[600009],nxt[600009];
int ext[600009];
void add(int sp,int c)
{
	int cur=++cnt,p;
	pos[sp]=cur;
	len[cur]=len[lst]+1;
	sz[cur]=1;
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
			int cln=++cnt;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x)
{
	o[x][0]=lnk[x];
	for(int i=1;i<=20;i++)
		o[x][i]=o[o[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs(eg[i]);
		sz[x]+=sz[eg[i]];
	}
}
void solve(int rp,int l)
{
	if(!l)
		return;
	int p=pos[rp];
	for(int i=20;i>=0;i--)
		if(len[o[p][i]]>=l)
			p=o[p][i];
	ans=max(ans,(ll)sz[p]*l);
}
void manacher()
{
	ps[1]='#';
	for(int i=1;i<=n;i++)
	{
		ps[2*i]=s[i];
		ps[2*i+1]='#';
	}
	ps[2*n+2]='@';
	int mx=0,id=0;
	for(int i=2;i<=2*n;i++)
	{
		int &p=ext[i];
		if(i<mx)
			p=min(ext[2*id-i],mx-i);
		while(ps[i+p]==ps[i-p])
		{
			p++;
			if(i+p>mx&&ps[i+p-1]=='#')
			{
				mx=i+p;
				id=i;
				int rp=(i+p-1)/2;
				int l=p-1;
				// if(l)
					// printf("rp:%d l:%d\n",rp,l);
				solve(rp,l);
			}
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
//	char *p=(char*)malloc(256<<20)+(256<<20);
//	__asm__("mov %0,%%esp"::"r"(p));
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	// printf("n:%d\n",n);
	// fflush(stdout);
	for(int i=1;i<=n;i++)
		add(i,s[i]-'a'+1);
	for(int i=2;i<=cnt;i++)
		ins(lnk[i],i);
	memset(o,0,sizeof(o));
	dfs(1);
	manacher();
	// for(int i=2;i<=2*n;i++)
	// 	printf("%d\n",ext[i]-1);
	printf("%lld",ans);
	return 0;
}
