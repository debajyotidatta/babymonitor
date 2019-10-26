rm -rf tempclassifier/build
rm -rf lightclassifier/build
rm -rf logiccontroller/build
tockloader erase-apps &&\
pushd logiccontroller && make && tockloader install && popd &&\
pushd tempclassifier && make && tockloader install && popd &&\
pushd lightclassifier && make && tockloader install && popd
