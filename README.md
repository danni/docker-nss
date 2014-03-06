docker-nss
==========

A libnss plugin for finding Docker containers

This is still a work in progress!

Installing
==========

    git clone git@github.com:danni/docker-nss.git
    cd docker-nss
    sudo make all install
    sudo sed -i -re 's/^(hosts: .*$)/\1 docker/' /etc/nsswitch.conf

or edit `/etc/nsswitch.conf`:

    hosts:      files dns mdns4_minimal myhostname docker
                                                   ^
Testing
=======

    LD_LIBRARY_PATH=`pwd` PATH=`pwd`/mocker:$PATH ./test

    LD_LIBRARY_PATH=`pwd` getent hosts badger.docker
    LD_LIBRARY_PATH=`pwd` getent hosts 10.0.0.0

ToDo
====

 * Look up containers by image name/ID (not just container ID)
 * Look up container names for IP addresses
