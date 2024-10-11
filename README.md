# 程式介紹

此程式可將pla檔案最簡化，但因為演算法的關係，.p數量越多，程式會越慢，建議不要超過5個.p

目前可處理之pla指令:

    .i
    .o
    .p
    .ilb
    .ob
    .e

# 所需函式庫

    iostream
    fstream
    sstream
    string
    vector
    set

# 使用方式

進入main.cpp所在之資料夾，並以g++進行編譯

    g++ main.cpp -o main

若無法正常編譯，請確認您是否安裝g++，且能正常連結到所需之函式庫，或是手動連結所需函式庫

或是使用資料夾內提供的setup.sh

    sudo bash setup.sh

這將自動檢查您的系統是否有g++，若沒有安裝g++，則會幫您安裝，裝好後會自動幫您編譯main.cpp

若無法正常安裝g++，可能代表您的ubuntu版本過低，請使用更高版本的ubuntu

使用下面指令將pla最簡化

    ./main [pla來源] [目標pla檔案]

若目標pla檔案不存在，則會創造該檔案

示範

    g++ main.cpp -o main
    ./main src.pla trg.pla
