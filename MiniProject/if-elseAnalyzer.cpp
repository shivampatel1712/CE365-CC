#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Token types for a simplified if-else syntax
enum TokenType {
    IF,
    ELSE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    IDENTIFIER,
    OPERATOR, // =, ==, !=, <, >, <=, >=
    NUMBER,
    SEMICOLON,
    INVALID,
    END_OF_INPUT
};

// Token structure
struct Token {
    TokenType type;
    string value;
};

// Lexer function to tokenize the input string
vector<Token> lexer(const string& input) {
    vector<Token> tokens;
    stringstream ss(input);
    char c;
    string buffer;

    while (ss.get(c)) {
        buffer = c;

        if (isspace(c)) {
            continue;
        } else if (c == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
        } else if (c == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
        } else if (c == '{') {
            tokens.push_back({TokenType::LBRACE, "{"});
        } else if (c == '}') {
            tokens.push_back({TokenType::RBRACE, "}"});
        } else if (c == ';') {
            tokens.push_back({TokenType::SEMICOLON, ";"});
        } else if (isalpha(c)) {
            while (ss.peek() != EOF && (isalnum(ss.peek()) || ss.peek() == '_')) {
                buffer += ss.get();
            }
            if (buffer == "if") {
                tokens.push_back({TokenType::IF, "if"});
            } else if (buffer == "else") {
                tokens.push_back({TokenType::ELSE, "else"});
            } else {
                tokens.push_back({TokenType::IDENTIFIER, buffer});
            }
        } else if (isdigit(c)) {
            while (ss.peek() != EOF && isdigit(ss.peek())) {
                buffer += ss.get();
            }
            tokens.push_back({TokenType::NUMBER, buffer});
        } else if (c == '=' || c == '!' || c == '<' || c == '>') {
            if(ss.peek() == '='){
                buffer += ss.get();
            }
            tokens.push_back({TokenType::OPERATOR, buffer});
        }
        else {
            tokens.push_back({TokenType::INVALID, buffer});
        }
    }

    tokens.push_back({TokenType::END_OF_INPUT, ""});
    return tokens;
}

// Parser function to analyze the token stream
bool parser(const vector<Token>& tokens) {
    int currentToken = 0;

    auto match = [&](TokenType expectedType) -> bool {
        if (tokens[currentToken].type == expectedType) {
            currentToken++;
            return true;
        }
        return false;
    };

    auto expression = [&]() -> bool {
        // Simplified expression: identifier operator number
        if (match(TokenType::IDENTIFIER) && match(TokenType::OPERATOR) && match(TokenType::NUMBER)) {
            return true;
        }
        return false;
    };

    auto block = [&]() -> bool {
        if (!match(TokenType::LBRACE)) {
            return false;
        }
        // Simplified block: just require a closing brace
        while(tokens[currentToken].type != TokenType::RBRACE && tokens[currentToken].type != TokenType::END_OF_INPUT){
            currentToken++;
        }
        return match(TokenType::RBRACE);
    };

    auto ifStatement = [&]() -> bool {
        if (!match(TokenType::IF)) {
            return false;
        }
        if (!match(TokenType::LPAREN)) {
            return false;
        }
        if (!expression()) {
            return false;
        }
        if (!match(TokenType::RPAREN)) {
            return false;
        }
        if (!block()) {
            return false;
        }
        return true;
    };

    auto elseStatement = [&]() -> bool {
        if (!match(TokenType::ELSE)) {
            return false;
        }
        if (!block()) {
            return false;
        }
        return true;
    };

    if (!ifStatement()) {
        return false;
    }

    if (tokens[currentToken].type == TokenType::ELSE) {
        if (!elseStatement()) {
            return false;
        }
    }

    if (tokens[currentToken].type != TokenType::END_OF_INPUT) {
        return false;
    }

    return true;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    string input;
    string line;
    while (getline(inputFile, line)) {
        input += line + " "; // Add spaces between lines to simulate original code spacing.
    }
    inputFile.close();

    vector<Token> tokens = lexer(input);

    cout << "Tokens:\n";
    for (const auto& token : tokens) {
        cout << "Type: " << token.type << ", Value: '" << token.value << "'\n";
    }

    if (parser(tokens)) {
        cout << "Syntax is valid.\n";
    } else {
        cout << "Syntax is invalid.\n";
    }

    return 0;
}