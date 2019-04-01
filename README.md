# Caesar Cipher
This is a program to encrypt and decrypt a given string of file using caesar cipher.

This program has been tested on Elementary OS 5.0 (Juno).

### Installation

<ol>
	<li>Change to the source directory</li>
	<li>Run the following commands:</li>
</ol>

```
sudo make
sudo make install
```
### Usage

```
Usage: caesar <-e | -d> -f <file name> [-o <output file name>] <shift size>
       caesar <-e | -d> <plain text> <shift size>

Options:
	-e		Encrypt plain text
	-d		Decrypt Caesar cipher text
	-I		Take input from stdin
	-f <file name>	Encrypt/Decrypt given file
	-h, -u		Show this help/usage message
```

See "COPYING" for license information.
