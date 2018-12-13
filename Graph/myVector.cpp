#include "myVector.h"

template<class T>
myVector<T>::myVector(){//初始化
	MAX = 10;
	_data = new T[MAX];
	_size = 0;
    factor = 2;
}

template<class T>
myVector<T>::myVector(const myVector<T> &other)
{
    if(this == &other)
        return;
    (*this) = other;
}


template<class T>
myVector<T>::~myVector(){
	delete _data;
	_data = 0;
	_size = 0;
}


template<class T>
void myVector<T>::pop_back(){//弹出最后一个元素
	_data[_size - 1] = 0;
	_size--;
}


template<class T>
void myVector<T>::pop_front(){//弹出前面的元素
	for(int i = 1; i < _size; i++){
		_data[i-1] = _data[i];
	}
	_data[_size - 1] = 0;
	_size--;
}


template<class T>
T myVector<T>::top(){//返回最后面的元素
	return _data[_size - 1];
}


template<class T>
T myVector<T>::front(){//返回最前面的元素
    return _data[0];
}

template<class T>
bool myVector<T>::empty()//返回是否是空的
{
    return _size == 0;
}


template<class T>
T & myVector<T>::operator[](int pos){//重载[]
	if(pos >= 0 && pos <_size)
		return _data[pos];
    T temp;
    return temp;
}


template<class T>
void myVector<T>::push_back(T ele){//从后面加入元素
	if(_size == MAX)
		extend();
	_data[_size] = ele;
	++_size;
}


template<class T>
int myVector<T>::size(){//返回大小
    return _size;
}

template<class T>
myVector<T> &myVector<T>::operator=(const myVector<T> &other)//重载等号
{
    this->MAX = other.MAX;
    this->_data = new T[other.MAX];
    this->_size = other._size;
    for(int i = 0; i < this->_size; i++){
        this->_data[i] = other._data[i];
    }
    return *this;
}


template<class T>
void myVector<T>::extend(){//数组范围扩大
	MAX *= factor;
	T * temp = new T[MAX];
	for(int i = 0; i < _size; i++){
		temp[i] = _data[i];
	} 
	delete _data;
	_data = temp;
}

template<class T>
T * myVector<T>::begin(){//返回开始节点
	return _data;
}
template<class T>
T * myVector<T>::end(){//返回结束节点
	return _data + _size;
}
