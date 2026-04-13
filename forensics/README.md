# gryphCTF Forensics Challenges
Created by: [Mourad Sherif (nubb)](https://0xnubb.com) and Mudit Sood

## Overview (Mourad; made `Cheapskate`, `Popcorn`, and `Under Lock and Key`)
Nothing too bad here, with the exception of `Under Lock and Key` since I basically gave you the hint of C2 traffic and registry usage and that's it, "Have fun sifting through my 81Kmb raw memory image." Additionally, because the image is so big, and Git doesn't like files >100MB, I can't really push it out to this repository, so I hope you have your own copy of the challenge (skull emoji).

As always, challenge artifacts are in each directory. `Cheapskate` contains the `updater.sh` script as well as recovered artifacts for the challenge.
- For `Cheapskate`, you had to extract a `passwords.txt` and `passwordispassword.jpg` file. The `passwordispassword.jpg` file contained a hidden DES-encrypted flag which was hidden with `steghide` under the passkey `password`. The `passwords.txt` file contained the DES IV and Key for encryption/decryption. 
    - Of course, `Cheapskate` requires `Wireshark` and `steghide` to solve the challenge.
- I had a lot of fun making this challenge since it encompasses both PCAP analysis and steganography in a reasonable manner (and no, steganography is NOT a safe measure of securing passwords, PirateSoftware is a fraud.)
