# keyed-caesar
A C++ program that encrypts and decrypts messages using keyed Caesar cypher method
## Method
The ciphering process is implemented using a 26x26 character array:

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
B C D E F G H I J K L M N O P Q R S T U V W X Y Z A
C D E F G H I J K L M N O P Q R S T U V W X Y Z A B
.
.
.
X Y Z A B C D E F G H I J K L M N O P Q R S T U V W
Y Z A B C D E F G H I J K L M N O P Q R S T U V W X
Z A B C D E F G H I J K L M N O P Q R S T U V W X Y

Ciphering is done by replacing the letters of the plaintext by characters from the array by this rule:
- the plaintext letter determines the column of the array,
- the keyword letter determines the row.

Deciphering consists of:
- determining the column of the array based on the keyword,
- locating the row by finding cryptogram's letter in that column,
- the first letter in that row is the decrypted phrase's letter.

## Program

The whole project consists of two programs, one to cipher the plaintext using a key entered by the user and save it in a .txt file (the cryptogram is saved in a file named "encrytpedtext", the keyword - "key"). The other program reads the encrypted text and the keyword from their respective files and returns decrypted message.