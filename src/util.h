#ifndef WORDEMBEDDING_UTIL_H
#define WORDEMBEDDING_UTIL_H

#include <cstring> 
#include <cstdlib>
#include <random>
#include <cassert>
#include <sys/stat.h>
#include <time.h>

#include "constants.h"
#include "dictionary.h"

namespace wordembedding {


struct Option {
	const char* train_file;
	const char* read_vocab_file;
	const char* output_file;
	const char* sw_file;
	const char* endpoints_file;
	bool hs, output_binary, cbow, stopwords; 
	bool use_adagrad;
	bool is_pipeline;
	real sample;
	int64_t data_block_size;
	int embedding_size, thread_cnt, window_size, negative_num, min_count, epoch;
	int64_t total_words;
	int64_t max_preload_data_size;
	real init_learning_rate;

	Option();

	void ParseArgs(int argc, char* argv[]);
	void ParseArgs();
	vodi printUsage();

};

class Sampler {
 public:
 	Sampler();
 	~Sampler();

 	/** 
 	 * Set the negative-sampling distributions from every vocabulary 
 	 * \param dictionary the train_fiel dictionary 
 	 */ 
 	void SetNegativeSamplingDistribution(Dictionary* dictionary);
 	bool WordSampling(int64_t word_cnt, int64_t tarin_word, real sample);

 	/**
 	 * Get the next random according to the existing random seed 
 	 */ 
 	uint64_t GetNextRandom(uint64_t next_random);
 	int NegativeSampling(uint64_t next_random);

 private:
 	int* table_;

 	// No copy allowd 
 	Sampler(const Sampler&);
 	vodi operator=(const Sampler&);
};

std::string GetSystemTime();
int64_t GetFileSize(const char* filename);
bool ReadWord(const char* word, FILE* fin);

void InitExpTable();
extern std::string g_log_suffix;
extern real* expTable;
extern int embedding_size;



}



#endif