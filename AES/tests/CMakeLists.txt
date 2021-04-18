add_executable(
        SBoxTest SBoxTest.c
        ../src/sBoxes/sBoxes.c ../src/sBoxes/sBoxes.h

)
add_executable(
        KeyExpansionTest KeyExpansionTest.c
        ../src/keyExpansion/keyExpansion.c ../src/keyExpansion/keyExpansion.h
        ../src/sBoxes/sBoxes.c ../src/sBoxes/sBoxes.h
)

add_executable(
        hexConversionTest
        hexConversionTest.c
        ../src/hexConversions/hexConversions.c ../src/hexConversions/hexConversions.h
)

add_library(test_library STATIC ../../lib/TestLibrary.c ../../lib/TestLibrary.h)
target_link_libraries(SBoxTest LINK_PUBLIC test_library)
target_link_libraries(KeyExpansionTest LINK_PUBLIC test_library)
target_link_libraries(hexConversionTest LINK_PUBLIC test_library)

add_test(SBox_Test SBoxTest)
add_test(KeyExpansion_Test KeyExpansionTest)
add_test(hexConversion_Test hexConversionTest)