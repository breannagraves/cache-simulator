#include<iostream>
#include<fstream>  // need this for file I/O
#include<cstdlib>   // for exit()
#include "cache_class.cpp"
using namespace std;

//THis is the file that handles file output to a file called "cache_sim_output"
//need to make updates to this code so that it does that 

using namespace std;

//const int MAX_SIZE = 1000;

  
int main(int argc, char*argv[]) 
{

    if (argc != 4) {
        cout << "Usage: " << endl;
        cout << "   ./file_process filename" << endl;
        return 0;
}
    int num_entries;
    int associativity;
    
  /* get base file name from command-line */
    num_entries = stoi(argv[1]);
    associativity = stoi(argv[2]);
    string filename = argv[3];
    

  /* create output filename */
    string output_filename = filename + "_output";

  /* create input and output files streams */
    ofstream output;
    ifstream input;


  /* open input stream for reading */
    input.open(filename);

  /* open output file stream for writing */
    output.open(output_filename);  

  /* check if input stream has been succesfully opened; bail otherwise */
    if (!input.is_open()) {
        cerr << "Could not open input file " << filename << ". Exiting ..." << endl;
        exit(0);
  }
    

  
    //create our cache
    Cache myCache(num_entries, associativity);
    int address;
    cout << "List of Memory References Accessed: " << endl;
    while (input >> address) {
        cout << address << "  "; 
        //myCache.display(output);
        
        if(myCache.hit(address))
        {
            //we have a hit 
            output << address << " : HIT" << endl;
            
        }
        else
        {
            //we have a miss 
            output << address << " : MISS" << endl;
            //add entry to cache
            myCache.update(address);

        }
    
        
    }

    cout << endl << "Please check current directory for output file which will entail Hits and Misses for each memory reference" << endl;

  /* done reading from input file; close the stream */
    input.close();


  return 0;
}