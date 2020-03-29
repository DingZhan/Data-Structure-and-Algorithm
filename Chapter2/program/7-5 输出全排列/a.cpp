#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int i, n;
    std::vector<int> d;

    cin>>n;

    d.resize(n);
    for(i=1; i<=n; ++i)
        d[i-1] = i;


    do
    {
        for(i=0; i<n; ++i)
            cout<<d[i];
        cout<<std::endl;
    }
    while(std::next_permutation(d.begin(), d.end()));

    return 0;
}
