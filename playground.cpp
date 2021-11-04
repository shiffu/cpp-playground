#include "playground.h"

#include <chrono>
#include <string>
#include <list>
#include <bitset>

using namespace std;

struct Test
{
    Test() { cout << "Test::Test()\n"; }
    Test(const string& name)
        : name(name) { cout << "Test::Test(const string&)\n"; }
    ~Test() { cout << "Test::~Test(), name: " << name << endl; }

    Test(const Test& other)
        : name(other.name) { cout << "Test Copy ctor\n"; }
    Test(Test&& other)
        : name(move(other.name)) { cout << "Test Move ctor\n"; }

    Test& operator=(const Test& other) {
        cout << "Test Copy assignment\n";
        name = other.name;
        
        return *this;
    }
    
    Test& operator=(Test&& other) {
        cout << "Test Move assignment\n";
        name = move(other.name);
    
        return *this;
    }

    string name{};
};

void dynArrayTest()
{
    cout << " + Dynamic Array\n";
    DynArray<float> a;

    a.add(3.0f);
    a.add(4.0f);
    a.add(5.0f);
    cout << a << endl;

    a.clear();
    cout << a << endl;
    cout << "Size: " << a.size() << endl;
    cout << "Capacity: " << a.capacity() << endl;

    a.add(8.0f);
    a.add(15.0f);
    a.add(3.0f);
    cout << a << endl;
    a.add(4.0f);
    a.add(5.0f);
    cout << "a[2]: " << a[2] << endl;
    
    DynArray<Test> b{};
    string s1("String1");
    b.add(s1);
    b.add(Test("cstr2"));
    b.add(Test("cstr3"));

    cout << "for each\n";
    for (auto& v : b)
    {
        cout << "v: " << v.name << endl;
    }
}

void stackTest()
{
    cout << " + Stack\n";
    Stack<int> s{};
    s.push(2);
    s.push(5);
    s.push(7);

    cout << s << endl;

    cout << "Peek:" << s.peek() << endl;
    cout << "Pop:" << s.pop() << endl;
    cout << "Peek:" << s.peek() << endl;

    cout << s << endl;
    cout << "Size: " << s.size() << endl;
    s.push(17);
    cout << s << endl;
    cout << "Size: " << s.size() << endl;
    cout << "Pop:" << s.pop() << endl;
    cout << "Pop:" << s.pop() << endl;
    cout << "Pop:" << s.pop() << endl;
    cout << "Pop:" << s.pop() << endl;
}

void queueTest()
{
    cout << " + Queue\n";
    Queue<string> q;

    q.insert("str1");
    q.insert("str2");

    cout << q << endl;

    cout << q.dequeue().value_or("NONE") << endl;
    cout << "Size: " << q.size() << endl;
    cout << q.dequeue().value_or("NONE") << endl;
    cout << q.dequeue().value_or("NONE") << endl;

    q.insert("str3");
    cout << q << endl;
}

void linkedListTest()
{
    SLinkedList<string> l;
    
    l.push_back("s1");
    l.push_back("s2");
    l.push_back("s3");

    cout << "front: " << l.front() << endl;
    cout << "back: " << l.back() << endl;
    cout << "size: " << l.size() << endl;
    cout << "isEmpty: " << l.empty() << endl;

    cout << "for each loop\n";
    for (auto& val : l)
    {
        cout << val << endl;
    }
    
    cout << "remove s3\n";
    l.remove("s3");
    cout << "for loop with iterator\n";
    for (auto it = l.begin(); it != l.end(); it++)
    {
        cout << *it << endl;
    }
    cout << "back: " << l.back() << endl;

    l.push_front("s4");
    cout << "front: " << l.front() << endl;
    for (auto& val : l)
    {
        cout << val << endl;
    }
    cout << "pop_front: " << l.pop_front() << endl;
    for (auto& val : l)
    {
        cout << val << endl;
    }

    l.clear();
    cout << "size after clear: " << l.size() << endl;
    for (auto& val : l)
    {
        cout << val << endl;
    }
}

void testInplaceReverseLinkedList()
{
    SLinkedList<string> l;
    
    l.push_back("s1");
    l.push_back("s4");
    l.push_back("s5");

    cout << "Before reverse (inplace):\n";
    for (auto& val : l)
    {
        cout << val << endl;
    }

    l.reverse();

    cout << "After reverse (inplace):\n";
    for (auto& val : l)
    {
        cout << val << endl;
    }
}

void testBTree()
{
    BSTree<int> t;

    t.insert(5);
    t.insert(2);
    t.insert(7);
    t.insert(1);
    t.insert(3);

    cout << "preorder traversal\n";
    t.preorder();
    
    cout << "inorder traversal\n";
    t.inorder();
    
    cout << "postorder traversal\n";
    t.postorder();
    
    {
        cout << "find node 3\n";
        auto nodeFound = t.find(3);
        if (nodeFound)
            cout << "Found node: " << nodeFound->value << endl;
        else
            cout << "Node not found" << endl;
    }
    
    {
        cout << "find node 4\n";
        auto nodeFound = t.find(4);
        if (nodeFound)
            cout << "Found node: " << nodeFound->value << endl;
        else
            cout << "Node not found" << endl;
    }
}

int neg(int a)
{
    int result = ~a;
    return ++result;
}

int multiply(int a, int b, int nbNegated=0)
{
    if (b == 0 || a == 0) return 0;
    if (a == 1) return b;
    if (b == 1) return a;
    
    if (a < 0)
    {
        a = neg(a);
        nbNegated++;
    }
    if (b < 0)
    {
        b = neg(b);
        nbNegated++;
    }

    if (a < b) return multiply(b, a, nbNegated);

    int mask = 1 << 30;
    int leftShiftValue = 30;
    // cout << "b: " << bitset<32>(b) << endl;
    // cout << "mask: " << bitset<32>(mask) << endl;
    while ((b & mask) == 0 && (mask != 1))
    {
        // cout << bitset<32>(mask) << endl;
        mask = mask >> 1;
        leftShiftValue--;
    }

    // cout << "mask: " << mask << endl;
    // cout << "leftShiftValue: " << leftShiftValue << endl;

    int result = a;
    int remainingAdds = b - 1;
    result = result << leftShiftValue;
    remainingAdds = b - mask;

    // cout << "remainingAdds: " << remainingAdds << endl;
    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    for (int i = 0; i < remainingAdds; i++)
    {
        result += a;
    }

    if (nbNegated % 2) return neg(result);

    return result;
}

int main()
{
    cout << "=== C++ Playground ===\n";

    // Dynanic Array
    // dynArrayTest();

    // Stack
    // stackTest();

    // Queue
    // queueTest();

    // SinglyLinked List
    // linkedListTest();
    // testInplaceReverseLinkedList();

    // BTree
    // testBTree();

    cout << multiply(135, 150) << endl;

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        multiply(4, 17);
        multiply(8, 26);
        multiply(-17, -26);
        multiply(127, -326);
        multiply(130, -326);
    }
    chrono::duration<float, std::milli> diff = chrono::steady_clock::now() - start;

    cout << "Time elapse: " << diff.count() << "ms" << endl;

    return 0;
}