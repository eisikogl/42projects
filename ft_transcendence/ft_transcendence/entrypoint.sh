#!/bin/sh

# Function to check if PostgreSQL is ready
postgres_ready() {
    python << END
import sys
import psycopg2

try:
    conn = psycopg2.connect(
        dbname="pongdb",
        user="postgres",
        password="inception123",
        host="db_postgres",
        port="5432"
    )
except psycopg2.OperationalError:
    sys.exit(-1)
sys.exit(0)
END
}

# Wait for PostgreSQL to start
until postgres_ready; do
    echo "Waiting for PostgreSQL to start..."
    sleep 5
done

echo "PostgreSQL is up - executing Django server startup"

# Your Django startup commands here
python manage.py makemigrations --no-input
python manage.py migrate --no-input
python manage.py collectstatic --no-input
python manage.py createsuperuser --noinput --username admin
#gunicorn django_project.wsgi:application
daphne -b 0.0.0.0 -p 8000 django_project.asgi:application