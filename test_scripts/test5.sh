rm "file"
gcc test.c -o lock
./lock 2 SH &
sleep 0.5
./lock 3 SH &
sleep 0.5
./lock -1 EX &
sleep 0.5
./lock -1 SH &
