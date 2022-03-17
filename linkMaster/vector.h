#pragma once

template <typename TElem> class DynamicVector
{
private:
	int size;
	int capacity;
	TElem data;

	void resize();
public:
	DynamicVector(int capacity=1);
	DynamicVector(const DynamicVector& vector);
	~DynamicVector();

	inline int getSize() const { return this->size; }
	TElem getElemet(int position) const;

	void add(TElem element);
	void remove(int position);

	DynamicVector& operator=(const DynamicVector& vector);
	TElem operator[](int position) const;
};

