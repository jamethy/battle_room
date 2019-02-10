FROM ubuntu:latest as builder

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y cmake clang libsdl2-dev libsdl2-2.0-0 libsdl2-image-dev libsdl2-image-2.0-0 libsdl2-ttf-dev libsdl2-ttf-2.0-0 libsdl2-net-dev libsdl2-net-2.0-0

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

COPY . /source
RUN mkdir /build
RUN cd /build && cmake ../source && make

FROM ubuntu:latest

COPY --from=builder /build/src/Release /bin

CMD /bin/battleroom
