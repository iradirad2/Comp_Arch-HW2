#include <iostream>
using namespace std;

// cache header
class cache {
    private:
    level l1;
    level l2;
 
	int mem_cyc, b_size, l1_size , l2_size , l1_assoc,
        l2_assoc, l1_cyc , l2_cyc , wr_alloc;
    

    int l1_accesses = 0;
    int l2_accesses = 0;
    int mem_accesses = 0;
    int l1_misses = 0;
    int l2_misses = 0;

    int total_cycles = 0;

    public:
    // constructor
    cache(int mem_cyc,
             int b_size,
             int l1_size,
             int l2_size,
             int l1_assoc,
             int l2_assoc,
             int l1_cyc,
             int l2_cyc,
             int wr_alloc)
    : mem_cyc(mem_cyc),
      b_size(b_size),
      l1_size(l1_size),
      l2_size(l2_size),
      l1_assoc(l1_assoc),
      l2_assoc(l2_assoc),
      l1_cyc(l1_cyc),
      l2_cyc(l2_cyc),
      wr_alloc(wr_alloc)
    {} ; // TODO: init level 

    // destructor
    ~cache(){};// TODO


    void read(uint32_t address);
    void write(uint32_t address);
    double get_miss_rate(int l);
    double get_access_time();
}
// level header
class level {
    private:
    // constructor
    level(){};
    // destructor
    ~level(){};
    getLRU(){};
    public:
    // return true for hit
    bool read(uint32_t address); 
    bool write(uint32_t address);
    // add data to level. 
    // reutrn address of block to evict. if no block to evict return null
    uint32_t fill(uint32_t address);
    // remove block from level 
    uint32_t evict(uint32_t address);
    // remove block from level
    bool invalidate(uint32_t address);
    

}

//cache functions
void cache::read(uint32_t address){
    //access l1
    l1_accesses++;
    total_cycles += l1_cyc; 
    // l1 read hit
    if (l1.read(address)) 
        return;   
    // l1 read miss
    l1_misses++;  
    
    //access l2
    l2_accesses++;
    total_cycles += l2_cyc;
    // l2 read hit
    if (l2.read(address)){   
        // fill l1
        uint32_t evicted_l1 = l1.fill(address); 
        if(evicted_l1)  
            l1.evict(aevicted_l1);
        return;
    }
    //  l2 read miss
    l2_misses++; 
    //  memory access
    mem_accesses++;
    total_cycles += mem_cyc;
    // fill l2 first
    uint32_t evicted_l2 = l2.fill(address); 
    if(evicted_l2){    
        l2.evict(evicted_l2);
        l1.invalidate(evicted_l2);
    }
    // fill l1
    uint32_t evicted_l1 = l1.fill(address); 
    if(evicted_l1) 
        l1.evict(evicted_l1);
    return;

}
void cache::write(uint32_t address){
    //access l1
    l1_accesses++;
    total_cycles += l1_cyc; 
    // l1 write hit
    if (l1.write(address)) 
        return;   
    // l1 write miss
    l1_misses++;  
    
    //access l2
    l2_accesses++;
    total_cycles += l2_cyc;
    
    // l2 write hit 
    if(wr_alloc){
    //if wr_allocate, fill l1 and write l1
        if (l2.read(address)){   
            //wr_allocate to l1 if needed
            //fill l1
            uint32_t evicted_l1 = l1.fill(address); 
            if(evicted_l1)  
                l1.evict(evicted_l1);
            //write l1
            l1.write(address);
            return;
            }
    
            //if wr_no_allocate, write l2
    } else {
        if (l2.write(address))
            return;
    }

    //  l2 read miss
    l2_misses++; 

    //  memory access
    mem_accesses++;
    total_cycles += mem_cyc;
    
    //if wr_allocate, fill l1 and l2, write l1
    if(wr_allocate){
        // fill l2 first
        uint32_t evicted_l2 = l2.fill(address); 
        if(evicted_l2){    
            l2.evict(evicted_l2);
            l1.invalidate(evicted_l2);
        }
        // fill l1
        uint32_t evicted_l1 = l1.fill(address); 
        if(evicted_l1) 
            l1.evict(evicted_l1);
        //write l1
        l1.write(address);
    }
    //if wr_no_allocate, write directly to mem
}

double cache:: get_miss_rate(int l){
    if (l != 1 && l !=2)
        reuturn -1;
    double accesses = (l == 1) ? l1_accesses : l2_accesses;
    double misses = (l == 1) ? l1_misses : l2_misses;
    return misses / accesses;
}
double cache::get_access_time(){
    double accesses = l1_accesses; 
    return accesses / total_cycles;
}