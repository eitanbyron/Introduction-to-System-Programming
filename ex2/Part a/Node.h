//
// Created by BBIRONN on 09/06/2021.
//

#ifndef MAIN_CPP_NODE_H
#define MAIN_CPP_NODE_H
namespace mtm {

    template<class T>
    class Node {
    public:
        T value;
        Node *next_node;
        bool dummy_last;

        /**
* Node constructor: creating new class from type Node.
*
* @param new_value - the value that contained in the node.
* @param new_next_node - pointer to the next node.
* @param is_last - if the the node is the last node in containing list.
*/
        explicit Node(T new_value, Node *new_next_node = nullptr, bool is_last = false);

        /**
* Node copy constructor: copying the node details to new class.
*
* @param node - node to copy.
*/
        Node(const Node &node) = default;

        /**
* Node destructor: deleting the node details.
*/
        ~Node() = default;

        /**
* operator==: checking if the left node's value equal to the right node's value.
*
* @param node - node.
*
* @return
* true - if the left node's value equal to the right node's value.
* false - if the left node's value not equal to the right node's value.
*/

        bool operator==(const Node &node) const;

        /**
 * operator<: checking if the left node's value smaller than the right node's value.
 *
 * @param node - node.
 *
 * @return
 * true - if the left node's value smaller the right node's value.
 * false - if the left node's value equal or bigger than the right node's value.
 */

        bool operator<(const Node &node) const;

        /**
* operator>: checking if the left node's value bigger than the right node's value.
*
* @param node - node.
*
* @return
* true - if the left node's value bigger the right node's value.
* false - if the left node's value equal or smaller than the right node's value.
*/
        bool operator>(const Node &node) const;

        /**
* operator<=: checking if the left node's value equal or smaller than the right node's value.
*
* @param node - node.
*
* @return
* true - if the left node's value equal or smaller the right node's value.
* false - if the left node's value bigger than the right node's value.
*/
        bool operator<=(const Node &node) const;


        /**
* operator>=: checking if the left node's value equal or bigger than the right node's value.
*
* @param node - node.
*
* @return
* true - if the left node's value equal or bigger the right node's value.
* false - if the left node's value smaller than the right node's value.
*/
        bool operator>=(const Node &node) const;
    };


    template<class T>
    Node<T>::Node(T new_value, Node *new_next_node, bool is_last):
            value(new_value),
            next_node(new_next_node),
            dummy_last(is_last) {
    }

    template<class T>
    bool Node<T>::operator==(const Node &node) const {
        if ((!(this->value < node.value)) && (!(node.value < this->value)))
            return true;
        else
            return false;
    }

    template<class T>
    bool Node<T>::operator<(const Node &node) const {
        if (this->value < node.value)
            return true;
        else
            return false;
    }

    template<class T>
    bool Node<T>::operator<=(const Node &node) const {
        if (*this < node || *this == node)
            return true;
        else
            return false;
    }

    template<class T>
    bool Node<T>::operator>(const Node &node) const {
        if (!(*this < node))
            return true;
        else
            return false;
    }

    template<class T>
    bool Node<T>::operator>=(const Node &node) const {
        if (*this > node || *this == node)
            return true;
        else
            return false;
    }

}
#endif //MAIN_CPP_NODE_H
