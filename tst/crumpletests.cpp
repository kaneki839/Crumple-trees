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
    tree.insert(15, "noooo");
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
    tree.insert(6, "internnnn");
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
    tree.insert(16, "gimmeeee");
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

    //
}

} // namespace