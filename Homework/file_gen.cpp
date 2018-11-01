// Author:  Melissa Danforth
// Purpose: Generate a file of the given number of ints

#include <iostream>
#include <fstream>
#include <stdlib.h>  // rand() function
#include <time.h>    // time() function
using namespace std;

// This file uses command line arguments. To run the code, issue the command:
//
//     ./file_gen <size> <output_filename>
//
// For example, to generate 50 elements into a file called "input50.txt",
// give the command:
//
//     ./file_gen 50 input50.txt
//
// This code uses the random number function rand() to create each element.
// Numbers are generated in the range of 0 to 9999.
//
// Duplicate numbers are allowed and should be handled appropriately by your
// searching/sorting algorithm.


// When using command line arguments, alter main() to take two parameters:
//    argc     A count of the number of arguments typed, including the command
//    argv     An array of C-style strings containing the arguments typed
//             argv[0] will always be the name of the command (e.g. "./a.out")
//             argv[1] will be the first command line argument
//             argv[2] will be the second command line argument, and so on
int main(int argc, char *argv[])
{
  ofstream fout;
  int size;
  int num;
  double r;

  // We must seed the random function. If we use a fixed number, rand() will
  // generate the same sequence of numbers each time we run the program. Using
  // a value such as time() changes the seed with each run of the program
  // since time() returns a different value each second (seconds since the
  // Unix/Linux Epoch date).
  srand(time(NULL));

  // Check that the argument count is at least 3 (command, size, filename)
  if(argc < 3)
  {
    cout << "Usage: " << argv[0] << " <size> <output_filename>\n";
    return 1;  // return error
  }

  // Open the output file given by the second command line argument. This will
  // overwrite everything contained in it, so be cautious when giving the
  // output filename on the command line.
  fout.open(argv[2]);
  if(fout.fail())
  {
    cout << "Error opening " << argv[2] << " for writing.\n";
    return 1;
  }

  // Convert the first command line argument from a C-style string to an int
  size = atoi(argv[1]);

  // Generate the requested number of integers
  for(int i = 0; i < size; i++)
  {
    // Note: Some people generate random numbers by taking rand() and using
    // modulo to convert it to the desired range (e.g. rand() % 10000). This
    // is not a secure method of generating a random number because it only
    // uses the low-order bits for randomness and discards all the randomness
    // in the high-order bits (10000 for example is contained in only the last
    // 14 bits, so modulo would throw away 18 bits of randomness for an int).
    // A better method is to convert the value returned by rand() into a
    // percentage (0 to slightly less than 1). Then multiply that percentage
    // by the number range we want (e.g. 10000) to convert it back to an int.
    // Double division preserves the randomness present in the high-order bits,
    // making this a more robust method of calculating random numbers than the
    // modulo method.
    r =  (double)rand() / ((double)RAND_MAX + 1.00);
    num = (int)(r * 10000);   // convert to an int from 0 to 9999
    fout << num;              // output the int to the output file

    if((i + 1) % 10) fout << " "; // put 10 ints per line, space delimit on line
    else fout << endl;
  }
  fout.close();

  return 0;
}
