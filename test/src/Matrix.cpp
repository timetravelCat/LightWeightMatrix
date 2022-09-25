#define CATCH_CONFIG_MAIN
#include <LightWeightMatrix/Matrix.hpp>
#include <catch2/catch.hpp>

TEST_CASE( "vectors can be sized and resized", "[lwm::Matrix]" ) {

    // Constructor build check
    float arr1[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    lwm::Matrix<float, 3, 2> matrix1{arr1};    
    float arr2[3][2] = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};
    lwm::Matrix<float, 3, 2> matrix2{arr2};
    double arr3[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    lwm::Matrix<float, 3, 2> matrix3{arr3};    
    double arr4[3][2] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    lwm::Matrix<float, 3, 2> matrix4{arr4};
    lwm::Matrix<double, 3, 2> matrix5;
    matrix4 = matrix3;
    matrix5 = matrix4;

    lwm::Matrix<int, 3, 2> matrix7;

    // How to not possible this method?
    printf("WTF? \n");
    float arr10[2][1];
    lwm::Matrix<float, 3, 2> matrix10{arr10, lwm::const_size_t<1>(), lwm::const_size_t<1>()};
    // matrix7.testfunc();

    SECTION( "Constructor Check" ) {
        

        // v.resize( 10 );

        // REQUIRE( v.size() == 10 );
        // REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        // v.resize( 0 );

        // REQUIRE( v.size() == 0 );
        // REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "reserving bigger changes capacity but not size" ) {
        // v.reserve( 10 );

        // REQUIRE( v.size() == 5 );
        // REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        // v.reserve( 0 );

        // REQUIRE( v.size() == 5 );
        // REQUIRE( v.capacity() >= 5 );
    }
}