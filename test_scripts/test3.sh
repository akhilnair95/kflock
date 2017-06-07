rm "file"
gcc test.c -o lock
./lock 1 EX &
sleep 0.5
./lock 2 EX &
sleep 0.5
./lock 3 EX &
sleep 0.5
./lock 4 EX &
