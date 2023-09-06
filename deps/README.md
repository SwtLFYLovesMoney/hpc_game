把当前目录的CMakeLists.txt替换到拉下来的opencv/CMakeLists.txt

在opencv目录下新建build目录，执行：
cmake -DBUILD_opencv_world=ON ..
即可编译得到opencv_world.so产物，位于hpc_game/output/opencv下