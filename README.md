Tiny Vault
==========

[![Platform](https://img.shields.io/badge/platform-linux-blue)](#)
[![License](https://img.shields.io/badge/License-GPL-3)](https://github.com/kstenschke/tiny-vault/blob/master/LICENSE)
[![Written in C++](https://img.shields.io/badge/written%20in-C++-blue)](#)  


Temporary local password store for Linux.  


## Table of Contents

* [What does it do?](#what-does-it-do)
* [Usage](#usage)
  + [Run and set secret](#run-and-set-secret)
  + [Retrieve secret](#retrieve-secret)
  + [Example usage script](#example-usage-script)
* [Author and License](#author-and-license)


## What does it do?

When starting **Tiny Vault**, the user is asked to enter a secret string, 
which is than temporarily (for the runtime of Tiny Vault) stored in the RAM 
(and never onto the file system).  

![Screenshot](/assets/screenshot.png) 

**Tiny Vault** than allows to retrieve the secret locally via HTTP request.  


## Usage

### Run and set secret

Run on default port 1234: ```tvault```  

Run on port 6789: ```tvault 6789```


### Retrieve secret

Retrieve current secret using CURL: ```curl http://localhost:1234```


### Example usage script

```sh
#!/bin/bash

# retrieve secret and store into shell variable
MY_SECRET=$(curl http://localhost:1234)

# type secret string using xdotool
xdotool type $MY_SECRET
# hit enter
xdotool key KP_Enter

# unset variable that held the secret
unset MY_SECRET
```  


## Build and install

1. Fetch dependencies: ```git submodule update --init --recursive```
2. Build: ```cmake CMakeLists.txt; make```
3. Install: ```sudo make install```
 

## Author and License

**Tiny Vault** was written by Kay Stenschke and is licensed under the 
[GNU General Public License V3.0](https://www.gnu.org/licenses/licenses.html#GPL)  

```
Permissions of this strong copyleft license are conditioned on making available 
complete source code of licensed works and modifications, which include larger 
works using a licensed work, under the same license. Copyright and license 
notices must be preserved. Contributors provide an express grant of patent 
rights.
```
