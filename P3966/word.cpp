#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int N=1e6+5;
const int M=2e5+5;
int f[N],ch[N][26];
int pos[M],NodeCnt,tot,qwq[N],ans[N],n;
char s[N];

struct ACcept_ACcidently_AUtomaton{
    inline void insert(int &cur){
        int len=strlen(s),u=0;
        for(int i=0;i<len;i++){
            int t=s[i]-'a';
            if(!ch[u][t])ch[u][t]=++NodeCnt;
            u=ch[u][t];
            ans[u]++;
        }
        cur=u;
    }   
    inline void build_fail(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int u=q.front(),k=f[u];q.pop();
            qwq[++tot]=u;
            for(int i=0;i<26;i++){
                int v=ch[u][i];
                if(!v){ch[u][i]=ch[k][i];continue;}
                f[v]=u?ch[k][i]:0;
                q.push(v);
            }
        }
    }
    inline void query(){
        for(int i=tot;i>=1;i--)
            ans[f[qwq[i]]]+=ans[qwq[i]];
    }
}AC;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        AC.insert(pos[i]);
    }
    AC.build_fail();
    AC.query();
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[pos[i]]);
    return 0;
}