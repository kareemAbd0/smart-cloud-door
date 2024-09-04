
# Append the DEPENDS variable to include unixodbc
DEPENDS += "unixodbc"

# Enable empty and odbc PACKAGECONFIG options by default
PACKAGECONFIG ??= "empty postgresql"


CXXFLAGS += "-std=c++17"

EXTRA_OECONF += "-DSOCI_CXX11=ON"
