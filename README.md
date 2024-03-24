# Evosim

Neural Networks and genetic evolution are fun!

</br>
</br>
</br>


# Install dependencies
```shell
sudo apt update
sudo apt install libeigen3-dev libsdl2-dev 
```

# Compile
Create the build directory
```shell
mkdir build && cd build
```

Configure CMake build
```shell
cmake -GNinja ..
```

Finally, start the build process
```shell
cmake --build .
```