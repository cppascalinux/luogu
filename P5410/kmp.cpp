//2020.07.21
//luoguP5410 【模板】扩展 KMP（Z 函数）拓展kmp..在O(n)时间内求出s与他的每一个后缀的lcp..和manacher和kmp都挺像的...
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
int n,m;
char s1[20000009],s2[20000009];
int f[20000009];
void getf(char *s)
{
	int mx=0,md=0;
	LL ans=m+1;
	for(int i=2;i<=m;i++)
	{
		int &p=f[i];
		if(i<=mx)
			p=min(mx-i+1,f[i-md+1]);
		while(s[1+p]==s[i+p])
			p++;
		if(i+p-1>mx)
			mx=i+p-1,md=i;
		ans^=(LL)i*(p+1);
		// printf("i:%d f:%d\n",i,p);
	}
	printf("%lld\n",ans);
}
void match(char *s,char *t)
{
	int mx=0,md=0;
	LL ans=0;
	s[n+1]='?';
	for(int i=1;i<=n;i++)
	{
		int p=0;
		if(i<=mx)
			p=min(mx-i+1,f[i-md+1]);
		while(t[1+p]==s[i+p])
			p++;
		if(i+p-1>mx)
			mx=i+p-1,md=i;
		ans^=(LL)i*(p+1);
		// printf("i:%d g:%d\n",i,p);
	}
	printf("%lld",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("kmp.in","r",stdin);
	freopen("kmp.out","w",stdout);
#endif
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1),m=strlen(s2+1);
	getf(s2);
	match(s1,s2);
	return 0;
}