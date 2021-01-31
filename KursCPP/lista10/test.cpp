#include <iostream>

using namespace std;

int main()
{
    string x;
    while(cin.peek()!=EOF)
    {
        cin>>x;
        cout<<x<<endl;
    }
    return 0;
}