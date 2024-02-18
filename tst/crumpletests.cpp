#include <CrumpleTree.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <vector>

namespace {
namespace proj4 = shindler::ics46::project4;

/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY.

*/

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
// readability-magic-numbers)
TEST_CASE("Tree:SimpleInsertAndFind:ExpectSingleInsertFound",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE(tree.contains(5));
}

TEST_CASE("Tree:DoubleInsert:ExpectFindSecondInsert",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE(tree.contains(10));
}

TEST_CASE("Tree:QuadInsert:ExpectFindFindTwoHopsAway",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE(tree.contains(12));
}

TEST_CASE("Tree:5Inserts:ExpectSize5", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE(tree.size() == 5);
}

TEST_CASE("Tree:DoAPostOrder:ExpectCorrectPostorderTraversal",
          "[Required][Basic][Insert][PostOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    static const std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrect",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(12));
    REQUIRE(tree.contains(9));
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and
    // remains at level 3.
    REQUIRE(!tree.contains(9));
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(12) == 1);
    REQUIRE(tree.level(19) == 3);
}
// NOLINTEND

// <--------------------Extra Tests-------------------->
TEST_CASE("Tree:SimpleFind:ExpectSingleInsertFoundAndConstVersion",
          "[Extra][Basic][Find][Const]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE(tree.find(5) == "foo");

    const proj4::CrumpleTree<int, std::string> &treeRef= tree;
    REQUIRE(treeRef.find(5) == "foo");
}

TEST_CASE("Tree:SimpleInOrder",
          "[Extra][Basic][InOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "fizz");
    tree.insert(10, "bar");
    std::vector<int> expect =  {3, 5, 10};
    REQUIRE(tree.inOrder() == expect);
}

TEST_CASE("Tree:SimplePreOrder",
          "[Extra][Basic][PreOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "fizz");
    tree.insert(10, "bar");
    std::vector<int> expect =  {5, 3, 10};
    REQUIRE(tree.preOrder() == expect);
}

TEST_CASE("Tree:WholeInsertionLogic",
          "[Extra][Insert][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    // insert 20
    tree.insert(20, "are");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.contains(20));

    // insert 19
    tree.insert(19, "you");
    REQUIRE(tree.level(20) == 2);
    REQUIRE(tree.level(19) == 1);
    REQUIRE(tree.contains(19));

    // insert 18
    tree.insert(18, "following");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.contains(18));

    // insert 12
    tree.insert(12, "from");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 3);
    REQUIRE(tree.level(18) == 2);
    REQUIRE(tree.level(12) == 1);
    REQUIRE(tree.contains(12));

    // insert 9
    tree.insert(9, "lecture?");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 3);
    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(12) == 2);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.contains(9));

    // insert 17 (rearrange)
    tree.insert(17, "yoo");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(12) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(18) == 3);
    REQUIRE(tree.contains(17));

    // insert 7
    tree.insert(7, "broke");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(7) == 1);
    REQUIRE(tree.level(9) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.contains(7));

    // insert 5
    tree.insert(5, "tire");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(5) == 1);
    REQUIRE(tree.level(7) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.contains(5));

    // insert 13, 15
    tree.insert(13, "uhhhhh");
    REQUIRE(tree.contains(13));
    tree.insert(15, "commmonnnnn");
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(5) == 1);
    REQUIRE(tree.level(7) == 2);
    REQUIRE(tree.level(15) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.contains(15));

    // insert 6
    tree.insert(6, "gimmeeee");
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(15) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(18) == 3);
    REQUIRE(tree.level(12) == 4);
    REQUIRE(tree.contains(6));

    // insert 16
    tree.insert(16, "internnnn");
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(16) == 1);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(15) == 3);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 5);
    REQUIRE(tree.contains(16));

    // insert 14
    tree.insert(14, "offeeeerrrrr");
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(14) == 1);
    REQUIRE(tree.level(16) == 1);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(13) == 2);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(15) == 3);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 5);
    REQUIRE(tree.contains(14));
}

