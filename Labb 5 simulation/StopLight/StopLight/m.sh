rm main.exe 
g++ -pthread ./*.cpp -o main
./main.exe /dev/ttyS0
