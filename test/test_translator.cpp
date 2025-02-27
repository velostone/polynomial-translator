#include "gtest.h"
#include "polynomial_translator.h"

class MonomTestF : public ::testing::Test
{
protected:
    Monom* m;
public:
    void SetUp()
    {
        m = new Monom(358, 5.5);
    }
    void TearDown()
    {
        delete m;
    }
};

TEST(MonomTest, can_create_monom)
{
    ASSERT_NO_THROW(Monom m(5, 3.8));
}

TEST(MonomTest, can_create_zero_monom)
{
    ASSERT_NO_THROW(Monom m);
}

TEST(MonomTest, cant_create_monom_with_too_large_degree)
{
    ASSERT_ANY_THROW(Monom(1100, 5));
}

TEST_F(MonomTestF, can_get_x_degree) 
{
    EXPECT_EQ(this->m->x_deg(), 3);
}

TEST_F(MonomTestF, can_get_y_degree) 
{
    EXPECT_EQ(this->m->y_deg(), 5);
}

TEST_F(MonomTestF, can_get_z_degree) 
{
    EXPECT_EQ(this->m->z_deg(), 8);
}

TEST_F(MonomTestF, can_check_degree_is_correct) 
{
    EXPECT_TRUE(this->m->is_deg_correct());
}

TEST_F(MonomTestF, can_addict_monoms)
{
    Monom op(358, 3.4);
    Monom res = *(this->m) + op;
    EXPECT_EQ(res.get_deg(), 358);
    EXPECT_EQ(res.get_k(), 8.9);
}

TEST_F(MonomTestF, cant_addict_monoms_with_diff_pows)
{
    Monom op(314, 3.4);
    ASSERT_ANY_THROW(*(this->m) + op);
}

TEST_F(MonomTestF, addiction_can_create_zero_monom)
{
    Monom op(358, -5.5);
    Monom res = *(this->m) + op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_k(), 0);
}

TEST_F(MonomTestF, can_diff_monoms)
{
    Monom op(358, 2.5);
    Monom res = *(this->m) - op;
    EXPECT_EQ(res.get_deg(), 358);
    EXPECT_EQ(res.get_k(), 3);
}

TEST_F(MonomTestF, cant_diff_monoms_with_diff_pows)
{
    Monom op(314, 2.5);
    ASSERT_ANY_THROW(*(this->m) - op);
}

TEST_F(MonomTestF, dif_can_create_zero_monom)
{
    Monom op(358, 5.5);
    Monom res = *(this->m) - op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_k(), 0);
}

TEST_F(MonomTestF, can_mult_with_scalar) 
{
    Monom res = *(this->m) * 5;
    EXPECT_EQ(res.get_deg(), 358);
    EXPECT_EQ(res.get_k(), 27.5);
}

TEST_F(MonomTestF, can_mult_with_zero_scalar)
{
    Monom res = *(this->m) * 0;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_k(), 0);
}

TEST_F(MonomTestF, can_mult_monoms) 
{
    Monom op(441, 2);
    Monom res = *(this->m) * op;
    EXPECT_EQ(res.get_deg(), 799);
    EXPECT_EQ(res.get_k(), 11);
}

TEST_F(MonomTestF, mult_throw_then_degree_is_out_of_range)
{
    Monom op(451, 2);
    ASSERT_ANY_THROW(*(this->m) * op);
}

TEST_F(MonomTestF, mult_can_create_zero_monom)
{
    Monom op(441, 0);
    Monom res = *(this->m) * op;
    EXPECT_EQ(res.get_deg(), 0);
    EXPECT_EQ(res.get_k(), 0);
}

class PolynomTestF : public ::testing::Test
{
protected:
    Polynom* p1, * p2;
public:
    void SetUp()
    {
        p1 = new Polynom;
        (*p1).push_back(Monom(102, -3));
        (*p1).push_back(Monom(137, 1.5));
        p2 = new Polynom;
        (*p2).push_back(Monom(102, 2));
        (*p2).push_back(Monom(721, -10));
        (*p2).push_back(Monom(300, 0.5));

    }
    void TearDown()
    {
        delete p1;
        delete p2;
    }
};

TEST(PolynomTest, can_create_polynom)
{
    ASSERT_NO_THROW(Polynom p);
}

TEST_F(PolynomTestF, can_addict_polynoms) {
    Polynom res = *(this->p1) + *(this->p2);

    List<Monom>::iterator it = res.begin()->next;

    EXPECT_EQ((*it).get_deg(), 102);
    EXPECT_EQ((*it).get_k(), -1);
    
    ++it;
    EXPECT_EQ((*it).get_deg(), 721);
    EXPECT_EQ((*it).get_k(), -10);

    ++it;
    EXPECT_EQ((*it).get_deg(), 300);
    EXPECT_EQ((*it).get_k(), 0.5);

    ++it;
    EXPECT_EQ((*it).get_deg(), 137);
    EXPECT_EQ((*it).get_k(), 1.5);
}

TEST_F(PolynomTestF, can_mult_with_scalar) 
{
    Polynom res = *(this->p1) * 2;

    List<Monom>::iterator it = res.begin()->next;
    EXPECT_EQ((*it).get_deg(), 102);
    EXPECT_EQ((*it).get_k(), -6);

    ++it;
    EXPECT_EQ((*it).get_deg(), 137);
    EXPECT_EQ((*it).get_k(), 3);
}


TEST_F(PolynomTestF, can_mult_polynoms) 
{
    Polynom res = *(this->p1) * *(this->p2);

    List<Monom>::iterator it = res.begin()->next;
    EXPECT_EQ((*it).get_deg(), 204);
    EXPECT_EQ((*it).get_k(), -6);

    ++it;
    EXPECT_EQ((*it).get_deg(), 823);
    EXPECT_EQ((*it).get_k(), 30);

    ++it;
    EXPECT_EQ((*it).get_deg(), 402);
    EXPECT_EQ((*it).get_k(), -1.5);

    ++it;
    EXPECT_EQ((*it).get_deg(), 239);
    EXPECT_EQ((*it).get_k(), 3);

    ++it;
    EXPECT_EQ((*it).get_deg(), 858);
    EXPECT_EQ((*it).get_k(), -15);

    ++it;
    EXPECT_EQ((*it).get_deg(), 437);
    EXPECT_EQ((*it).get_k(), 0.75);
}