// https://www.codeeval.com/open_challenges/94/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>

#define BUFFER_LENGTH 256

enum TOKEN_TYPE {
	TOK_OPER,
	// All minus signs are treated as negatives initially.
	// while building the parse tree the analyzer can convert it
	// to subtraction operator if appropriate.
	TOK_NEG,
	TOK_NUM,
	TOK_PAREN_OPEN,
	TOK_PAREN_CLOSE,
	TOK_EOF
};

struct Token {
	union {
		double val;
		char op;
	};
	TOKEN_TYPE type;
};

struct Node {
public:
	Node(): left(NULL), right(NULL), parent(NULL) {
		data.type = TOK_EOF;
	}
	~Node() {
		delete left;
		delete right;
	}
	// Attempts to insert a new child between this node and one of its
	// children.
	void spliceNode(Node *newChild,Node *oldChild) {
		assert(oldChild == left || oldChild == right);
		oldChild->parent = newChild;
		newChild->parent = this;
		newChild->left = oldChild;
		if(oldChild == left) {
			left = newChild;
		} else {
			right = newChild;
		}
	}

	Token data;
	Node *left;
	Node *right;
	Node *parent;
};

Token tokenize(char **linePos) {
	Token tok;
	tok.type = TOK_EOF;
	//printf("Starting run at %s\n",*linePos);

	bool parsed = false;
	char c = **linePos;
	while(c != '\0') {
		//printf("c=%c\n",c);
		if((c >= '0' && c <= '9') || c == '.') {
			// Parse a number
			tok.type = TOK_NUM;
			char *start = *linePos;
			char *end = *linePos+1;
			// Not foolproof - assuming all numbers are well-formed
			while((*end >= '0' && *end <= '9') || *end == '.') {
				end++;
			}
			tok.val = atof(start);
			*linePos = end-1;
			parsed = true;
		} else if(c == '-') {
			tok.type = TOK_NEG;
			tok.op = c;
			parsed = true;
		} else if(c == '+' ||
				  c == '^' ||
				  c == '*' ||
				  c == '/') {
			tok.type = TOK_OPER;
			tok.op = c;
			parsed = true;
		} else if(c == ')') {
			tok.type = TOK_PAREN_CLOSE;
			parsed = true;
		} else if(c == '(') {
			tok.type = TOK_PAREN_OPEN;
			parsed = true;
		}
		(*linePos)++;
		c = **linePos;
		if(parsed) {
			break;
		}
	}

	//printf("Tokenized (val=%f,op=%c,type=%d)\n",tok.val,tok.op,tok.type);

	return tok;
}

double evaluateTree(Node *n) {
	switch(n->data.type) {
	case TOK_OPER:
		switch(n->data.op) {
			case '-':
				return evaluateTree(n->left)-evaluateTree(n->right);
			case '+':
				return evaluateTree(n->left)+evaluateTree(n->right);
			case '/':
				return evaluateTree(n->left)/evaluateTree(n->right);
			case '*':
				return evaluateTree(n->left)*evaluateTree(n->right);
			case '^':
				return pow(evaluateTree(n->left),evaluateTree(n->right));
		}
	case TOK_NEG:
		return -evaluateTree(n->left);
	case TOK_NUM:
		return n->data.val;
	case TOK_PAREN_OPEN:
	default:
		return evaluateTree(n->left);
	}
}

int operPriority(const Token& tok) {
	if(tok.type == TOK_NEG) {
		return 4;
	} else if(tok.type == TOK_OPER) {
		switch(tok.op) {
		case '^':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
		default:
			return 1;
		}
	} else {
		return -1;
	}
}

void _printTree(Node *n) {
	if(n->data.type == TOK_OPER) {
		_printTree(n->left);
		printf("%c",n->data.op);
		_printTree(n->right);
	} else if(n->data.type == TOK_NEG) {
		printf("-");
		_printTree(n->left);
	} else if(n->data.type == TOK_NUM) {
		printf("%f",n->data.val);
	} else if(n->data.type == TOK_PAREN_OPEN) {
		printf("(");
		_printTree(n->left);
		printf(")");
	}
}
void printTree(Node *n) {
	_printTree(n);
	printf("\n");
}

double parseExpr(char *line) {
	Token tok;
	tok.type = TOK_EOF;
	Token lastToken = tok;
	Node *root = new Node();
	tok = tokenize(&line);
	while(tok.type != TOK_EOF) {
		switch(tok.type) {
			case TOK_NUM:
				assert(root->data.type == TOK_EOF);
				root->data = tok;
				break;
			case TOK_NEG:
				// If it's truly a negative, make it a unary node, otherwise
				// It becomes a minus.
				if(lastToken.type == TOK_OPER || lastToken.type == TOK_EOF ||
				   lastToken.type == TOK_PAREN_OPEN) {
					root->data = tok;
					root->left = new Node();
					root->left->parent = root;
					root = root->left;
			//		printf("Got a negative\n");
					break;
				} else {
					tok.type = TOK_OPER;
				}
			case TOK_OPER:
				{
				// Move up the tree until hitting parenthesis, end of scope,
				// or lower-priority operator
			//	printf("Got an oper\n");
				while(root->parent != NULL && root->parent->data.type != TOK_PAREN_OPEN &&
					  operPriority(root->parent->data) >= operPriority(tok)) {
					root = root->parent;
				}
				Node *n = new Node();
				n->data = tok;
				if(root->parent != NULL) {
					root->parent->spliceNode(n,root);
				} else {
					root->parent = n;
					n->left = root;
				}
				n->right = new Node();
				n->right->parent = n;
				root = n->right;
				}
				break;
			case TOK_PAREN_OPEN:
				root->data = tok;
				root->left = new Node();
				root->left->parent = root;
				root = root->left;
				break;
			case TOK_PAREN_CLOSE:
				do {
					root = root->parent;
				} while(root->data.type != TOK_PAREN_OPEN);
				break;
		}
		lastToken = tok;
		tok = tokenize(&line);
	}

	while(root->parent != NULL) {
		root = root->parent;
	}

	if(root->data.type != TOK_EOF) {
		//printTree(root);
		return evaluateTree(root);
	} else {
		return nan("");
	}
}

// Deals with the fussy print requirements.
void printNum(double n, char *buf) {
	int chars = sprintf(buf,"%.5f",n);
	// Get rid of trailing zeroes
	chars--;
	while(buf[chars] == '0') {
		buf[chars] = '\0';
		chars--;
	}
	if(buf[chars] == '.') {
		buf[chars] = '\0';
	}
}

int main(int argc, char *argv[]) {
	std::ifstream fid;
	fid.open(argv[1],std::ios::in);

	if(!fid.is_open()) {
		fprintf(stderr,"Error opening file!\n");
	}

	char buffer[BUFFER_LENGTH];

	while(!fid.eof()) {
		fid.getline(buffer,BUFFER_LENGTH);
		if(strlen(buffer) == 0) {
			continue;
		}
		//printf("Analyzing new line %s\n",buffer);
		double answer = parseExpr(buffer);
		printNum(answer,buffer);
		printf("%s\n",buffer);
	}
	fid.close();

	return 0;
}