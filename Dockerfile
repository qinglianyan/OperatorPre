FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc OperatorPre.c -o OperatorPre
RUN chmod +x OperatorPre