
#ifndef MY_QUEUE
#define MY_QUEUE

#include <stack>

template<class T>
class MyQueue
{
public:
    MyQueue() {}
    virtual ~MyQueue() {}

    void add(T item)
    {
        firstStack.push(item);
    }

    T remove()
    {
        T return_val;

        // Pop the first stack onto the second stack
        while(!firstStack.empty())
        {
            secondStack.push(firstStack.top());
            firstStack.pop();
        }

        return_val = secondStack.top();
        secondStack.pop();

        // Put everything back onto the first stack
        while(!secondStack.empty())
        {
            firstStack.push(secondStack.top());
            secondStack.pop();
        }

        return return_val;
    }

    T peek()
    {
        T return_val;

        // Pop the first stack onto the second stack
        while(!firstStack.empty())
        {
            secondStack.push(firstStack.top());
            firstStack.pop();
        }

        return_val = secondStack.top();

        // Put everything back onto the first stack
        while(!secondStack.empty())
        {
            firstStack.push(secondStack.top());
            secondStack.pop();
        }

        return return_val;
    }

    inline bool isEmpty() { return firstStack.empty() && secondStack.empty(); }

private:
    std::stack<T> firstStack;
    std::stack<T> secondStack;
};

#endif // MY_QUEUE