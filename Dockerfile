FROM ubuntu:latest

RUN apt update && \
    apt install -y \
    bash \
    bc \
    curl \
    python3 \
    build-essential \
    openmpi-bin \
    openmpi-common \
    libomp-dev \
    libopenmpi-dev && \
    apt clean && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash mpiuser
USER mpiuser
WORKDIR /home/mpiuser

CMD ["/bin/bash"]
