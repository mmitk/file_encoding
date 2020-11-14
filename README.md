# File Encoding
File encoding for text, image, and sound files 

Encode text, image, and sound files using Linear Feedback Shift Register

Build:
```
make all
```
Use:
```
./Encrypt <input_file> <output_file> <password>
```
Password is used to generate seed and tap position for LFSR, and acts as a key for encoding/decoding
To decode encoded file usage is the same:
```
./Encrypt <path/to/encoded_file> <path/to/decoded_file> <password>
```
Use same password for decoding and encoding


# Notes
LFSR can be used as random number generator with custom seed and tap
