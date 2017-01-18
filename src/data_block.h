#ifndef WORDEMBEDDING_DATA_BLOCK_H
#define WORDEMBEDDING_DATA_BLOCK_H

#include <iostream>

#include "utilh.h"
#include "huffman_encoder.h"
#include "constant.h"

namespace wordembedding {

class DataBlock {
 public:
 	std::unordered_set<int> input_nodes, output_nodes;
 	std::unordered_set<int> negativesample_pools;

 	DataBlock() {}
 	~DataBlock() {} 

 	/**
 	 * Get the number of sentences stored in DataBlock 
 	 */ 
 	std::size_t Size();

 	/**
 	 * Add a new sentence to the DataBlock
 	 * starting addres of the sentence 
 	 * length of the sentence 
 	 * word_count the number of words when getting
 	 * 	sentences from tain-file
 	 * next_random the seed for getting random number 
 	 */ 

 	void AddSentence(int* sentence, int sentence_length, 
 					int64_t word_count, uint64_t next_random);


 	/** 
 	 * Get the information of the index-th sentence 
 	 */ 
 	void GetSentence(int index, int*& sentence, 
 					 int& sentence_length, int64_t& word_count, 
 					 uint64_t& next_random);

 	/**
 	 * Release the memory which are using the store sentences
 	 */ 
 	void ClearSentences();

 	void ClearParameters();

 	void MallocMemory(int dictionary_size, bool is_use_adagrad);

 	void SetWeightIE(int input_node_id, real* ptr);
 	void SetWeightEO(int output_node_id, real* ptr);
 	real* GetWeightIE(int input_node_id);
 	real* GetWeightEO(int output_node_id);

 	void SetSumGradient2IE(int input_node_id, real* ptr);
 	void SetSumGradient2EO(int output_node_id, real* ptr);
 	real* GetSumGradient2IE(int input_node_id);
 	real* GetSumGradient2EO(int output_node_id);

 	void SetLastFlag();
 	void isLast();

 private:

 	/** 
 	 * The information of sentences 
 	 * head othe head 
 	 */ 

 	 struct Sentence {
 	 	int* head;
 	 	int length;
 	 	int64_t word_count;
 	 	uint64_t next_random;

 	 	Sentence(int* head, int length, int64_t word_count, 
 	 			 uint64_t next_random)
 	 		: head(head), length(length), 
 	 		  word_count(word_count), next_random(next_random) 
 	 	{

 	 	}

 	 };

 	 	void Get(int*& local_head, int& sentence_length, 
 	 			 int64_t& local_word_count, uint64_t& local_next_random) {
 	 		local_head = head;
 	 		sentence_length = length;
 	 		local_word_count = word_count;
 	 		local_next_random = next_random;
 	 	}


 	 	std::vector<Sentence> sentences_;

 	 	real** weight_IE_ = nullptr;
 	 	real** wight_EO_ = nullptr;


 	 	real** sum_gradient2_IE_ = nullptr;
 	 	real** sum_gradient2_EO_ = nullptr;

 	 	bool is_use_adagrad_ = false;
 	 	bool is_last_one_ = false;

 	 	// No opying allowd 

 	 
};



}

#endif