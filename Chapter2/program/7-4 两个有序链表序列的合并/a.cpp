#include <iostream>
#include <list>

using namespace std;

int main()
{
    std::list<int> S1, S2;
    std::list<int>::iterator it1, it2;
    int v;
    while(cin>>v)
    {
        if(v==-1)
            break;
        S1.push_back(v);
    }
    while(cin>>v)
    {
        if(v==-1)
            break;
        S2.push_back(v);
    }
    bool bEmpty=true;
    for(it1=S1.begin(), it2=S2.begin(); it1!=S1.end()&&it2!=S2.end(); )
    {
        if(!bEmpty)
            cout<<" ";
        if(*it1<*it2)
        {
            cout<<*it1;
            ++it1;
        }
        else if(*it1>*it2)
        {
            cout<<*it2;
            ++it2;
        }
        else
        {
            cout<<*it1;
            cout<<" "<<*it2;
            ++it1;
            ++it2;
        }
        bEmpty = false;
    }
    while(it1!=S1.end())
    {
        if(!bEmpty)
            cout<<" ";
        cout<<*it1;
        ++it1;
        bEmpty = false;
    }
    while(it2!=S2.end())
    {
        if(!bEmpty)
            cout<<" ";
        cout<<*it2;
        ++it2;
        bEmpty = false;
    }

    if(bEmpty)
        cout<<"NULL";
    cout<<"\n";
    return 0;
}
