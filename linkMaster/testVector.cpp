
#include "tests.h"
#include "vector.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <exception>


namespace VectorTests
{
	void testConstructor()
	{
		DynamicVector <int> vector1{};
		assert(vector1.getSize() == 0);

		DynamicVector <int> vector2{ 10 };
		assert(vector1.getSize() == 0);

		DynamicVector <int> vector3{ vector2 };
		assert(vector3.getSize() == 0);

		std::cout << "Constructor tests: success\n";
	}

	void testGetters()
	{
		DynamicVector <int> vector;
		assert(vector.getSize() == 0);

		for (int i = 0; i < 10; i++)
		{
			vector.add(i);
			assert(vector.getSize() == i + 1);
			assert(vector.getElement(i) == i);
			assert(vector[i] == i);
		}

		try
		{
			vector.getElement(-1);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		try
		{
			vector.getElement(10);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		try
		{
			vector[-1];
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		try
		{
			vector[10];
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		std::cout << "Getters tests: success\n";
	}

	void testAdd()
	{
		DynamicVector <int> vector;
		assert(vector.getSize() == 0);

		for (int i = 1; i <= 10; i++)
		{
			vector.add(i);
			assert(vector.getSize() == i);
			assert(vector.getElement(i - 1) == i);
		}

		DynamicVector <int> vectorCopy{ vector };

		assert(vectorCopy.getSize() == 10);
		for(int i = 1; i <= 10; i++)
			assert(vectorCopy.getElement(i - 1) == i);

		std::cout << "Add tests: success\n";
	}

	void testRemove()
	{
		DynamicVector <int> vector;
		assert(vector.getSize() == 0);

		for (int i = 1; i <= 10; i++)
		{
			vector.add(i);
			assert(vector.getSize() == i);
			assert(vector.getElement(i - 1) == i);
			assert(vector[i - 1] == i);
		}

		try
		{
			vector.remove(-1);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		try
		{
			vector.remove(10);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Index out of bounds!\n") == 0);
		}

		for (int i = 1; i <= 10; i++)
		{
			vector.remove(0);
			assert(vector.getSize() == 10 - i);
		}

		std::cout << "Remove tests: success\n";
	}

	void testOperatorEqual()
	{
		DynamicVector <int> vector1{};
		DynamicVector <int> vector2{};

		vector1.add(1);

		vector2 = vector1;

		assert(vector2.getSize() == 1);
		assert(vector2.getElement(0) == 1);
		assert(vector2[0] == 1);
		
		std::cout << "Operator equal test: success\n";
	}

	void testOperatorPlus()
	{
		DynamicVector <int> vector{};
		vector = vector + 1;
		assert(vector.getSize() == 1);
		vector = vector + 2;
		assert(vector.getSize() == 2);
		vector = 2 + vector;
		assert(vector.getSize() == 3);


	}
}

void testVector()
{
	std::cout << "Vector tests:\n";
	VectorTests::testConstructor();
	VectorTests::testGetters();
	VectorTests::testAdd();
	VectorTests::testRemove();
	VectorTests::testOperatorEqual();
	VectorTests::testOperatorPlus();
	std::cout << std::endl;
}