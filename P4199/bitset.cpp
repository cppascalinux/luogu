//2020.08.18
//luoguP4199 万径人踪灭 用manacher求出最长回文子串,再用bitset求出回文的位置个数,总时间复杂度O(n^2/64)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define LL long long
#define MOD 1000000007
#define BS bitset<100009>
using namespace std;
int n,ans;
char s0[200009];
int f[200009];
BS s,t,pn;
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(LL)a*a%MOD)
		if(b&1)
			ans=(LL)ans*a%MOD;
	return ans;
}
int solve(int k)
{
	int x=n+1-k,sm;
	if(x<0)
		sm=((~(s^(t>>-x)))&pn&(pn>>-x)).count();
	else
		sm=((~(s^(t<<x)))&pn&(pn<<x)).count();
	sm=(sm+1)>>1;
	return (qpow(2,sm)-1+MOD)%MOD;
}
void getb()
{
	for(int i=1;i<=n;i++)
		s[i]=s0[i]-'a',t[i]=s0[n-i+1]-'a',pn[i]=1;
	for(int i=2;i<=2*n;i++)
		ans=(ans+solve(i))%MOD;
}
void manacher()
{
	int mx=0,id=0;
	for(int i=n;i>=1;i--)
		s0[i*2]=s0[i],s0[i*2+1]='#';
	s0[1]='#',s0[n*2+2]='?';
	for(int i=2;i<=2*n;i++)
	{
		int &p=f[i];
		if(i<=mx)
			p=min(f[2*id-i],mx-i+1);
		while(s0[i-p]==s0[i+p])
			p++;
		if(i+p-1>mx)
			mx=i+p-1,id=i;
		ans=(ans-(p>>1)+MOD)%MOD;
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("fft.in","r",stdin);
	freopen("bitset.out","w",stdout);
#endif
	scanf("%s",s0+1);
	n=strlen(s0+1);
	getb();
	manacher();
	printf("%d",ans);
	return 0;
}