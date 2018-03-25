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
			//substoken‚Ì––”ö‚ª‹æØ‚è•¶š‚È‚çíœ
			if ('\n' == value.back()) {
				value.pop_back();
			}
			//substoken‚É•¶š‚ª“ü‚Á‚Ä‚¢‚ê‚ÎToken‚Æ‚µ‚Ä“o˜^
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
		//•¶š‚ğ•”•ª•¶š—ñsubstoken‚Ì’Ç‰Á
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
		//•¶š‚ğ•”•ª•¶š—ñsubstoken‚Ì’Ç‰Á
		subtoken.push_back(it);

		if (ArrayEndChar == it) {
			subtoken.pop_back();
			array_root->pushParam(subtoken.c_str());

			(*param_str)++;
			return 0;
		}
		else if(ArraySeparateChar == it){//",ŒŸo"
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
	string name;	//Node‚Ì–¼‘O‚ğŠi”[‚·‚é•¶š—ñ
	/*
	‰ğÍ‘ÎÛ‚©‚ç1•¶š‚Æ‚è‚¾‚µAname‚Épush
	‚à‚µ	push‚µ‚½•¶š‚ª:‚È‚çname‚Ìì¬‚ğ‚¨‚¦‚éB
	:‚ÌŸ‚Ì•¶š‚ª“Á’è‚Ì•¶š‚È‚çV‚µ‚¢Item‚ğì¬‚·‚é
	*/
	while ('\0' != **cline_str) {
		char it = **cline_str;
		//•¶š‚ğ•”•ª•¶š—ñname‚Ì’Ç‰Á
		name.push_back(it);
		if (NameSeparateChar == it) {
			//name‚Ì––”ö‚ª‹æØ‚è•¶š‚È‚çíœ
			if (NameSeparateChar == name.back()) {
				name.pop_back();
				rmchar(&name);
			}

			//name‚É•¶š‚ª“ü‚Á‚Ä‚¢‚ê‚ÎToken‚Æ‚µ‚Ä“o˜^
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
		//1•¶ši‚ß‚é
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

