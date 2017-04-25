#include "arena.h"
#include <assert.h>

namespace leveldb{

	static const int kBlockSize=4096;

	Arena::Arena():memory_usage_(0){
		alloc_ptr_=NULL;
		alloc_bytes_remaining_=0;
	}

	Arena::~Arena(){
		for(size_t i=0;i<blocks_.size();i++){
			delete[] blocks_[i];  //存放char*指针的vector   本质上是二维数组
		}
	}

	char* Arena::AllocateFallback(size_t bytes){
		if(bytes>kBlockSize/4){
			char* result=AllocateNewBlock(bytes);
			return result;
		}

		alloc_ptr_=AllocateNewBlock(kBlockSize);
		alloc_bytes_remaining_=kBlockSize;

		char* result=alloc_ptr_;
		alloc_ptr_+=bytes;
		alloc_bytes_remaining_-=bytes;
		return result;
	}

	char* Arena::AllocateAligned(size_t bytes){
		const int align=(sizeof(void*)>8?sizeof(void*):8;
		assert();
	}


}