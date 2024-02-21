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

    // other test cases (including case 1 and 2)
    proj4::CrumpleTree<int, std::string> anotherTree;
    anotherTree.insert(20, "are");
    anotherTree.insert(19, "you");
    anotherTree.insert(18, "following");
    anotherTree.insert(12, "from");
    anotherTree.insert(9, "lecture?");
    anotherTree.insert(17, "holdonnn");
    anotherTree.remove(18);
    REQUIRE(anotherTree.level(20) == 1);
    REQUIRE(anotherTree.level(17) == 1);
    REQUIRE(anotherTree.level(9) == 1);
    REQUIRE(anotherTree.level(12) == 2);
    REQUIRE(anotherTree.level(19) == 3);


    proj4::CrumpleTree<int, std::string> treetree;
    treetree.insert(20, "c");
    treetree.insert(21, "r");
    treetree.insert(22, "u");
    treetree.insert(28, "m");
    treetree.insert(31, "p");
    treetree.insert(23, "le?");
    treetree.insert(33, "emmm");
    treetree.insert(35, "whatttt");
    treetree.insert(27, "noo i want...");
    treetree.insert(25, "SWEEEEEEE");
    treetree.insert(34, "INT..");
    treetree.insert(24, "ERNNN...");
    treetree.insert(26, "hjb");

    // Case 3
    treetree.remove(21);
    REQUIRE(treetree.level(20) == 1);
    REQUIRE(treetree.level(24) == 1);
    REQUIRE(treetree.level(26) == 1);
    REQUIRE(treetree.level(31) == 1);
    REQUIRE(treetree.level(34) == 1);
    REQUIRE(treetree.level(23) == 2);
    REQUIRE(treetree.level(27) == 2);
    REQUIRE(treetree.level(35) == 2);
    REQUIRE(treetree.level(22) == 3);
    REQUIRE(treetree.level(33) == 3);
    REQUIRE(treetree.level(25) == 4);
    REQUIRE(treetree.level(28) == 5);

    // Case 4A and 4B
    treetree.remove(20);
    REQUIRE(treetree.level(22) == 1);
    REQUIRE(treetree.level(24) == 1);
    REQUIRE(treetree.level(26) == 1);
    REQUIRE(treetree.level(31) == 1);
    REQUIRE(treetree.level(34) == 1);
    REQUIRE(treetree.level(23) == 2);
    REQUIRE(treetree.level(27) == 2);
    REQUIRE(treetree.level(35) == 2);
    REQUIRE(treetree.level(33) == 3);
    REQUIRE(treetree.level(25) == 4);
    REQUIRE(treetree.level(28) == 5);
}

TEST_CASE("Tree:11thInClass: remove 87",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(44, 1);
   tree.insert(17, 43); 
   tree.insert(78, 41);    
   tree.insert(32, 4);    
   tree.insert(87, 55);    
   tree.insert(50, 132);    
   tree.insert(48, 99);    
   tree.insert(62, 100);    
   tree.remove(87);
   
   REQUIRE(!tree.contains(87));
   REQUIRE(tree.size() == 7);
   REQUIRE(tree.level(50) == 3);   
   REQUIRE(tree.level(78) == 2); 
   REQUIRE(tree.level(17) == 2); 
   REQUIRE(tree.level(32) == 1); 
   REQUIRE(tree.level(48) == 1); 
   REQUIRE(tree.level(62) == 1); 
   REQUIRE(tree.level(44) == 4); 
}

TEST_CASE("Tree:12thInClass: remove 62 & 87",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(44, 1);
   tree.insert(17, 43); 
   tree.insert(78, 41);    
   tree.insert(32, 4);    
   tree.insert(87, 55);    
   tree.insert(50, 132);    
   tree.insert(48, 99);    
   tree.insert(62, 100);   
   tree.remove(62);
   tree.remove(87);

   REQUIRE(!tree.contains(62));
   REQUIRE(!tree.contains(87));
   REQUIRE(tree.size() == 6);
   REQUIRE(tree.level(44) == 4);
   REQUIRE(tree.level(17) == 2); 
   REQUIRE(tree.level(32) == 1);
   REQUIRE(tree.level(48) == 1);
   REQUIRE(tree.level(50) == 2);   
   REQUIRE(tree.level(78) == 1); 
}

TEST_CASE("Tree:13thInClass: remove 48 & 62",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(44, 1);
   tree.insert(17, 43); 
   tree.insert(78, 41);    
   tree.insert(32, 4);    
   tree.insert(87, 55);    
   tree.insert(50, 132);    
   tree.insert(48, 99);    
   tree.insert(62, 100);   
   tree.remove(48);
   tree.remove(62);

   REQUIRE(!tree.contains(62));
   REQUIRE(!tree.contains(48));
   REQUIRE(tree.size() == 6);
   REQUIRE(tree.level(50) == 1);  
   REQUIRE(tree.level(78) == 3); 
   REQUIRE(tree.level(17) == 2); 
   REQUIRE(tree.level(32) == 1); 
   REQUIRE(tree.level(87) == 1); 
   REQUIRE(tree.level(44) == 4);  
}

