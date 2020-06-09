#include "doctest.h"
#include "lists/DL.hpp"

using namespace exam::list;

TEST_CASE("DL") {
    DL<int> l;
    l.insert(1);
    l.insert(5);
    l.insert(2);
    l.insert(16);
    l.insert(0);

    DL<int>::Iterator it = l.begin();

    REQUIRE((*it == 1));
    REQUIRE((*++it == 5));
    REQUIRE((*--it == 1));
    REQUIRE((*l.end() == 0));
    REQUIRE((*--l.end() == 16));

    it = l.search(5);
    REQUIRE((*it == 5));

    l.remove(1);
    REQUIRE((*l.begin() == 5));
    
    it = l.search(1);
    REQUIRE((it.empty()));
}