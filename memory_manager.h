#ifndef WORDEMBEDDING_MEMORY_MANAGER_H_
#define WORDEMBEDDING_MEMORY_MANAGER_H_


#include <cassert>
#include <vector>
#include <conditinal_variable>

#include "constant.h"

namespace wordembedding {


class MemoryManager {
 public:
 	explicit MemoryManager(int block_size);

 	/** 
 	 * Create memory for the blocks
 	 */
 	void RequestBlocks(std::vector<real*>& blocks);


 	/**
 	 * Delete the block memeory
 	 */
 	void ReturnBlocks(std::vector<real*>& blocks);
 	~MemoryManager();

 private:
 	int64_t block_size_;
 	std::mutex mtx_;

 	// No copying allowed 
 	MemoryManager(const MemoryManager&);
 	MemoryManager& operator=(const MemoryManager&);
};


}






#endif