TEST_CASE("Tree:14thInClass: remove 87 after 12thInClass",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(44, 1);
   tree.insert(17, 43); 
   tree.insert(78, 41);    
   tree.insert(32, 4);    
   tree.insert(87, 55);    
   tree.insert(50, 132);    
   tree.insert(48, 99);    
   tree.insert(62, 100);   
   tree.remove(48);
   tree.remove(62);
   tree.remove(87);

   REQUIRE(!tree.contains(87));
   REQUIRE(tree.size() == 5);
   REQUIRE(tree.level(50) == 1);    
   REQUIRE(tree.level(78) == 2);  
   REQUIRE(tree.level(17) == 2); 
   REQUIRE(tree.level(32) == 1);   
   REQUIRE(tree.level(44) == 4); 
}

TEST_CASE("Tree:15thInClass: remove 50 after 13thInClass",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(44, 1);
   tree.insert(17, 43); 
   tree.insert(78, 41);    
   tree.insert(32, 4);    
   tree.insert(87, 55);    
   tree.insert(50, 132);    
   tree.insert(48, 99);    
   tree.insert(62, 100);   
   tree.remove(48);
   tree.remove(62);
   tree.remove(87);
   tree.remove(50);

   REQUIRE(!tree.contains(50));
   REQUIRE(tree.size() == 4);
   REQUIRE(tree.level(17) == 2);    
   REQUIRE(tree.level(32) == 1);    
   REQUIRE(tree.level(44) == 3);    
   REQUIRE(tree.level(78) == 1);    
}

TEST_CASE("Tree:16thInClass: number",
         "[InClass][Insert][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);    
   tree.insert(12, 55);    
   tree.insert(18, 132);    
   tree.insert(20, 99);    

   REQUIRE(tree.level(10) == 4);
   REQUIRE(tree.level(15) == 3);
   REQUIRE(tree.level(18) == 2);
   REQUIRE(tree.level(2) == 1);
   REQUIRE(tree.level(5) == 2);
   REQUIRE(tree.level(12) == 1);
   REQUIRE(tree.level(20) == 1); 
}

TEST_CASE("Tree:17thInClass: remove 2",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);    
   tree.insert(12, 55);    
   tree.insert(18, 132);    
   tree.insert(20, 99);    
   tree.remove(2);

   REQUIRE(!tree.contains(2));
   REQUIRE(tree.level(10) == 3);
   REQUIRE(tree.level(15) == 4);
   REQUIRE(tree.level(18) == 2);
   REQUIRE(tree.level(5) == 1);
   REQUIRE(tree.level(12) == 1);
   REQUIRE(tree.level(20) == 1); 
}

TEST_CASE("Tree:18thInClass: number",
         "[InClass][Insert][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);    
   tree.insert(12, 55);    
   tree.insert(20, 132);    
   tree.insert(11, 99);    
   tree.insert(13, 99);       

   REQUIRE(tree.level(10) == 4);
   REQUIRE(tree.level(15) == 3);
   REQUIRE(tree.level(11) == 1);
   REQUIRE(tree.level(2) == 1);
   REQUIRE(tree.level(5) == 2);
   REQUIRE(tree.level(12) == 2);
   REQUIRE(tree.level(13) == 1); 
   REQUIRE(tree.level(20) == 1); 
}

TEST_CASE("Tree:19thInClass: remove 2",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);    
   tree.insert(12, 55);    
   tree.insert(20, 132);    
   tree.insert(11, 99);    
   tree.insert(13, 100);       
   tree.remove(2); 

   REQUIRE(!tree.contains(2));
   REQUIRE(tree.size() == 7);
   REQUIRE(tree.level(10) == 2);
   REQUIRE(tree.level(15) == 2);
   REQUIRE(tree.level(11) == 1);
   REQUIRE(tree.level(5) == 1);
   REQUIRE(tree.level(12) == 4);
   REQUIRE(tree.level(13) == 1); 
   REQUIRE(tree.level(20) == 1); 
}

TEST_CASE("Tree:20thInClass: number",
         "[InClass][Insert][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);       
   tree.insert(20, 132);    
   tree.insert(11, 99);         

   REQUIRE(tree.size() == 6);
   REQUIRE(tree.level(10) == 3);
   REQUIRE(tree.level(15) == 2);
   REQUIRE(tree.level(11) == 1);
   REQUIRE(tree.level(5) == 2);
   REQUIRE(tree.level(20) == 1); 
   REQUIRE(tree.level(2) == 1); 
}

TEST_CASE("Tree:21thInClass: remove 2",
         "[InClass][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);       
   tree.insert(20, 132);    
   tree.insert(11, 99);         
   tree.remove(2); 

   REQUIRE(!tree.contains(2));
   REQUIRE(tree.size() == 5);
   REQUIRE(tree.level(10) == 3);
   REQUIRE(tree.level(15) == 2);
   REQUIRE(tree.level(11) == 1);
   REQUIRE(tree.level(5) == 1);
   REQUIRE(tree.level(20) == 1); 
}

