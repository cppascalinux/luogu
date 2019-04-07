#include<cstdio>
#include<algorithm>
using namespace std;
#define R register int
#define I inline void
#define lc c[x][0]
#define rc c[x][1]
#define in(z) ini=&z;\
    while(*++q<'-');\
    *ini=*q&15;\
    while(*++q>'-')*ini*=10,*ini+=*q&15//读入卡常
const int N=50001,M=200009,L=N+M;
int f[L],c[L][2],mn[L],ff[N];
unsigned short v[L];//short卡常
bool r[L],vis[M];
char str[M<<6];
struct EDGE{
    int u,v,l;
    inline bool operator<(EDGE x)const{
        return l<x.l;
    }
}e[M];
inline bool nroot(R x){return c[f[x]][0]==x||c[f[x]][1]==x;}
inline int get(R x,R y){return v[x]<v[y]?x:y;}
I pushup(R x){mn[x]=get(x,get(mn[lc],mn[rc]));}
I pushdown(R x){
    if(r[x]){
        R t=lc;
        r[lc=rc]^=1;r[rc=t]^=1;r[x]=0;
    }
}
I pushall(R x){
    if(nroot(x))pushall(f[x]);
    pushdown(x);
}
I rotate(R x){
    R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
    if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;
    f[w]=y;f[y]=x;f[x]=z;
    pushup(y);
}
I splay(R x){
    R y=x;
    pushall(x);
    while(nroot(x)){
        if(nroot(y=f[x]))
            rotate((c[y][0]==x)^(c[f[y]][0]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}
I access(R x){
    for(R y=0;x;x=f[y=x])
        splay(x),rc=y,pushup(x);
}
I mroot(R x){
    access(x);splay(x);
    r[x]^=1;
}
I link(R i){//卡常版写法
    mroot(e[i].u);
    f[f[e[i].u]=N+i]=e[i].v;
}
I cut(R x){//也是卡常版写法
    access(e[x-N].u);splay(x);
    lc=rc=f[lc]=f[rc]=0;
}
int getf(R x){//并查集卡常
    if(x==ff[x])return x;
    return ff[x]=getf(ff[x]);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("std.out","w",stdout);
    fread(str,1,sizeof(str),stdin);//fread卡常
    R n,m,i,x,y,h,cnt,ans,*ini;
    register char*q=str-1;
    in(n);in(m);
    for(i=0;i<=n;++i)
        ff[i]=i,v[i]=-1;
//-1放在unsigned里等于是极大值，注意v[0]也改了
    for(i=1;i<=m;++i){
        in(e[i].u);in(e[i].v);in(e[i].l);
    }
    sort(e+1,e+m+1);
    for(cnt=h=i=1;i<=m;++i){
        v[i+N]=e[i].l;
        if(getf(x=e[i].u)!=getf(y=e[i].v))
        {
            vis[i]=1,link(i),ff[ff[x]]=ff[y],++cnt;
            if(cnt==n)ans=e[i].l-e[h].l;
//刚完全建好生成树要马上更新答案
        }
        else{
            if(x==y)continue;
            vis[i]=1;
            mroot(x);
            access(y);splay(y);
            vis[mn[y]-N]=0;while(!vis[h])++h;//维护好最小边
            cut(mn[y]);link(i);
            if(cnt==n)ans=min(ans,e[i].l-e[h].l);
        }
    }
    printf("%d\n",ans);
    return 0;
}