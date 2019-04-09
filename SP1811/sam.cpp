//2019.04.09
//luoguSP1811 LCS - Longest Common Substring
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,lst,tot;
char s[250009],t[250009];
int o[500009][27],lnk[500009],len[500009];
void ins(int c)
{
	lnk[0]=-1;
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
void solve()
{
	int p=0,mxl=0,ans=0;
	for(int i=1;i<=m;i++)
	{
		for(;p!=-1;p=lnk[p])
			if(o[p][t[i]])
			{
				mxl=min(mxl+1,len[p]+1);
				ans=max(ans,mxl);
				p=o[p][t[i]];
				break;
			}
		if(p==-1)
			p=mxl=0;
	}
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=m;i++)
		t[i]-='a'-1;
	for(int i=1;i<=n;i++)
		ins(s[i]);
	solve();
	return 0;
}