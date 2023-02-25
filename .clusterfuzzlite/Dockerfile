FROM gcr.io/oss-fuzz-base/base-builder:v1
RUN apt-get update && apt-get install cmake ninja-build -y --no-install-recommends && apt-get clean && rm -rf /var/lib/apt/lists/*
COPY . $SRC/phi
WORKDIR $SRC/phi
COPY .clusterfuzzlite/build.sh $SRC/
