#ifndef UTILS_H
#define UTILS_H

/*************************************************************************************************
 * < Utils >
 *
 * A class to handle all utility function, which ResourceProcessor & InputProcessor both needs to
 * process the data.
 *
 *************************************************************************************************/

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

#define assertm(exp, msg) assert(((void)msg, exp))

class Utils
{
public:
	static vector<string> ParseSentenceIntoWord(const string & input);
	static vector<double> GetInputTermFreq(const vector<string> & inputWords, const vector<string> & vocabData, const unordered_map<string, double> & termFreqData);
	static vector<double> MakeInputForCosine(const string & inputSentence, const vector<string> & vocabData, const unordered_map<string, double> & termFreqData);
	static double GetCosineSimilarity(const vector<double> & data1, const vector<double> & data2);
};
#endif