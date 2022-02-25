PROJECT:
----------
Build a small intent recognition command line tool.

DESCRIPTION:
-------------
This is an intent recognition command line tool. Which currently supports four intents. User will ask a question, if the intent of it matching with four available intents, it will print that otherwise it will print "No Intent Recognized".

HOW TO RUN:
------------
Clone the repo (use recursive)

git clone --recursive https://github.com/SuchetaBasu/IntentRecognizer.git

cd into the cloned directory

Run below commands from this directory.

chmod 777 scripts/run_main.sh

chmod 777 scripts/run_utest.sh

To execute the main program run below command.

./scripts/run_main.sh

To run the unit test cases run below command.

./scripts/run_utest.sh

EXAMPLE:
---------

******** Intent Detection ********

Enter a question: What is the weather like today? Intent: Get Weather

Enter a question: What is the weather like in Paris today? Intent: Get Weather City

Enter a question: Tell me an interesting fact. Intent: Get Fact

Enter a question: Tell me something about Paris. Intent: Get City Fact