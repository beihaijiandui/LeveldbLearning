/*
 * slice.h
 *
 *  Created on: 2017年4月27日
 *      Author: ryanxin
 */

#ifndef INCLUDE_LEVELDB_SLICE_H_
#define INCLUDE_LEVELDB_SLICE_H_

#include <assert.h>
#include <string.h>
#include <stddef.h>
#include <string>

namespace leveldb{

class Slice{
public:
	//create an empty Slice
	Slice():data_(""),size_(0){}
	//use const char* innitialize
	Slice(const char* d,size_t n):data_(d),size_(n){}
	//use string get array to initialize
	Slice(const std::string& s):data_(s.data()),size_(s.size()){}
    //not give length  const char*
	Slice(const char* s):data_(s),size_(strlen(s)){}

	const char* data()const{return data_;}
	size_t size()const{return size_;}
	bool empty(){return size_==0;}

	char operator[](size_t n) const{
		assert(n<size());
		return data_[n];
	}
	void clear(){
		data_="";
		size_=0;
	}
	void remove_prefix(size_t n){
		assert(n<size());
		data_+=n;
		size_-=n;
	}
	std::string ToString() const{
		return std::string(data_,size_);
	}

	int compare(const Slice& b) const;
	bool starts_with(const Slice& x)const{
		return((size_>=x.size())&&(memcmp(data_,x.data(),x.size())==0));
	}
private:
	const char* data_;
	size_t size_;
};
//定义在命名空间内的非成员函数
inline bool operator==(const Slice& x,const Slice& y){
	return((x.size()==y.size())&&(memcmp(x.data(),y.data(),x.size())==0));
}
inline bool operator!=(const Slice& x,const Slice& y){
	return !(x==y);
}

inline int Slice::compare(const Slice& b)const{
	const size_t min_len=size_<b.size()?size_:b.size();
	int r=memcmp(data_,b.data(),min_len);
	if(r==0)
	{
		if(size_<b.size())
			r=-1;
		else
			r=+1;
	}
	return r;
}
}




#endif /* INCLUDE_LEVELDB_SLICE_H_ */
