# In order to save time, I refused to build the rpm package, so we will build it manually

## before installation, you need to create directories if they do not exist:

/home/your_username/.local/sbin

/home/your_username/.local/include

/home/your_username/.local/lib



## you also need to change variable USER in makefile

## Install library:

```
1. install the curl, g++ and nlohmann libraries:
    apt-get -y install nlohmann-json-devel(on alt linux)
    apt-get -y install libcurl
    apt-get -y install gcc-c++
2. clone the github repository and go to it in our terminal using cd
3. make install -fmakelibbranchescomparing.txt
```

Done! Library is installed

## Install CLI:

```
1. install library(upper)
2. make install -fmakeclibranchescomparing.txt
```

## Usage example:

in this case, the json structure will be written to the output.txt file:

( export PATH=/home/badbad/.local/sbin dont work)

```
 /home/your_username/.local/sbin/CLIBranchComparing -1sisyphus -2p10 -foutput.txt
```

If you omit the f parameter or do not specify a file name, then json will be output to the standard stream

- the only_in_first array stores all packages that are in the 1st but not in the 2nd

- the only_in_second array stores all packages that are in the 2nd but not in the 1st

- the version_more_than_second array stores all packages, all packages whose version is greater in the 1st than in the 2nd