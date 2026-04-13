# Stage 1: build
FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y gcc make
WORKDIR /build
COPY armory.c .
RUN gcc -g armory.c -o armory -fno-stack-protector -no-pie -Wno-deprecated-declarations

# Stage 2: runtime
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*
WORKDIR /home/ctf
COPY --from=builder /build/armory .
COPY armory.c .
COPY flag.txt .
RUN chmod +x armory
EXPOSE 1337
USER 1000
CMD ["bash", "-c", "export GLIBC_TUNABLES=glibc.warn_on_gets=0 && socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/home/ctf/armory"]