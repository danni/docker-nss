docker-nss
==========

A libnss plugin for finding Docker containers

This is still a work in progress!

Installing
==========

There is no `make install` yet!

`/etc/nsswitch.conf`
--------------------

    hosts:      files dns mdns4_minimal myhostname docker
                                                   ^
Testing
=======

    LD_LIBRARY_PATH=`pwd` getent hosts badger.docker
    LD_LIBRARY_PATH=`pwd` getent hosts 10.0.0.0
