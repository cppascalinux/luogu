//2020.08.18
//luoguP4199 万径人踪灭 用manacher求出最长回文子串,再用FFT暴力匹配回文位置,总时间复杂度O(nlogn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define LL long long
#define MOD 1000000007
#define BS bitset<100009>
#define DB double
#define PI 3.14159265358979323846
using namespace std;
struct cp
{
	DB x,y;
	cp operator+(const cp &p)const{return cp{x+p.x,y+p.y};}
	cp operator-(const cp &p)const{return cp{x-p.x,y-p.y};}
	cp operator*(const cp &p)const{return cp{x*p.x-y*p.y,x*p.y+y*p.x};}
	cp operator/=(const DB &v){return cp{x/=v,y/=v};}
};
int n,ans,ftn,ftm;
char s0[200009];
int f[200009];
int mp[270009];
cp rt[2][270009],sp[270009];
int sm[200009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(LL)a*a%MOD)
		if(b&1)
			ans=(LL)ans*a%MOD;
	return ans;
}
void init(int l)
{
	while((1<<ftm)<l)
		ftm++;
	ftn=1<<ftm;
	rt[0][0]=rt[1][0]=cp{1,0};
	for(int i=1;i<ftn;i++)
		rt[1][ftn-i]=rt[0][i]=cp{cos(2*PI*i/ftn),sin(2*PI*i/ftn)};
	for(int i=0;i<ftn;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(ftm-1));
}
void fft(cp *s,int typ)
{
	for(int i=0;i<ftn;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=ftn;l<<=1)
	{
		int p=l>>1;
		for(int j=0;j<ftn;j+=l)
			for(int i=0;i<p;i++)
			{
				cp t=rt[typ][ftn/l*i]*s[i+j+p];
				s[i+j+p]=s[i+j]-t;
				s[i+j]=s[i+j]+t;
			}
	}
	if(typ)
		for(int i=0;i<ftn;i++)
			s[i]/=ftn;
}
void geta()
{
	for(int i=0;i<=n;i++)
		sp[i]=s0[i]=='a'?cp{1,0}:cp{0,0};
	init(2*n+1);
	fft(sp,0);
	for(int i=0;i<ftn;i++)
		sp[i]=sp[i]*sp[i];
	fft(sp,1);
	for(int i=2;i<=2*n;i++)
		sm[i]+=(int)(sp[i].x+0.5);
}
void getb()
{
	memset(sp,0,sizeof(sp));
	for(int i=0;i<=n;i++)
		sp[i]=s0[i]=='b'?cp{1,0}:cp{0,0};
	init(2*n+1);
	fft(sp,0);
	for(int i=0;i<ftn;i++)
		sp[i]=sp[i]*sp[i];
	fft(sp,1);
	for(int i=2;i<=2*n;i++)
		sm[i]+=(int)(sp[i].x+0.5);
}
void getans()
{
	for(int i=2;i<=2*n;i++)
	{
		// printf("i:%d sm:%d\n",i,sm[i]);
		int ts=(qpow(2,(sm[i]+1)>>1)+MOD-1)%MOD;
		ans=(ans+ts)%MOD;
	}
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
	freopen("fft.out","w",stdout);
#endif
	scanf("%s",s0+1);
	n=strlen(s0+1);
	geta();
	getb();
	getans();
	manacher();
	printf("%d",ans);
	return 0;
}