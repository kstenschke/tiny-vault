Tiny Vault
==========

## What does it do?
**Tiny Vault** keeps a secret string (e.g. a password), typed-in once at start-up time,
in memory **w/o ever storing the secret on the file system** 
and allows to retrieve it again via HTTP.


## Table of Contents
* [What does it do?](#what-does-it-do)
* [Usage](#usage)
  + [Run and set secret](#run-and-set-secret)
  + [Retrieve secret](#retrieve-secret)
  + [Example usage script](#example-usage-script)
* [Author and License](#author-and-license)


## Usage

### Run and set secret

Run **tvault** on default port 1234: ```tvault```  

Run **tvault** on port 6789: ```tvault 6789```

At startup tvault opens a GTK popup window with an input prompt,
asking you to enter the secret.  

![Screenshot](/assets/screenshot.png) 

To replace the secret by a different string, stop and restart Tiny Vault. 


### Retrieve secret

Retrieve current secret using CURL: ```curl http://localhost:1234```


### Example usage script

```sh
#!/bin/bash

# retrieve secret and store into shell variable
MY_SECRET=$(curl http://localhost:1234)

# type secret string
...
# hit enter
...

# unset variable that held the secret
unset MY_SECRET
```  


## Build and install

1. Fetch dependencies: ```git submodule update --init --recursive```
2. Build: ```cmake CMakeLists.txt; make```
3. Install: ```sudo make install```
 

## Author and License
...
