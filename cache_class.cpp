#include<iostream>
#include<fstream>
#include<string> 
using namespace std;


class Entry {
public:
    Entry(); 
    ~Entry(){}
    void display(ofstream &outfile); 

    void set_tag(int _tag) { tag = _tag; }
    int get_tag() { return tag; }

    void set_valid(bool _valid) { valid = _valid; }
    bool get_valid() { return valid; }

    void set_ref(int _ref) { ref = _ref; }
    int get_ref() { return ref; }

    void set_accessed(int _accesed) { last_accessed = _accesed; }
    int get_accesed() { return last_accessed; }

private:  
    bool valid; // 0 or 1 for is in cache or not
    unsigned tag; // quotient of mod by associativity
    int ref; // data being asked for
    int last_accessed; // counter for when it was accessed
};

class Cache {
public:
    Cache(int num_entries, int assoc);
    ~Cache();

    void display(ofstream &outfile); 

    int get_tag(int addr);

    bool hit(int addr);

    void update(int addr);
    
    

  
private:
    int assoc;
    unsigned num_entries;
    int num_sets;
    Entry **entries;
    int time; 
};

Entry::Entry() 
{
    valid = 0; // 0 or 1 for is in cache or not // !! Valid bit should be set after we put data 
    // into a slot thats it
    tag = 0; // quotient of mod by associativity
    ref = 0; // data being asked for
    last_accessed = 0;  
}

void Entry::display(ofstream &outfile)
{
    outfile << "Ref: " << ref << " Valid bit: " << valid 
    << " Tag: " << tag << " Last Accessed: " << last_accessed << endl;
    

}

Cache::Cache(int num_entries, int assoc)
{
    num_sets = num_entries/ assoc;
    this -> num_entries = num_entries;
    this -> assoc = assoc;
    time = 0; // incremented every time there is an access

    entries = new Entry*[num_sets];

    for (int i = 0; i < num_sets; i++) 
    {
 
        // Declare a memory block
        // of size n - create each row
        entries[i] = new Entry[assoc];
    }

    // Traverse the 2D array
    for (int i = 0; i < num_sets; i++) 
    {
        for (int j = 0; j < assoc; j++) 
        {
 
            Entry new_entry;
            
            // Assign values to the
            // memory blocks created
            entries[i][j] = new_entry; // now entries is a table of blank entry objs

        }
    }
}

Cache::~Cache()
{
    for (int i=0; i <= num_sets; i++)
        delete [] entries[i];
        delete [] entries;
}

void Cache::display(ofstream &outfile) 
{
     for (int i = 0; i < num_entries; i++)
     {
         for (int j = 0; j < assoc; j++) 
         {
            outfile << "ADDR : " << entries[i] << endl; 
            outfile << i << "][" << j << "]: ";
            entries[i][j].display(outfile);
            outfile << endl;
            
         }
    }    
       
}

int Cache::get_tag(int addr)
{
    int tag = addr % num_sets;
    return tag;
}

  
bool Cache::hit(int addr)
{
    int tag_of_curr_addr = get_tag(addr);
    
    //need a way to search the array
    for (int i = 0; i < assoc; i++)
    {
        
            //if address is found - hit
            if(entries[tag_of_curr_addr][i].get_ref() == addr)
            {
                entries[tag_of_curr_addr][i].set_accessed(++time);
                return true;
            }
            //else address is not found - miss 
        
    }
    return false;
}

void Cache::update(int addr)
{
    // addr needs to be loaded into cache 
    // addr needs to be translated into an index in the cache using get_tag
    // pointing to one of the rows

    //case 1: available cache entry exists
    
    int tag = get_tag(addr);
    
    for(int i = 0; i < assoc; i++)
    {
        if(entries[tag][i].get_valid() == false)
        {
            entries[tag][i].set_ref(addr);
            entries[tag][i].set_valid(true);
            entries[tag][i].set_accessed(++time);
            return;
        }
        
    }
    
    //case 2: there is not an available cache entry, must find LRU entry and update to new reference
    int least_recently_accessed = entries[tag][0].get_accesed();
    int index_of_LRU = 0;

    for(int i = 0; i < assoc; i++)
    {
        if(least_recently_accessed > entries[tag][i].get_accesed())
        {
            least_recently_accessed = entries[tag][i].get_accesed();
            index_of_LRU = i;
        }
    }

    entries[tag][index_of_LRU].set_ref(addr);
    entries[tag][index_of_LRU].set_valid(true);
    entries[tag][index_of_LRU].set_accessed(++time);
    
    return;
}

//////////////////////////////IGNORE //////////////////////////////////////////////////////////

    // need to call constructor to load array with values entered by user
    

    // need to check array for all the first requested values that come from 
    // a file , what method to call ? how does that work with the file i/o

    // none of them will be there so they will all be miss first time
   
    // now need to load "addresses" or the ints in the infile into the 2d array based upon users 
    // input for number of entries and associativity

    // now that the "addresses" or ints are in the array, we need to write to the file the hits/ 
    // misses using the appropreate method (they are all misses the first time)

    // now a new file will be read in using fileio.cpp

    // need to load those into 2d array - not sure if at this point I will need
    // to check addresses to see if they are already in cache? or if i will just 
    // check for the values with a loop?
    
    
    // the CPU should only be able to send a physical mem address to the cache to check
    // if its a hit or miss


    
   