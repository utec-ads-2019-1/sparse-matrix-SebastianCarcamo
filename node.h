#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next = nullptr;
    Node<T> *down = nullptr;
    unsigned row,column;
    T value;

public:
    Node() = default;
    
    Node(unsigned rp, unsigned cp, T v){
    	this->row = rp;
    	this->column = cp;
    	this->value = v;
    }

    ~Node(){}

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
