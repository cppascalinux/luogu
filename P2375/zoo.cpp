#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 1000000007
using namespace std;
int n;
char s[1000009];
int f[1000009],sm[1000009];
void initf()
{
	int j=0;
	sm[1]=1;
	for(int i=2;i<=n;i++)
	{
		while(j&&s[j+1]!=s[i])
			j=f[j];
		j+=s[j+1]==s[i];
		sm[i]=sm[j]+1;
		f[i]=j;
	}
//	for(int i=1;i<=n;i++)
//		printf("i:%d f:%d sm:%d\n",i,f[i],sm[i]);
}
void solve()
{
	int j=0,ans=1;
	for(int i=2;i<=n;i++)
	{
		while(j&&s[j+1]!=s[i])
			j=f[j];
		j+=s[j+1]==s[i];
		while(j>(i>>1))
			j=f[j];
	//	printf("i;%d j:%d\n",i,j);
		ans=(ll)ans*(sm[j]+1)%mod;
	}
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		initf();
		solve();
	}
	return 0;
}
