
#include "vector.h"

#include <exception>


template <class TElem> 
Vector <TElem>::Vector(int capacity)
{
	this->capacity = capacity;
	if (capacity < 1)
		throw "Invalid capacity!\n";
	
	this->size = 0;
	this->data = new void* [this->capacity];
}

template <class TElem> 
Vector<TElem>::Vector(Vector& vector)
{
	//TODO: create implementation for copy constructor
}

template <class TElem> 
Vector<TElem>::~Vector()
{
	delete[] this->data;
}

template <class TElem> 
TElem Vector<TElem>::get(int position)
{
	if (position < 0 || position > this->size)
		throw "Index out of range!\n";

	return this->data[position];
}

template <class TElem> 
void Vector<TElem>::add(TElem element)
{
	if (this->size == this->capacity)
		this->resize();

	this->data[this->size++] = element;
}

template <class TElem>
void Vector<TElem>::remove(int position)
{
	if (position < 0 || position > this->size)
		throw "Index out of range!\n";

	//delete this->data[position];

	while (position < this->size - 1)
		this->data[position] = this->data[++position];
	
	this->size--;
}

template <class TElem> 
void Vector<TElem>::update(int position, TElem element)
{

}

template <class TElem> 
void Vector<TElem>::resize()
{
	
}
