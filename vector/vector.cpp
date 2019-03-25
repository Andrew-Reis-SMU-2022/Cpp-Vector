#include "vector.h"
#include <random>
#include <ctime>
#include <iostream>
#include <initializer_list>

template class vector<int>;
template class vector<double>;


template<class T> T &memcpy(T arr[], int lenght) {
	T *new_arr;
	new_arr = new T[lenght];
	for (int i = 0; i < lenght; i++) {
		new_arr[i] = arr[i];
	}
	return *new_arr;
}


template<class T> vector<T>::vector()
{
	this->num_of_elems = 0;
	this->list = new T[this->num_of_elems];
}

template<class T> vector<T>::vector(vector &vector) {
	this->num_of_elems = vector.num_of_elems;
	this->list = &memcpy<T>(vector.list, vector.num_of_elems);
}

template<class T> vector<T>::vector(T arr[], int length) {
	this->num_of_elems = length;
	this->list = &memcpy<T>(arr, length);
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
	this->num_of_elems = vector.num_of_elems;
	this->list = &memcpy<T>(vector.list, vector.num_of_elems);
	return *this;
}

template<class T> T vector<T>::operator[](int index) {
	return this->at(index);
}

template <class T> void vector<T>::append(vector vector_to_append) {
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
		return NULL;
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

template <class T> void vector<T>::credit() {
	std::cout << "This class was made by Andrew Reis\nSMU 2022\n";
}

template <class T> vector<T>::~vector()
{
	delete[] this->list;
}
