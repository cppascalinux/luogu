//2019.04.14
//luoguP5284 [十二省联考2019]字符串问题 反向sam+后缀树+拓扑排序+拆点
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,na,nb,cnt=1,lst=1;
char s[200009];
int o[400009][19],lnk[400009],len[400009];
void add(int c)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
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
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cur;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1;i<=n;i++)
			add(s[i]=s[i]-'a'+1);
		
	}
	return 0;
}