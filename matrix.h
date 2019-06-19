#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>
#include "node.h"
#include <iostream>

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(){}
    Matrix(unsigned rows, unsigned columns){
        this->rows = rows;
        this->columns = columns;
        this->root = new Node<T>();
        Node<T>* aux = root;

        for(int i = 0;i<=rows;i++){
            aux->down = new Node<T>();
            aux = aux->down;
        }
        aux = root;        
        for(int i = 0;i<=columns;i++){
            aux->next = new Node<T>();
            aux = aux->next;
        }
    }   

    bool verify(unsigned r, unsigned c)const{
        if(r > this->rows  || c > this->columns){
            return false;
        }
            return true;
    }
    void set(unsigned r, unsigned c, T v){
        if(!verify(r,c)){
            throw "La matriz no es tan grande :c";
        }

        Node<T>* inserted = new Node<T>(r,c,v);
        Node<T>** aux = &root;

        aux = &((*aux)->down);
        for(int i = 0; i<r;i++){
            aux = &((*aux)->down);
        }

        aux = &((*aux)->next);
        
        while((*aux)->column < c){
            aux = &((*aux)->next);
        }

        if(*aux != nullptr && (*aux)->column == c){
            if(v != 0){
                (*aux)->value = v;
                return;
            }
            Node<T>* skipC = (*aux)->next;
            *aux = skipC;
        }
        else if(v != 0){
            inserted->next = *aux;
            *aux = inserted;
        }
        else{
            return;
        }

        aux = &root;
        aux = &((*aux)->next);
        for(int i = 0; i<c;i++){
            aux = &((*aux)->next);
        }

        aux = &((*aux)->down);
        while((*aux)->row < c){
            aux = &((*aux)->down);
        }

        if(*aux != nullptr && (*aux)->row == r){
            Node<T>* skipR = (*aux)->down;
            delete *aux;
            *aux = skipR;
        }

        inserted->down = *aux;
        *aux = inserted;

    }

    T operator()(unsigned r, unsigned c) const{
        if(!verify(r,c)){
            throw "La matriz no es tan grande :c";
        }
        Node<T>* aux = root;
        for(int i = 0; i<=r;i++){
            aux = aux->down;
        }
        aux = aux->next;
        for(int i = 0; i<c;i++){
            aux = aux->next;
        }
        if(!aux || aux->column > c){
            return 0;
        }
        return aux->value;
    }

    Matrix<T> operator*(T scalar) const{
        Matrix<T> M2(rows,columns);

        Node<T>* i = root->next;
        while(i != nullptr){
            Node<T>* d = i->down;
            while(d != nullptr){
                M2.set(d->row,d->column,d->value * scalar); 
                d = d->down;
            } 
        }
        return M2;
    }
    Matrix<T> operator*(Matrix<T> M2) const{

    }
    Matrix<T> operator+(Matrix<T> M2) const{
        Matrix M3(rows,columns);

        for(int i = 0;i<rows;i++){
            for(int j = 0; j<columns;j++){
                T v1 = (*this)(i,j);
                T v2 = M2(i,j);
                M3.set(i,j,v1+v2);
            }
        }
        return M3;
    }
    Matrix<T> operator-(Matrix<T> M2) const{
        Matrix M3(rows,columns);

        for(int i = 0;i<rows;i++){
            for(int j = 0; j<columns;j++){
                T v1 = (*this)(i,j);
                T v2 =  M2(i,j);
                M3.set(i,j,v1-v2);
            }
        }
        return M3;
    }
    Matrix<T> transpose() const{
        Matrix<T> transposed(rows,columns);
        for(int i =0;i<rows;i++){
            for(int j = 0;j<columns;j++){
                T aux = (*this)(i,j);
                if(aux != 0){
                    transposed.set(j,i,aux);
                }
            }
        }
        return transposed;
    }
    void print() const{
        for(int i =0;i<rows;i++){
            for(int j = 0;j<columns;j++){
                std::cout<<(*this)(i,j)<<" ";
            }
            std::cout<<"\n";
        }
    }

    ~Matrix(){}
};

#endif //SPARSE_MATRIX_MATRIX_H