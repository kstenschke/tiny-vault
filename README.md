Tiny Vault
==========

## What does it do?
When starting **Tiny Vault**, the user enters a secret string, which is than
stored temporarily for the runtime of Tiny Vault in the RAM (and never onto the
file system).  

![Screenshot](/assets/screenshot.png) 

While running, **Tiny Vault** allows to retrieve the secret locally via HTTP 
request.  


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

**Tiny Vault** was written by Kay Stenschke and is licensed under the 
[GNU General Public License V3.0](https://www.gnu.org/licenses/licenses.html#GPL)  

```
Permissions of this strong copyleft license are conditioned on making available 
complete source code of licensed works and modifications, which include larger 
works using a licensed work, under the same license. Copyright and license 
notices must be preserved. Contributors provide an express grant of patent 
rights.
```
