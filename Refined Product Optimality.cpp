#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#include<climits>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<queue>
#include<deque>
#define ll long long int
using namespace std;
ll mod=998244353;
const int N = 2e5+5;


ll binpow(ll a, ll b, ll &m) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = ((res%m) * (a%m)) % m;
        a = ((a%m) * (a%m)) % m;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll &m) {
    return binpow(a, m-2, m);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--){
        ll n,q;
        cin>>n>>q;
        vector<ll>a(n);
        vector<ll>b(n);
        map<ll,deque<ll> >ia;
        map<ll,deque<ll> >ib;
        ll ma[n], mb[n];  
        ll aa[n],bb[n];

        vector<pair<ll,ll> >va;
        vector<pair<ll,ll> >vb;
        for(int i=0;i<n;i++){
            cin>>a[i];
            va.push_back(make_pair(a[i],i+1));
        }
        for(int i=0;i<n;i++){
            cin>>b[i];
            vb.push_back(make_pair(b[i],i+1));
        }

        ll p=1;
        
        

        sort(va.begin(),va.end());
        sort(vb.begin(),vb.end());

       

        for(int i=0;i<n;i++){
            p=((p%mod)*((min(va[i].first,vb[i].first))%mod))%mod;
            ia[va[i].first].push_back(va[i].second);
            ib[vb[i].first].push_back(vb[i].second);

            aa[va[i].second]=i;

            bb[vb[i].second]=i;

            if(va[i].first<vb[i].first){
                ma[va[i].second]=-1;
                mb[vb[i].second]=1;
            }
            else if(va[i].first>vb[i].first){
                ma[va[i].second]=1;
                mb[vb[i].second]=-1;
            }
            else{
                ma[va[i].second]=0;
                mb[vb[i].second]=0;
            }
        }

        cout<<p<<" ";

        while(q--){
            ll o,x;
            cin>>o>>x;
            x--;
            
            if(o==1){
                ll num=a[x];
                a[x]++;
                
                ll ind=ia[num].back();
                ll ind2=aa[ind];
                ll bind=vb[ind2].second;

                if(ma[ind]==1){
                    //no change in answer
                }
                else if(ma[ind]==-1){
                    p = (p * modinv(num, mod)) % mod;
                    p=(p%(mod)*(num+1)%(mod))%mod;
                   
                    if(num+1==vb[ind2].first){
                        ma[ind]=0;
                        mb[bind]=0;
                    }
                }
                else{
                    ma[ind]=1;
                    mb[bind]=-1;
                }
                
                ia[num].pop_back();
                ia[num+1].push_front(ind);
               
                va[ind2].first=num+1;
            }
            else {
                ll num=b[x];
                b[x]++;
                ll ind=ib[num].back();
                ll ind2=bb[ind];
                ll aind=va[ind2].second;

                if(mb[ind]==1){
                    //no change in answer
                }
                else if(mb[ind]==-1){
                    p = (p * modinv(num, mod)) % mod;
                    p=(p%(mod)*(num+1)%(mod))%mod;
                    if(num+1==va[ind2].first){
                        mb[ind]=0;
                        ma[aind]=0;
                    }
                }
                else{
                    mb[ind]=1;
                    ma[aind]=-1;
                }
                
                ib[num].pop_back();
                ib[num+1].push_front(ind);
              
                vb[ind2].first=num+1;
            }
            
            cout<<p<<" ";
        }
        cout<<endl;
    }
    return 0;
}