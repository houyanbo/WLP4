#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int loopcount = 0;
int ifcount = 0;
int deletecount = 0;
map<string, map<string, int>> position;
struct Node {
	string str;
	vector<Node*> children;
};

void push(int reg) {
	cout << "sw $" << reg << ", -4($30)" << endl;
	cout << "sub $30, $30, $4" << endl;
}

void pop(int reg) {
	cout << "add $30, $30, $4" << endl;
	cout << "lw $" << reg << ", -4($30)" << endl;
}

void code(string id, string curstr) {
	cout << "lw $3, " << -(position[curstr][id] - 1) * 4 << "($29)" << endl;
	//cout << id << " " << -(position[curstr][id] - 1) * 4 << endl;
}

void callProcedure(string name) {
	push(31);
	cout << "lis $5" << endl;
	cout << ".word " << name << endl;
	cout << "jalr $5" << endl;
	pop(31);
}

Node* constructTree(Node* root) {
  string line;
	getline(cin, line);
	stringstream sin(line);
	int count = 0;
	string curStr; 
	while (sin >> curStr) {
		if (count == 0) {
			root->str = curStr;
			count++;
			continue;
		}
		Node* child = new Node();
		child->str = curStr;
		if (curStr.front() > 'Z' || curStr.front() < 'A') {
			child = constructTree(child);
		} else {
			string terminal;
			getline(cin, terminal);
			stringstream sinn(terminal);
			string t;
			sinn >> t;
			sinn >> t;
			Node* newNode = new Node();
			newNode->str = t;
			child->children.push_back(newNode);
		}
		root->children.push_back(child);
	}
	return root;
}

void printTree(Node* tree) {
  cout << tree->str << " ";
  for (int i = 0; i < (int)tree->children.size(); i++) {
    cout << tree->children[i]->str << " ";
	}
	cout << endl;
	for (int i = 0; i < (int)tree->children.size(); i++) {
		if ((tree->children[i]->str.front() <= 'z' && 
				tree->children[i]->str.front() >= 'a') || (int) tree->children[i]->children.size() != 0) {
			printTree(tree->children[i]);
		}
    delete(tree->children[i]);
  }
  tree->children.clear();
}

void deleteTree(Node* tree) {
  for (int i = 0; i < (int)tree->children.size(); i++) {
   	 deleteTree(tree->children[i]);
  }
	delete(tree);
}

string vectorToString(vector<Node*> children) {
	string ans = "";
	for (int i = 0; i < (int)children.size(); i++) {
		ans += children[i]->str;
		if (i != (int)children.size() - 1) {
			ans += " ";
		}
	}
	return ans;
}

/*string findID(Node* root) {
	string lstring = root->str;
	string rstring = vectorToString(root->children);
	if (lstring == "lvalue") {
		if (rstring == "ID") {
			return root->children[0]->children[0]->str;
		} else if (rstring == "STAR factor") {
			return findID(root->children[1]);
		} else {
			return findID(root->children[1]);
		}
	 else {
		if (rstring == "ID") {
			return root->children[0]->children[0]->str;
		} else if (rstring ==
	}
}*/

