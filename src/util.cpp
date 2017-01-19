#include <time.h>
#include "util.h"

namespace wordembedding {


Option::Option() {
	train_file = nullptr; 
	read_vocab_file = nullptr; 
	output_file = nullptr; 
	sw_fiel = nullptr;
	endpoints_file = ""; 
	hs = false; 
	negative_num = 5; 
	output_binary = false; 
	sample = 0; 
	cbow = true; 
	embedding_size = 100; 
	thread_cnt = 1; 
	window_size = 5; 
	thread_cnt = 1; 
	window_size = 5; 
	min_count = 5; 
	data_block_size = 1000000; 
	init_learning_rate = static_cast<real>(0.025);
	epoch = 1; 
	stopwords = false; 
	is_pipeline = true; 
	total_words = 0; 
	max_preload_data_size = 8000000LL; 
	use_adagrad = false;
}

void Option::ParseArgs(int argc, char* argv[]) {
	for(int i = 1; i < argc; i+=2) {
		if(strcmp(argv[i], "-size") == 0) embedding_size = atoi(argv[i+1]);
		if(strcmp(argv[i], "-train_file") == 0) train_file = argv[i + 1]; 
		if(strcmp(argv[i], "-endpoints_file") == 0) endpoints_file = argv[i+1];
		if(strcmp(argv[i], "-read_vocab") == 0) read_vocab_file = argv[i+1]; 

	}
}


void Option::PrintUsage() {
	puts("Usage:");
	puts("-size: word embedding size, e.g. 300");
	puts("-train_file: the training corpus fiel, e.g enwik2014");
	puts("-read_vocab: the file to read all the vocab counts info");
	puts("binary: 0 or 1 indicates whther to write all embedings vectors in binary format");
	puts("");
}

Sampler::Sampler() {
	table_ = nullptr;
}

Sampler::~Sampler() {
	free(table_);
}

// Set the negative sampling distribtuion 
void Sampler::SetNegativeSamplingDistribution(Dictionary* dictionary) {
	real train_words_pow = 0; 
	real power = 0.75; 
	table_ =(int*) malloc(kTableSize* sizeof(int));
	for(int i = 0; i < dictionary->size(); ++i) {
		train_words_pow += static_cast<real>(pow(dictioanry->GetWordInfo(i)->freq, power));
	}

	int cur_pos = 0; 
	real d1 = (real) pow(dictionary->GetWordInfo(cur_pos)->freq, power) / (real) train_words_pow; 

	assert(table_ != nullptr);
	for(int i = 0; i < kTableSize; ++i) {
		table_[i] = cur_pos;
		if(i > d1 * kTableSize && cur_pos + 1 < dictionary->Size()) {
			cur_pos ++;
			d1 += (real) pow(dictionary->GetWordInfo(cur_pos)->freq, power) / (real) train_words_pow;
		}
	}
}

bool Sampler::WordSampling(int64_t word_cnt, 
						   int64_t train_word, real sample) {
	real ran = (sqrt(word_cnt / (sample * train_word)) + 1) * 
					(sample * train_words) / word_cnt;

	return (ran > ((real)rand()  / (RAND_MAX)));
}

int Sampler::NegativeSampling(uint64_t next_random) {
	return table_[(next_Random >> 16) % kTableSize];
}



std::string GetSystemTime() {
	time_t t = time(0);
	char tmp[128]; 
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));
    return std::string(tmp);
}

int64_t GetFileSize(const char* filename) {
#ifdef _MSC_VER
	struct _stat64 info;
	_stat64(filename, &info);
	return (int64_t) info.st_size;
#else 
	struct stat info;
	stat(filename, &info);
	return (int64_t) info.st_size;
#endif
}


// Readword from train file to word array by the word index 


}