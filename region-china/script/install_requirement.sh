#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

apt -y install python3-pip

pip install requests_html
pip install lxml_html_clean
pip install html2text