string valueExp(Node* root, map<string, pair<vector<string>, map<string, string>>> table, string curstr) {
	string lstring = root->str;
	string rstring = vectorToString(root->children);
	if (lstring == "expr") {
		if (rstring == "term") {
			return valueExp(root->children[0], table, curstr);
		} else if (rstring == "expr PLUS term") {
			string v1 = valueExp(root->children[0], table, curstr);
			if (v1 == "int") {
				cout << "mult $3, $4" << endl;
				cout << "mflo $3" << endl;
			} 
			push(3);
			string v2 = valueExp(root->children[2], table, curstr);
			if (v2 == "int") {
				cout << "mult $3, $4" << endl;
				cout << "mflo $3" << endl;
			}
			pop(5);
			cout << "add $3 ,$5 ,$3" << endl;
			if (v1 == "int" && v2 == "int") {
				cout << "div $3, $4" << endl;
				cout << "mflo $3" << endl;
			}
			if (v1 == "ERROR" || v2 == "ERROR") {
				return "ERROR";
			}
			if (v1 == v2 && v1 == "int") {
				return "int";
			} else if ((v1 == "int*" || v2 == "int*") && v1 != v2) {
				return "int*";
			} else {
				cerr << "ERROR: invalid operation" << endl;
	  		return "ERROR";
			}
		} else {
			string v1 = valueExp(root->children[0], table, curstr);
			push(3);
			string v2 = valueExp(root->children[2], table, curstr);
			if (v1 == "int*" && v2 == "int*") {
				pop(5);
				cout << "sub $3 ,$5 ,$3" << endl;
				cout << "div $3, $4" << endl;
        cout << "mflo $3" << endl;	
			} else if (v1 == "int*" && v2 == "int") {
				cout << "mult $3, $4" << endl;
        cout << "mflo $3" << endl;
				pop(5);
				cout << "sub $3 ,$5 ,$3" << endl;
			} else {
				pop(5);
				cout << "sub $3, $5, $3" << endl;
			}
				
			//cout << "sub $3 ,$5 ,$3" << endl;
			if (v1 == "ERROR" || v2 == "ERROR") {
				return "ERROR";
			}
   		if (v1 == v2) {
     		return "int";
   		} else if (v1 == "int*") {
				return "int*";
			} else {
				cerr << "ERROR: invalid operation" << endl;
     		return "ERROR";
			}
		}
	} else if (lstring == "term") {
		if (rstring == "factor") {
	   	return valueExp(root->children[0], table, curstr);
  	} else {
    	string v1 = valueExp(root->children[0], table, curstr);
			push(3);
			string v2 = valueExp(root->children[2], table, curstr);
			pop(5);
			if (rstring == "term STAR factor") {
				cout << "mult $3, $5" << endl;
				cout << "mflo $3" << endl;
			} else if (rstring == "term SLASH factor") {
				cout << "div $5, $3" << endl;
				cout << "mflo $3" << endl;
			} else {
				cout << "div $5, $3" << endl;
				cout << "mfhi $3" << endl;
			}
			if (v1 == "ERROR" || v2 == "ERROR") {
      	return "ERROR";
    	}
    	if (v1 == v2 && v1 == "int") {
      	return "int";
    	}
    	cerr << "ERROR: invalid operation" << endl;
    	return "ERROR";
  	}
	} else if (lstring == "factor") {
		if (rstring == "ID") {
	    if (table[curstr].second.find(root->children[0]->children[0]->str) != table[curstr].second.end()) {
			  code(root->children[0]->children[0]->str, curstr);
				//cout << root->children[0]->children[0]->str << " " << curstr << endl;
				return table[curstr].second[root->children[0]->children[0]->str];
    	} else {
     		cerr << "ERROR: variable has not been declared1" << endl;
      	return "ERROR";
    	}
  	} else if (rstring == "NUM") {
    	cout << "lis $3" << endl;
			cout << ".word " << root->children[0]->children[0]->str << endl;
			return "int";
  	} else if (rstring == "NULL") {
			cout << "add $3, $0, $11" << endl;
    	return "int*";
  	} else if (rstring == "LPAREN expr RPAREN") {
    	return valueExp(root->children[1], table, curstr);
  	} else if (rstring == "AMP lvalue") {
  	  /*string v = valueExp(root->children[1], table, curstr);
    	if (v == "ERROR") {
      	return "ERROR";
    	} else if (v == "int") {
      	return "int*";
    	} else {
      	cerr << "ERROR: invalid operation" << endl;
      	return "ERROR";
    	}*/
			if (root->children[1]->children[0]->str == "ID") {
				cout << "lis $3" << endl;
				cout << ".word " << -(position[curstr][(root->children[1]->children[0]->children[0]->str)]-1)*4 << endl;
				cout << "add $3, $3, $29" << endl;
				return "int*";
			} else if (root->children[1]->children[0]->str == "STAR") {
				string v = valueExp(root->children[1]->children[1], table, curstr);
				/*if (v == "ERROR") {
        	return "ERROR";
      	} else if (v == "int") {
        	return "int*";
      	} else {
        	cerr << "ERROR: invalid operation" << endl;
        	return "ERROR";
      	}*/
				return v;
			} else {
				string v = valueExp(root->children[1], table, curstr);
      	if (v == "ERROR") {
        	return "ERROR";
      	} else if (v == "int") {
        	return "int*";
      	} else {
        	cerr << "ERROR: invalid operation" << endl;
        	return "ERROR";
      	}
			} 
  	} else if (rstring == "STAR factor") {
    	string v = valueExp(root->children[1], table, curstr);
			cout << "lw $3, 0($3)" << endl;
    	if (v == "ERROR") {
      	return "ERROR";
    	} else if (v == "int*") {
      	return "int";
    	} else {
      	cerr << "ERROR: invalid operation" << endl;
      	return "ERROR";
    	}
  	} else if (rstring == "NEW INT LBRACK expr RBRACK") {
    	string v = valueExp(root->children[3], table, curstr);
			cout << "add $1, $3, $0" << endl;
			push(31);
			cout << "lis $5" << endl;
			cout << ".word new" << endl;
			cout << "jalr $5" << endl;
			pop(31);
			cout << "bne $3, $0, 1" << endl;
			cout << "add $3, $11, $0" << endl;
    	if (v == "ERROR") {
      	return "ERROR";
    	} else if (v == "int") {
      	return "int*";
    	} else {
      	cerr << "ERROR: invalid operation" << endl;
      	return "ERROR";
    	}
  	} else if (rstring == "ID LPAREN RPAREN") {
			if (table[curstr].second.find(root->children[0]->children[0]->str) == table[curstr].second.end()) {
				push(29);
        callProcedure("F" + root->children[0]->children[0]->str);     
        pop(29);
				return "int";
			} else {
				cerr << "ERROR" << endl;
				return "ERROR";
			}
			//if (vectorToString(root->children[2]->children) == "") {   
        //push(29);
        //callProcedure("F" + root->children[0]->children[0]->str);        
				//pop(29);
      //}
		} else if (rstring == "ID LPAREN arglist RPAREN") {
			string ID = root->children[0]->children[0]->str;
      push(29);
			push(31);
			int size = 0;
			//int size = table[curstr].first.size() - 1;
			//cout << curstr << "  HIHIHIHIHIHIHI" << endl;
			//cout << size << "  gg" << endl;
			root = root->children[2];
			valueExp(root->children[0], table, curstr);
			push(3);
			size += 1;
			while ((int)root->children.size() > 1) {
				root = root->children[2];
				valueExp(root->children[0], table, curstr);
				push(3);
				size += 1;
			}
			//cout << "hgjkjhjkhjk   " << root->children[0]->children[0]->children[0]->children[0]->children[0]->str; 
			//cout << "hjghjkhghjk   " << size << endl;
			/*for (int i = 0; i < size; i++) {
				valueExp(root->children[0], table, curstr);
				push(3);
				root = root->children[2];
			}*/
			//valueExp(root->children[0], table, curstr);
			//push(3);
			cout << "lis $5" << endl;
			cout << ".word F" << ID << endl;
			cout << "jalr $5" << endl;
			for (int i = 0; i < size; i++) {
				cout << "add $30, $30, $4" << endl;
			}
			pop(31);
			pop(29);
			return "int";	
		}
	} else if (lstring == "lvalue") {
		string rstring = vectorToString(root->children);
  	if (rstring == "ID") {
    	if (table[curstr].second.find(root->children[0]->children[0]->str) != table[curstr].second.end()) {
				code(root->children[0]->children[0]->str, curstr);
				return table[curstr].second[root->children[0]->children[0]->str];
    	} else {
     		cerr << "ERROR: variable has not been declared" << endl;
     		return "ERROR";
    	}
  	} else if (rstring == "STAR factor") {
    	string v = valueExp(root->children[1], table, curstr);
			cout << "lw $3, 0($3)" << endl;
    	if (v == "ERROR") {
      	return "ERROR";
    	} else if (v == "int*") {
     		return "int";
    	} else {
      	cerr << "ERROR: invalid operation" << endl;
      	return "ERROR";
    	}
  	} else {
    	return valueExp(root->children[1], table, curstr);
  	}
	}
	return "CRASHED";
}