TEST_CASE("Tree:OtherInsertionInCludeMirroringOfLeft",
          "[Extra][Insert][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(22, "day1");
    tree.insert(23, "day2");
    tree.insert(24, "day3");
    tree.insert(25, "day4");
    tree.insert(26, "day5");
    tree.insert(27, "day6");
    tree.insert(28, "day7");
    REQUIRE(tree.level(22) == 1);
    REQUIRE(tree.level(24) == 1);
    REQUIRE(tree.level(26) == 1);
    REQUIRE(tree.level(28) == 1);
    REQUIRE(tree.level(23) == 2);
    REQUIRE(tree.level(27) == 2);
    REQUIRE(tree.level(25) == 3);

    proj4::CrumpleTree<int, std::string> tree2;
    tree2.insert(20, "c");
    tree2.insert(21, "r");
    tree2.insert(22, "u");
    tree2.insert(28, "m");
    tree2.insert(31, "p");
    tree2.insert(23, "le?");
    REQUIRE(tree2.level(20) == 1);
    REQUIRE(tree2.level(23) == 1);
    REQUIRE(tree2.level(31) == 1);
    REQUIRE(tree2.level(21) == 2);
    REQUIRE(tree2.level(28) == 2);
    REQUIRE(tree2.level(22) == 3);

    tree2.insert(33, "huhh");
    tree2.insert(35, "whatttt");
    tree2.insert(27, "noo i want...");
    tree2.insert(25, "SWEEEEEEE");
    REQUIRE(tree2.level(20) == 1);
    REQUIRE(tree2.level(23) == 1);
    REQUIRE(tree2.level(27) == 1);
    REQUIRE(tree2.level(31) == 1);
    REQUIRE(tree2.level(35) == 1);
    REQUIRE(tree2.level(21) == 2);
    REQUIRE(tree2.level(25) == 2);
    REQUIRE(tree2.level(33) == 2);
    REQUIRE(tree2.level(28) == 3);
    REQUIRE(tree2.level(22) == 4);

    tree2.insert(34, "INT..");
    tree2.insert(24, "ERNNN...");
    tree2.insert(26, "and RESEARCH PLZZZZZ");
    REQUIRE(tree2.level(20) == 1);
    REQUIRE(tree2.level(24) == 1);
    REQUIRE(tree2.level(26) == 1);
    REQUIRE(tree2.level(31) == 1);
    REQUIRE(tree2.level(34) == 1);
    REQUIRE(tree2.level(21) == 2);
    REQUIRE(tree2.level(23) == 2);
    REQUIRE(tree2.level(27) == 2);
    REQUIRE(tree2.level(35) == 2);
    REQUIRE(tree2.level(25) == 3);
    REQUIRE(tree2.level(33) == 3);
    REQUIRE(tree2.level(22) == 4);
    REQUIRE(tree2.level(28) == 5);
}

TEST_CASE("Tree:OtherRemove",
          "[Extra][Remove][Contains][Level]") {
    // if tree is empty and key not in the tree
    proj4::CrumpleTree<int, std::string> tree1;
    tree1.remove(3);
    
    // extra test for the required test case
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(12));
    REQUIRE(tree.contains(9));
    tree.remove(9);
    tree.remove(18);
    tree.remove(12);
    REQUIRE(!tree.contains(9));
    REQUIRE(!tree.contains(18));
    REQUIRE(!tree.contains(12));
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 2);

    // other test cases
    proj4::CrumpleTree<int, std::string> anotherTree;
    anotherTree.insert(20, "are");
    anotherTree.insert(19, "you");
    anotherTree.insert(18, "following");
    anotherTree.insert(12, "from");
    anotherTree.insert(9, "lecture?");
    anotherTree.insert(17, "holdonnn");
    anotherTree.remove(18);

}
} // namespace