#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

struct Info
{
    string s;
    int numOpen;
    int numClosed;
};
    
vector<string> generateParenthesis(int n)
{
    bool done = false;
    vector<string> result;
    
    if(n == 0) return result;
    
    stack<Info> onestack, twostack;
    Info first;
    first.s = "(";
    first.numOpen = 1;
    first.numClosed = 0;
    onestack.push(first);
    stack<Info>* currStack = &onestack;
    stack<Info>* otherStack = &twostack;
    
    while(!done)
    {
        while(!currStack->empty())
        {
            Info info = currStack->top();
            currStack->pop();
            
            if(info.numOpen < n)
            {
                Info otherInfo;
                otherInfo.s = info.s + "(";
                otherInfo.numOpen = info.numOpen + 1;
                otherInfo.numClosed = info.numClosed;
                otherStack->push(otherInfo);
            }
            if(info.numOpen > info.numClosed)
            {
                Info otherInfo;
                otherInfo.s = info.s + ")";
                otherInfo.numOpen = info.numOpen;
                otherInfo.numClosed = info.numClosed + 1;
                otherStack->push(otherInfo);
            }
        }
        
        stack<Info>* temp = currStack;
        currStack = otherStack;
        otherStack = temp;
        
        if(currStack->top().numOpen == n && currStack->top().numClosed == n) break;
    }
    
    while(!currStack->empty())
    {
        result.push_back(currStack->top().s);
        currStack->pop();
    }
    
    return result;
}

int main()
{
  int n = 0;
  bool keep_going = true;

  while(keep_going)
  {
    cout << "How many Parenthesis?" << endl;
    cin >> n;

    if(n == 0) break;
    
    vector<string> results = generateParenthesis(n);

    for(int i = 0; i < results.size(); ++i)
    {
        cout << results[i] << endl;
    }

    cout << results.size() << endl;
  }

  return 0;
}