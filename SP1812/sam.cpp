//2019.04.09
//luoguSP1812 LCS2 - Longest Common Substring II 后缀自动机
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int m,n[11],lst,tot;
char s[11][100009];
int o[200009][27],len[200009],lnk[200009],deg[200009];
int st[200009];
int mx[11][200009];
void ins(int c)
{
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	for(p=lst;p!=-1&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(p!=-1)
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
			for(;p!=-1&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void dfs(int p,int c,int l,int mxl)
{
	mx[c][p]=max(mx[c][p],mxl);
	// printf("l:%d p:%d mxl:%d\n",l,p,mxl);
	if(l>n[c])
		return;
	int ch=s[c][l];
	for(;p!=-1;p=lnk[p])
		if(o[p][ch])
		{
			dfs(o[p][ch],c,l+1,min(mxl+1,len[p]+1));
			return;
		}
	dfs(0,c,l+1,0);
}
void init()
{
	for(int i=1;i<=tot;i++)
		deg[lnk[i]]++;
	queue<int> q;
	for(int i=1;i<=tot;i++)
		if(!deg[i])
			q.push(i);
	int tp=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		st[++tp]=x;
		if(!--deg[lnk[x]])
			q.push(lnk[x]);
	}
	// for(int i=1;i<=tot+1;i++)
	// 	printf("i:%d st:%d\n",i,st[i]);
}
void dbg()
{
	for(int i=0;i<=tot;i++)
		printf("i:%d len:%d lnk:%d mx2:%d mx3:%d oa:%d ob:%d\n",i,len[i],lnk[i],mx[2][i],mx[3][i],o[i][1],o[i][2]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	while(scanf("%s",s[m+1]+1)!=EOF)
	{
		m++;
		n[m]=strlen(s[m]+1);
		for(int i=1;i<=n[m];i++)
			s[m][i]-='a'-1;
	}
	// printf("m;%d\n",m);
	// fflush(stdout);
	lnk[0]=-1;
	for(int i=1;i<=n[1];i++)
		ins(s[1][i]);
	init();
	for(int i=2;i<=m;i++)
		dfs(0,i,1,0);
	// dbg();
	// for(int i=2;i<=m;i++)
	// 	for(int j=1;j<=tot+1;j++)
	// 		mx[i][lnk[st[j]]]=max(mx[i][lnk[st[j]]],min(mx[i][st[j]],len[lnk[st[j]]]));
	for(int i=2;i<=m;i++)
		for(int j=1;j<=tot+1;j++)
			if(mx[i][st[j]])
				mx[i][lnk[st[j]]]=len[lnk[st[j]]];
	for(int i=3;i<=m;i++)
		for(int j=1;j<=tot;j++)
			mx[2][j]=min(mx[2][j],mx[i][j]);
	int ans=0;
	for(int i=1;i<=tot;i++)
		ans=max(ans,mx[2][i]);
	if(m==1)
		ans=n[1];
	printf("%d",ans);
	return 0;
}