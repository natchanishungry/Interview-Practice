#include <iostream>
#include <cstring>
#include <string>
#include <array>

using namespace std;

//Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
//cannot use additional data structures?

bool isUnique(string s){ //O(1)
	if(s.length() > 256) return false; //it is O(1) because we discard all strings with
									//length greater than ASCII chart length(pigeonhole principle)

	bool values[256] = {false};
	for(int i = 0; i<s.length(); i++){
		if(values[s[i]]) return false;
		values[s[i]] = true;
	}

	//for(int i = 0; i<sizeof(values)/sizeof(*values); i++) std::cout<<values[i];

	return true;
} 

//Check Permutation: Given two strings, write a method to decide if one is a permutation of the
//other. 

bool checkPermutation(string s1, string s2){ //O(n), case sensitive, whitespace significant
	if(s1.length() != s2.length()) return false;

	int values[256] = {0};
	for(int i = 0; i<s1.length(); i++) values[s1[i]]++;
	for(int i = 0; i<s2.length(); i++){
		values[s2[i]]--;
		if(values[s2[i]] < 0) return false;
	} 	
		
	return true;
}

// URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
// has sufficient space at the end to hold the additional characters, and that you are given the "true"
// length of the string. (Note: If implementing in Java, please use a character array so that you can
// perform this operation in place.) 

void URLify(string &s){ //O(n)
	string buff = "";
	
	for(int i = 0; i<s.length(); i++){
		if(s[i]==' '){		
			buff+="%20";
		} 
		if(buff.length() != 0){
			if(s[i]!=' ') buff += s[i];
			s[i] = buff[0];
			buff.erase(0, 1);
		}
	}
	s += buff;
}

// Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome. 
// A palindrome is a word or phrase that is the same forwards and backwards. A permutation
// is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words. 

bool palindromePermutation(string s){ //O(n)
	bool values[256] = {0};
	bool oddEncountered = false;
	for(int i = 0; i<s.length(); i++) values[s[i]] = !values[s[i]];

	for(int i = 0; i<sizeof(values)/sizeof(*values); i++){
		if(values[i] == false){
			if(oddEncountered) return false;
			oddEncountered = true;
		}
	}
	return true;
}

// One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character, or replace a character. Given two strings, write a function to check if they are
// one edit (or zero edits) away. 

bool oneAway(string s1, string s2){ //O(n)
	int l = (int)s1.length() - (int)s2.length();
	if(l > 1 || (l*-1) > 1) return false;

	bool discrepancyFound = false;

	int length = (s1.length() < s2.length())? s1.length() : s2.length();
	if(s1.length() < s2.length()){
		string temp = s1;
		s1 = s2;
		s2 = temp;
	} //s1 will always be the string with more characters
	
	bool removedOrInsertedC, replacedC;
	removedOrInsertedC = replacedC = true;

	for(int i = 0; i<length; i++){
		if(s1[i] != s2[i]){
			discrepancyFound = true;
		}
		if(discrepancyFound){
			//removed or inserted character
			if(removedOrInsertedC){
				if(s1[i+1] != s2[i]) removedOrInsertedC = false;
			}
			//replaced character
			if(replacedC){
				if(s1[i+1] != s2[i+1]) replacedC = false;
			}
		}
	}

	if(discrepancyFound && (removedOrInsertedC || replacedC) || !discrepancyFound) return true;
	return false;

}

//Number Swapper: Write a function to swap a number in place (that is, without temporary variables). 
void numSwap(int& a, int& b){
	b = b + a;
	a = b - a;
	b = b - a;
	cout << "a= " << a << ", b= " << b;
}

int main(){
	cout << "isUnique: " << isUnique("asdfghj") << endl;
	cout << "checkPermutation: " << checkPermutation("asdfgh", "hgfdas") << endl;
	string s = "asdfgh hihi";
	URLify(s);
	cout << "URLify: " << s << endl;
	cout << "oneAway: " << oneAway("pale", "palke") << endl;
	cout << "numSwap: ";
	int a = 5; int b = 4;
	numSwap(a, b);
	cout << endl;

	return 0;
}

