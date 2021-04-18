# Readme 
This Version of the AES in C is being created as part of a project seminar at the Research Group for Cyber Security, University of Münster.

## Usage Guide
*For further information in which technical environments the program can be securely compiled and run, please see the "Usage Guide" section of the provided documentation. This also entails a detailed description of the interfaces and can be found in the directory "Thesis and Documentation"*

In order to demonstrate how the product can be used, an exemplary build is given in the directory *cmake-build-release*. In this build, the two core executables offering the AES functionality have been compiled and can be found on the directory's top-level. Both the encryption and decryption work on *.txt*-files from which they read Extended-ASCII or hexadecimal strings, depending on what the user requires. The outputs are formatted accordingly. For all in- and outputs the *Files/*-directory of the respective build has to be used. The message and key have to be provided through this directory and all outputs will be provided here as well. For this example an exemplary message and key are given and have been processed by both the encryption and decryption. The respective exemplary outputs can be retrieved from the default output files *encryptedMessage.txt* and *decryptedMessage.txt*.

## Directory Structure


### AES Directory
The *AES*-directory holds all source code of the given implementation (except for the test-library which is located in the *lib* directory described below). It is subdivided into the following three parts:

Within the *AES/src*-directory all modules that are shared by both the encryption and decryption can be found. For some of the modules located here, tests were developed and are given in the directory *AES/tests*. For further information please see the chapter "General Modules" of the provided documentation.

The subdirectory *AES/decryption* entails all source code which is only required by the decryption implementation. It is also subdivided into a *src/*-directory holding all created modules and into a *tests/*-directory containing all developed tests. The main method of the decryption executable can be found in *decrypt_MAIN.c*. For further information please see the chapter "Decryption Modules" of the provided documentation.

The modules which are exclusive to the encryption implementation can be found in the subdirectory *AES/encryption*. Like the *AES/decryption*-directory, it is also split into a *src/*-directory holding the implemented modules and a *tests/*-directory providing the respective tests. The main method of the encryption executable can be found in *mainEncryption.c*.  For further information please see the chapter "Encryption Modules" of the provided documentation.

### cmake-build-release Directory
The cmake-build-release directory holds an exemplary build of the encryption and decryption executables. It was created using the GCC-compiler on a Microsoft Windows machine. For usage hints please check the above section "Usage Guide".

### lib Directory
The *lib*-directory contains a small test-library developed for all tests within the project. It only consists of a single *assertExpectedEqualsActual()* function and is further described in subsection 4.6 of the provided documentation.

### Thesis and Documentation Directory
The *Thesis and Documentation*-directory contains all LaTeX source-files of both the provided documentation and thesis. These can be found in their respective subdirectories, whilst the final versions of the documents are also given at this level. 
