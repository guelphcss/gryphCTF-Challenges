# Dockerfile Guide

To ensure the pwn challenges run exactly as it did during the competition, we have provided the original `Dockerfile`. Binary exploitation is extremely environment-dependent, and this Docker setup ensures your local memory offsets and `libc` versions match our live event infrastructure perfectly.

Ensure you have Docker and `netcat` installed on your host machine. To build the image, deploy the container, connect to the challenge, and clean up your environment afterward, simply run the following commands in order from this directory:

The environment should be the same as it was at the competition, but in the case that it's not and something breaks let us know on the Discord!

# cd into the challenge directory and run the following command to build the challenge image (name doesn't matter)
docker build -t <challenge_name> .

# Start the container (you can use a different port if you want)
docker run -d -p 1337:1337 --name <challenge_instance> challenge_name

# Connect and exploit
nc localhost 1337

# Stop and remove the container when finished
docker stop challenge_instance && docker rm challenge_instance
