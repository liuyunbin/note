#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

USERNAME=lyb
PASSWORD=654321

sudo useradd -m -s /bin/bash $USERNAME

echo "$USERNAME:$PASSWORD" | sudo chpasswd

echo "User '$USERNAME' created with password: '$PASSWORD'"

