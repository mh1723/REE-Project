// Main.cpp
//
// This program is being used for the 2016_08 CS4953 REverse Engineering Project
// It encrypts or decrypts the input file based on the password
//
// The students are given an encrypted file that has the password embedded. The program, given an input file
// extracts the password and decrypts the file.
//
// The task is to create the code to encrypt an arbitrary file, so that this specific decryption program succeeds.
//

#include <windows.h>
#include <stdio.h>
#include <io.h>

int sha256(char *fileName, char *dataBuffer, DWORD dataLength, unsigned char sha256sum[32]);

// this function is actually the answer - when completed!
int encryptFile(FILE *fptr, char *password)
{
   char *buffer;
   BYTE pwdHash[32];

   FILE *fptrOut;
   DWORD passwordLength, filesize, i;
   int resulti, pwdHashIndx;

   filesize = _filelength(_fileno(fptr));
   if (filesize > 0x100000)	// 1 MB, file too large
   {
      fprintf(stderr, "Error - Input file too large.\n\n");
      return -1;
   }

   passwordLength = (size_t)strlen(password);

   if (passwordLength == 0 || passwordLength >= 256)
   {
      fprintf(stderr, "Error - Password is too long!\n\n");
      return -1;
   }

   resulti = sha256(NULL, password, passwordLength, pwdHash);
   if (resulti != 0)
   {
      fprintf(stderr, "Error - Password not hashed correctly.\n\n");
      return -1;
   }

   // use the password hash to encrypt
   buffer = (char *)malloc(filesize);
   if (buffer == NULL)
   {
      fprintf(stderr, "Error - Could not allocate %d bytes of memory on the heap.\n\n", filesize);
      return -1;
   }

   fread(buffer, 1, filesize, fptr);	// should read entire file

                                       ////////////////////////////////////////////////////////////////////////////////////
                                       // INSERT ENCRYPTION CODE HERE
                                       ////////////////////////////////////////////////////////////////////////////////////

   fptrOut = fopen("encrypted.txt", "wb+");
   if (fptrOut == NULL)
   {
      fprintf(stderr, "Error - Could not open output file.\n\n");
      free(buffer);
      return -1;
   }

   ////////////////////////////////////////////////////////////////////////////////////
   // INSERT OUTPUT FILE WRITING CODE HERE
   ////////////////////////////////////////////////////////////////////////////////////

   fclose(fptrOut);
   return 0;
} // encryptFile

FILE *openInputFile(char *filename)
{
   FILE *fptr;

   fptr = fopen(filename, "rb");
   if (fptr == NULL)
   {
      fprintf(stderr, "Error - Could not input file %s!\n\n", filename);
      exit(-1);
   }

   return fptr;
} // openInputFile

char func1(char c) {
   char x, y, z, w;
   x = (c & 0x0C0) >> 2;
   y = (c & 0x003) << 2;
   z = (c << 2) & 0x0C0;
   w = (c >> 2) & 0x003;

   z = x | z | y | w;
   return z;
}

char func2(char c) {
   char x, y;

   x = c << 4;
   y = (c >> 4) & 0x00F;
   x = x + y;

   return x;
}

char func3(char c, short n) {
   // ??? 
   char x;
   char y;
   if (n == 1) {
      y = n & 1;
      y <<= 7;
   }
   else {

   }
   return c;
}

// reveersing 
int decryptFile(FILE *fp) {
   char *fileBuf;
   int sha256return;
   int fileLength;
   int fileBufOffset;
   unsigned int passwdLength;
   unsigned char sha256sum[32];
   char passwd[256];

   // get the length of the file, check that it is not too long
   fileLength = _filelength(_fileno(fp));
   if (fileLength > 0x100000) {
      fprintf(stderr, "Error - Input file too large.\n\n");
      return -1;
   }

   // read the password from the file (first 256 bytes)
   memset(passwd, 0, 256);
   fgets(passwd, 256, fp);

   // get the length of the password, make sure it's appropriate size
   passwdLength = strlen(passwd);
   if (passwdLength < 1 || passwdLength > 256) {
      fprintf(stderr, "Error - Password is too long!\n\n");
      return -1;
   }

   // zero terminate (chopping off that last byte ?)
   passwdLength -= 1;
   passwd[passwdLength] = '\0';

   // get the sha256sum of the password
   sha256return = sha256(NULL, passwd, passwdLength, sha256sum);
   if (sha256return != 0) {
      fprintf(stderr, "Error - Password not hashed correctly.\n");
      return -1;
   }

   fileBuf = (char *)malloc(fileLength);
   if (fileBuf == NULL) {
      fprintf(stderr, "Error - Could not allocate %d bytes of ", fileLength);
      return -1;
   }

   // read the remaining bytes in the file into a buffer
   fread(fileBuf, 1, fileLength, fp);

   // for each byte in the buffer, we apply a three pass dcryption, and an xor (one of two depending on the count)
   for (fileBufOffset = 0; fileBufOffset < fileLength - (passwdLength + 1); fileBufOffset++) {
      // pass 1
      fileBuf[fileBufOffset] = func1(fileBuf[fileBufOffset]);
      // pass 2
      fileBuf[fileBufOffset] = func2(fileBuf[fileBufOffset]);
      // pass 3
      fileBuf[fileBufOffset] = func3(fileBuf[fileBufOffset], 0);
      // xor
      if (fileBufOffset & 4) {

      }
      else {

      }


   }
   return 0;
}




void main_Student(int argc, char *argv[])
{
   FILE *fptr;

   if (argc < 3)
   {
      fprintf(stderr, "\n\nTo encrypt, you must enter the file to encrypt followed by the password.\n\n");
      fprintf(stderr, "%s filename password\n\n", argv[0]);
      exit(0);
   }

   //fptr = openInputFile(argv[1]);
   //encryptFile(fptr, argv[2]);
   //fclose(fptr);

   fptr = openInputFile("encrypted.txt");

   decryptFile(fptr);
   fclose(fptr);
   return;
} // main

