# CMake generated Testfile for 
# Source directory: /cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption
# Build directory: /cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/cmake-build-release/AES/decryption
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Decrypt_AddRoundKeyTest "DecryptTest_AddRoundKey")
set_tests_properties(Decrypt_AddRoundKeyTest PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;24;add_test;/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;0;")
add_test(Decrypt_InvSubBytesTest "DecryptTest_InvSubBytes")
set_tests_properties(Decrypt_InvSubBytesTest PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;25;add_test;/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;0;")
add_test(Decrypt_InvMixColumnsTest "DecryptTest_InvMixColumns")
set_tests_properties(Decrypt_InvMixColumnsTest PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;26;add_test;/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;0;")
add_test(Decrypt_InvShiftRowsTest "DecryptTest_InvShiftRows")
set_tests_properties(Decrypt_InvShiftRowsTest PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;27;add_test;/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;0;")
add_test(Decrypt_128bitKeyDecryptionTest "DecryptTest_128bitKeyDecryption")
set_tests_properties(Decrypt_128bitKeyDecryptionTest PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;28;add_test;/cygdrive/c/Users/Hendrik/CLionProjects/PS-ITAES/AES/decryption/CMakeLists.txt;0;")
subdirs("src")
subdirs("tests")
