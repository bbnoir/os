#!/bin/bash

fifo_read="hw5_read.fifo"
fifo_write="hw5_write.fifo"
total=$((6 + $RANDOM % 5))
length=10

if [ ! -p "$fifo_read" ] || [ ! -p "$fifo_write" ]; then
    echo "Have you called mkfifo(...)?"
    exit 1
fi

for ((i=1; i<=$total; i++)); do
    secret_string=$(cat /dev/urandom | tr -dc 'A-Z0-9' | fold -w $length | head -n 1)
    sorted_string=$(echo -n "$secret_string" | fold -w1 | sort | tr -d '\n')
    echo "Testcase $i/$total :"
    echo "$secret_string" > "$fifo_read"
    if read line <$fifo_write; then
        :
        # echo "Recieved: $line"
    else
        echo "No data recieved."
    fi

    if [ "$line" = "$sorted_string" ]; then
        echo -e "\e[32mAccept!\e[0m"
    else
        echo -e "\e[31mWrong Answer.\e[0m"
        exit 1
    fi
done

echo "Well done!" > "$fifo_read"
echo -e "\e[33mWINNER WINNER CHICKEN DINNER!!\e[0m"
exit 0