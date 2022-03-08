#!/bin/bash

while getopts 'k' 'r' opt;
do
    case ${OPTKEY} in
        'k') OPT_KILL='true'
            ;;
        'r') OPT_REMOVE='true'
            ;;
        *)
            echo "Unimplemented option -- ${OPTKEY}" >&2
            exit 1
            ;;
    esac
done

[ -z ${OPT_KILL} ] && echo 'Kill filebeat process' && pkill -9 filebeat; \
                    echo 'Kill prometheus process' && pkill -9 prometheus; \
                    echo 'Kill pos-exporter' && pkill -9 pos-exporter

[ -z ${OPT_REMOVE} ] && echo 'Clean up log files' && rm -rf /var/log/pos/*;