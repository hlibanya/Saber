#include <vector>

#include "LinkedList.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(LinkedListTests)
{
	struct TestNode
	{
		int randPos;
		std::string str;
	};

	void pushNodes(List& list, std::vector<TestNode>& nodes)
	{
		for (auto& node : nodes)
		{
			list.addNode(node.str, node.randPos);
		}
	}

	std::vector<std::vector<TestNode>> testSets =
	{
		{{0, "aaaaaa"},{1, "aab"},{0, "aaabaaa"},{1, "a"},{3, "aa"},{2, ""}},
		{{0, "bb"},{1, "b"},{1, "bbb"},{2, "bbaabbb"},{3, "bbbb"},{4, "ba"}},
		{{0, "its 3am"},{0, "god"},{1, "help"},{2, "me"},{4, "tommorow"},{1, "please"}},
		{{0, ""}},
		{{0, "abcde"},{1, "123"}},
		{{0, "abcde"},{1, "123"},{1, "blabla"}},
	};
};

TEST(LinkedListTests, Test)
{
	for (auto& set : testSets)
	{
		FILE* file = fopen("myFile.bin", "wb");
		List listSz{};
		pushNodes(listSz, set);
		listSz.Serialize(file);
		fclose(file);
		file = fopen("myFile.bin", "rb");
		List listDsz{};
		listDsz.Deserialize(file);
		fclose(file);
		
		auto nodeDsz = listDsz.getHead();
		for (auto nodeSz = listSz.getHead(); ; nodeSz = nodeSz->next)
		{
			CHECK_EQUAL(nodeSz->data, nodeDsz->data);
			CHECK_EQUAL(nodeSz->rand->data, nodeDsz->rand->data);

			if (nodeSz == listSz.getTail()) break;
			nodeDsz = nodeDsz->next;
		}

	}
}
