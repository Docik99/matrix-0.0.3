#include <catch.hpp>
#include <sstream>
#include "matrix.hpp"
using namespace std;

TEST_CASE("creating matrix")
{
    matrix_t <int> matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("read and write")
{
    string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t <int> matrix;
    istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("a+b")
{
    string input1{
        "3, 3\n"
        "1.1 1.3 1.6\n"
        "2.2 2.5 2.1\n"
        "3.4 3.3 3.7" };
    matrix_t <float> matrix1;
    istringstream istream1{input1};
   
    string input2{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    matrix_t <float> matrix2;
    istringstream istream2{input2};
    
    string input3{
        "3, 3\n"
        "2.1 2.3 2.6\n"
        "3.2 3.5 3.1\n"
        "4.4 4.3 4.7" };
    matrix_t <float> matrix3;
    istringstream istream3{input3};
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix3 = matrix1 + matrix2;
    
    REQUIRE( matrix3.rows() == 3 );
    REQUIRE( matrix3.collumns() == 3 );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a-b")
{
    string input1{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
   
    string input2{
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    
    string input3{
        "3, 3\n"
        "0 0 0\n"
        "1 1 1\n"
        "2 2 2" };
    matrix_t <int> matrix3;
    istringstream istream3{input3};
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix3 = matrix1 - matrix2;
    
    REQUIRE( matrix3.rows() == 3 );
    REQUIRE( matrix3.collumns() == 3 );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a*b")
{
    string input1{
        "3, 4\n"
        "2 2 2 2\n"
        "2 2 2 2\n"
        "2 2 2 2" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
   
    string input2{
        "4, 2\n"
        "1 1\n"
        "1 1\n"
        "1 1\n"
        "1 1\n" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    
    string input3{
        "3, 2\n"
        "8 8\n"
        "8 8\n"
        "8 8" };
    matrix_t <int> matrix3;
    istringstream istream3{input3};
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix3 = matrix1 * matrix2;
    
    REQUIRE( matrix3.rows() == 3 );
    REQUIRE( matrix3.collumns() == 2 );
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a*=b")
{
    string input1{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
    string input2{
        "3, 2\n"
        "4 6\n"
        "5 3\n"
        "2 7" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    string input3{
        "3, 2\n"
        "11 16\n"
        "22 32\n"
        "33 48" };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix1 *= matrix2;
    REQUIRE( matrix1.rows() == 3 );
    REQUIRE( matrix1.collumns() == 2 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a+=b")
{
    string input1{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
    string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    string input3{
        "3, 3\n"
        "3 3 3\n"
        "4 4 4\n"
        "5 5 5" };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix1 += matrix2;
    REQUIRE( matrix1.rows() == 3 );
    REQUIRE( matrix1.collumns() == 3 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("a-=b")
{
    string input1{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
    string input2{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    string input3{
        "3, 3\n"
        "-1 -1 -1\n"
        "0 0 0\n"
        "1 1 1" };
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix1 -= matrix2;
    REQUIRE( matrix1.rows() == 3 );
    REQUIRE( matrix1.collumns() == 3 );
    
    ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}

TEST_CASE("dfgh"){
   string input1{
        "3, 4\n"
        "2 2 2 2\n"
        "2 2 2 2\n"
        "2 2 2 2" };
    matrix_t <int> matrix1;
    istringstream istream1{input1};
   
    string input2{
        "4, 2\n"
        "1 1\n"
        "1 1\n"
        "1 1\n"
        "1 1\n" };
    matrix_t <int> matrix2;
    istringstream istream2{input2};
    
    string input3{
        "3, 2\n"
        "8 8\n"
        "8 8\n"
        "8 8" };
    matrix_t <int> matrix3;
    istringstream istream3{input3};
    
    matrix1.read(istream1);
    matrix2.read(istream2);
    matrix3 = matrix1 * matrix2;
    
    ostringstream ostream;
    matrix3.write( ostream );
    
    REQUIRE( input3 == ostream.str());
}
