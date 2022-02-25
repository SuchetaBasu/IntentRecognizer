#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

/*************************************************************************************************
 * < InputProcessor >
 *
 * A class to process user input and detect intent.
 * 
 * This program uses cosine similarity along with term frequency
 * to measure the similary between given sentence and the reference sentence and
 * detect intent based on the score of reference sentences present in json file.
 * 
 * Logic:
 * For each intent present in model, we will get cosine similarity for list of sentences.
 * Find maxsimilarityScore[i] = score for intent[i] data set 
 * Find SimilarityScore = max(maxsimilarityScore[0], maxsimilarityScore[0],....maxsimilarityScore[n])
 * 
 * Here we have combined intent like "Get Weather" & "Get Weather City". So there is a chance we can get
 * almost similar value for both intent. If that happen, we will check tagged data associated with the intent.
 *
 * Future Scope:
 * From intent we can predict the expected output.
 * Tagged data can be categorized.
 *************************************************************************************************/

#include<ResourceProcessor.h>

class InputProcessor
{
private:
	ResourceProcessor *mResourceProcessor;
	std::string mInputString;
//This is for unit testing
#ifdef TESTING
public:
#endif
	double GetCoSineSimilarityScore(const std::string & intent);
	int GetMatchingTagScore(const string & intent);
public:
	InputProcessor(ResourceProcessor *resProcessor, const std::string & input);
	std::string GetIntent();
};
#endif