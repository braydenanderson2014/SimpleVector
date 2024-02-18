#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <Arduino.h>
template<typename T>
class SimpleVector {
private:
    T* array;
    unsigned int count;
    unsigned int capacity;

    /**
     * @brief Resize the array to the specified capacity
     * @param newCapacity The new capacity of the array
     * 
     * @private This method is private because it is only used internally.
     * 
     * @note This method will copy all elements from the old array to the new array.
    */
    void resize(unsigned int newCapacity) {
        T* newArray = new T[newCapacity];
        
        for (unsigned int i = 0; i < count; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    // The SimpleVectorIterator class will be defined below
    class SimpleVectorIterator;

    SimpleVector() : array(new T[4]), count(0), capacity(4) {}
    
    ~SimpleVector() {
        delete[] array;
    }

    // ... Other methods ...

    /**
     * @brief Release the memory used by the vector
     * 
     * @public This method is public because it is meant to be called by the user.
    */
    void releaseMemory() {
        delete[] array;
        array = nullptr;
        capacity = 0;
        count = 0;
    }

    /**
    * @brief Clears the vector by setting all elements to their default value and resetting the count.
    * 
    * @public This method is public because it is meant to be called by the user.
    */
    void clear() {
        for (unsigned int i = 0; i < count; i++) {
            array[i] = T(); // Set each element to its default value
        }
        count = 0; // Reset the count
    }


//Changed to put() for better naming conventions.
    /**
     * @brief Add an element to the vector
     * @param item The item to be added to the vector
     * 
    */
    void put(const T& item) {
        if (count == capacity) {
            resize(2 * capacity);
        }
        array[count++] = item;
    }

    // Remove an element from the vector by shifting elements (Added in Version 1.0.1)
    /**
     * @brief Remove an element from the vector
     * @param item The item to be removed from the vector
     * 
     * @note This method will shift all elements after the specified element to the left by one.
    */
    void remove(const T& item) {
        unsigned int index = 0;
        for (unsigned int i = 0; i < count; i++) {
            if (array[i] == item) {
                // Element found, skip it
                continue;
            }
            array[index++] = array[i];
        }
        count = index;
    }

    /**
     * Overloads the subscript operator for the SimpleVector class.
     * 
     * This function is used to access elements in the vector at a given index.
     * If the index is out of bounds (i.e., greater than or equal to the count of elements), it returns nullptr.
     * 
     * @param index The index of the element to be accessed.
     * @return Reference to the element at the given index, or nullptr if the index is out of bounds.
     */
    T& operator[](unsigned int index) {
        if (index >= count) {
            return nullptr; // You can handle this error differently if needed
        }
        return array[index];
    }

    /**
     * @brief Get the size of the vector
     * @return The size of the vector
     * 
     * @note This method returns the capacity of the vector, not the count of elements.
    */
    unsigned int size() const {
        if(this -> capacity == 0){
            return 0;
        }
        return this -> capacity;
    }

    /**
     * @brief Get the count of elements in the vector
     * @return The count of elements in the vector
    */
    unsigned int elements() const {
        if(this -> count == 0){
            return 0;
        }
        return this -> count;
    }

// Get the element at the specified index
    /**
     * @brief Get the element at the specified index
     * @param index The index of the element to be accessed
     * @return Reference to the element at the specified index
    */
    T& get(unsigned int index) {
        if (index >= count) {
            return nullptr; // You can handle this error differently if needed
        }
        return array[index];
    }

    // Get the index of the specified element
    /**
     * @brief Get the index of the specified element
     * @param element The element to be searched for
     * @return The index of the specified element, or 0 if the element is not found
    */
    int indexOf(const T& element) {
        for (unsigned int i = 0; i < count; i++) {
            if (array[i] == element) {
                return i;
            }
        }
        return 0; // Element not found
    }

    // ... Other methods ...

    // SimpleVectorIterator related methods
    /**
     * @brief Get an iterator pointing to the first element in the vector
     * @return An iterator pointing to the first element in the vector
    */
    SimpleVectorIterator begin() {
        return SimpleVectorIterator(array, array + count);
    }

    /**
     * @brief Get an iterator pointing to the end of the vector
     * @return An iterator pointing to the end of the vector
    */
    SimpleVectorIterator end() {
        return SimpleVectorIterator(array + count, array + count);
    }

    // The iterator type should be defined after the SimpleVectorIterator class.
    // This is because the SimpleVectorIterator class needs to be defined first.
    typedef SimpleVectorIterator iterator;

    // Definition of the SimpleVectorIterator class
    class SimpleVectorIterator {
    private:
        T* current;
        T* end;
    public:
        SimpleVectorIterator(T* start, T* stop) : current(start), end(stop) {}

        /**
         * @brief Check if the iterator has reached the end of the vector
         * @return True if the iterator has reached the end of the vector, false otherwise
        */
        bool hasNext() {
            return current != end;
        }

        /**
         * @brief Get the next element in the vector
         * @return The next element in the vector
        */
        T& next() {
            return *current++;
        }

        // The iterator needs to be compatible with STL-style iteration
        /**
         * @brief Overload the prefix increment operator
        */
        SimpleVectorIterator& operator++() {
            ++current;
            return *this;
        }

        /**
         * @brief Overload the postfix increment operator
        */
        bool operator!=(const SimpleVectorIterator& other) const {
            return current != other.current;
        }

        /**
         * @brief Overload the dereference operator
        */
        T& operator*() {
            return *current;
        }
    };
};
#endif // SIMPLEVECTOR_H
