#include <ResourceProcessor.h>

ResourceProcessor* ResourceProcessor::mInstance = nullptr;

//Constructor
ResourceProcessor::ResourceProcessor(const string & dataFilePath, const string & stopWordFilePath)
{
    ifstream streamData(dataFilePath);
    IStreamWrapper streamDataWrapper(streamData);
    
    Document resourceData;
    resourceData.ParseStream(streamDataWrapper);
    assertm(resourceData.IsObject(), "Error in accessing data, Please check the reference data file");

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    resourceData.Accept(writer);

    //Making resource data ready
    MakeResourceData(resourceData);

    ifstream stopWordFile;
    stopWordFile.open(stopWordFilePath);
    assertm(stopWordFile.is_open(), "Error in accessing stop word data, Please check the reference data file");
        
    LoadStopWord(stopWordFile);

    ProcessResourceData();
    MakeInputForCosineOfResourceSentence();

    //All resource data processing complete. Now it is ready to process input.
}

//Creating instance of ResourceProcessor
ResourceProcessor * ResourceProcessor::GetResourceProcessorInstance(const string & dataFilePath, const string & stopWordFilePath)
{
    if(!mInstance)
        mInstance = new ResourceProcessor(dataFilePath, stopWordFilePath);
    return mInstance;
}

//Reading data from json file & filling into map, where key is string & value is list of sentences.
void ResourceProcessor::MakeResourceData(Document & resData)
{
	if(resData.HasMember("intents"))
	{
        for(auto &intent:resData["intents"].GetArray())
        {
            auto currentIntent = intent["intent"].GetString();
            if(intent.HasMember("texts"))
            {
                vector<string> texts;
                for(auto &line:intent["texts"].GetArray()){
                    texts.push_back(line.GetString());
                }
                mIntentList.push_back(currentIntent);
                mResourceData[currentIntent] = texts;
            }
            if(intent.HasMember("tags"))
            {
                unordered_set<string> cityTagsList;
                auto cities = intent["tags"].GetObject();
                for(auto &city:cities["city"].GetArray()){
                    string cityName = city.GetString();
                    cityTagsList.insert(cityName);
                }
                mResourceTagData[currentIntent] = cityTagsList;
            }
        }
	}
}

//Loading stop word from file
void ResourceProcessor::LoadStopWord(ifstream & stopWordFile)
{
    string word;
    while (stopWordFile >> word)
    {
        mStopWords.insert(word);
    }
}

/* Processing resource data
*   Logic : 
*   Remove all stop word from reference sentences
*   Calculate frequency of each word
*   Calculate term frequency (frequency/total word count) of each word
*   Store in this data in against intent.
*/
void ResourceProcessor::ProcessResourceData()
{
    for(auto & resourceData: mResourceData)
    {
        //count of all non-stop words for intent
        int totalWordCount = 0;

        //store unique words tagged to intent
        std::vector<std::string> words;
        
        //store frequency of word
        std::unordered_map<string, int> wordFrequencyList;
        
        //store term frequency of word
        std::unordered_map<string, double> wordTermFrequencyList;
        for(auto resourceWord: resourceData.second)
        {
            if(!resourceWord.empty())
            {
                boost::tokenizer<> tok(resourceWord);
                for(boost::tokenizer<>::iterator itr = tok.begin(); itr != tok.end(); ++ itr) 
                {
                    string word = *itr;
                    boost::algorithm::to_lower(word);
                    //Remove StopWord
                    if(mStopWords.find(word) != mStopWords.end()) continue;
                    wordFrequencyList[word]++;
                    totalWordCount++;
                }
            }
        }
        //calculating term frequency for each word -- freq/total word count
        for(auto wordFrequencyPair:wordFrequencyList)
        {
            wordTermFrequencyList[wordFrequencyPair.first] = ((double)wordFrequencyPair.second) / (double)totalWordCount;
            words.push_back(wordFrequencyPair.first);
        }

        sort(words.begin(), words.end());

        //store vocabulary tagged to intent
        mIntentVocab[resourceData.first] = words;
        
        //storing all word term frequency data against intent
        mProcessedResourceData[resourceData.first] = wordTermFrequencyList;
    }
}

//Making input vector for checking cosinSimilarity for each sentences present in resource data
void ResourceProcessor::MakeInputForCosineOfResourceSentence()
{
    //Processing each intent
    for(auto & resourceData: mResourceData)
    {
        //processing list of sentence listed against intent
        vector<vector<double>> refdataList; 
        for(auto resourceSentence: resourceData.second)
        {
            if(!resourceSentence.empty())
            {
                boost::algorithm::to_lower(resourceSentence);
                auto refData = Utils::MakeInputForCosine(resourceSentence, mIntentVocab[resourceData.first], mProcessedResourceData[resourceData.first]);
                refdataList.push_back(refData);
            }
        }
        //storing
        mStoredRefData[resourceData.first] = refdataList;
    }
}
