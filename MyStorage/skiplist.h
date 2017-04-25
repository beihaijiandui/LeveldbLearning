#ifndef LEVELDB_DB_SKIPLIST_H_
#define LEVELDB_DB_SKIPLIST_H_

#include "util\random.h"
#include <assert.h>
#include <stdlib.h>
#include "port\port.h"


namespace leveldb{
	template<typename Key,class Comparator>
	class Skiplist
	{
	private:
		struct Node;
	
	public:
		explicit Skiplist(Comparator cmp);
		void Insert(const Key& key);
		bool Contains(const Key& key) const;
        
		class Iterator
		{
		public:
			explicit Iterator(const Skiplist* list);
			bool Valid() const;
			const Key& Key() const;
			void Next();
			void Prev();
			void Seek(const Key& target);
		    void SeekToFirst();
			void SeekToLast();
		private:
			const Skiplist* list_;
			Node* node_;
		};
	private:
		enum {kMaxHeight=12};

		Comparator const compare_;
		Node* const head_;

		int max_height_;// 整个skiplist的高度
		
		inline int GetMaxHeight() const{
			return max_height_; 
		}

		Random rnd_;

		Node* NewNode(const Key& key,int height);
		int RandomHeight();
		bool Equal(const Key& a,const Key& b) const {return compare_(a,b)==0);}

		bool KeyIsAfterNode(const Key& key,Node* n) const;

		Node* FindGreaterOrEqual(const Key& key, Node** prev) const;
		Node* FindLessThan(const Key& key) const;
		Node* FindLast() const;

		//禁止复制
		Skiplist(const Skiplist&);
		void operator=(const Skiplist&);
	};

	//Implementation details follow
	template<typename Key,class Comparator>
	struct Skiplist<Key,Comparator>::Node{
		explicit Node(const Key& k):key(k){}

		Key const key;

		Node* Next(int n){
		  assert(n>=0);
		  return next[n];
		}

		void SetNext(int n,Node* x){
		  assert(n>=0);
		  next[n]=x;
		}

		Node* NoBarrier_Next(int n){
			assert(n>=0);
			return next[n];
		}

		void NoBarrier_SetNext(int n, Node* x){
			assert(n>=0);
			next[n]=x;
		}
	private:
		Node* next[1];
	};


}
#endif