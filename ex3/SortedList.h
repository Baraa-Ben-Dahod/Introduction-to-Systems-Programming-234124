#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        struct Node {
            T m_data;
            Node* m_next;
            Node(T data, Node* next = nullptr) : m_data(data), m_next(next) {}
        };
        int m_size;
        Node* m_head;
        void swap(SortedList<T>& other);
    public:
        //default constructor, creates an empty list
        SortedList() : m_size(0), m_head(nullptr){}
        //copy constructor
        SortedList(const SortedList<T>& other) : m_size(other.m_size), m_head(nullptr){
            if (other.m_head) {
                //copy the head's node
                m_head = new Node(other.m_head->m_data);
                //copy the rest of the nodes
                Node* current = m_head;
                Node* other_current = other.m_head->m_next;
                while (other_current) {
                    current->m_next = new Node(other_current->m_data);
                    current = current->m_next;
                    other_current = other_current->m_next;
                }
            }
        }
        //destructor
        ~SortedList() {
            while (m_head) {
                Node* temp = m_head;
                m_head = m_head->m_next;
                delete temp;
            }
        }

        //Iterator class
        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;

        //operator assignment =
        SortedList<T>& operator=(const SortedList<T>& other);

        //inserts a new element to the list
        void insert(const T& element);

        //removes an element from the list
        void remove(const SortedList<T>::ConstIterator& iterator);

        //returns the number of elements in the list
        int length() const;

        //returns a new list with elements that satisfy a given condition
        template<class op>
        SortedList<T> filter(op predict) const;

        //returns a new list with elements that were modified by an operation
        template<class op>
        SortedList<T> apply(op predict) const;

    };

    template <class T>
    class SortedList<T>::ConstIterator {
    private:
        const SortedList<T>* m_list;
        Node* m_current;
        friend class SortedList<T>;
        bool operator==(const ConstIterator& iterator) const;
    public:
        ConstIterator(const SortedList<T>* list, Node* current)
                : m_list(list), m_current(current) {}

        ConstIterator(const ConstIterator& other) = default;

        ConstIterator& operator=(const ConstIterator& other) = default;

        ~ConstIterator() = default;
        const T& operator*() const;
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& iterator) const;
    };

//Implementation:
//list:
    template <class T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(this, m_head);
    }

    template <class T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(this, nullptr);
    }

    template <class T>
    void SortedList<T>::swap(SortedList<T>& other) {
        Node* temp_head = m_head;
        m_head = other.m_head;
        other.m_head = temp_head;
        int temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;
    }

    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& other){
        if (this == &other) {
            return *this;
        }
        SortedList<T> temp(other);
        swap(temp);
        return *this;
    }

    template <class T>
    void SortedList<T>::insert(const T& element){
        Node* newNode = new Node(element);
        if (m_head == nullptr) {
            m_head = newNode;
        } else {
            ConstIterator it = begin();
            ConstIterator prev = end();
            while (it != end() && ((*it > element) || !(element > *it) )) { // (a>=b) equivalent to (a>b or !(b>a)) , we use it because T may not have operator ==
                prev = it;
                ++it;
            }
            if (prev == end()) {
                newNode->m_next = m_head;
                m_head = newNode;
            } else {
                Node* prevNode = prev.m_current;
                newNode->m_next = prevNode->m_next;
                prevNode->m_next = newNode;
            }
        }
        ++m_size;
    }

    template <class T>
    void SortedList<T>::remove(const SortedList<T>::ConstIterator& iterator){
        if (m_head == nullptr || iterator.m_list != this) {
            return;
        }

        if (iterator == begin()) {
            Node* temp = m_head;
            m_head = m_head->m_next;
            delete temp;
        } else {
            Node* prev = nullptr;
            Node* current = m_head;
            for (; current != nullptr && current != iterator.m_current; current = current->m_next) {
                prev = current;
            }
            if (current != nullptr) {
                prev->m_next = current->m_next;
                delete current;
            }
        }
        --m_size;
    }


    template <class T>
    int SortedList<T>::length() const{
        return m_size;
    }

    template <class T>
    template <class op>
    SortedList<T> SortedList<T>::filter(op predict) const {
        SortedList<T> filteredList;
        for (ConstIterator it = begin(); it != end(); ++it) {
            if (predict(*it)) {
                filteredList.insert(*it);
            }
        }
        return filteredList;
    }


    template <class T>
    template<class op>
    SortedList<T> SortedList<T>::apply(op predict) const {
        SortedList<T> resultList;
        for (ConstIterator it = begin(); it != end(); ++it) {
            resultList.insert(predict(*it));
        }
        return resultList;
    }

//iterator:

    template <class T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        return m_current->m_data;
    }


    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
        if(m_current == nullptr) {
            throw std::out_of_range("out of range");
        }
        m_current = m_current->m_next;
        return *this;

    }

    template <class T>
    bool SortedList<T>::ConstIterator::operator==(const SortedList::ConstIterator &iterator) const {
        if(m_list == iterator.m_list && m_current == iterator.m_current) {
            return true;
        }
        return false;

    }

    template <class T>
    bool SortedList<T>::ConstIterator::operator!=(const SortedList::ConstIterator &iterator) const {
        return !(*this == iterator);
    }

}