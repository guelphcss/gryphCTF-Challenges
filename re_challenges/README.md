# gryphCTF RE Challenges
Created by: [Mourad Sherif (nubb)](https://0xnubb.com)

## Overview
None of the challenges strictly require debugging. There were no restrictions on decompiler usage or tooling in general. Each directory below contains the challenge binary, its source code, and other challenge assets. For `iloveyoumy...` specifically, I wrote a disassembler for the VM. I would recommend you (the reader) to do the same, as this is a very fun and meaningful learning exercise to understand how cracking VMs really feels like (if you didn't already write one, cough cough AI).

The `Wish` challenge uses a Z3 solver script, which I would highly recommend you look into. I have many notes on [Symbolic Execution](https://codeberg.org/nubbie/SymExec-Playground), and other reverse engineering topics [here](https://codeberg.org/nubbie/pages/src/branch/main/Notes/RevEng/notes). Please feel free to reach out to me on Discord (the GCSS server, I'm not in the CTF one) if you have any questions, or file an issue on this repository!

The `Faith Beyond Question` challenge effectively had an unintended path if you took advantage of Google. You may notice through program execution that some weird sentences get printed until the flag is output to `prescript.ppm`. These are actually lyrics for [Children Of The City](https://genius.com/Mili-jpn-children-of-the-city-lyrics). You were basically given a hint for the flag from the very beginning!
