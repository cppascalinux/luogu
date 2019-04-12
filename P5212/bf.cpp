//2019.04.09
//luoguP5212 SubString sam+lct维护parent树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
using namespace std;
int n,q,tot,lst;
char s[3000009],typ[10];
int o[1200009][3],lnk[1200009],len[1200009],cnt[1200009];
void add(int c)
{
	// printf("c:%d\n",c);
	// fflush(stdout);
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
			cnt[cln]=cnt[q];
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],3<<2);
			for(;p!=-1&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=cln;
			lnk[q]=cln;
		}
	}
	lst=cur;
	for(p=cur;p!=-1;p=lnk[p])
		cnt[p]++;
}
int solve()
{
	int p=0;
	for(int i=0;i<n;i++)
		s[i]-='A'-1;
	for(int i=0;i<n;i++)
		if(!o[p][s[i]])
			return 0;
		else
			p=o[p][s[i]];
	// printf("rua!");
	return cnt[p];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("lct.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d",&q);
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++)
		add(s[i]-'A'+1);
	int msk=0;
	while(q--)
	{
		// printf("q:%d\n",q);
		scanf("%s%s",typ,s);
		n=strlen(s);
		int tsk=msk;
		for(int i=0;i<n;i++)
		{
			tsk=(tsk*131LL+i)%n;
			swap(s[i],s[tsk]);
		}
		if(typ[0]=='A')
			for(int i=0;i<n;i++)
				add(s[i]-'A'+1);
		else
		{
			int ans=solve();
			msk^=ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}