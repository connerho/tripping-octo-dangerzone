#include "MyQueue.h"
#include <iostream>

int main()
{
    MyQueue<int> intQueue;
    
    for(int i = 0; i < 10; ++i)
    {
        intQueue.add(i);
    }

    while(!intQueue.isEmpty())
    {
        std::cout << intQueue.peek() << std::endl;
        intQueue.remove();
    }

    return 0;
}