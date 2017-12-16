FROM ubuntu:latest

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-net-2.0-0

COPY ./bin/battleroom /app/bin/battleroom
COPY ./res /app/res

CMD /app/bin/battleroom dedicated
