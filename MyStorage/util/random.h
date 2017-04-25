#ifndef LEVELDB_UTIL_RANDOM_H_
#define LEVELDB_UTIL_RANDOM_H_

#include <stdint.h>
#include <math.h>

namespace leveldb{

	class Random{
	private:
		uint32_t  seed_;
	public:
		explicit Random(uint32_t s):seed_(s & 0x7fffffffu){
			if(seed_==0 || seed_==2147483647L){
			seed_ =1;
			}
		}
		uint32_t Next(){
			static const uint32_t M=2147483647L;
			static const uint64_t A=16807;

			uint64_t product=seed_*A;
			seed_=static_cast<uint32_t>((product>>31)+(product & M));
			if(seed_>M){
				seed_-=M;
			}
			return seed_;
		}
		uint32_t Uniform(int n) {
			return Next()%n;
		}
		bool OneIn( int n){
			return (Next()%n)==0;
		}
		uint32_t Skewed(int maxlog){
			return Uniform(1<<Uniform(maxlog+1));
		}
	};
}

#endif