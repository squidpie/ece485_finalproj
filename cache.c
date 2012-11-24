//===============================================
// cache.c
//
// Implementation of cache model
//===============================================

#include "cache.h"

//Cache Initialization
void cache_i_init(CacheStats * statsAddr)
{
    int i = 0;
	int j = 0;
	

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
		for (j = 0; j < ICACHE_ASSOC; j ++) {
			L1I.sets[i].lines[j].tag = 0xFFFF;
			memset(L1I.sets[i].lines[j].data,0xAA,64) ;
		}
        L1I.sets[i].set_info = 0;        
    }
	L1I.stats = statsAddr;
}

void cache_d_init(CacheStats * statsAddr)
{
    int i = 0;
	int j = 0;

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
		for (j = 0; j < DCACHE_ASSOC; j++) { 
       	L1D.sets[i].lines[j].tag  = 0xFFFF;
       	memset(L1D.sets[i].lines[j].data,0xAA,64);
		}
        L1D.sets[i].set_info = 0;        
    }
	
	L1D.stats = statsAddr;
}


void cache_write(int address, uint8_t data){
	uint16_t readTag = (address & TAG) >> TAG_SHIFT;
	uint16_t index = (address &  INDEX) >> INDEX_SHIFT;
	uint8_t offset = address & OFFSET;
	int victim;
	int hit = 0;
	int i = 0;

    printf("Cache.c L1D: %X\n", L1D);
	L1D.stats->cache_writes++;
	
	//Search set at index for read tag
	for (i = 0; i < DCACHE_ASSOC; i++){
		if (readTag == (L1D.sets[index].lines[i].tag)) {
		
			// tag is valid, process read request
			hit = 1;
			L1D.stats->cache_write_hits++;
			//update_LRU(L1D.sets[index], i);
			
			//Return data
			L1D.sets[index].lines[i].data[offset] = data;
			break;
		}
	}

	if (!hit) {
		L1D.stats->cache_write_misses++;
		
		// get victim if miss wasn't from invalid state
		victim = 0; //evict_LRU(L1D.sets[index]);
		
		// update victim line tag and set MESI to exclusive, get data from L2
		L1D.sets[index].lines[victim].tag = readTag;
		L2_read(address, &L1D.sets[index].lines[victim].data);
		
		// Return data
		L1D.sets[index].lines[victim].data[offset] = data;
	}
	L2_write(address,data);
}
/* takes input of address and outputs data
*/
uint8_t cache_read(int address){
	uint16_t readTag = (address & TAG) >> TAG_SHIFT;
	uint16_t index = (address &  INDEX) >> INDEX_SHIFT;
	uint8_t offset = address & OFFSET;
	uint8_t data = 0xA;
	int hit = 0;
	int victim;
	int i = 0;

	L1D.stats->cache_reads++;
	
	//Search set at index for read tag
	for (i = 0; i < DCACHE_ASSOC; i++){
		if (readTag == (L1D.sets[index].lines[i].tag)) {
		
			// tag is valid, process read request
			hit = 1;
			L1D.stats->cache_read_hits++;
			//update_LRU(L1D.sets[index], i);
			
			//Return data
			data = L1D.sets[index].lines[i].data[offset];
			break;
		}
	}

	// If cache miss, evict and write to cache, get data from L2
	if (!hit) {
		L1D.stats->cache_read_misses++;
		
		// get victim if miss wasn't from invalid state
		victim = 0; //evict_LRU(L1D.sets[index]);
		
		// update victim line tag and set MESI to exclusive, get data from L2
		L1D.sets[index].lines[victim].tag = readTag;
		L2_read(address, &L1D.sets[index].lines[victim].data);
		
		// Return data
		data = L1D.sets[index].lines[victim].data[offset];
	}
	
	return data;
}


void cache_print(void)
{
    printf("L1 Data Cache Contents: \n");        
    print_datacache();
    //printf("L1 Instruction Cache Contents: \n");        
    //print_instrcache();
}

//Static cache print functions
static void print_datacache(void)
{
    int i = 0;
    DataCacheSet *currentSet;

    for(i = 0; i < DCACHE_NUMSETS; i++)
    {
        currentSet = &L1D.sets[i];
        
        //If any lines are valid, print set
        if(data_set_any_valid(currentSet))
        {
            print_dcacheset(i, currentSet);
        } 

    }
}

static void print_instrcache(void)
{

    int i = 0;
    InstrCacheSet *currentSet;

    for(i = 0; i < ICACHE_NUMSETS; i++)
    {
        currentSet = &L1I.sets[i];
        
        //If any lines are valid, print set
        if(instr_set_any_valid(currentSet))
        {
            print_icacheset(i, currentSet);
        } 

    }
}

static void print_icacheset(uint16_t index, InstrCacheSet * set)
{

    int i = 0;

    printf("-------------------------------------\n");
    printf("Index: %X\n LRU: %d\n", index, set->set_info);

    for(i = 0; i < ICACHE_ASSOC; i++)
    {
        if(line_valid(&set->lines[i]))
        {
            printf("\tLine: %d Tag: %X\n",
                i,
                set->lines[i].tag);
            print_data(&set->lines[i]);
        }
    }
}

static void print_dcacheset(uint16_t index, DataCacheSet * set)
{
    int i = 0;

    printf("-------------------------------------\n");
    printf("Index: %X\n LRU: %d\n", index, set->set_info);

    for(i = 0; i < DCACHE_ASSOC; i++)
    {
        if(line_valid(&set->lines[i]))
        {
            printf("\tLine: %d Tag: %X\n",
                i,
                set->lines[i].tag);
            print_data(&set->lines[i]);
        }
    }
}

static void print_data(line *line)
{
    int i = 0;

    printf("\t\tData[0-31]: ");
    for(i = 0; i < LINE_SIZE / 2; i++)
    {
        printf("%X ", line->data[i]);
    }
    printf("\n\t\tData[32-63]: ");
    for(i = LINE_SIZE / 2; i < LINE_SIZE; i++)
    {
        printf("%X ", line->data[i]);
    }
    printf("\n");
}
static int line_valid(line *cacheline)
{
    return !(cacheline->tag & VALID);
}

static int data_set_any_valid(DataCacheSet* set)
{
    int i = 0;
    int valid = 0;

    for(i = 0; i < DCACHE_ASSOC; i++)
    {
        if(line_valid(&set->lines[i]))
        {
            valid++;
            break;
        }
    }
    return valid;
}
static int instr_set_any_valid(InstrCacheSet* set)
{

    int i = 0;
    int valid = 0;

    for(i = 0; i < ICACHE_ASSOC; i++)
    {
        if(line_valid(&set->lines[i]))
        {
            valid++;
            break;
        }
    }
    return valid;
}
