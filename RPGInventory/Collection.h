#pragma once
#include <functional>

// An interface for accessing an arbitrary collection of objects.
template <typename T>
class Collection
{
public:
    virtual ~Collection() = 0;

    // Gets the number of elements in the collection.
    virtual unsigned int getSize() const = 0;

    // Performs the specified accept() function on each element in the collection (read-only).
    virtual void forEach(const std::function<void(const T&)>& accept) const = 0;

    // Performs the specified accept() function on each element in the collection, 
    // potentially making changes to elements as they’re visited.
    virtual void forEach(const std::function<void(T&)>& accept) = 0;
};

template <typename T>
Collection<T>::~Collection()
{
}