void generate(vector<string> &arglist, Node* root, 
							map<string, pair<vector<string>, map<string, string>>> table, string curstr) {
	string rstring = vectorToString(root->children);
	arglist.push_back(valueExp(root->children[0], table, curstr));
	push(3);
	if (rstring != "expr") {
		generate(arglist, root->children[2], table, curstr);
	} 
}

void prologue() {
	/*cout << "; begin prologue" << endl;
	cout << ".import print" << endl;
	cout << ".import init" << endl;
	cout << ".import new" << endl;
	cout << ".import delete" << endl;
	cout << "lis $4 ; new convention $4 always contains 4" << endl;
	cout << ".word 4" << endl;
	cout << "lis $10 ; $10 will always hold address for print" << endl;
	cout << ".word print" << endl;
	cout << "lis $11 ; $11 will always hold 1" << endl;
	cout << ".word 1" << endl;*/
	cout << "sub $29, $30, $4" << endl;
	cout << "sw $1 , -4($30) ; store variable a at $30 -4" << endl;
	cout << "sw $2 , -8($30) ; store variable b at $30 -8" << endl;
	cout << "sub $30, $30, $4" << endl;
	cout << "sub $30, $30, $4" << endl;
	cout << ";end prologue" << endl;
}

void epilogue() {
	cout << "; begin epilogue" << endl;	
	for (int i = 0; i < (int) position["wain"].size(); i++) {
		cout << "add $30, $30, $4" << endl;
	}
	cout << "jr $31" << endl;
}

