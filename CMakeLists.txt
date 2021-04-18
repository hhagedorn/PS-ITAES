cmake_minimum_required(VERSION 3.17)
project(AES C)

set(CMAKE_C_STANDARD 11)

enable_testing()

add_subdirectory(AES)
add_subdirectory(Files)

add_executable(
        Encryption
        AES/encryption/src/mainEncryption.c
        AES/src/sBoxes/sBoxes.c AES/src/sBoxes/sBoxes.h
        AES/src/keyExpansion/keyExpansion.c AES/src/keyExpansion/keyExpansion.h
        AES/src/hexConversions/hexConversions.c                         AES/src/hexConversions/hexConversions.h
        AES/encryption/src/encryptionAlgorithm/encryptionAlgorithm.c    AES/encryption/src/encryptionAlgorithm/encryptionAlgorithm.h
        AES/encryption/src/resources/resources.c                        AES/encryption/src/resources/resources.h
        AES/encryption/src/encryptionAlgorithm/encryptionAlgorithm.c    AES/encryption/src/encryptionAlgorithm/encryptionAlgorithm.h
        AES/encryption/src/roundKeyTransformation/roundKeyTransformation.c AES/encryption/src/roundKeyTransformation/roundKeyTransformation.h
        AES/encryption/src/mixedColumnsTransformation/mixedColumnsTransformation.c AES/encryption/src/mixedColumnsTransformation/mixedColumnsTransformation.h
        AES/encryption/src/shiftRowsTransformation/shiftRowsTransformation.c AES/encryption/src/shiftRowsTransformation/shiftRowsTransformation.h
        AES/encryption/src/sBoxTransformation/sBoxTransformation.c AES/encryption/src/sBoxTransformation/sBoxTransformation.h
        AES/encryption/src/input/inputDialog/inputDialog.c              AES/encryption/src/input/inputDialog/inputDialog.h
        AES/encryption/src/output/outputDialog/outputDialog.c           AES/encryption/src/output/outputDialog/outputDialog.h
        AES/encryption/src/controlStructure/controlStructure.c AES/encryption/src/controlStructure/controlStructure.h
        AES/encryption/src/fileManagement/fileManagement.c              AES/encryption/src/fileManagement/fileManagement.h
        AES/src/charText.h AES/encryption/src/input/inputHandling/inputHandling.c AES/encryption/src/input/inputHandling/inputHandling.h
        AES/encryption/src/output/outputHandling/outputHandling.c AES/encryption/src/output/outputHandling/outputHandling.h)

add_executable(
        Decryption
        AES/decryption/src/decrypt_MAIN.c
        AES/decryption/src/inverseSBox/inverseSBox.c                    AES/decryption/src/inverseSBox/inverseSBox.h
        AES/decryption/src/decrypt_Services.c                           AES/decryption/src/decrypt_Services.h
        AES/decryption/src/decryption/decrypt_Decryption.h AES/decryption/src/decryption/decrypt_Decryption.c
        AES/src/keyExpansion/keyExpansion.c AES/src/keyExpansion/keyExpansion.h
        AES/src/sBoxes/sBoxes.c AES/src/sBoxes/sBoxes.h
        AES/decryption/src/decrypt_UserInterface.c AES/decryption/src/decrypt_UserInterface.h
        AES/src/hexConversions/hexConversions.c                         AES/src/hexConversions/hexConversions.h
        AES/decryption/src/fileManager/decrypt_FileManager.c            AES/decryption/src/fileManager/decrypt_FileManager.h
        AES/src/aes_config.h
        AES/src/charText.h
        )