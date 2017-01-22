#ifndef WORDEMBEDDING_READER_H
#define WORDEMBEDDING_READER_H

/**
 * file reader.h 
 * Class reader helpts the function to loaddata to fill the datablock 
 */ 

#include <unordered_set> 

#include "util.h"
#include "dictionary.h"
#include "constants.h"

namespace wordembedding {


class Reader {
 public:
 	Reader(Dictionary* dictionary, Option* options, 
 		   Sampler* sampler, const char* input_file);
 	~Reader();

 	/** 
 	 * GetSentence from the traing file 
 	 */
 	int GetSentence(int* sentence, int64_t& word_count);
 	void ResetStart();
 	void ResetSize(int64_t size);

 private:
 	const Option* option_;
 	FILE* file_;
 	char word[kMaxString + 1];
 	Dictionar* dictionary_;
 	Sampler* sampler_;
 	int64_t byte_count_, byte_size_;
 	std::unordered_set<std::string> stopwords_table_;

 	/** 
 	 * Read words from the train file
 	 */ 
 	bool ReadWord(char* word, FILE* file);

 	// No copying allowed 
 	Reader(const Reader&); 
 	Reader& operator=(const Reader&);
};

}


#endif