
#!/bin/sh
if [ ! -f "/var/lib/postgresql/.init_done" ]; then
    # Initialize the PostgreSQL database
    su - postgres -c "initdb -D /var/lib/postgresql/data"
    chown -R postgres:postgres /var/lib/postgresql/data
    chmod 700 /var/lib/postgresql/data
    cp /usr/bin/smart_cloud_door /var/lib/postgresql/
    touch /var/lib/postgresql/connection_string.txt
    echo "host=smart-cloud-door.postgres.database.azure.com port=5432 dbname=postgres user=kareem password={your-password}" > /var/lib/postgresql/connection_string.txt



    # Mark that the initialization has been done
    touch /var/lib/postgresql/.init_done
fi


cd /var/lib/postgresql

./smart_cloud_door



