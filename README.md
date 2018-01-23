Jazmine Blockchain

See https://jazmine.io/ for info.

This is JazmineGUIQt. The front-end GUI for jazmined and jazminewalletd, configured to build using Qt.

This software starts three server processes listening on localhost (127.0.0.1). The ports are psuedo-randomized, 
the software will look for an open port to use for each service. This minimizes issues with security.


```
NOTE: This software will start an RPC/HTTP server listening on your computer on localhost (127.0.0.1). 
It is not accessible to the outside, HOWEVER PLEASE NOTE that a specially scripted javascript code 
on a remote web site could possibly manipulate the rpc/http server running on your machine. 
This means people could steal your coins. If you are running througn the JazmineGui it randomizes
the port used, but it is still a bad idea to have a wallet open while surfing the www.
```

At the moment do not "surf the web" while running this software, it's potentially an issue. 

Will have authorization added to future release.



To BUILD:

```
qmake
make
```

You will need to copy the jazmine-php directory to your exe/build directory.

You will also need php 7.2+, build with curl and sodium.

Also need to build jazmine for Linux and put build in JazmineGuiQt directory.

Use the included php.ini file. Put php.ini in php/sapi/cli/