TEST_CASE("Tree:1000001Elements:ExpectInsertedCorrectly",
          "[Additional][Insert][Contains]") {
    proj4::CrumpleTree<unsigned, unsigned> tree;
    for (size_t i{0}; i < 1000001; i++) {
        tree.insert(i, i);
        REQUIRE(tree.contains(i));
    }
    REQUIRE(tree.size() == 1000001); 
    REQUIRE(tree.level(524287) == 20);
    REQUIRE(tree.level(786431) == 19);
    REQUIRE(tree.level(262143) == 19);
}

TEST_CASE("Tree:DeleteEdgeCase",
          "[Additional][Delete][Contains]") {
      proj4::CrumpleTree<int, int> tree;
      tree.insert(43, 0);
      tree.insert(65, 0);
      tree.insert(34, 0);
      tree.insert(6, 0);
      tree.insert(3, 0);
      tree.insert(5, 0);
      tree.insert(76, 0);
      tree.insert(45, 0);
      tree.insert(10, 0);
      tree.insert(83, 0);
      tree.insert(78, 0);
      tree.insert(44, 0);
      tree.insert(99, 0);
      tree.remove(3);
      tree.remove(45);
      tree.remove(78);
      REQUIRE(tree.level(5) == 1);
      REQUIRE(tree.level(10) == 1);
      REQUIRE(tree.level(44) == 1);
      REQUIRE(tree.level(76) == 1);
      REQUIRE(tree.level(99) == 1);
      REQUIRE(tree.level(34) == 2);
      REQUIRE(tree.level(65) == 2);
      REQUIRE(tree.level(6) == 3);
      REQUIRE(tree.level(83) == 3);
      REQUIRE(tree.level(43) == 5);
}

TEST_CASE("Tree:moreInsertandRemove:",
         "[Extra][Remove][Contains][Level]") {
   proj4::CrumpleTree<int, int> tree;
   tree.insert(10, 1);
   tree.insert(5, 43); 
   tree.insert(15, 41);    
   tree.insert(2, 4);       
   tree.insert(20, 132);    
   tree.insert(11, 99);
   tree.insert(3, 99); 
   tree.insert(6, 99); 
   tree.insert(7, 99); 
   tree.insert(25, 99); 
   tree.insert(67, 99); 
   tree.insert(34, 99); 
   tree.insert(56, 99); 
   tree.insert(72, 99); 
   tree.insert(58, 99); 

   REQUIRE(tree.find(7) == 99);
   REQUIRE(tree.size() == 15);

   tree.remove(2);
   tree.remove(56); 
   REQUIRE(tree.level(58) == 3);
   
   tree.remove(6);
   REQUIRE(tree.level(25) == 4);
   REQUIRE(tree.level(10) == 5);
   REQUIRE(tree.level(5) == 3);
   REQUIRE(tree.level(3) == 1);
   REQUIRE(tree.level(7) == 1);
   
   tree.remove(34);
   REQUIRE(tree.level(67) == 2);
   REQUIRE(tree.level(58) == 1);

   tree.remove(25);
   REQUIRE(tree.level(58) == 4);

   tree.remove(20);
   REQUIRE(!tree.contains(20));

   // single delete
   proj4::CrumpleTree<int, int> tree1;
   tree1.insert(1, 1);
   REQUIRE(tree1.contains(1));
   tree1.remove(1);
   REQUIRE(!tree1.contains(1));

   // random insert/delete
   proj4::CrumpleTree<int, int> tree2;
   tree2.insert(20, 0);
   tree2.insert(13, 0);
   tree2.insert(3, 0);
   tree2.insert(4, 0);
   tree2.insert(2, 0);
   tree2.insert(1, 0);
   tree2.insert(9, 0);
   tree2.insert(490, 0);
   tree2.insert(38, 0);
   tree2.insert(4900, 0);
   REQUIRE(tree2.level(1) == 1);
   REQUIRE(tree2.level(9) == 1);
   REQUIRE(tree2.level(20) == 1);
   REQUIRE(tree2.level(4900) == 1);
   REQUIRE(tree2.level(2) == 2);
   REQUIRE(tree2.level(4) == 2);
   REQUIRE(tree2.level(490) == 2);
   REQUIRE(tree2.level(3) == 3);
   REQUIRE(tree2.level(38) == 3);
   REQUIRE(tree2.level(13) == 4);
   tree2.remove(38);
   tree2.remove(490);
   tree2.remove(3);
   tree2.remove(4);
   REQUIRE(tree2.level(1) == 1);
   REQUIRE(tree2.level(9) == 1);
   REQUIRE(tree2.level(20) == 1);
   REQUIRE(tree2.level(2) == 2);
   REQUIRE(tree2.level(4900) == 2);
   REQUIRE(tree2.level(13) == 4);
}

} // namespace