// Author:  Melissa Danforth
// Purpose: A demo of passing command line arguments to C++

#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

// Change main so that the command line arguments can be passed as
// parameters to the function.
//   argc contains the count of command line arguments plus one for the
//     executable name. So if there are 2 command line arguments, argc
//     will be 3.
//   argv is an array of C-style strings, one string per argument
//     argv[0] will be the name of the executable
//     argv[1] is the first argument
//     argv[2] is the second argument

int main(int argc, char *argv[])
{

  if(argc < 3)
  {
    cout << "Error: Must pass at least 2 arguments.\n";

    // Remember that argv[0] contains the name of the executable, so this
    // will print out a usage line that has the name of the executable and
    // the reminder to pass two filenames
    cout << "Usage: " << argv[0] << " <input_filename> <output_filename>\n";
    return 1;  // return error
  }

  cout << "Input filename:  " << argv[1] << endl;
  cout << "Output filename: " << argv[2] << endl;

  // Create a temporary filename out of the input filename
  // This makes use of the mkstemp POSIX function which replaces each X in
  // the given filename with a random character and ensures a file with the
  // generated filename does not already exist.
  char tempfile[strlen(argv[1]) + 8];
  int fd;

  // It is safe to use strcpy and strcat since the tempfile was allocated
  // to be big enough to hold strlen(argv[1]) plus 8 more characters (including
  // the null character).
  strcpy(tempfile, argv[1]);
  strcat(tempfile, "XXXXXX");
  fd = mkstemp(tempfile);  // Create the temporary file
  close(fd);               // Close the temporary file so we can use streams

  cout << "Random filename: " << tempfile << endl;
  // At this point, you can pass tempfile to a stream open() function to open
  // the temporary file for writing.

  return 0;
}
