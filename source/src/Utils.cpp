#include<Utils.h>

//Parsing a sentence in to words
vector<string> Utils::ParseSentenceIntoWord(const string & input)
{
    vector<string> tokens;
    if(!input.empty())
    {
        boost::tokenizer<> token(input);
        for(boost::tokenizer<>::iterator itr = token.begin(); itr != token.end(); ++ itr)
            tokens.push_back(*itr);
    }
    return tokens;
}

/*  
Logic: It will search all words of vecInput into vocabulary, if found calculate freq*TF
Example: 
    Vocab: ["the", "weather", "nice", "today"] - size 4
    input: ["how", "the", "weather"]
    output: [(1*TF of "the") (1*TF of "weather") (0) (0)]
Input:
    inputWords - input splitted word vector
    vocabData - calculate base on these list of words
    termFreqData - vocab word's TF is saved on this data
*/
vector<double> Utils::GetInputTermFreq(const vector<string> & inputWords, const vector<string> & vocabData, const unordered_map<string, double> & termFreqData)
{
    std::vector<double> outPut(vocabData.size(), 0);
    for (std::string word : inputWords)
    {
        size_t idx = std::find(vocabData.begin(), vocabData.end(), word) - vocabData.begin();
        if (idx != vocabData.size())
            outPut.at(idx) += termFreqData.at(word);

    }

    return outPut;
}

/*
Input: inputSentence - for which we are calculating vector
       vocabData - calculate base on these list of words
       termFreqData - vocab word's TF is saved on this data
Output: It will return Term frequency vector based on vocabulary
*/
vector<double> Utils::MakeInputForCosine(const string & inputSentence, const vector<string> & vocabData, const unordered_map<string, double> & termFreqData)
{
    //splitting sentence into words
    auto words = ParseSentenceIntoWord(inputSentence);
    return GetInputTermFreq(words, vocabData, termFreqData);
}


//Calculating Cosine similarity of two vector - Cos(x, y) = x . y / ||x|| * ||y||
double Utils::GetCosineSimilarity(const vector<double> & data1, const vector<double> & data2)
{
    assertm(data1.size() == data2.size(), "Error in GetCosineSimilarity, Please check the Input and the reference data file");
    
    double d1, d2, d3 = 0;
    unsigned int len = data1.size();
    for (unsigned int i = 0; i < len; ++i)
    {
        d1 += (data1[i] * data2[i]);
        d2 += (data1[i] * data1[i]);
        d3 += (data2[i] * data2[i]);
    }

    return d1 / (sqrt(d2) * sqrt(d3));
}