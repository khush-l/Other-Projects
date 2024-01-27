//Author:Khush Lalchandani
# include <iostream>
#include <string>
using namespace std;

// returns count of non-overlapping occurrences of 'sub' in 'str'
int countSubstring(const string& str, const string& sub)
{
	if (sub.length() == 0) return 0;
	int count = 0;
	for (int offset = str.find(sub); offset != string::npos; 
		offset = str.find(sub, offset + sub.length()))
	{
		++count;
	}
	return count;
}
int numberWords(const string& str)
{
  int count=1;
  for (int i=0;i<str.length()-1;i++){
    if ((str[i] == ' ')&&(isdigit(str[i+1])==0)&&(str[i+1]!=' ')){
      count++;
    }
  }
  return count;
}
int uniqueWords(const string& str)
{
  string lowerStr = str;
  for (char& c: lowerStr){
    c = tolower(c);
  }
  const int max = numberWords(str);
  string uniqueWords[max];
  int numUniqueWords = 0;
  string word;
  for (char f:lowerStr){
    if (isalpha(f)){
      word+=f;
    }
    else if (!word.empty()){
      bool isUnique= true;
    for (int i=0;i<numUniqueWords;++i){
      if (word==uniqueWords[i]){
        isUnique=false;
        break;
      }
    }
      if (isUnique && numUniqueWords < max){
        uniqueWords[numUniqueWords++] = word;
      }
      word.clear();
    }
  }
  return numUniqueWords;
}
int numSentences(const string& str)
{
  int count = 0;
  for (int i=0;i<str.length();i++){
    if (str[i]=='.'){
      count++;
    }
  }
  return count;
}

int averageWPS(const string& str){
  int words=numberWords(str);
  int sentences=numSentences(str);
  return words/sentences;
}

int lexicalDensity(const string& str){
  double wordTotal = numberWords(str);
  double wordUnique = uniqueWords(str);
  double lexicalD = (wordUnique/wordTotal)*100;
  lexicalD+=.5;
  return (int)lexicalD;
}
int main()
{

   string source = ("I was born in Lousiana down on the ol bayou raised on shrimps and catfish mamas good gumbo.  I got the ramblin fever.  Said goodbye to ma and pa.   Crossed that ol red river and this is what I saw. I saw miles and miles of Texas 1000 stars up in the sky.  I saw miles and miles of Texas gonna live here till I die.");


	cout << "substring count: " << countSubstring(source, "is")        << '\n';
  cout << "word count: " << numberWords(source)   << '\n';
  cout << "Unique word count: " << uniqueWords(source)   << '\n';
  /*cout << "Sentence count: " << numSentences(source) <<'\n';
  cout << "Average Words per Sentence: " << averageWPS(source) <<'\n';*/
  cout << "Lexical density: " << lexicalDensity(source) << "%" <<'\n';

	return 0;
}