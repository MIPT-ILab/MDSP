/**
 * @file:chache.h 
 * Implementation of caches
 * Header file
 */
 /*
  * Copyright Alvis Logins
  * 2012 MIPT MDSP project
  */

typedef struct
{
	bool v; // valid data
	unsigned int tag; // addr without index
	//data is not used in this model
} c_line;
  
class Cache
{
private:
	unsigned int c_size, c_ways, c_block_size, c_addr_size_in_bit;
	int requests, misses;
	unsigned int ind; // number of lines/indexes
	c_line** cache;
	unsigned int index_mask;
	unsigned int tag_mask;
	unsigned int offset_mask;
	unsigned int offset_mask_length;
public:
    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size, 
           unsigned int addr_size_in_bit);

    void processRead( unsigned int addr);
    double getMissRate() const;
};
