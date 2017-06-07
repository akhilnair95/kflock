rm "file"
gcc test.c -o lock
./lock -1 SH &
sleep 1
./lock 3 SH &
sleep 1
./lock 2 EX &
sleep 1
./lock -1 SH &

