#include "LineStringParser.h"
#include <iostream>
namespace {
	const char SeparateChar=' ';
	const char NameSeparateChar = ':';
	const char ListStartChar = '{';
	const char ListEndChar = '}';
	const char ArrayStartChar = '(';
	const char ArraySeparateChar = ',';
	const char ArrayEndChar = ')';
}
int NameParser2(ListElement *vir_root, const char **cline_str);

void rmchar(std::string *str) {

	while (str->front() == '\t' || str->front()==' '|| str->front() == '\n') {
		*str = str->substr(1);
	}
	while (str->back() == '\t' || str->back() == ' ' || str->front() == '\n') {
		str->pop_back();
	}
}

int PushNomalParam(ListElement *vir_root, const char *name, const char **param_str) {
	std::string value;

	char it;
	while ('\0' != **param_str) {
		it = **param_str;
		value.push_back(it);
		if ('\n' == it || '\0' == it) {
			//substokenの末尾が区切り文字なら削除
			if ('\n' == value.back()) {
				value.pop_back();
			}
			//substokenに文字が入っていればTokenとして登録
			if (!value.empty()) {
				rmchar(&value);
				vir_root->listmenber.emplace_back();
				vir_root->listmenber.back() = new nomaltoken(name, value.c_str());
				value.clear();
				return 0;
			}
			return 1; //error
		}
		(*param_str)++;

	}

	return 1; //error
}

int ListParser( const char **param_str, std::string *dist) {
	using namespace std;
	string subtoken;
	const char *list_head;
	int list_count = 0;

	if (ListStartChar != **param_str) {
		cout << "ListParser { not found" << endl;
		return 1;
	}
	list_head = *param_str;
	list_count++;
	(*param_str)++;

	while ('\0' != **param_str) {
		char it = **param_str;
		//文字を部分文字列substokenの追加
		subtoken.push_back(it);
		if (ListStartChar == it) {
			list_count++;
		}
		else if (ListEndChar == it) {
			list_count--;
			if (list_count == 0) {
				subtoken.pop_back();
				*dist = subtoken;
				(*param_str)++;
				return 0;
			}
		}
		(*param_str)++;
	}
	return 1;
}
int ArryParser(ArrayElement *array_root,const char **param_str) {
	using namespace std;
	string subtoken;
	const char *list_head;

	if (ArrayStartChar != **param_str) {
		cout << "ArrayParser ( not found" << endl;
		return 1;
	}
	list_head = *param_str;
	(*param_str)++;

	while ('\0' != **param_str) {
		char it = **param_str;
		//文字を部分文字列substokenの追加
		subtoken.push_back(it);

		if (ArrayEndChar == it) {
			subtoken.pop_back();
			array_root->pushParam(subtoken.c_str());

			(*param_str)++;
			return 0;
		}
		else if(ArraySeparateChar == it){//",検出"
			subtoken.pop_back();
			array_root->pushParam(subtoken.c_str());
			subtoken.clear();
		}
		
		(*param_str)++;
	}
	return 1;

}

int PushArrayToken(ListElement *vir_root, const char *name, const char **param_str) {
	vir_root;
	vir_root->listmenber.emplace_back();
	vir_root->listmenber.back() = new ArrayElement(name);
	ArryParser(dynamic_cast<ArrayElement *>(vir_root->listmenber.back()), param_str);
	
	//const char *param_c_str = param.c_str();
	return 0;
}

int PushListToken(ListElement *vir_root, const char *name, const char **param_str) {
	std::string param;
	ListParser(param_str,&param);
	vir_root->listmenber.emplace_back();
	vir_root->listmenber.back() = new ListElement(name);
	const char *param_c_str = param.c_str();
	NameParser2(dynamic_cast<ListElement *>(vir_root->listmenber.back()),&param_c_str);
	return 0;
}

int NameParser2(ListElement *vir_root, const char **cline_str) {
	using namespace std;
	string name;	//Nodeの名前を格納する文字列
	/*
	解析対象から1文字とりだし、nameにpush
	もし	pushした文字が:ならnameの作成をおえる。
	:の次の文字が特定の文字なら新しいItemを作成する
	*/
	while ('\0' != **cline_str) {
		char it = **cline_str;
		//文字を部分文字列nameの追加
		name.push_back(it);
		if (NameSeparateChar == it) {
			//nameの末尾が区切り文字なら削除
			if (NameSeparateChar == name.back()) {
				name.pop_back();
				rmchar(&name);
			}

			//nameに文字が入っていればTokenとして登録
			if (name.empty()) {
				(*cline_str)++;
				continue;
			}

			(*cline_str)++;
			it = *((*cline_str));
			if ('\0' != it) {
				if (ListStartChar==it ) {
					PushListToken(vir_root, name.c_str(), cline_str);
					name.clear();
				}
				else if (ArrayStartChar == it ) {
					PushArrayToken(vir_root, name.c_str(), cline_str);
					name.clear();
				}
				else {
					PushNomalParam(vir_root, name.c_str(), cline_str);
					name.clear();
				}
			}
			else {
				//return false;
			}
		}
		//1文字進める
		(*cline_str)++;
	}
	return 0;
}

LineStringParser::LineStringParser(const char *c_str):Root("TreeRoot"){
	std::string Line(c_str);

	NameParser2(&Root,&c_str);
//	TokenIterator = Tokens.begin();
}


LineStringParser::~LineStringParser()
{
}

