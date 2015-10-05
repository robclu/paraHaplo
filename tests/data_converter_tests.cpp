// ----------------------------------------------------------------------------------------------------------
/// @file   data_checker_tests.cpp
/// @brief  Test suite for parahaplo data converter tets
// ----------------------------------------------------------------------------------------------------------

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
    #define BOOST_TEST_MODULE DataConverterTests
#endif
#include <boost/test/unit_test.hpp>
#include <vector>

#include "../haplo/data_converter.hpp"

#define ZERO    0x00
#define ONE     0x01
#define TWO     0x02


static constexpr const char* input_1    = "input_files/input_simulated_2.txt";
static constexpr const char* input_2    = "input_files/input_simulated_1.txt";
static constexpr const char* input_3    = "input_files/input_simulated_3.txt";
static constexpr const char* output_1   = "output_files/output_simulated_2.txt";

BOOST_AUTO_TEST_SUITE( DataConverterSuite )
    
BOOST_AUTO_TEST_CASE( canCreateDataConverter )
{
    haplo::DataConverter converter(input_1);
    
    //converter.print();

    converter.write_data_to_file(output_1);
}

BOOST_AUTO_TEST_CASE( canConvertDataFromBinary )
{
    
    haplo::DataConverter converter(input_1);
    converter.write_data_to_file(output_1);
    haplo::BinaryArray<30, 2> input;
    std::vector<char> output;
    for(size_t i = 0; i < 30; ++i){
        if(i % 2 == 0){
            input.set(i, ONE);
        }
        else if(i % 3 == 0){
            input.set(i, ZERO);
        }
        else {
            input.set(i, TWO);
        }
    }
    
    output = converter.convert_data_from_binary(input);
    
    std::cout << "Before:" << std::endl;
    for (auto i = 0; i < 30; ++i) std::cout << static_cast<unsigned>(input.get(i));
    
    std::cout << "After:" << std::endl;
    for (auto i = 0; i < 30; ++i) std::cout << output.at(i);
}


BOOST_AUTO_TEST_SUITE_END()
