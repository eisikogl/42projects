FROM python:3.12.1

RUN pip install --upgrade pip

COPY ./requirements.txt .
RUN pip install -r requirements.txt

EXPOSE 443
EXPOSE 80

COPY ./django_project /
WORKDIR /

COPY ./entrypoint.sh /
ENTRYPOINT ["sh", "/entrypoint.sh"]

