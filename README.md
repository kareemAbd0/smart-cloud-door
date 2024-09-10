
# 🚪🔒 Smart Cloud Door System

## Project Overview

The **Smart Cloud Door System** is a secure access control system designed to verify and log employee IDs for accessing department doors in a company. It uses a custom application that interfaces with an **Azure PostgreSQL cloud database** to ensure real-time verification and logging of door access attempts.

## Key Features

- **Custom Kernel Drivers**:
  - **Keypad Driver**: For ID input.
  - **LCD Driver**: Displays information on a 16x2 LCD.
  - **GPIO Driver**: Manages input/output for the system.
  
- **Yocto Image**:
  - Includes custom recipes for the app, SOCI append, and auto-start system services.

- **Database Integration**: The application connects to an Azure PostgreSQL database to verify entered IDs and logs the data for access tracking.

- **Custom Device Tree**: A custom device tree binary matches GPIO pins to the appropriate drivers.

## How to Use

1. **Add Yocto Layers**: Include the necessary Yocto layers in your `bblayers.conf`.

2. **Update PostgreSQL Connection String**: Modify the connection string in the `recipes-support/postgresql-init' script with your Azure PostgreSQL credentials.

3. **Build the Image**: Build the image using:

   ```bash
   bitbake scd-image
   ```

4. add the custom device tree binary to the boot partion after flashing the image.

5. enable the systemd service to start the application on boot in 'lib/systemd/system/scd-service'.
