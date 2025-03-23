#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSets;
map<char, set<char>> followSets;

// Function to compute First Set
void computeFirst(char symbol) {
    if (!firstSets[symbol].empty()) return;

    for (const string &production : grammar[symbol]) {
        bool epsilonPresent = true;

        for (char c : production) {
            if (isupper(c)) {  // If non-terminal
                computeFirst(c);
                for (char first : firstSets[c]) {
                    if (first != 'ε') firstSets[symbol].insert(first);
                    else epsilonPresent = true; // ε is present, so continue to next symbol
                }
                if (!epsilonPresent) break; // Stop if a non-ε terminal is found
            } else {  // If terminal
                firstSets[symbol].insert(c);
                epsilonPresent = false;
                break;
            }
        }

        if (epsilonPresent) firstSets[symbol].insert('ε'); // If all symbols were nullable, add ε
    }
}

// Function to compute Follow Set
void computeFollow(char symbol) {
    if (!followSets[symbol].empty()) return;

    if (symbol == 'S') followSets[symbol].insert('$'); // Start symbol gets $

    for (auto &[lhs, productions] : grammar) {
        for (const string &production : productions) {
            for (size_t i = 0; i < production.length(); i++) {
                if (production[i] == symbol) {
                    if (i + 1 < production.length()) { // Check next symbol
                        char nextSymbol = production[i + 1];

                        if (isupper(nextSymbol)) {  // If next is non-terminal
                            for (char first : firstSets[nextSymbol]) {
                                if (first != 'ε') followSets[symbol].insert(first);
                            }
                            if (firstSets[nextSymbol].count('ε')) { // If ε is in First(nextSymbol)
                                computeFollow(lhs);
                                followSets[symbol].insert(followSets[lhs].begin(), followSets[lhs].end());
                            }
                        } else {  // If next is terminal
                            followSets[symbol].insert(nextSymbol);
                        }
                    } else {  // If symbol is at the end of production
                        computeFollow(lhs);
                        followSets[symbol].insert(followSets[lhs].begin(), followSets[lhs].end());
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    
    cout << "Enter grammar (e.g., S=AB|a):\n";
    for (int i = 0; i < n; i++) {
        char lhs;
        string rhs;
        cin >> lhs >> rhs;

        size_t pos = 0;
        string production;
        while ((pos = rhs.find('|')) != string::npos) {
            production = rhs.substr(0, pos);
            grammar[lhs].push_back(production);
            rhs.erase(0, pos + 1);
        }
        grammar[lhs].push_back(rhs);
    }

    // Compute First Sets
    for (auto &[symbol, _] : grammar) computeFirst(symbol);

    // Compute Follow Sets
    for (auto &[symbol, _] : grammar) computeFollow(symbol);

    // Output First Sets
    cout << "\nFirst Sets:\n";
    for (auto &[symbol, firstSet] : firstSets) {
        cout << "First(" << symbol << ") = { ";
        for (char first : firstSet) cout << first << " ";
        cout << "}\n";
    }

    // Output Follow Sets
    cout << "\nFollow Sets:\n";
    for (auto &[symbol, followSet] : followSets) {
        cout << "Follow(" << symbol << ") = { ";
        for (char follow : followSet) cout << follow << " ";
        cout << "}\n";
    }

    return 0;
}
