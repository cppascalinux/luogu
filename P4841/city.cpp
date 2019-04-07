#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1004535809
#define ll long long
using namespace std;
int n,len;
int iv[1050000];
int rt[2][1050000],mp[1050000];
int f[1050000],g[1050000],tf[1050000];
int mul[1050000],inm[1050000];
void initc()
{
	iv[1]=1;
	for(int i=2;i<1050000;i++)
		iv[i]=(ll)(mod-mod/i)*iv[mod%i]%mod;
	mul[0]=inm[0]=1;
	for(int i=1;i<1050000;i++)
	{
		mul[i]=(ll)mul[i-1]*i%mod;
		inm[i]=(ll)inm[i-1]*iv[i]%mod;
	}
}
int qpow(int a,ll b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void init(int bit)
{
	len=1<<bit;
	for(int i=0;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,479*(1<<(21-bit)));
	for(int i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
}
void fft(int *s,int c)
{
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1,sp=len/l;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)rt[c][sp*i]*s[i+j+d]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*iv[len]%mod;
}
void getinv(int *f,int *g,int l)
{
	g[0]=qpow(f[0],mod-2);
	for(int i=1;(1<<i)<2*l;i++)
	{
		// printf("i:%d\n",i);
		init(i+1);
		memcpy(tf,f,len<<1);
		fft(tf,0);
		fft(g,0);
		for(int j=0;j<len;j++)
			g[j]=g[j]*(2-(ll)g[j]*tf[j]%mod+mod)%mod;
		fft(g,1);
		for(int j=len>>1;j<len;j++)
			g[j]=0;
		// for(int j=0;j<len;j++)
		// 	printf("j:%d g:%d\n",j,g[j]);
	}
	for(int i=l;i<len;i++)
		g[i]=0;
}
void dif(int *s,int l)
{
	for(int i=0;i<l-1;i++)
		s[i]=(ll)s[i+1]*(i+1)%mod;
	s[l-1]=0;
}
void ing(int *s,int l)
{
	for(int i=l-1;i>0;i--)
		s[i]=(ll)s[i-1]*iv[i]%mod;
	s[0]=0;
}
void getln(int *f,int *g,int l)
{
	getinv(f,g,l);
	dif(f,l);
	// for(int i=0;i<l*2;i++)
	// 	printf("i:%d f:%d g:%d\n",i,f[i],g[i]);
	int bit=0;
	while(1<<bit<2*l)
		bit++;
	init(bit);
	fft(f,0);
	fft(g,0);
	for(int i=0;i<len;i++)
		g[i]=(ll)g[i]*f[i]%mod;
	fft(g,1);
	ing(g,l);
	// for(int i=0;i<len;i++)
	// 	printf("i:%d g:%d\n",i,g[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
#endif
	initc();
	scanf("%d",&n);
	n++;
	f[0]=1;
	for(int i=1;i<n;i++)	
		f[i]=(ll)qpow(2,(ll)i*(i-1)/2)*inm[i]%mod;
	getln(f,g,n);
	printf("%lld",(ll)g[n-1]*mul[n-1]%mod);
	return 0;
}