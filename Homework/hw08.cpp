/* Juan Garcia
 * CMPS 223 / Derrick
 * Homework 8
 * May 31, 2013
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>

using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

#ifndef COL_WIDTH
#define COL_WIDTH 5
#endif

#ifndef ROW_LENGTH
#define ROW_LENGTH 15
#endif

void mergesort(char *, char *);
void natural_split(char *, char *, char *);
int natural_merge(char *, char *, char *);

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    cout << "Natural mergesort called. Sorting file " << argv[1] << "...\n";
    mergesort(argv[1], argv[2]);

    return 0;
}

void mergesort(char *input, char *output)
{
    ELEMTYPE num;
    ifstream fin;
    ofstream fout;
    int runs = 0;
    int iter = 0;

    if(strlen(input) < 1)
    {
        cout << "Invalid input filename.\n";
        return;
    }
    if(strlen(output) < 1)
    {
        cout << "Invalid output filename.\n";
        return;
    }

    fin.open(input);
    if(fin.fail())
    {
        cout << "Cannot open " << input << " for reading.\n";
        return;
    }
    fout.open(output);
    if(fout.fail())
    {
        cout << "Cannot open " << output << " for writing.\n";
        fin.close();
        return;
    }

    char oddfile[strlen(input) + 8];
    char evenfile[strlen(input) + 8];
    int fd;

    strcpy(oddfile, input);
    strcat(oddfile, "XXXXXX");
    fd = mkstemp(oddfile);
    if(fd < 0)
    {
        cout << "Cannot create temporary filename.\n";
        fin.close();
        return;
    }
    else
    {
        close(fd);
    }

    strcpy(evenfile, input);
    strcat(evenfile, "XXXXXX");
    fd = mkstemp(evenfile);
    if(fd < 0)
    {
        cout << "Cannot create temporary filename.\n";
        fin.close();
        return;
    }
    else
    {
        close(fd);
    }

    cout << "Created temporary files: " << evenfile << " and " << oddfile << endl;

    int count = 0;
    while(fin >> num)
    {
        fout << num << " ";
        count ++;
    }
    fin.close();
    fin.clear();
    fout.close();
    fout.clear();

    if(count == 0)
    {
        cout << "File " << input << " contained no data. Cannot sort it.\n";
        return;
    }
    cout << "Sorting " << count << " elements into " << output << endl;

    do
    {
        natural_split(output, evenfile, oddfile);
        runs = natural_merge(evenfile, oddfile, output);
        cout << "Iteration " << ++iter << " merged data into " << runs << "runs\n";
    }while(runs != 1);

    remove(oddfile);
    remove(evenfile);

    cout << "File " << input << " has been sorted into file " << output << endl;
}

void natural_split(char *output, char *evenfile, char *oddfile)
{
    bool file1 = true;
    int num, last = -1, runs = 0;
    ifstream inFile(output);
    ofstream outFile1(evenfile), outFile2(oddfile);

    while(inFile >> num)
    {
        if(num < last)
        {
            runs++;
            file1 = !file1;
        }
        if(file1)
        {
            outFile1 << num << " ";
        }
        else
        {
            outFile2 << num << " ";
        }
        last = num;
    }
    inFile.close();
    outFile1.close();
    outFile2.close();
}

int natural_merge(char *evenfile, char *oddfile, char *output)
{
    int runs = 0;
    int num1, last1, num2, last2;
    bool read1 = false, read2 = false;
    ifstream inFile1(evenfile), inFile2(oddfile);
    ofstream outFile(output);

    read1 = (inFile1 >> num1);
    read2 = (inFile2 >> num2);

    while(read1 && read2)
    {
        if(num1 < num2)
        {
            outFile << num1 << " ";
            last1 = num1;
            read1 = (inFile1 >> num1);
            if(!read1 || num1 < last1)
            {
                runs ++;
                do
                {
                    outFile << num2 << " ";
                    last2 = num2;
                    read2 = (inFile2 >> num2);
                }while(read2 && num2 > last2);
            }
        }
        else
        {
            outFile << num2 << " ";
            last2 = num2;
            read2 = (inFile2 >> num2);
            if(!read2 || num2 < last2)
            {
                runs ++;
                do
                {
                    outFile << num1 << " ";
                    last1 = num1;
                    read1 = (inFile1 >> num1);
                }while(read1 && num1 > last1);
            }
        }
    }

    while(read1)
    {
        outFile << num1 << " ";
        last1 = num1;
        read1 = (inFile1 >> num1);
        if(!read1 || num1 < last1)
        {
            runs ++;
        }
    }
    while(read2)
    {
        outFile << num2 << " ";
        last2 = num2;
        read2 = (inFile2 >> num2);
        if(!read2 || num2 < last2)
        {
            runs ++;
        }
    }

    inFile1.close();
    inFile2.close();
    outFile.close();

    return (runs);
}
