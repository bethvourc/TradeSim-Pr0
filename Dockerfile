# Multi-stage Dockerfile for TradeSim Pro development
FROM ubuntu:22.04 as base

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1
ENV PYTHONDONTWRITEBYTECODE=1

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    pkg-config \
    python3 \
    python3-pip \
    python3-dev \
    python3-venv \
    nodejs \
    npm \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -m -s /bin/bash developer
USER developer
WORKDIR /home/developer

# Install Python dependencies
COPY --chown=developer:developer py/requirements.txt /tmp/requirements.txt
RUN python3 -m pip install --user --upgrade pip && \
    python3 -m pip install --user -r /tmp/requirements.txt

# Install Node.js dependencies for GUI
COPY --chown=developer:developer gui/package.json /tmp/gui-package.json
RUN mkdir -p /home/developer/gui && \
    cp /tmp/gui-package.json /home/developer/gui/ && \
    cd /home/developer/gui && \
    npm install

# Set up development environment
ENV PATH="/home/developer/.local/bin:${PATH}"
ENV PYTHONPATH="/home/developer/tradesim:${PYTHONPATH}"

# Development stage
FROM base as development

# Install additional development tools
USER root
RUN apt-get update && apt-get install -y \
    clang-tidy \
    clang-format \
    valgrind \
    gdb \
    && rm -rf /var/lib/apt/lists/*

USER developer

# Copy source code
COPY --chown=developer:developer . /home/developer/tradesim-pro
WORKDIR /home/developer/tradesim-pro

# Build C++ core
RUN mkdir -p build && \
    cd build && \
    cmake ../cpp && \
    make -j$(nproc)

# Production stage
FROM base as production

USER root
# Install runtime dependencies only
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

USER developer

# Copy built artifacts from development stage
COPY --from=development --chown=developer:developer /home/developer/tradesim-pro/build /home/developer/tradesim-pro/build
COPY --from=development --chown=developer:developer /home/developer/tradesim-pro/cpp /home/developer/tradesim-pro/cpp
COPY --from=development --chown=developer:developer /home/developer/tradesim-pro/py /home/developer/tradesim-pro/py
COPY --from=development --chown=developer:developer /home/developer/tradesim-pro/gui /home/developer/tradesim-pro/gui

WORKDIR /home/developer/tradesim-pro

# Default command
CMD ["/bin/bash"] 