cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(DecryptTest_AddRoundKey
        tests/AddRoundKey_DecryptTest.c)

add_executable(DecryptTest_InvSubBytes
        tests/InvSubBytes_DecryptTest.c)

add_executable(DecryptTest_InvMixColumns
        tests/InvMixColumns_DecryptTest.c)

add_executable(DecryptTest_InvShiftRows
        tests/InvShiftRows_DecryptTest.c)

add_executable(DecryptTest_128bitKeyDecryption
        tests/128bitDecryption_DecryptTest.c)


add_test(Decrypt_AddRoundKeyTest DecryptTest_AddRoundKey)
add_test(Decrypt_InvSubBytesTest DecryptTest_InvSubBytes)
add_test(Decrypt_InvMixColumnsTest DecryptTest_InvMixColumns)
add_test(Decrypt_InvShiftRowsTest DecryptTest_InvShiftRows)
add_test(Decrypt_128bitKeyDecryptionTest DecryptTest_128bitKeyDecryption)

