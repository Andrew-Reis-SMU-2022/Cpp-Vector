#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>


template <class T> class vector
{
public:
	vector();
	vector(vector &vector);
	vector(T arr[], int length);
	vector(std::initializer_list<T> iList);
	vector& operator=(const vector &vector);
	T operator[](int index);
	void append(vector vector_to_append);
	void append(T t_to_append);
	void append(T arr[], int length);
	T at(int index);
	void del(int index);
	void shuffle();
	int size();
	~vector();
	static void credit();
private:
	int num_of_elems;
	T *list;
};

#endif