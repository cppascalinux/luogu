//2019.05.22
//luoguP4548 [CTSC2006]歌唱王国 结论题...好像是用概率生成函数推的,跑一下kmp找出所有border就行了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10000
using namespace std;
int n,m;
int mul[100009];
int s[100009],f[100009];
void init()
{
	mul[0]=1;
	int t=n%mod;
	for(int i=1;i<=100000;i++)
		mul[i]=mul[i-1]*t%mod;
}
void getf()
{
	int j=0;
	for(int i=2;i<=m;i++)
	{
		while(j&&s[i]!=s[j+1])
			j=f[j];
		j+=s[i]==s[j+1];
		f[i]=j;
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sing.in","r",stdin);
	freopen("sing.out","w",stdout);
#endif
	int t;
	scanf("%d%d",&n,&t);
	init();
	while(t--)
	{
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
			scanf("%d",s+i);
		getf();
		// for(int i=1;i<=m;i++)
		// 	printf("i:%d f:%d\n",i,f[i]);
		int ans=0;
		for(int i=m;i;i=f[i])
			ans=(ans+mul[i])%mod;
		printf("%d%d%d%d\n",ans/1000%10,ans/100%10,ans/10%10,ans%10);
	}
	return 0;
}