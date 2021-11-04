#pragma once

#include <vector>
using namespace std;

template<typename T>
class Stack
{
public:
    Stack() = default;
    ~Stack() { m_data.clear(); }

    void push(const T& value);
    T& pop();
    T& peek();
    const T& peek() const;

    size_t size() const { return m_data.size(); }

    const T& operator[](size_t index) const;

private:
    vector<T> m_data{};
};

template<typename T>
const T& Stack<T>::operator[](size_t index) const
{
    if (index >= size())
        throw runtime_error("Out of bound access!");
    
    return m_data[index];
}

template<typename T>
void Stack<T>::push(const T& value)
{
    m_data.push_back(value);
}

template<typename T>
T& Stack<T>::pop()
{
    auto& result = m_data.back();
    if (m_data.size())
        m_data.resize(m_data.size() - 1);

    return result;
}

template<typename T>
T& Stack<T>::peek()
{
    return m_data.back();
}

template<typename T>
const T& Stack<T>::peek() const
{
    return m_data.back();
}


template<typename T>
ostream& operator<<(ostream& out, const Stack<T>& stack)
{
    out << "[";
    for(int i = 0; i < stack.size(); i++)
    {
        out << stack[i];
        if (i < stack.size() - 1)
            out << ", ";
    }

    out << "]";
    return out;
}
