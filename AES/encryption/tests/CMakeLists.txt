cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_STANDARD 11)

#Add round key test
add_executable(
        roundKeyTest roundKeyTest.c
        ../../src/keyExpansion/keyExpansion.c ../../src/keyExpansion/keyExpansion.h
        ../../src/sBoxes/sBoxes.c ../../src/sBoxes/sBoxes.h
        ../src/resources/resources.c ../src/resources/resources.h
        ../src/roundKeyTransformation/roundKeyTransformation.c ../src/roundKeyTransformation/roundKeyTransformation.h
)

add_test(Encryption_roundKey_Test roundKeyTest)

#Apply sBoxTransformation test
add_executable(
        applySBoxTest applySBoxTest.c
        ../../src/keyExpansion/keyExpansion.c ../../src/keyExpansion/keyExpansion.h
        ../../src/sBoxes/sBoxes.c ../../src/sBoxes/sBoxes.h
        ../src/resources/resources.c ../src/resources/resources.h
        ../src/sBoxTransformation/sBoxTransformation.c ../src/sBoxTransformation/sBoxTransformation.h
)

add_test(Encryption_applySBox_Test applySBoxTest)

#Shift row test
add_executable(
        ShiftRowTest ShiftRowLayerTest.c
        ../src/shiftRowsTransformation/shiftRowsTransformation.c ../src/shiftRowsTransformation/shiftRowsTransformation.h
)
add_test(Encryption_ShiftRow_Test ShiftRowTest)

#mixed column test
add_executable(
        MixedColumnTest MixedColumnLayerTest.c
        ../src/mixedColumnsTransformation/mixedColumnsTransformation.c ../src/mixedColumnsTransformation/mixedColumnsTransformation.h
)
add_test(Encryption_MixedColumn_Test MixedColumnTest)

#Encryption algorithm test
add_executable(
        encryptionAlgorithmTest encryptionAlgorithmTest.c
        ../src/encryptionAlgorithm/encryptionAlgorithm.c ../src/encryptionAlgorithm/encryptionAlgorithm.h
        ../../src/keyExpansion/keyExpansion.c ../../src/keyExpansion/keyExpansion.h
        ../../src/sBoxes/sBoxes.c ../../src/sBoxes/sBoxes.h
        ../src/roundKeyTransformation/roundKeyTransformation.c ../src/roundKeyTransformation/roundKeyTransformation.h
        ../src/sBoxTransformation/sBoxTransformation.c ../src/sBoxTransformation/sBoxTransformation.h
        ../src/shiftRowsTransformation/shiftRowsTransformation.c ../src/shiftRowsTransformation/shiftRowsTransformation.c
        ../src/mixedColumnsTransformation/mixedColumnsTransformation.c ../src/mixedColumnsTransformation/mixedColumnsTransformation.h
        ../src/resources/resources.c ../src/resources/resources.h
)
add_test(Encryption_encryptionAlgorithm_Test encryptionAlgorithmTest)


#Control structure encryptionTest
add_executable(
        ControlStructureEncryptionTest ControlStructureEncryptionTest.c
        ../src/controlStructure/controlStructure.c ../src/controlStructure/controlStructure.c
        ../src/encryptionAlgorithm/encryptionAlgorithm.c ../src/encryptionAlgorithm/encryptionAlgorithm.h
        ../../src/keyExpansion/keyExpansion.c ../../src/keyExpansion/keyExpansion.h
        ../../src/hexConversions/hexConversions.c ../../src/hexConversions/hexConversions.h
        ../../src/sBoxes/sBoxes.c ../../src/sBoxes/sBoxes.h
        ../src/roundKeyTransformation/roundKeyTransformation.c ../src/roundKeyTransformation/roundKeyTransformation.h
        ../src/sBoxTransformation/sBoxTransformation.c ../src/sBoxTransformation/sBoxTransformation.h
        ../src/shiftRowsTransformation/shiftRowsTransformation.c ../src/shiftRowsTransformation/shiftRowsTransformation.c
        ../src/mixedColumnsTransformation/mixedColumnsTransformation.c ../src/mixedColumnsTransformation/mixedColumnsTransformation.h
        ../src/resources/resources.c ../src/resources/resources.h
        ../src/input/inputDialog/inputDialog.c              ../src/input/inputDialog/inputDialog.h
        ../src/output/outputDialog/outputDialog.c           ../src/output/outputDialog/outputDialog.h
        ../src/fileManagement/fileManagement.c              ../src/fileManagement/fileManagement.h
        ../src/input/inputHandling/inputHandling.c ../src/input/inputHandling/inputHandling.h
        ../src/output/outputHandling/outputHandling.c ../src/output/outputHandling/outputHandling.h
        ../../src/charText.h
)

add_test(ControlStructureEncryption_Test ControlStructureEncryptionTest)

target_link_libraries(roundKeyTest LINK_PUBLIC test_library)
target_link_libraries(applySBoxTest LINK_PUBLIC test_library)
target_link_libraries(ShiftRowTest LINK_PUBLIC test_library)
target_link_libraries(MixedColumnTest LINK_PUBLIC test_library)
target_link_libraries(encryptionAlgorithmTest LINK_PUBLIC test_library)
target_link_libraries(ControlStructureEncryptionTest LINK_PUBLIC test_library)