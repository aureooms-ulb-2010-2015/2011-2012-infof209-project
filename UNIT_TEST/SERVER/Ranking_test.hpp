#include "../../Server/Ranking.hpp"
#include <cassert>

class Test
{
	public :
		Test();
		~Test();
		void test_addPlayer();
		void test_addPointToPlayer();
		void test_subtractPointToPlayer();

	private :

		Ranking* rank;
		string* name;
		int* point;
		
};
