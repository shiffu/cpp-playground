#pragma once

#include <exception>
#include <cstring>

using namespace std;


template<typename T>
class DynArray
{
public:
    DynArray(size_t capacity = 0);
    ~DynArray() {
        cout << "~DynArray(), size: " << m_size << endl;
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i].~T();
        }
        free((void*)m_data);
    };

    void reserve(size_t size);
    void add(T&& value);
    void add(const T& value);
    void remove(size_t index);
    void clear();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t capacity() const { return m_capacity; }
    size_t size() const { return m_size; }

    T* begin() { return m_data; }
    T* end() { return &m_data[m_size]; }

private:
    T* m_data{nullptr};
    size_t m_capacity{0};
    size_t m_size{0};
};


template<typename T>
DynArray<T>::DynArray(size_t capacity /*= 0*/)
{
    if (capacity)
    {
        m_data = (T*)malloc(sizeof(T) * capacity);
    }
}

template<typename T>
void DynArray<T>::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        cout << "DynArray: Reserving more memory from " << m_capacity << " to " << capacity << endl;

        auto newData = (T*)malloc(sizeof(T) * capacity);
        if (newData == nullptr)
            throw runtime_error("Unable to reserve the requested memory");

        if (capacity < m_size)
        {
            m_size = capacity;
        }

        // Move data to the new location in memory
        for (int i = 0; i < m_size; i++)
        {
            new (&newData[i]) T(move(m_data[i]));
        }

        for (int i = 0; i < m_size; i++)
        {
            m_data[i].~T();
        }

        free(m_data);
        m_data = newData;
        m_capacity = capacity;
    }
}

template<typename T>
void DynArray<T>::add(T&& value)
{
    if (m_size >= m_capacity)
    {
        auto newCapacity = m_capacity ? m_capacity << 1 : 1;
        reserve(newCapacity);
    }

    new (&m_data[m_size++]) T(move(value));
    // m_data[m_size++] = move(value);
}

template<typename T>
void DynArray<T>::add(const T& value)
{
    if (m_size >= m_capacity)
    {
        auto newCapacity = m_capacity ? m_capacity << 1 : 1;
        reserve(newCapacity);
    }

    m_data[m_size++] = value;
}

template<typename T>
void DynArray<T>::remove(size_t index)
{
}

template<typename T>
void DynArray<T>::clear()
{
    m_size = 0;
}

template<typename T>
T& DynArray<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw runtime_error("Out of bound access!");

    return m_data[index];
}

template<typename T>
const T& DynArray<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw runtime_error("Out of bound access!");
    
    return m_data[index];
}

template<typename T>
ostream& operator<<(ostream& out, const DynArray<T>& arr)
{
    out << "[";
    for(int i = 0; i < arr.size(); i++)
    {
        out << arr[i];
        if (i < arr.size() - 1)
            out << ", ";
    }

    out << "]";
    return out;
}
