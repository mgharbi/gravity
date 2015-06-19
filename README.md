Gravity
=======

Dependencies
------------

* Irrlicht graphics engine `brew install irrlicht`
* Bullet physics engine `brew install bullet`
* Boost


Install
-------

* On OSX with Xcode:

    cd macbuild
    cmake -G "Xcode" ..

Open the Xcode project, all set !

* On OSX with make

    cd build
    cmake ..
    make
    open ../bin/gravity.app

