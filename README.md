# Caesar Cipher
This is a program to encrypt and decrypt a given string of file using caesar cipher.

### Installation

<ol>
	<li>Change to the source directory.</li>
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
       caesar <-e | -d> -I <shift size>

Options:
	-e, --encrypt		Encrypt plain text
	-d, --decrypt		Decrypt Caesar cipher text
	-I, --input		Take input from stdin
	-f, --file <file name>	Encrypt/Decrypt given file

	-o, --out <file name	Name of the output file in which
				the encrypted/decrypted fileis going
				to be stored

	-h, --help		Show this help message
	-V, --version		Show version information
```

See "COPYING" for license information.
