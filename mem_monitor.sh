#!/bin/bash
set -x
mem_monitor()
{
    APP_NAME_STR="baloo_file"
    MAX_MEM_USAGE=5.0
    TEMP_FIME_NAME=1.txt

    PID=`ps -el | grep $APP_NAME_STR | awk '{ print $4}'`

    if [ $PID ]
    then 
        MEM=`top -d 1 -p $PID -n 1 -b > $TEMP_FIME_NAME; cat $TEMP_FIME_NAME | tail -1 | awk '{ print $10}'`
        
        RESULT=$(echo "$MEM > $MAX_MEM_USAGE" | bc -l)
        
        #if [ $MEM -gt $MAX_MEM_USAGE ]
        if [ $RESULT != 0 ]
        then
            PROCESS_NAME=`cat /proc/$PID/status | head -1 | awk '{ print $2}'`
            kill -9 $PID
            echo "Going to kill process $PID:$PROCESS_NAME"
        fi
    else
        echo "pid not found"
    fi

    rm $TEMP_FIME_NAME
}

mem_monitor
