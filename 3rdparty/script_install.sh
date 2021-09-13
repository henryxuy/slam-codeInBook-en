# Eigen
sudo apt-get install libeigen3-dev

# Pangolin
cd Pangolin
mkdir build
cd build
cmake ..
make
sudo make install
cd ..
cd ..


# opencv:
sudo apt-get install build-essential libgtk2.0-dev libvtk5-dev libjpeg-dev libtiff-dev libjasper-dev libopenexr-dev libtbb-dev
sudo pip install numpy scipy matplotlib scikit-image scikit-learn ipython
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout 3.4.15
mkdir build
cd build
cmake ..
make -j4
sudo make install
# go back to the original directory
cd ..
cd ..

# ceres:
sudo apt-get install liblapack-dev libsuitesparse-dev libcxsparse3 libgflags-dev libgoogle-glog-dev libgtest-dev
cd ceres-solver
mkdir build_dir
cd build_dir
cmake ..
make
sudo make install
cd ..
cd ..


# g2o:
sudo apt-get install qt5-qmake qt5-default libqglviewer-dev-qt5 libsuitesparse-dev libcxsparse3 libcholmod3
cd g2o
mkdir build
cd build
cmake ..
make
sudo make install
cd ..
cd ..