void check(map<string, pair<vector<string>, map<string, string>>> &table, 
					 Node* root, string &curstr, bool isparam) {
	string lstring = root->str;
	string rstring = vectorToString(root->children);
	/*if (lstring == "procedures") {
		if (rstring == "main") {
			table["wain"];
			curstr = "wain";
			isparam = true;
			prologue();
		}
	}*/ 
  /*if (lstring == "procedure") {
		if (rstring != "") {
			string name = root->children[1]->children[0]->str;
			if (table.find(name) == table.end()) {
				table[name];
				curstr = name;
			} else {
				cerr << "ERROR: duplicate procedures" << endl;
			}
		}
	}*/
	 
	if (lstring == "dcl") {
		string type = vectorToString(root->children[0]->children);
		string ID = vectorToString(root->children[1]->children);
		type = type == "INT" ? "int" : "int*";
		map<string, string>::iterator it = table[curstr].second.find(ID);
		if (it == table[curstr].second.end()) {
			table[curstr].second.insert(make_pair(ID, type));
			if (curstr != "wain" && !isparam) {
				//cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
				//cout << curstr << " " << ID << " " << table[curstr].second.size() << " " << table[curstr].first.size() << endl;
				position[curstr][ID] = table[curstr].second.size() - table[curstr].first.size();
			} else {
				position[curstr][ID] = table[curstr].second.size();
			}
			if ((curstr == "wain" && (int)table[curstr].first.size() < 2) || isparam) {
				table[curstr].first.push_back(type);
			} /*else {
				isparam = false;
			}*/
			if ((curstr == "wain" && (int)table[curstr].first.size() == 2) && isparam) {
				if (table[curstr].first[0] == "int") {
					//push(2);
					cout << "add $2, $0, $0" << endl;
					callProcedure("init");
					//pop(2);
				} else {
					callProcedure("init");
				}
				isparam = false;
			}
		} else {
			cerr << "ERROR: variable has been declared" << endl;
		}
	} 
  if (lstring == "paramlist") {
		isparam = true;
		check(table, root->children[0], curstr, isparam);
		if ((int)root->children.size() > 1) {
			check(table, root->children[2], curstr, isparam);
		}
		/*int paramnum = table[curstr].first.size();
		cout << "HERE IS NUM OF PARAM :" << "paramnum" << endl;
		for (auto &t : position[curstr]) {
			t.second -= paramnum;
		}*/
		isparam = false;
	} 
	if (lstring == "factor" || lstring == "lvalue") {
		/*if (rstring == "ID") {
			string ID = vectorToString(root->children[0]->children);
			map<string, string>::iterator it = table[curstr].second.find(ID);
    	if (it == table[curstr].second.end()) {
      	cerr << "ERROR: variable has not been declared" << endl;
    	} else {
				cout << "lw $3, " << (table[curstr].second.size() - position[ID]) * 4 << "($30)" << endl;
			}
		} else*/ if (rstring == "ID LPAREN arglist RPAREN") {
			string ID = root->children[0]->children[0]->str;
      if (table.find(ID) == table.end()) {
        cerr << "ERROR: procedure has not been declared" << endl;
      } else {
				push(29);
				push(31);
				vector<string> arglist;
				generate(arglist, root->children[2], table, curstr);
				cout << "lis $5" << endl;
				cout << ".word F" << ID << endl;
				cout << "jalr $5" << endl;
				for (int i = 0; i < (int)arglist.size(); i++) {
					cout << "add $30, $30, $4" << endl;
				} 
				pop(31);
				pop(29);
				if (table[ID].first != arglist) {
					cerr << "ERROR: parameters do not match" << endl;
				}	
			}
			
		} else if (rstring == "ID LPAREN RPAREN") {
			string ID = root->children[0]->children[0]->str;
			if (table.find(ID) == table.end()) {
        cerr << "ERROR: procedure has not been declared" << endl;
        cerr << "ERROR: procedure has not been declared" << endl;
      } else {
        if (!table[ID].first.empty()) {
          cerr << "ERROR: parameters do not match" << endl;
        }
      }
			//if (vectorToString(root->children[2]->children) == "") {   
        push(29);
        callProcedure("F" + root->children[0]->children[0]->str);        
				pop(29);
      //}
			
		} else if (rstring == "NEW INT LBRACK expr RBRACK") {
      valueExp(root->children[3], table, curstr);
      cout << "add $1, $3, $0" << endl;
      push(31);
      cout << "lis $5" << endl;
      cout << ".word new" << endl;
      cout << "jalr $5" << endl;
      pop(31);
      cout << "bne $3, $0, 1" << endl;
      cout << "add $3, $11, $0" << endl;
		}
	} 
	
	if (lstring == "procedures") {
    if (rstring == "main") {
      table["wain"];
      curstr = "wain";
      isparam = true;
      prologue();
			for (int i = 0; i < (int) root->children.size(); i++) {
     		check(table, root->children[i], curstr, isparam);
    	}
    } else {
			check(table, root->children[1], curstr, isparam);
			check(table, root->children[0], curstr, isparam);
		}
  }	else if (lstring == "procedure") {
    if (rstring != "") {
      string name = root->children[1]->children[0]->str;
      if (table.find(name) == table.end()) {
        table[name];
        curstr = name;
      } else {
        cerr << "ERROR: duplicate procedures" << endl;
      }
    }
		if (vectorToString(root->children[3]->children) != "") {
			check(table, root->children[3], curstr, isparam);
			int paramnum = table[curstr].first.size();
    	//cout << "HERE IS NUM OF PARAM :" << "paramnum" << endl;
   		for (auto &t : position[curstr]) {
      	t.second -= paramnum;
    	}
		}
			cout << "F" << root->children[1]->children[0]->str << ":" << endl;
			cout << "sub $29, $30, $4" << endl;
			isparam = false;
			check(table, root->children[6], curstr, isparam);
			/*if (vectorToString(root->children[3]->children) != "") {
      	check(table, root->children[3], curstr, isparam);
      	int paramnum = table[curstr].first.size();
      	//cout << "HERE IS NUM OF PARAM :" << "paramnum" << endl;
      	for (auto &t : position[curstr]) {
        	t.second -= paramnum;
      	}
    	}*/
			/*push(1);
			push(2);
			push(5);
			push(6);
			push(7);*/
			//check(table, root->children[6], curstr, isparam);
			check(table, root->children[7], curstr, isparam);
			check(table, root->children[9], curstr, isparam);
			/*pop(7);
			pop(6);
			pop(5);
			pop(2);
			pop(1);*/
			cout << "add $30, $29, $4" << endl;
			cout << "jr $31" << endl;
		//} else {
		//	check(table, root->children[3], curstr, isparam);
		//}
		/*if (vectorToString(root->children[3]->children) != "") {
      check(table, root->children[3], curstr, isparam);
      int paramnum = table[curstr].first.size();
      //cout << "HERE IS NUM OF PARAM :" << "paramnum" << endl;
      for (auto &t : position[curstr]) {
        t.second -= paramnum;
      }
    }*/
  } else if (lstring == "test") {
		if (rstring == "expr LT expr") {
			string str1 = valueExp(root->children[0], table, curstr);
			push(3);
			string str2 = valueExp(root->children[2], table, curstr);
			pop(5);
			if (str1 == str2) {
				if (str1 == "int") {
					cout << "slt $3, $5, $3" << endl;
				} else {
					cout << "sltu $3, $5, $3" << endl;
				}
			}
		} else if (rstring == "expr GT expr") {
			string str1 = valueExp(root->children[2], table, curstr);
      push(3);
      string str2 = valueExp(root->children[0], table, curstr);
      pop(5);
      if (str1 == str2) {
        if (str1 == "int") {
          cout << "slt $3, $5, $3" << endl;
        } else {
          cout << "sltu $3, $5, $3" << endl;
        }
      }
		} else if (rstring == "expr NE expr") {
      string str1 = valueExp(root->children[0], table, curstr);
      push(3);
      string str2 = valueExp(root->children[2], table, curstr);
      pop(5);
			if (str1 == str2) {
        if (str1 == "int") {
					cout << "slt $6, $3, $5" << endl;
      		cout << "slt $7, $5, $3" << endl;
				} else {
					cout << "sltu $6, $3, $5" << endl;
          cout << "sltu $7, $5, $3" << endl;
				}
			}
			cout << "add $3, $6, $7" << endl;
		} else if (rstring == "expr EQ expr") {
			string str1 = valueExp(root->children[0], table, curstr);
      push(3);
      string str2 = valueExp(root->children[2], table, curstr);
      pop(5);
			if (str1 == str2) {
        if (str1 == "int") {
					cout << "slt $6, $3, $5" << endl;
      		cout << "slt $7, $5, $3" << endl;	
				} else {
					cout << "sltu $6, $3, $5" << endl;
      		cout << "sltu $7, $5, $3" << endl;
				}
			}
      cout << "add $3, $6, $7" << endl;
			cout << "sub $3, $11, $3" << endl;
		} else if (rstring == "expr LE expr") {
			string str1 = valueExp(root->children[2], table, curstr);
      push(3);
      string str2 = valueExp(root->children[0], table, curstr);
      pop(5);
			if (str1 == str2) {
				if (str1 == "int") {
      		cout << "slt $3, $5, $3" << endl;
				} else {
					cout << "sltu $3, $5, $3" << endl;
				}	
			}
			cout << "sub $3, $11, $3" << endl;
		} else {
			string str1 = valueExp(root->children[0], table, curstr);
      push(3);
      string str2 = valueExp(root->children[2], table, curstr);
      pop(5);
			if (str1 == str2) {
        if (str1 == "int") {
          cout << "slt $3, $5, $3" << endl;
        } else {
          cout << "sltu $3, $5, $3" << endl;
        }
      }
			cout << "sub $3, $11, $3" << endl;
		}
	}	else if (lstring == "expr") {
		valueExp(root, table, curstr);
	} else if (rstring == "PRINTLN LPAREN expr RPAREN SEMI") {
		push(1);
		valueExp(root->children[2], table, curstr);
		cout << "add $1, $3, $0" << endl;
		push(31);
		//cout << "lis $5" << endl;
		//cout << ".word print" << endl;
		cout << "jalr $10" << endl;
		pop(31);
		pop(1);
	} else if (lstring == "dcls" && rstring == "dcls dcl BECOMES NUM SEMI") {
		check(table, root->children[0], curstr, isparam);
		check(table, root->children[1], curstr, isparam);
		cout << "lis $3" << endl;
    cout << ".word " << root->children[3]->children[0]->str << endl;
    push(3);
		if (curstr == "wain") {
      position[curstr][root->children[1]->children[1]->children[0]->str] = position[curstr].size();
    } else {
      position[curstr][root->children[1]->children[1]->children[0]->str] = position[curstr].size() - table[curstr].first.size();
    }
		//position[curstr][root->children[1]->children[1]->children[0]->str] = position[curstr].size();
	}	else if (lstring == "dcls" && rstring == "dcls dcl BECOMES NULL SEMI") {
		check(table, root->children[0], curstr, isparam);
    check(table, root->children[1], curstr, isparam);
    //cout << "lis $5" << endl;
    //cout << ".word " << root->children[3]->children[0]->str << endl;
		cout << "add $3, $0, $11" << endl;
    push(3);
		if (curstr == "wain") {
    	position[curstr][root->children[1]->children[1]->children[0]->str] = position[curstr].size();
		} else {
			position[curstr][root->children[1]->children[1]->children[0]->str] = position[curstr].size() - table[curstr].first.size();
		}
	} else if (lstring == "statement") {
		if (rstring == "lvalue BECOMES expr SEMI") {
			check(table, root->children[0], curstr, isparam);
			check(table, root->children[2], curstr, isparam);
			if (root->children[0]->children[0]->str == "ID") {
				cout << "sw $3, " << -(position[curstr][(root->children[0]->children[0]->children[0]->str)]-1)*4 << "($29)" << endl;
			} else {
				push(3);
				valueExp(root->children[0]->children[1], table, curstr);
				//cout << "sw $3, " << -(position[(root->children[0]->children[1]->children[0]->children[0]->str)]-1)*4 << "($29)" << endl;
				pop(5);
				cout << "sw $5, 0($3)" << endl;
			} 
		} else if (rstring == "WHILE LPAREN test RPAREN LBRACE statements RBRACE") {
			int lcount = loopcount;
			loopcount += 1;
			cout << "loop" << lcount << ":" << endl;
			check(table, root->children[2], curstr, isparam);
			cout << "beq $3, $0, endWhile" << lcount << endl;
			check(table, root->children[5], curstr, isparam);
			cout << "beq $0, $0, loop" << lcount << endl;
			cout << "endWhile" << lcount << ":" << endl;
		} else if (rstring == "IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE") {
			int icount = ifcount;
			ifcount ++;
			check(table, root->children[2], curstr, isparam);
			cout << "beq $3, $0, else" << icount << endl;
			check(table, root->children[5], curstr, isparam);
			cout << "beq $0, $0, endif" << icount << endl;
			cout << "else" << icount << ":" << endl;
			check(table, root->children[9], curstr, isparam);
			cout << "endif" << icount << ":" << endl;
		} else if (rstring == "DELETE LBRACK RBRACK expr SEMI") {
			valueExp(root->children[3], table, curstr);
			deletecount++;
			cout << "beq $3, $11, skipDelete" << deletecount << endl;
			cout << "add $1, $3, $0" << endl;
			push(31);
			cout << "lis $5" << endl;
			cout << ".word delete" << endl;
			cout << "jalr $5" << endl;
			pop(31);
			cout << "skipDelete" << deletecount << ":" << endl;
		}
	} else if (lstring != "paramlist" && !(lstring == "factor" && rstring == "ID LPAREN arglist RPAREN")) {
		for (int i = 0; i < (int) root->children.size(); i++) {
			check(table, root->children[i], curstr, isparam);
		}
	}
	if (lstring == "main") {
		 epilogue();
	}
}	

