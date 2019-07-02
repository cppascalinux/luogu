//2019.07.02
//luoguP3620 好像和广州集训某一天的A题一模一样...差分之后变成选k个不相邻的城市,使得和最小,显然每多选一个城市带来的贡献是单调不降的,也就是dp数组构成一个
//下凸包,直接wqs二分+dp即可(也可以使用堆+双向链表贪心,但那个写过了就懒得再写一遍了,那个双向链表我还写两个并查集,然后删除还用了set qwq,蠢死)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define getmn(a,b) (a>b?(a=b,1):0)
using namespace std;
int n,m;
int s[100009];
li f[100009][2];
int g[100009][2];
int check(int x)
{
	for(int i=1;i<=n;i++)
		s[i]-=x;
	memset(f,0x7F,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		if(f[i-1][0]!=f[i-1][1]?f[i-1][0]<f[i-1][1]:g[i-1][0]>g[i-1][1])
			f[i][0]=f[i-1][0],g[i][0]=g[i-1][0];
		else
			f[i][0]=f[i-1][1],g[i][0]=g[i-1][1];
		f[i][1]=f[i-1][0]+s[i];
		g[i][1]=g[i-1][0]+1;
	}
	int mx=0;
	if(f[n][0]!=f[n][1]?f[n][0]<f[n][1]:g[n][0]>g[n][1])
		mx=g[n][0];
	else
		mx=g[n][1];
	for(int i=1;i<=n;i++)
		s[i]+=x;
	return mx>=m;
}
void solve()
{
	int l=-1000000000,r=1000000000;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	check(l);
	printf("%lld",min(f[n][0],f[n][1])+(li)l*m);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	n--;
	for(int i=1;i<=n;i++)
		s[i]=s[i+1]-s[i];
	solve();
	return 0;
}