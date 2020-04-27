

struct ListNode
{
  int val;
  ListNode* next;

  ListNode(int x) : val(x), next(nullptr) {}
};


class MyLinkedList
{
public:

  MyLinkedList() : head(nullptr) {}
  ~MyLinkedList()
  {
    while(head)
    {
      ListNode* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void insertAtFront(int x)
  {
    ListNode* newNode = new ListNode(x);
    newNode->next = head;
    head = newNode;
  }

private:

  ListNode* head;

};