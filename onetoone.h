#ifndef ONE_TO_ONE_H
#define ONE_TO_ONE_H
#include <string>
using namespace std;

template <typename KEY,typename VALUE>
class OneToOne {
private:
	void ** keys;
	void ** values;	
	int cap;
	int len;
public:
	OneToOne() {
		cap=8;
		keys=new void*[cap];
		values=new void*[cap];
		len=0;	
	}
	void push(KEY k,VALUE v) {
		if (len>=cap) {
			cap*=2;
			void ** keys_cpy=new void*[cap];
			void ** values_cpy=new void*[cap];
			for (unsigned i=0;i<len;i++) {
				keys_cpy[i]=keys[i];
				values_cpy[i]=values[i];
			}
			delete keys;
			delete values;
			keys=keys_cpy;
			values=values_cpy;
		}
		keys[len]=k;
		values[len]=v;
		len++;

	}
	void remove(KEY k) {
		int index=-1;
		for (unsigned i=0;i<len;i++) {
			if (k==keys[i])
				index=i;	
		}
		if (index!=-1) {
			for (unsigned i=index;i<len;i++) {
				keys[i-1]=keys[i];
				values[i-1]=values[i];	
			}
			len--;
		}
	}
	bool has_key(KEY k) {
		for (unsigned i=0;i<len;i++) {
			if (v==keys[i])
				return 1;
		}
		return 0;
	
	}
	bool has_value(VALUE v) {
		for (unsigned i=0;i<len;i++) {
			if (v==values[i])
				return 1;
		}
		return 0;
	}
	int capacity() const {return cap;}
	int length() const {return len;}
	VALUE operator[](KEY k) const {
		int index=-1;
		for (unsigned i=0;i<len;i++) {
			if (k==keys[i])	
				index=i;
		}
		if (index==-1) {
			return 0;
		}
		return values[index];
	}
};





#endif 
