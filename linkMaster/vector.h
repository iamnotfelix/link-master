#pragma once

template <class TElem>
class Vector
{
public:
	Vector(int capacity=2);
	Vector(Vector& vector);
	~Vector();


	TElem get(int position);

	void add(TElem element);
	void remove(int position);
	void update(int position, TElem element);

private:
	TElem* data;
	int capacity;
	int size;

	void resize();
};
