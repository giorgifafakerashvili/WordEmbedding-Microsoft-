#include "communicator.h"

namespace wordembedding {

Communicator::Communicator(Option* option, MemoryManager* memory_manager) {
	option_ = option;
	process_id_ = multiverso::MV_Rank();
	process_count_ = multiverso::MV_NumWorkers();
	memory_manager_ = memory_manager;
	embedding_size_ = option->embedding_size;
}

Communicator::~Communicator() {
	ClearParameterTables();
}


void Communicator::PrepareParameterTable(int row_size, int column_size) {
	worker_input_table_ = new multiverso::MatrixWorkerTable<real>(row_size, column_size);
    worker_output_table_ = new multiverso::MatrixWorkerTable<real>(row_size, column_size);
    server_input_table_ = new multiverso::MatrixServerTable<real>(row_size, column_size, -0.5f / embedding_size, 0.5f / embedding_size); 
    server_output_table_ = new multiverso::MatrixServerTable<real>(row_size, column_size);
    multiverso::KVTableOption<int, int64> option;
    worker_wordcount_table_ = multiverso::MV_CreateTable(option); // new multiverso::KVWorkerTable<int, int64>();

     if (option_->use_adagrad){
      worker_input_gradient_table_ = new multiverso::MatrixWorkerTable<real>(row_size, column_size);
      worker_output_gradient_table_ = new multiverso::MatrixWorkerTable<real>(row_size, column_size);
      server_input_gradient_table_ = new multiverso::MatrixServerTable<real>(row_size, column_size);
      server_output_gradient_table_ = new multiverso::MatrixServerTable<real>(row_size, column_size);
    }
}

void Communicator::ClearParameterTables() {
	delete worker_input_table_;
    delete worker_output_table_;
    delete server_input_table_;
    delete server_output_table_;
    delete worker_wordcount_table_;
    delete server_wordcount_table_;

    if (option_->use_adagrad){
      delete worker_input_gradient_table_;
      delete worker_output_gradient_table_;
      delete server_input_gradient_table_;
      delete server_output_gradient_table_;
    }
}




}