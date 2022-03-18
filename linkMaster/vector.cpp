//
//#include "vector.h"
//
//
//template <typename TElem>
//DynamicVector <TElem>::DynamicVector(int capacity) : size{0}, capacity{capacity}
//{
//	this->data = new TElem[this->capacity];
//}
//
//template<typename TElem>
//DynamicVector<TElem>::DynamicVector(const DynamicVector& vector)
//{
//	this->size = vector.size;
//	this->capacity = vector.capacity;
//	this->data = new TElem[vector.capacity];
//
//	for (int i = 0; i < vector.size; i++)
//		this->data[i] = vector.data[i];
//}
//
//template <typename TElem> 
//DynamicVector <TElem>::~DynamicVector()
//{
//	delete[] this->data;
//}
//
//template<typename TElem>
//void DynamicVector<TElem>::resize()
//{
//	this->capacity *= 2;
//	TElem* newData = new TElem[this->capacity];
//
//	for (int i = 0; i < this->size; i++)
//		newData[i] = this->data[i];
//
//	delete[] this->data;
//	this->data = newData;
//}
//
//template<typename TElem>
//TElem DynamicVector<TElem>::getElemet(int position) const
//{
//	if (position < 0 || position > this->size - 1)
//		throw "Index out of bounds!\n";
//
//	return this->data[position];
//}
//
//template<typename TElem>
//void DynamicVector<TElem>::add(TElem element)
//{
//	if (this->size == this->capacity)
//		this->resize();
//
//	this->data[this->size++] = element;
//}
//
//template<typename TElem>
//void DynamicVector<TElem>::remove(int position)
//{
//	if (position < 0 || position > this->size - 1)
//		throw "Index out of bounds!\n";
//
//	for (int i = position; i < this->size - 1; i++)
//		this->data[i] = this->data[i + 1];
//}
//
//template<typename TElem>
//DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector& vector)
//{
//	this->size = vector.size;
//	this->capacity = vector.capacity;
//	delete[] this->data;
//	TElem* newData = new TElem[vector.capacity];
//
//	for (int i = 0; i < vector.size; i++)
//		newData[i] = vector.data[i];
//
//	this->data = newData;
//
//	return *this;
//}
//
//template<typename TElem>
//TElem DynamicVector<TElem>::operator[](int position) const
//{
//	if (position < 0 || position > this->size - 1)
//		throw "Index out of bounds!\n";
//
//	return this->data[position];
//}
