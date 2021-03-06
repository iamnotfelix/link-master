
#include "tests.h"
#include "repository.h"
#include "tutorial.h"
#include "exception.h"

#include <assert.h>
#include <exception>
#include <fstream>
#include <mysqlx/xdevapi.h>


namespace RepositoryTests
{
	/*void testConstructor()
	{
		Repository repo;
		assert(repo.getSize() == 10);
		assert(repo.getElement(0).getTitle() == "Title 1");
		assert(repo.getElement(3).getTitle() == "Title 4");
		assert(repo.getElement(3).getLink() == "Link 4");
		assert(repo.getElement(9).getLink() == "https://en.cppreference.com/w/");
	}*/

	void testFind()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");
		Tutorial tutorial4(repo.getNextId(), "title4", "presenter4", 1, 2, "link1");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.find(tutorial3) == false);
		assert(repo.find(tutorial2) == true);
		assert(repo.find(tutorial1) == true);
		assert(repo.find(tutorial4) == true);
	}

	void testGetElement()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getElement(0) == tutorial1);
		assert(repo.getElement(1) == tutorial2);

		try
		{
			repo.getElement(2);
			assert(false);
		}
		catch (const Exception& e)
		{
			assert(e.what() == std::string("Tutorial not found!\n"));
		}
	}
	
	void testGetAll()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);
		repo.add(tutorial3);

		std::vector<Tutorial> data = repo.getAll();
		for (int i = 0; i < data.size(); i++)
		{
			assert(data[i] == repo.getElement(i));
		}
	}

	void testAdd()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 1);

		repo.add(tutorial2);
		assert(repo.getSize() == 2);

		repo.add(tutorial3);
		assert(repo.getSize() == 3);

		try
		{
			repo.add(tutorial1);
			assert(false);
		}
		catch (const Exception& e)
		{
			assert(e.what() == std::string("Tutorial already exists!\n"));
		}
	}
	
	void testRemove()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);

		try
		{
			repo.remove(2);
			assert(false);
		}
		catch (const Exception& e)
		{
			assert(e.what() == std::string("Tutorial not found!\n"));
		}
	}

	void testUpdate()
	{
		Repository repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		
		try
		{
			repo.update(0, "title", "presenter", 1, 2, "link");
			assert(false);
		}
		catch (const Exception& e)
		{
			assert(e.what() == std::string("Tutorial not found!\n"));
		}

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

namespace TXTRepositoryTests
{
	void testAdd()
	{
		std::ofstream f("testFile.txt");
		f << "title5|presenter5|1|2|link5\n";
		f.close();

		TXTRepository repo{"testFile.txt"};

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 2);

		repo.add(tutorial2);
		assert(repo.getSize() == 3);

		repo.add(tutorial3);
		assert(repo.getSize() == 4);
	}

	void testRemove()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		TXTRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);
	}

	void testUpdate()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		TXTRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

namespace CSVRepositoryTests
{
	void testAdd()
	{
		std::ofstream f("testFile.txt");
		f << "title5,presenter5,1,2,link5\n";
		f.close();

		CSVRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 2);

		repo.add(tutorial2);
		assert(repo.getSize() == 3);

		repo.add(tutorial3);
		assert(repo.getSize() == 4);
	}

	void testRemove()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		CSVRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);
	}

	void testUpdate()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		CSVRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

namespace HTMLRepositoryTests
{
	void testAdd()
	{
		std::ofstream f("testFile.txt");
		f << "<tr><td>Title 2</td><td>Presenter 2 </td><td>1234</td><td>1234</td><td><a href=\"Link 2\">Link</a></td></tr>";
		f.close();

		HTMLRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 2);

		repo.add(tutorial2);
		assert(repo.getSize() == 3);

		repo.add(tutorial3);
		assert(repo.getSize() == 4);
	}

	void testRemove()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		HTMLRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);
	}

	void testUpdate()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		HTMLRepository repo{ "testFile.txt" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

namespace SQLRepositoryTests
{
	void clearTestTable()
	{
		using namespace mysqlx;

		Session sess("localhost", 33060, "root", "root");
		sess.sql("USE link_master").execute();
		sess.sql("DELETE FROM test_table").execute();
		sess.close();
	}

	void testAdd()
	{
		clearTestTable();

		using namespace mysqlx;
		Session sess("localhost", 33060, "root", "root");
		sess.sql("USE link_master").execute();
		sess.sql("INSERT INTO test_table (id, title, presenter, duration, likes, link) VALUES (0, 'a', 'b', 0, 0, 'c')")
			.execute();
		sess.close();

		SQLRepository repo{ "localhost", 33060, "root", "root", "link_master", "test_table" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 2);

		repo.add(tutorial2);
		assert(repo.getSize() == 3);

		repo.add(tutorial3);
		assert(repo.getSize() == 4);
	}

	void testRemove()
	{
		clearTestTable();
		SQLRepository repo{ "localhost", 33060, "root", "root", "link_master", "test_table" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);
	}

	void testUpdate()
	{
		clearTestTable();
		SQLRepository repo{ "localhost", 33060, "root", "root", "link_master", "test_table" };

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

void testRepository()
{
	//RepositoryTests::testConstructor();
	RepositoryTests::testFind();
	RepositoryTests::testGetElement();
	RepositoryTests::testGetAll();
	RepositoryTests::testAdd();
	RepositoryTests::testRemove();
	RepositoryTests::testUpdate();

	TXTRepositoryTests::testAdd();
	TXTRepositoryTests::testRemove();
	TXTRepositoryTests::testUpdate();

	CSVRepositoryTests::testAdd();
	CSVRepositoryTests::testRemove();
	CSVRepositoryTests::testUpdate();

	HTMLRepositoryTests::testAdd();
	HTMLRepositoryTests::testRemove();
	HTMLRepositoryTests::testUpdate();

	SQLRepositoryTests::testAdd();
	SQLRepositoryTests::testRemove();
	SQLRepositoryTests::testUpdate();
}
