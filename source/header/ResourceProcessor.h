#ifndef RESOURCEPROCESSOR_H
#define RESOURCEPROCESSOR_H

/*************************************************************************************************
 * < ResourceProcessor >
 *
 * A class to handle the resource data - mainly modeling data.
 * 
 * The reference senteces are used for the finding the intent, can be found in the data folder. 
 * Here json file has used for storing list of possible sentences & tags associated with intent & text file contains
 * stop words . Now we We can add more data tagged with intent in future to make model more accurate.
 * 
 * Future scope: 
 * We can add multiple tag for a particular intent.
 * We can add language specific file to support more language.
 * 
 * This is a singleton class. Below things are done here :
 * Reference data reading from json file.
 * Stop word reading from text file.
 * Using json data making vocabulary for each intent.
 * Constructing term frequency vector for all sentence present in json file.
 * So once this object is created, it means model is ready to process user input data.
 * 
 * Future Scope: 
 * Using this class we can do tag(name, location) identification
 *
 * This program uses cosine similarity along with term frequency
 * to measure the similary between given sentence and the reference sentence
 *
 *
 *************************************************************************************************/



#include <fstream>
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include <rapidjson/prettywriter.h> // for stringify JSON
#include <rapidjson/istreamwrapper.h>
#include <Utils.h>

using namespace std;
using namespace rapidjson;

class ResourceProcessor
{
private:

	static ResourceProcessor *mInstance;

	//This map holds resource data - key - intent, value - list of reference sentences
	map<string, vector<string>> mResourceData;

    //This map holds resource data - key - intent, value - list tagged data
    map<string, unordered_set<string>> mResourceTagData;

    /*  NOTE: As of now, we have only one tag per intent. 
    *   When more than one tag will be supported this need to changed.
    *   Instead of taking unordered_set<string>, we have to take map <tag, tagdata>
    */

	//This vector store all intents available for this model
	vector<string> mIntentList;

	//This map holds processed data - key - intent, unordered_map - < word, tf >
	map<string, std::unordered_map<string, double>> mProcessedResourceData;

	//This map holds all words tagged to intent - < (key - intent) ,(data - list of words)>
	map<string, vector<string>> mIntentVocab;

	//This will store all stop words
	unordered_set<string> mStopWords;

	//we are making input vector for checking cosinSimilarity for each input sentence
	//This map holds the data for this input vector. key - intent - data - list of 
	map<string, vector<vector<double>>> mStoredRefData;

	ResourceProcessor(const string & dataFilePath, const string & stopWordFilePath);
	void MakeResourceData(Document & resData);
	void MakeInputForCosineOfResourceSentence();
	void LoadStopWord(ifstream & stopWordFile);
	void ProcessResourceData();

public:
	static ResourceProcessor * GetResourceProcessorInstance(const string & dataFilePath, const string & stopWordFilePath);
	vector<string> GetVocab(const string& intent) { return mIntentVocab[intent];};
	unordered_map<string, double> GetTermFrequencyForVocabWords(const string& intent) { return mProcessedResourceData[intent];};
	vector<string> GetAllIntents() { return mIntentList;};
	vector<vector<double>> GetInputForCosineOfResourceSentence(const string& intent) { return mStoredRefData[intent]; };
    unordered_set<string> GetIntentTag(const string& intent) { return mResourceTagData[intent]; };
};

#endif