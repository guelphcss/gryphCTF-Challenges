# Stage 1: build
FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y gcc make libseccomp-dev
WORKDIR /build
COPY library.c .
RUN gcc library.c -o library -lseccomp -static -fno-stack-protector -no-pie

# Stage 2: runtime
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y socat libseccomp-dev && rm -rf /var/lib/apt/lists/*
WORKDIR /home/ctf
COPY --from=builder /build/library .
COPY flag.txt .
RUN chmod +x library
EXPOSE 1337
USER 1000
CMD ["bash", "-c", "export GLIBC_TUNABLES=glibc.warn_on_gets=0 && socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/home/ctf/library"]