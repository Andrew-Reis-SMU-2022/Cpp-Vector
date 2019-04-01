#include "vector.h"
#include <random>
#include <ctime>
#include <iostream>
#include <initializer_list>
#include <stdlib.h>
#include <exception>

//Add template type declarations here
template class vector<int>;
template class vector<double>;
template class vector<char>;


template<class T> T* memcpy(T arr[], int length) {
	T *new_arr;
	new_arr = new T[length];
	for (int i = 0; i < length; i++) {
		new_arr[i] = arr[i];
	}
	return new_arr;
}


template<class T> vector<T>::vector()
{
	this->num_of_elems = 0;
	this->list = new T[this->num_of_elems];
}

template<class T> vector<T>::vector(const vector &vector) {
	this->num_of_elems = vector.num_of_elems;
	this->list = memcpy<T>(vector.list, vector.num_of_elems);
}

template<class T> vector<T>::vector(T arr[], int length) {
	this->num_of_elems = length;
	this->list = memcpy<T>(arr, length);
}

template<class T> vector<T>::vector(std::initializer_list<T> iList) {
	this->num_of_elems = iList.size();
	this->list = new T[this->num_of_elems];
	int i = 0;
	for (T elem : iList) {
		this->list[i] = elem;
		i++;
	}
}

template<class T> vector<T>& vector<T>::operator=(const vector &vector) {
	if (this != &vector) {
		this->num_of_elems = vector.num_of_elems;
		delete[] this->list;
		this->list = memcpy<T>(vector.list, vector.num_of_elems);
	}
	return *this;
}

template<class T> T vector<T>::operator[](int index) {
	return this->at(index);
}

template <class T> void vector<T>::append(vector &vector_to_append) {
	T *temp;
	temp = this->list;
	int temp_size = this->num_of_elems;
	this->num_of_elems += vector_to_append.num_of_elems;
	this->list = new T[this->num_of_elems];
	for (int i = 0; i < temp_size; i++) {
		this->list[i] = temp[i];
	}
	for (int i = 0; i < vector_to_append.num_of_elems; i++) {
		this->list[i + temp_size] = vector_to_append.list[i];
	}
	delete[] temp;
}

template<class T> void vector<T>::append(T t_to_append) {
	T *temp;
	temp = this->list;
	int temp_size = this->num_of_elems;
	this->num_of_elems += 1;
	this->list = new T[this->num_of_elems];
	for (int i = 0; i < temp_size; i++) {
		this->list[i] = temp[i];
	}
	this->list[this->num_of_elems - 1] = t_to_append;
	delete[] temp;
}

template<class T> void vector<T>::append(T arr[], int length) {
	T *temp;
	temp = this->list;
	int temp_size = this->num_of_elems;
	this->num_of_elems += length;
	this->list = new T[this->num_of_elems];
	for (int i = 0; i < temp_size; i++) {
		this->list[i] = temp[i];
	}
	for (int i = 0; i < length; i++) {
		this->list[temp_size + i] = arr[i];
	}
	delete[] temp;
}

template <class T> T vector<T>::at(int index) {
	if (index >= 0 && index < this->num_of_elems) {
		return this->list[index];
	}
	else if (index < 0 && index * -1 <= this->num_of_elems) {
		return this->list[this->num_of_elems + index];
	}
	else {
		std::cout << "Index Out Of Bounds Exception!!!\n";
		std::terminate();
	}
}

template <class T> void vector<T>::del(int index) {
	int index_to_del;
	if (index >= 0 && index < this->num_of_elems) {
		index_to_del = index;
	}
	else if (index < 0 && index * -1 <= this->num_of_elems) {
		index_to_del = this->num_of_elems + index;
	}
	else {
		return;
	}
	T *temp;
	temp = this->list;
	int temp_size = this->num_of_elems;
	this->num_of_elems -= 1;
	this->list = new T[this->num_of_elems];
	int j = 0; //this->list incrementor
	for (int i = 0; i < temp_size; i++) {
		if (i != index_to_del) {
			this->list[j] = temp[i];
			j++;
		}
	}
	delete[] temp;
}

template <class T> int vector<T>::find(T elem) {
	for (int i = 0; i < this->num_of_elems; i++) {
		if (this->list[i] == elem) {
			return i;
		}
	}
	return -1; //index is not found
}

template <class T> void vector<T>::insert(int index, T elem) {
	T *temp;
	temp = this->list;
	int temp_size = this->num_of_elems;
	this->num_of_elems++;
	this->list = new T[this->num_of_elems];
	int j = 0; //temp incrementor
	for (int i = 0; i < this->num_of_elems; i++) {
		if (i != index) {
			this->list[i] = temp[j];
			j++;
		}
		else {
			this->list[i] = elem;
		}
	}
}

template <class T> void vector<T>::replace(int starting_index, int ending_index, T arr[], int length) {
	for (int i = starting_index; i <= ending_index; i++) {
		this->del(starting_index);
	}
	for (int i = 0; i < length; i++) {
		this->insert(starting_index + i, arr[i]);
	}
}

template <class T> void vector<T>::replace(int starting_index, int ending_index, vector<T> vec) {
	this->replace(starting_index, ending_index, vec.list, vec.num_of_elems);
}

bool index_taken(int index, int arr[], int length) {
	for (int i = 0; i < length; i++) {
		if (arr[i] == index) {
			return true;
		}
	}
	return false;
}

template <class T> void vector<T>::shuffle() {
	std::mt19937 gen(time(NULL));
	std::uniform_int_distribution<int> dis(0, this->num_of_elems - 1);
	T *temp;
	temp = this->list;
	this->list = new T[this->num_of_elems];
	int *new_locations;
	new_locations = new int[this->num_of_elems];
	new_locations[0] = dis(gen);
	for (int i = 1; i < this->num_of_elems; i++) {
		int new_index = dis(gen);
		while (true) {
			if (!index_taken(new_index, new_locations, i)) {
				new_locations[i] = new_index;
				break;
			}
			else {
				new_index = dis(gen);
			}
		}
	}
	for (int i = 0; i < this->num_of_elems; i++) {
		this->list[i] = temp[new_locations[i]];
	}
	delete[] temp;
}

template <class T> int vector<T>::size() {
	return this->num_of_elems;
}

template<class T> T* vector<T>::getList() {
	return this->list;
}

template<class T> void vector<T>::empty() {
	delete[] this->list;
	this->num_of_elems = 0;
	this->list = new T[this->num_of_elems];
}

template <class T> void vector<T>::credit() {
	std::cout << "This class was made by Andrew Reis\nSMU 2022\n";
}

template <class T> vector<T>::~vector()
{
	delete[] this->list;
}
