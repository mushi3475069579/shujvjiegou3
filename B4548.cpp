#include<iostream>
#include<string>
using namespace std;
int main(){
    int N;
    cin>>N;
    string s;
    cin>>s;
    for(int i=0;i<N;++i){
        if(s[i]=='J'){
            s[i]='O';
        }else if(s[i]=='O'){
            s[i]='I';
        }else if(s[i]=='I'){
            s[i]='J';
        }
    }
    cout<<s<<endl;
    return 0;
}
