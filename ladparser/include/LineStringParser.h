#pragma once

#include <vector>
#include <string>



class NodeElement {
public:
	int type;
	virtual ~NodeElement() = 0 {};
	//virtual int GetType() { return type; };
};
class nomaltoken :public NodeElement {
public:
	nomaltoken() {
		type = 1;
	}
	nomaltoken(const char *name, const char *param):name(name),param(param) {
		type = 1;
	}
	std::string name;
	std::string param;
};
class ListElement:public NodeElement {
public:
	ListElement() {
		type = 2;
	}
	ListElement(const char *name) :listname(name) {
		type = 2;
	}
	ListElement(const char *name,const char *param) :listname(name) {
		type = 2;
	}
	std::string listname;
	std::vector<NodeElement*> listmenber;
};

//îzóÒÅ@
class ArrayElement :public NodeElement {
public:
	ArrayElement() {
		type = 3;
	}
	ArrayElement(const char *name):arrayname(name) {
		type = 3;
	}
	ArrayElement(const char *name,const char *raw_param) :arrayname(name) {
		type = 3;

	}
	int pushParam(const char *param) {
		if (param == nullptr) {
			return -1;
		}
		arraymenber.emplace_back(param);
		return 0;
	}
	std::string arrayname;
	std::vector<std::string> arraymenber;
};


class LineStringParser
{
public:
	typedef std::vector<std::string> TokenList;


	ListElement Root;
	
	LineStringParser(const char *c_str);
	virtual ~LineStringParser();



private:
	TokenList Tokens;
//	TokenList::iterator TokenIterator;

};
