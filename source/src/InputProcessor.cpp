#include<InputProcessor.h>
#include <cmath>

static const string kNoIntent = "No Intent Recognized";
static const double kMinSimilarityScore = 0.5;

//Constructor
InputProcessor::InputProcessor(ResourceProcessor *resProcessor, const std::string & input)
{
    mResourceProcessor = resProcessor;
    mInputString = input;
}

//Finding the intent for user input
std::string InputProcessor::GetIntent()
{
    std::string intentResult = kNoIntent;
    double similarityScore = 0.0;

    if(mInputString.empty())
    {
        std::cout<< "Please input a valid sentence" << std::endl; 
    }

    auto intents = mResourceProcessor->GetAllIntents();
    //Get Score for all intents
    for(auto & intent: intents)
    {
        double currentIntentSimilarityScore = GetCoSineSimilarityScore(intent);
        //This check for if two intents have almost same score
        if(abs(currentIntentSimilarityScore - similarityScore)<std::numeric_limits<double>::epsilon() && intentResult.compare(kNoIntent))
        {
            //check for tagged data score
            if(GetMatchingTagScore(intent) > GetMatchingTagScore(intentResult))
            {
                similarityScore = currentIntentSimilarityScore;
                intentResult = intent;
            }
        }
        //assigning intent which is having more score
        else if(currentIntentSimilarityScore > similarityScore)
        {
            similarityScore = currentIntentSimilarityScore;
            intentResult = intent;
        }
    }

    //if none of them meeting minimum criteria, we need to improve our dataset
    if(similarityScore < kMinSimilarityScore)
        return kNoIntent;
    return intentResult;
}

//Finding max cosine similarity value in set of sentences which is tagged with strIntent
double InputProcessor::GetCoSineSimilarityScore(const std::string & intent)
{
    auto intentVocabList = mResourceProcessor->GetVocab(intent);
    auto termFreqData = mResourceProcessor->GetTermFrequencyForVocabWords(intent);
    boost::algorithm::to_lower(mInputString);
    auto inputRef = Utils::MakeInputForCosine(mInputString, intentVocabList, termFreqData);
    double similarity = 0.0;

    auto resourceSentencesInputForCosine = mResourceProcessor->GetInputForCosineOfResourceSentence(intent);
    for(auto & sentenceRef: resourceSentencesInputForCosine)
    {
        similarity = max(similarity, Utils::GetCosineSimilarity(inputRef, sentenceRef));
    }

    return similarity;
}

//It will just find each word of input sentence into tagged data, if found add the count & in the end it will return total matched word count
int InputProcessor::GetMatchingTagScore(const string & intent)
{
    auto intentTagList = mResourceProcessor->GetIntentTag(intent);
    if(intentTagList.empty()) return 0;
    int taggedCount = 0;
    auto parseWords = Utils::ParseSentenceIntoWord(mInputString);
    for(auto word: parseWords)
    {
        boost::algorithm::to_lower(word);
        if(intentTagList.find(word) != intentTagList.end())
            taggedCount++;
    }
    return taggedCount;
}