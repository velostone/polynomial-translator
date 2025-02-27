#include "gtest.h"
#include "tlist.h"

TEST(ListTest, can_create_list) 
{
    Node<int>* node = new Node<int>(8, nullptr);
    ASSERT_NO_THROW(List<int> list(node));
}

TEST(ListTest, can_create_empty_list) 
{
    List<int> list;
    EXPECT_EQ(list.begin(), nullptr);
}

TEST(ListTest, can_push_front) 
{
    List<int> list;
    list.push_front(8);
    EXPECT_EQ(list.begin()->data, 8);
    list.push_front(16);
    EXPECT_EQ(list.begin()->data, 16);
}

TEST(ListTest, can_pop_front) 
{
    List<int> list;
    list.push_front(8);
    list.push_front(16);
    list.pop_front();
    EXPECT_EQ(list.begin()->data, 8);
}

TEST(ListTest, can_push_back) 
{
    List<int> list;
    list.push_back(8);
    EXPECT_EQ(list.begin()->data, 8);
}

TEST(ListTest, can_get_last) 
{
    List<int> list;
    list.push_back(8);
    EXPECT_EQ(list.get_last()->data, 8);
}

TEST(ListTest, can_copy_list) 
{
    List<int> list;
    list.push_back(8);
    list.push_back(16);
    List<int> list_cpy(list);
    EXPECT_EQ(list_cpy.begin()->data, 8);
    EXPECT_EQ(list_cpy.get_last()->data, 16);
}

TEST(ListTest, can_iterate_through_list) {
    List<int> list;
    list.push_back(8);
    list.push_back(16);
    list.push_back(24);
    List<int>::iterator it = list.begin();
    EXPECT_EQ(*it, 8);
    ++it;
    EXPECT_EQ(*it, 16);
    ++it;
    EXPECT_EQ(*it, 24);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, can_insert_elem) 
{
    List<int> list;
    list.push_back(8);
    list.push_back(16);
    List<int>::iterator it = list.begin();
    EXPECT_EQ(*it, 8);
    list.insert(24, it.get_current());
    it++;
    EXPECT_EQ(*it, 24);
    it++;
    EXPECT_EQ(*it, 16);
}

TEST(ListTest, can_erase_elem) 
{
    List<int> list;
    list.push_back(8);
    list.push_back(16);
    List<int>::iterator it = list.begin();
    list.erase(it.get_current());
    EXPECT_EQ(list.begin()->data, 8);
}