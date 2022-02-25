DIR="build"
if [ -d "$DIR" ]; then
  ### Take action if $DIR exists ###
  cd build
else
  ###  Control will jump here if $DIR does NOT exists ###
  echo "Making ${DIR}..."
  mkdir build
  echo "Installing config files in ${DIR}..."
  cd build
  cmake ..
  make
fi
echo "Running IntentRecognizer..."
./IntentRecognizer

