//
// Created by BBIRONN on 09/06/2021.
//

#ifndef SORTED_LISTTT_SORTEDLIST_H
#define SORTED_LISTTT_SORTEDLIST_H

#include "Node.h"
#include <stdexcept>


namespace mtm {

    template<class T>
    class SortedList {
        Node<T> *first;
        Node<T> *dummy;
    public:
        /**
* SortedList constructor: creating new class from type SortedList.
*/
        SortedList();

        /**
* SortedList destructor: deleting the list details.
*/

        ~SortedList();

        /**
* SortedList copy constructor: copying the list details to new class.
*
* @param old_list - list to copy.
*/
        SortedList(const SortedList &old_list);

        /**
* operator=: assignment operator.
*
* @param old_list - list to assign.
*/
        SortedList &operator=(const SortedList &old_list);


        /**
* filter: returning new sorted list only with the nodes that satisfy the condition.
*
* @param c - predict (boolean function).
*
* @return
* new sorted list only with the nodes that satisfy the condition.
*/
        template<class Condition1>
        SortedList filter(Condition1 c) const;


        /**
* apply: returning new sorted list with nodes which are the result of the function's apply on the original list.
*
* @param c - function.
*
* @return
* new sorted list with nodes which are the result of the function's apply on the original list.
*/
        template<class Condition2>
        SortedList apply(Condition2 c) const;

        /**
* insert: inserting new elemnt to the list.
*
* @param new_object - value for new node.
*/

        void insert(const T new_object);

        /**
* length: returning the list's length (number of nodes).
*
* @return
* list's length (number of nodes).
*/

        int length() const;


        class const_iterator {

            const SortedList *list;

            Node<T> *CI;

            friend class SortedList;

            explicit const_iterator(const SortedList *sorted_list);

            bool operator!=(const const_iterator &OCI);


        public:


            /**
* operator++: advancing the iterator to the next node.
*/
            const_iterator operator++();

            /**
* operator=: assignment operator.
*
* @param old_const_iterator - iterator to assign.
*/
            const_iterator &operator=(const const_iterator &old_const_iterator) = default;

            /**
* const_iterator destructor: deleting the iterator.
*/
            ~const_iterator() = default;

            /**
* operator++: advancing the iterator to the next node.
*/
            const_iterator operator++(int);

            /**
       * operator==: checking if the iterator equal to the right iterator.
       *
       * @param OCI - iterator.
       *
       * @return
       * true - if the left iterator equal to the iterator value.
       * false - if the left iterator not equal to the right iterator.
       */
            bool operator==(const const_iterator &OCI);

            /**
* operator*: returning const reference to the node .
*/
            const T &operator*();
        };

        /**
* begin: returning iterator that pointing to list's begin.
*/
        const_iterator begin() const;

        /**
* end: returning iterator that pointing to list's end.
*/

        const_iterator end() const;

        /**
    * remove: removing a node from the list.
    *
    * @param to_remove - iterator pointing to the node.
    */

        void remove(const_iterator to_remove);

    };

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList &old_list) {
        if (this == &old_list) {
            return *this;
        }
        SortedList<T> *temp = new SortedList<T>(old_list);   //leak!!!!!
        int length = this->length();
        for (int i = 0; i <= length; i++) {
            SortedList<T>::const_iterator head = this->begin();
            this->remove(head);
        }
        dummy = nullptr;
        first = nullptr;
        this->first = temp->first;
        this->dummy = temp->dummy;
        temp->first= nullptr;
        temp->dummy= nullptr;
        delete temp;
        return *this;
    }


    template<class T>
    SortedList<T>::SortedList() {
        first = nullptr;
        dummy = nullptr;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        const_iterator it = this->begin();
        if (first == nullptr) {
            return it;
        }
        while (it.CI != dummy) {
            it++;
        }
        return (it);
    }

    template<class T>
    void SortedList<T>::insert(const T new_object) {
        Node<T> *new_node;
        try {
            new_node = new Node<T>(new_object);
        }
        catch (std::bad_alloc &a) {
            throw std::bad_alloc();
        }
        const_iterator iterator = begin();
        if (first == nullptr) {
            first = new_node;
            try {
                dummy = new Node<T>(new_object);
            }
            catch (std::bad_alloc &a) {
                delete new_node;
                throw std::bad_alloc();
            }

            dummy->dummy_last = true;
            new_node->next_node = dummy;
            return;
        }
        if ((*new_node) <= (*first)) {
            new_node->next_node = first;
            first = new_node;
            return;
        }
        while ((*(iterator.CI->next_node) <= (*new_node)) && (iterator.CI->next_node != dummy)) {
            iterator++;
        }
        new_node->next_node = iterator.CI->next_node;
        iterator.CI->next_node = new_node;
    }

    template<class T>
    void SortedList<T>::remove(const_iterator to_remove) {
        if (first == nullptr) {
            return;
        }
        if (first == to_remove.CI) {
            first = to_remove.CI->next_node;
            delete to_remove.CI;
            to_remove.CI = nullptr;
            return;
        }
        Node<T> *current = first;
        while (current->next_node != to_remove.CI) {
            current = current->next_node;
        }
        current->next_node = to_remove.CI->next_node;
        delete to_remove.CI;
        to_remove.CI = nullptr;
    }

    template<class T>
    int SortedList<T>::length() const {
        if (first == nullptr) {
            return 0;
        }
        int length = 0;
        const_iterator iterator = begin(), end_iterator = end();
        while (iterator != end_iterator) {
            length++;
            iterator++;
        }
        return length;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        const_iterator it(this);
        return (it);
    }

    template<class T>
    SortedList<T>::~SortedList() {
        int length = this->length();
        for (int i = 0; i <= length; i++) {
            SortedList<T>::const_iterator head = this->begin();
            this->remove(head);
        }

    }


    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int) {
        const_iterator current = *this;
        if (current.CI == this->list->dummy) {
            throw std::out_of_range("error");
        }
        ++*this;
        return current;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++() {
        this->CI = this->CI->next_node;
        return *this;
    }


    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &OCI) {
        if (OCI.CI == this->CI) {
            return true;
        } else {
            return false;
        }
    }

    template<class T>
    const T &SortedList<T>::const_iterator::operator*() {

        return ((const T &) this->CI->value);
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator!=(const const_iterator &OCI) {
        if (!(OCI.CI == this->CI)) {
            return true;
        } else {
            return false;
        }
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T> *sorted_list_new) :
            list(sorted_list_new),
            CI(sorted_list_new->first) {
    }

    template<class T>
    template<class Condition1>
    SortedList<T> SortedList<T>::filter(Condition1 c) const {
        SortedList general;
        const_iterator it = begin();
        const_iterator end_it = end();
        while (it.CI != end_it.CI) {
            if (c(it.CI->value))
                general.insert(it.CI->value);
            it++;
        }
        return general;
    }

    template<class T>
    template<class Condition2>
    SortedList<T> SortedList<T>::apply(Condition2 c) const {
        SortedList general;
        const_iterator it = begin();
        const_iterator end_it = end();
        while (it.CI != end_it.CI) {
            general.insert(c(it.CI->value));
            it++;
        }
        return general;
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList &old_list) :
            first(nullptr), dummy(nullptr) {
        int length = old_list.length();
        const_iterator it = old_list.begin();
        for (int i = 0; i < length; i++) {
            insert(it.CI->value);
            it++;
        }

    }
}


#endif //SORTED_LISTTT_SORTEDLIST_H
