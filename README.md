# SelfTLS
A home grown ground up implementation of TLS heavily inspired by Implementing SSL/TLS by Joshua Davies (https://www.amazon.com/Implementing-SSL-TLS-Using-Cryptography/dp/0470920416 ). 
This implementaion is build as  an exercise to understand all the cryptography involved in operating a secure channel as well
as the attacks that discovered over the years. The goal is to provide an open test bed to "play test" practical attacks that can be 
replicated with real world implementations. 

##Rules of the game:
* No contributors: all the code will be written completely by me
* Comlpetely ground up: no use of any pre-cooked math or crypto libraries

##Why this will "work":
* **Practical :** Gain practical understanding of the attacks SSL/TLS has suffered from, I want to be able to actually exploit the Padding Oracles, RSA Exponentiation Side Channels, Memory Scraping attacks etc. 
* **Mistakes :** There are no people who are naturally good at crypto, only people who have made enough mistakes. The project is designed as an engine 
to manufacture as much as the same implementation flaws / mistakes that real world openssl and gnutls went through. If I make certain mistakes the chances are other people would have (in the past) or currently made the same mistakes too. 
* **Understanding :**The only way to get a working understanding of anything is to try to build it. Proof by construction!  
* **Ground Up :** With a ground up implementation I can debug / edit and inspect the code with a much greater ease, there is no overhead suffered in learning the documentation styles of the openssl / gnutls project.
* **In C :** I suck at C, I'm not nearly fluent enough :/ 

### DISCLAIMER: 
*If its not obvious already, this code is not be used in production, or for the communication of any actual secrets, 
this is an academic exercise in understanding TLS and its various cryptographic primitives.*
