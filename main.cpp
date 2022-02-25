
#include "ResourceProcessor.h"
#include "InputProcessor.h"

using namespace std;

static const string kResourceDataFileLocation = "../data/dataset.json";
static const string kStopWordFileLocation = "../data/stopwords.txt";

int main(){

    ResourceProcessor *resProcessor = ResourceProcessor::GetResourceProcessorInstance(kResourceDataFileLocation, kStopWordFileLocation);

    cout << "\n********  Intent Detection ********" << std::endl;
    while(true) {
        std::string inputText;
        std::cout<<"Enter a question: ";
        std::getline(std::cin, inputText);

        InputProcessor inputProcessor(resProcessor, inputText);
        std::cout<< "Intent: "<< inputProcessor.GetIntent() <<std::endl<<std::endl;
    } 
    return 0;
}