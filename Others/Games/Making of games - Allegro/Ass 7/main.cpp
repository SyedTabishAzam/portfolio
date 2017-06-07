#include "list.cpp"
#include "Circular.cpp"
#include <iostream>

using namespace std;
int main()
{
    DoubleLinkedList<string> ll;
    ll.Push("Tabish");
    ll.Push("Azam");
    ll.Push("Iqbal");
    ll.DisplayFirstToLast();
    ll.DisplayLastToFirst();
    cout<<ll.Pop();


    SingleCircularList<int> cs;
    cs.Push(30);
    cs.Push(40);
    cs.Push(50);
    cs.Display();
    cout<<cs.Pop()<<endl;

    return 0;
}
