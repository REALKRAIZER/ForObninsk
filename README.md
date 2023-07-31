# ForObninskin order to save time, I refused to build the rpm package, so we will build it manually

## set environment variables:

```
export LD_LIBRARY_PATH=/usr/local/lib
export CPLUS_INCLUDE_PATH=/usr/local/include
export PATH=/usr/local/sbin
```

## Install library:

```
1. install the curl and nlohmann libraries:
    apt-get -y install nlohmann-json-devel(on alt linux),
    apt-get -y install libcurl
2. clone the github repository and go to it in our terminal using cd
3. mv branch.h cur_path/usr/local/include
4. g++ -fPIC -shared cur_path/src/branch.cpp -o /usr/local/lib/libbranchcomparing.so
```

Done! Library is installed

## Install CLI:

```
1. install library(upper)
2. g++ cli.cpp -lbranchcomparing.so -o /usr/local/sbin/CLIBranchComparing -lcurl
```

## Usage example:

in this case, the json structure will be written to the output.txt file:

```
 CLIBranchComparing -1sisyphus -2p10 -foutput.txt
```

If you omit the f parameter or do not specify a file name, then json will be output to the standard stream