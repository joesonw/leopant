#ifndef MMO_SERVER_PACKET
#define MMO_SERVER_PACKET
#include <boost/any.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
using namespace std;
using boost::any;
using boost::any_cast;


class AnyArray {
private:
	map<string,any> data;
public:
	AnyArray() {}
	~AnyArray() {}
	void write(string name,any value) {
		data[name]=value;
	}
	void remove(string name) {
		data.erase(name);
	}
	map<string,any> array() {return data;}
	string readString(string name) {
		string result="";
		if (data[name].type()==typeid(string)) {
			result=any_cast<string>(data[name]);
		}
		return result;
	}
	int readInt(string name) {
		int result=0;
		if (data[name].type()==typeid(int)) {
			result=any_cast<int>(data[name]);
		}	
		return result;
	}
	int readFloat(string name) {
		float result=0;
		if (data[name].type()==typeid(float)) {
			result=any_cast<int>(data[name]);
		}
		return result;
	}
	AnyArray readArray(string name) {
		if (data[name].type()==typeid(AnyArray)) {
			return any_cast<AnyArray>(data[name]);
		}
	}
		
};
class Packet {
public:	
	enum { header_length=8};
	Packet() {}
	~Packet() {}	
	static string pack(AnyArray a) {
		ostringstream ss;	
		map<string,any> v=a.array();
		for (std::map<string,any>::iterator i=v.begin();i!=v.end();i++) {
			string key=i->first;
			any value=i->second;
			if (value.type()==typeid(string)) {
				ss<<"{0,"<<key<<","<<any_cast<string>(value)<<"},";
			} else if (value.type()==typeid(int)) {
				ss<<"{1,"<<key<<","<<any_cast<int>(value)<<"},";
			} else if (value.type()==typeid(float)) {
				ss<<"{2,"<<key<<","<<any_cast<float>(value)<<"},";
			} else if (value.type()==typeid(double)) {
				ss<<"{2,"<<key<<","<<any_cast<double>(value)<<"},";
			} else if (value.type()==typeid(AnyArray)) {
				ss<<"{3,"<<key<<","<<Packet::pack(any_cast<AnyArray>(value))<<"},";	
			}
		}
		return ss.str();
	}
	static AnyArray unpack(string content) {
		AnyArray result;	
		unsigned i=0;
		while (i<content.length()) {
			unsigned count=0;
			char type=content[i+1];
			unsigned j=i+3;
			while(1) {
				if (content[j]==',')
					break;
				j++;
			}	
			string name=content.substr(i+3,j-i-3);
			j++;
			count=j;
			if (type=='3') {
				unsigned bracket_count=1;
				string array_content="";
				while(1) {
					array_content+=content[j];
					if (content[j]=='{') {
						bracket_count++;
					} else if (content[j]=='}') {
						bracket_count--;
					}
					if (bracket_count==0) {
						break;
					}
					j++;
				}	
				array_content.erase(array_content.length()-1,1);
				result.write(name,Packet::unpack(array_content));
				count=j+2;
			} else {
				while(1) {
					if (content[j]==',') {
						break;
					}
					j++;
				}
				string value=content.substr(count,j-1-count);
				count=j+1;
				if (type=='1') {
					int v;
					std::istringstream ss(value);
					ss>>v;
					result.write(name,v);
				} else if (type=='2') {
					float v;
					std::istringstream ss(value);
					ss>>v;
					result.write(name,v);
				} else {
					result.write(name,value);
				}
			}
			i=count;
		}	
		return result;
	}
};
#endif
