# Brute-Force

---- ABOUTE ----

training project for effective programming skills in C++. The program was created exclusively for educational purposes.

It is a a student program for encrypting and decrypting files. Decryption is carried out by brute-force passwords. The password can contain an unlimited number of characters: english letters and / or numbers.

When brute-force is used, the program displays the speed of guessing passwords, the number of options searched, and additional information. Finally, the program shows the user the correct password and writes the decrypted content to the file.

At the request of the user, the program can record all candidate passwords used during brute-force.

---- SOME SCREENSOTS ----

encryptyng:


![image](https://user-images.githubusercontent.com/52506956/133293661-b476b849-6882-4b79-ae22-6f4f23aac713.png)


brute-force in progress:


![image](https://user-images.githubusercontent.com/52506956/133293986-1d848d56-7838-4e75-954b-2ee0384f0216.png)

result of brute-force:

![image](https://user-images.githubusercontent.com/52506956/133294361-304c1f59-2e2b-409b-bfd9-967a761eda84.png)

PS speed and total brute-force time depends on your computer ;-)

---- HOW TO USE ----

run program in console and first param after program name write filename with path, wich you want to crypt or decrypt. If you want to save all tried candidate passwords, after filename/filepath write "--log_passwords".

---- PLUG-IN LIBRARIES ----

Program uses OpenSSL 1.1.1 encryption methods, so include OpenSSL version 1.1.1 library to the project.
