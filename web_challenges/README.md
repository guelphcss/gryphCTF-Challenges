# gryphCTF Web Challenges

Created by: [Jas Sri](https://jassri.online)

## Overview

Welcome to the web challenges directory! This part of the repo are all NodeJS projects which test you on a load of basic to difficult web vulnerabilities! Note that most of these projects have have barely any comments, most of the time none, meaning, even though you see the source, finding the solution might not always be directly there.

The flag may be there in the source, and going directly to it isn't the way to solve it, unless you're really good at guessing (lol). What I'm trying to say is, for most of these challenges, it can't be done in one step.

## Usage

In order to run these challenges, make sure you have `docker` installed and running, and then run the following:

```bash
$ docker compose up --build -d
```

The following command will create / build / deploy the dockers when this command is ran from the `/web ` directory. Navigate to `http://localhost:<port>` to get to the challenge instances, here's what each challenge maps to:
| Challenge | Port |
|----------|-------|
| misplaced_message | 4000 |
| bothersome_blacksmith | 4010 |
| castle_culling | 4020 |
| abducted_art | 4030 |
| breach_barracks | 4040 |
| township_trickery | 4050 |
| rewind_release | 4060 |
