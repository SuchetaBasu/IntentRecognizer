#define TESTING
#include "InputProcessor.h"
#undef TESTING

#include <gtest/gtest.h>

static const string kResourceDataFileLocation = "../data/dataset.json";
static const string kStopWordFileLocation = "../data/stopwords.txt";

TEST(UnitTest, ParseSentenceIntoWord) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    std::vector<std::string> input = {"Welcome","to","Intent","Recognition"};
    std::vector<std::string> output = Utils::ParseSentenceIntoWord("Welcome to Intent Recognition");
    ASSERT_EQ(output, input);
}

TEST(UnitTest, GetInputTermFreq) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    vector<string> inputWords = {"what", "is", "the", "weather", "like", "in", "paris", "today"};
    vector<string> vocabData = {"bangalore", "berlin", "cloudy", "like", "london", "paris", "report", "share", "tell", "temperature", "today", "tomorrow", "weather"};
    unordered_map<string, double> termFreq = {{"like",0.111111},  {"paris",0.037037}, {"bangalore",0.111111}, {"today",0.148148}, 
    {"temperature",0.037037}, {"tell",0.037037}, {"cloudy",0.037037}, {"london",0.037037}, {"share",0.037037}, {"berlin",0.111111}, 
    {"weather",0.222222}, {"tomorrow",0.037037}, {"report",0.037037}};
    vector<double> output = {0, 0, 0, 0.111111, 0, 0.037037, 0, 0, 0, 0, 0.148148, 0, 0.222222};
    ASSERT_EQ(output, Utils::GetInputTermFreq(inputWords, vocabData, termFreq));
}

TEST(UnitTest, GetCosineSimilarity) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    vector<double> inputData1 = {0, 0, 0, 0.111111, 0, 0.037037, 0, 0, 0, 0, 0.148148, 0, 0.222222};
    vector<double> inputData2 = {0, 0.111111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.222222};
    EXPECT_NEAR(0.681554, Utils::GetCosineSimilarity(inputData1, inputData2), .001);
}

TEST(UnitTest, GetIntent) 
{ 
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);

    InputProcessor inputP1(resP, "What is the weather like today");
    ASSERT_EQ("Get Weather", inputP1.GetIntent());

    InputProcessor inputP2(resP, "what is the temperature today?");
    ASSERT_EQ("Get Weather", inputP2.GetIntent());
    
    InputProcessor inputP3(resP, "What is the weather like in Paris today?");
    ASSERT_EQ("Get Weather City", inputP3.GetIntent());
    
    InputProcessor inputP4(resP, "Is it cloudy in Bangalore today?");
    ASSERT_EQ("Get Weather City", inputP4.GetIntent());
    
    InputProcessor inputP5(resP, "Tell me an interesting fact");
    ASSERT_EQ("Get Fact", inputP5.GetIntent());
}

TEST(UnitTest, GetCoSineSimilarityScore) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    InputProcessor inputP(resP, "What is the weather like today?");
    ASSERT_EQ(1, inputP.GetCoSineSimilarityScore("Get Weather"));
}

TEST(UnitTest, GetVocab) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    vector<string> output = { "economy", "funny", "interesting", "last", "new", "past", "share", "somethiing", "tell", "trending", "year" };
    ASSERT_EQ(output, resP->GetVocab("Get Fact"));
}

TEST(UnitTest, GetAllIntents) 
{
    ResourceProcessor *resP = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);
    vector<string> output = {"Get Weather", "Get Fact", "Get Weather City", "Get City Fact"};
    ASSERT_EQ(output, resP->GetAllIntents());
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

