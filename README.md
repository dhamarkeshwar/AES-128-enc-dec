# AES-128-enc-dec

main.c contains the function spilt_text_into_array_with_nonce, if the input to the function is char text[], then specify size=sizeof(text)/sizeof(text[0]).
The plain text will be cleared off the memory once the aforementioned function runs.

Running the above mentioned function will write assign values to the global 2-D array named "array", which is of dimension n_blocks*16.

After the array is assigned with values, CBC_encrypt or CBC_decrypt can be performed.

Use the resulting array(without 1st element, i.e., array[0]) to construct the modified text, be it encrypted or decrypted text.

Throughout the process, note that, a little bit of randomness(specified as "nonce") is added to avoid "known plain text" and "known cipher text" oracle attacks.

Also, "nonce", can further be used to construct MAC, i.e., CBC-MAC, which will lead to MAC-then-encrypt protocol; Thus, resulting in authenticated encryption.


Please note that, this cryptosystem is ultra light weight, meaning, it runs in linear time to encrypt or decrypt. 
