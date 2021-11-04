#pragma once

template<typename T>
struct Node
{
    Node<T>* next{nullptr};
    T data;
};


template<typename ListType>
class SLinkedList_Iterator
{
public:
    using NodeType = typename ListType::NodeType;
    using PointerNodeType = NodeType*;

    using ValueType = typename ListType::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:
    SLinkedList_Iterator(PointerNodeType ptr)
        : m_nodePtr(ptr) {}
    ~SLinkedList_Iterator() {}

    // Pre-fixed increment operator
    SLinkedList_Iterator& operator++()
    {
        m_nodePtr = m_nodePtr->next;
        return *this;
    }
    
    // Post-fixed increment operator
    SLinkedList_Iterator operator++(int)
    {
        auto tmp = *this;
        m_nodePtr = m_nodePtr->next;
        return tmp;
    }

    PointerType operator->()
    {
        return &m_nodePtr->data;
    }
    
    ReferenceType operator*()
    {
        return m_nodePtr->data;
    }
    
    bool operator==(const SLinkedList_Iterator& other)
    {
        return m_nodePtr == other.m_nodePtr;
    }
    
    bool operator!=(const SLinkedList_Iterator& other)
    {
        return !(*this == other);
    }

private:
    PointerNodeType m_nodePtr;
};


template<typename T>
class SLinkedList
{
public:
    using ValueType = T;
    using NodeType = Node<ValueType>;
    using Iterator = SLinkedList_Iterator<SLinkedList<T>>;

public:
    SLinkedList()  = default;
    ~SLinkedList() = default;

    void push_back(T node);
    T pop_back();

    void push_front(const T& node);
    T pop_front();

    void remove(const T& node);

    void reverse();

    // Container must be NOT EMPTY (otherwise: undefined behavior)
    T& front() const { return m_head->data; }
    T& back() const { return m_tail->data; }
    
    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    void clear();

    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return Iterator(m_tail->next); }

private:
    void recursiveReverse(Node<T>* currentNode, Node<T>** nodeToSwapWith);
    void nonrecursiveReverse();

private:
    Node<T>* m_head{nullptr};
    Node<T>* m_tail{nullptr};
    size_t m_size{0};
};


// Implementation

template<typename T>
void SLinkedList<T>::push_back(T value)
{
    auto newNode = new Node<T>();
    newNode->data = value;
    if (m_head == nullptr)
    {
        m_head = newNode;
    }
    
    if (m_tail == nullptr)
    {
        m_tail = newNode;
    }
    else
    {
        m_tail->next = newNode;
        m_tail = newNode;
    }
    m_size++;
}

template<typename T>
T SLinkedList<T>::pop_back()
{
    auto nodeBeforeTail = m_head;
    while (nodeBeforeTail->next != m_tail)
    {
        nodeBeforeTail = nodeBeforeTail->next;
    }

    auto previousTail = *m_tail;
    delete m_tail;

    nodeBeforeTail->next = nullptr;
    m_size--;

    return previousTail.data;
}

template<typename T>
void SLinkedList<T>::push_front(const T& value)
{
    auto newNode = new Node<T>();
    newNode->next = m_head;
    newNode->data = value;
    m_head = newNode;
    m_size++;
}

template<typename T>
T SLinkedList<T>::pop_front()
{
    auto frontData = m_head->data;
    auto newHead = m_head->next;
    delete m_head;
    m_head = newHead;
    m_size--;

    return frontData;
}

template<typename T>
void SLinkedList<T>::remove(const T& value)
{
    if (m_size)
    {
        auto current = m_head;
        Node<T>* previous = nullptr;
        while (current != m_tail->next)
        {
            if (current->data == value)
            {
                if (previous)
                {
                    previous->next = current->next;
                }
                else
                {
                    m_head = current->next;
                    previous = m_head;
                }

                if (current == m_tail)
                {
                    m_tail = previous;
                }

                auto next = current->next;
                delete current;
                current = next;
                m_size--;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }
}

template<typename T>
void SLinkedList<T>::reverse()
{
    auto current = m_head;
    if (m_size > 1)
    {
        // recursiveReverse(current, &current);
        nonrecursiveReverse();
    }
}


template<typename T>
void SLinkedList<T>::nonrecursiveReverse()
{
    Node<T>* previous = nullptr;
    auto current = m_head;
    m_tail = m_head;
    while (current != nullptr)
    {
        auto tmp = current->next;
        current->next = previous;
        previous = current;
        current = tmp;
    }
    m_head = previous;
}

template<typename T>
void SLinkedList<T>::recursiveReverse(Node<T>* currentNode, Node<T>** nodeToSwapWith)
{
    if (currentNode->next)
    {
        recursiveReverse(currentNode->next, nodeToSwapWith);
    }

    if (*nodeToSwapWith && *nodeToSwapWith != currentNode)
    {
        auto tmp = currentNode->data;
        currentNode->data = (*nodeToSwapWith)->data;
        (*nodeToSwapWith)->data = tmp;
        *nodeToSwapWith = (*nodeToSwapWith)->next;
        if (*nodeToSwapWith == currentNode)
        {
            // terminate the recursion since we have passed the middle of the list
            *nodeToSwapWith = nullptr;
        }
    }
    else
    {
        // terminate the recursion since we have passed the middle of the list
        *nodeToSwapWith = nullptr;
    }
}

template<typename T>
void SLinkedList<T>::clear()
{
    if (m_size)
    {
        auto current = m_head;
        auto next = current;
        while (current != m_tail)
        {
            next = current->next;
            delete current;
            current = next;
        }
        
        delete m_tail;
    }
    m_size = 0;
}
