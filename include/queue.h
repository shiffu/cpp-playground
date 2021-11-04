#pragma once

#include <vector>
#include <optional>

using namespace std;

// FIFO Queue
template<typename T>
class Queue
{
public:
    Queue() = default;
    ~Queue() = default;

    void clear()
    {
        cout << "Queue: Clear()" << endl;
        m_data.clear();
    }
    
    void insert(const T& value)
    {
        m_data.push_back(value);
    }

    optional<T> dequeue()
    {
        if (m_front < m_data.size())
            return m_data[m_front++];
        
        clear();
        return {};
    }

    size_t size() const { return m_data.size(); }

    const T& operator[](size_t index) const;

private:
    vector<T> m_data;
    size_t m_front{0};
};


template<typename T>
const T& Queue<T>::operator[](size_t index) const
{
    if (index >= size())
        throw runtime_error("Out of bound access!");
    
    return m_data[index];
}

template<typename T>
ostream& operator<<(ostream& out, const Queue<T>& queue)
{
    out << "[";
    for(int i = 0; i < queue.size(); i++)
    {
        out << queue[i];
        if (i < queue.size() - 1)
            out << ", ";
    }

    out << "]";
    return out;
}
