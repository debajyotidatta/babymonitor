tockloader listen --timestamp|grep --line-buffered -E "[0-9]+\.[0-9]+,[0-9]+\.[0-9]+"|stdbuf -o0 sed -e 's/\[//g' -e 's/\] /,/g'>new.txt