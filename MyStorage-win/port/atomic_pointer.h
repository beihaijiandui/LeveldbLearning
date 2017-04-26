#ifndef ATOMIC_POINTER_H_
#define ATOMIC_POINTER_H_

#include <stdint.h>
#include <atomic>
//#ifdef LEVELDB_ATOMIC_PRESENT
#include <atomic>
//#endif
//#ifdef OS_WIN
#include <Windows.h>
//#endif

//#if defined (_M_X64)||defined (_x86_64_)
#define ARCH_CPU_X86_FAMILY 1
//#elif defined (_M_IX86)|| defined (_i386_)||defined(_i386)
//#define ARCH_CPU_X86_FAMILY 1
//#endif

namespace leveldb{
namespace port{
	//define MemoryBarrier() if available
	//Windows on x86

//#if defined(OS_WIN) && defined(COMPILER_MSVC)&& defined (ARCH_CPU_X86_FAMILY)
#define LEVELDB_HAVE_MEMORY_BARRIER
//#endif

//AtomicPointer built using platform-specific  MemoryBarrier()
#if defined(LEVELDB_HAVE_MEMORY_BARRIER)

class AtomicPointer{
	 private:
		void* rep_ ;
	 public:
		 AtomicPointer(){};
		 explicit AtomicPointer(void* p):rep_(p){}
		 inline void* NoBarrier_Load() const {return rep_;}
		 inline void* NoBarrier_Store(void* v){rep_=v;}
		 inline void* Acquire_Load()const {
			void* result=rep_;
			MemoryBarrier();
			return result;
		 }
		 inline void Release_Store(void* v){
			MemoryBarrier();
			rep_=v;
		 }
};

/*◊¢ ÕµÙ’‚∏ˆ¿‡
//AtomicPointer based on <cstdatomic>
#elif defined(LEVELDB_ATOMIC_PRESENT)
	class AtomicPointer{
	private:
		std::atomic<void*> rep_;
		std::
	public:
		AtomicPointer(){};
		explicit AtomicPointer(void* v):rep_(v){}
		
		inline void* Acquire_Load() const {
			return rep_.load(std::memory_order _acquire);
		}

		inline void Release_Store(void* v){
			rep_.store(v,std::memory_order_release);
		}

		inline void* NoBarrier_Load() const {
      		return rep_.load(std::memory_order_relaxed);
		}

		inline void NoBarrier_Store(void* v){
			rep_.store(v,std::memory_order_relaxed);
		}
	};
#endif
	*/


//#undef LEVELDB_HAVE_MEMORY_BARRIER
}//namespace port 
}//namespace leveldb
#endif