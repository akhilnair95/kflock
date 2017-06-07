rm "file"
gcc test.c -o lock
./lock 2 SH &
sleep 0.5
./lock 3 SH &
sleep 0.5
./lock 4 EX &
sleep 0.5
./lock 3 SH &

