<h1 align="center" style="margin-bottom:0">UsDa Apps - (User Database)</h1>
<p align="center">Created by <a href="https://github.com/rizalarfiyan/" target="_blank">Rizal Arfiyan</a> by <span style="color:red">&#10084;</span></p><br />

UsDa Apps adalah sebuah mini program create read delete user yang di simpan dalam file csv. Proyek ini digunakan untuk memenuhi tugas UAS matkul Algoritma dan Pemrograman yang diampu oleh ibu Wiwi Widayani, M.Kom.

## Flow Chart
```mermaid
graph TD
    start(["Mulai"])
    stop(["Akhir"])
    action1["signal handler"]
    action2["filter user"]
    action3["push data to vector"]
    action4["filter user delete"]
    
    clear1["clear Screen"]
    clear2["clear Screen"]
    clear3["clear Screen"]
    clear4["clear Screen"]
    clear5["clear Screen"]

    read1["read file"]
    read2["read file"]
    read3["read file"]
    read4["read file"]

    write1["write file"]

    print1[/"Show Menu"/]
    
    print2[/"Print info Get all users"/]
    print3[/"Print info Search user by name"/]
    print4[/"Print info Add users"/]
    print5[/"Print info Delete user"/]

    print7[/"Print Get all users"/]
    print8[/"Print Search user by name"/]
    print9[/"Print Status Add users"/]
    print10[/"Print Delete user"/]

    input1[/"Input Menu"/]
    input2[/"Input Search"/]
    input3[/"Input Many user"/]

    input4[/"Input Name"/]
    input5[/"Input Adress"/]
    input6[/"Input Hoby"/]
    input7[/"Input Phone"/]
    input8[/"Input Age"/]
    input9[/"Input Search"/]

    cond1{"confirm 'y'"}
    cond2{"current index < many user"}

    case1{"user input 1"}
    case2{"user input 2"}
    case3{"user input 3"}
    case4{"user input 4"}
    case5{"user input 5"}

    start-->action1
    action1-->clear1
    clear1-->print1

    print1 --> input1
    input1 --> case1
    case1 --> |FALSE| case2
    case1 --> |TRUE| clear2
    clear2 --> print2
    print2 --> read1
    read1 --> print7
    print7 --> cond1

    case2 --> |FALSE| case3
    case2 --> |TRUE| clear3
    clear3 --> print3
    print3 --> input2
    input2 --> read2
    read2 --> action2
    action2 --> print8
    print8 --> cond1

    case3 --> |FALSE| case4
    case3 --> |TRUE| clear4
    clear4 --> print4
    print4 --> input3
    input3 --> read3
    read3 --> cond2
    cond2 --> |FALSE| write1
    cond2 --> |TRUE| input4
    input4 --> input5
    input5 --> input6
    input6 --> input7
    input7 --> input8
    input8 --> action3
    action3 --> cond2
    write1 --> print9
    print9 --> cond1

    case4 --> |TRUE| clear5
    case4 --> |FALSE| case5
    clear5 --> print5
    print5 --> input9
    input9 --> read4
    read4 --> action4
    action4 --> print10
    print10 --> cond1

    case5 --> |TRUE| stop
    case5 --> |FALSE| stop

    cond1 --> |TRUE| clear1
    cond1--> |FALSE| stop

```