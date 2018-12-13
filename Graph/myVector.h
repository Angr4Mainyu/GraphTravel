#ifndef MYVECTOR_H
#define MYVECTOR_H

template<class T>
class myVector
{
public:
	myVector();
    myVector(const myVector & other);
	~myVector();
	void pop_back();
	void pop_front();
	T top();
	T front();
    bool empty();
    T & operator[](int pos);
	void push_back(T ele);
	int size();
    myVector & operator=(const myVector & other);

	T * begin();
	T * end();
private:
	T * _data;
	int _size;
	int factor;
	int MAX;
	void extend();
};
#endif
