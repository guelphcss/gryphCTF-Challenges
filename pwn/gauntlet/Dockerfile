# Stage 1: build
FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y gcc make
WORKDIR /build
COPY gauntlet.c .
COPY gauntlet.h .
RUN gcc gauntlet.c -g -o gauntlet -fno-stack-protector -no-pie -Wno-deprecated-declarations

# Stage 2: runtime
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*
WORKDIR /home/ctf
COPY --from=builder /build/gauntlet .
COPY flag.txt .
RUN chmod +x gauntlet
EXPOSE 1337
USER 1000
CMD ["bash", "-c", "export GLIBC_TUNABLES=glibc.warn_on_gets=0 && socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/home/ctf/gauntlet", "pty", "stderr"]