void printMap(map<string, pair<vector<string>, map<string, string>>> table) {
	for (auto &subtable : table) {
    cerr << subtable.first << ": ";
		for (int i = 0; i < (int) subtable.second.first.size(); i++) {
			cerr << subtable.second.first[i];
			if (i != (int) subtable.second.first.size() - 1) cerr << " ";
			if (subtable.first == "wain" && i == 2 && subtable.second.first[1] != "int") {
				cerr << "ERROR: second parameter of wain is not int" << endl;
			}
		}
		cerr << endl;
  	for (auto &p : subtable.second.second) {
			cerr << p.first << " " << p.second << endl;
		}
	}
}

bool isWellType(map<string, pair<vector<string>, map<string, string>>> table, Node* root, string curstr) {
	string lstring = root->str;
  string rstring = vectorToString(root->children);
	if (lstring == "procedures" && rstring == "main") {
		curstr = "wain";
		bool dcls = isWellType(table, root->children[0]->children[8], curstr);
		bool stats = isWellType(table, root->children[0]->children[9], curstr);
		//cout << table["wain"].first[1] << endl;
		//cout << dcls << endl;
		//cout << stats << endl;
		if (table["wain"].first[1] == "int" && dcls && stats && 
				valueExp(root->children[0]->children[11], table, "wain") == "int") {
			return true;
		} else {
			//cerr << "ERROR: main is not well typed" << endl;
			return false;
		}
	}
	
	if (lstring == "procedure") {
    curstr = root->children[1]->children[0]->str; 
		bool dcls = isWellType(table, root->children[6], curstr);
    bool stats = isWellType(table, root->children[7], curstr);
		if (dcls && stats && valueExp(root->children[9], table, curstr) == "int") {
      return true;
    } else {
      //cerr << "ERROR: main is not well typed" << endl;
    	return false;
		}
	}
	
	if (lstring == "dcls") {
		if (rstring == "") return true;
		if (rstring == "dcls dcl BECOMES NUM SEMI") {
			if (isWellType(table, root->children[0], curstr) && vectorToString(root->children[1]->children[0]->children) == "INT") {
				return true;
			}	else {
				//cerr << "ERROR: dcls" << endl;
				return false;
			}
		} 
		if (rstring == "dcls dcl BECOMES NULL SEMI") {
			if(isWellType(table, root->children[0], curstr) && vectorToString(root->children[1]->children[0]->children) == "INT STAR") {
				return true;
			} else {
				//cerr << "ERROR: dcls" << endl;
				return false;
			}
		}
		return false;
	}
	
	if (lstring == "statements") {
		if (rstring == "") return true;
		if (rstring == "statements statement") {
			if (isWellType(table, root->children[0], curstr) && isWellType(table, root->children[1], curstr)) {
				return true;	
			} else {
				//cerr << "ERROR: statements" << endl;
				return false;
			}
		}
		return false;
	}
	
	if (lstring == "statement") {
		if (rstring == "lvalue BECOMES expr SEMI") {
			string v1 = valueExp(root->children[0], table, curstr);
			string v2 = valueExp(root->children[2], table, curstr);
			if (v1 == v2 && ((v1 == "int") || (v1 == "int*"))) {
				return true;	
			} else {
				cerr << "ERROR: statement" << endl;
				return false;
			}
		} else if (rstring == "PRINTLN LPAREN expr RPAREN SEMI") {
			if (valueExp(root->children[2], table, curstr) == "int") {
				return true;
			} else {
        cerr << "ERROR: statement" << endl;
        return false;
      }
		} else if (rstring == "DELETE LBRACK RBRACK expr SEMI") {
			if (valueExp(root->children[3], table, curstr) == "int*") {
				return true;
			} else {
        //cerr << "ERROR: statement" << endl;
        return false;
      }
		} else if (rstring == "WHILE LPAREN test RPAREN LBRACE statements RBRACE") {
			if (isWellType(table, root->children[2], curstr) && isWellType(table, root->children[5], curstr)) {
				return true;
			} else {
        //cerr << "ERROR: statement" << endl;
        return false;
      }
		} else {
			if (isWellType(table, root->children[2], curstr) && isWellType(table, root->children[5], curstr) && 
					isWellType(table, root->children[9], curstr)) {
				return true;
			} else {
        //cerr << "ERROR: statement" << endl;
        return false;
      }
		}
	}
	
	if (lstring == "test") {
		string v1 = valueExp(root->children[0], table, curstr);
    string v2 = valueExp(root->children[2], table, curstr);
    if (v1 == v2 && ((v1 == "int") || (v1 == "int*"))) {
			return true;
		} else {
      //cerr << "ERROR: test" << endl;
      return false;
    }
	}
	
	for (int i = 0; i < (int)root->children.size(); i++) {
    isWellType(table, root->children[i], curstr);
  }
	
	return true;
}

int main() {
	Node* root = new Node();
	root = constructTree(root);
	//printTree(root);
	map<string, pair<vector<string>, map<string, string>>> table;
	string str;
	bool isparam = false;
	cout << "; begin prologue" << endl;
  cout << ".import print" << endl;
  cout << ".import init" << endl;
  cout << ".import new" << endl;
  cout << ".import delete" << endl;
  cout << "lis $4 ; new convention $4 always contains 4" << endl;
  cout << ".word 4" << endl;
  cout << "lis $10 ; $10 will always hold address for print" << endl;
  cout << ".word print" << endl;
  cout << "lis $11 ; $11 will always hold 1" << endl;
  cout << ".word 1" << endl;
	check(table, root, str, isparam);
	//isWellType(table, root, str);
	/*for (auto &t : position) {
		cout << t.first << " " << t.second << endl;
	}*/
	//printMap(table);	
	/*for (auto &t : position) {
		cout << t.first << ":" << endl;
		for (auto &s : t.second) {
			cout << s.first << " " << s.second << endl;
		}
	}*/
	deleteTree(root);
	return 0;
}
