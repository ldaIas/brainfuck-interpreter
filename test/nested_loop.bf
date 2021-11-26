++++            Load 4 into c0
>+++            Load 3 into c1

[<
    [
        ->>+<<  Add 1 into c2 for each value in c0
    ]
    ++++        Load 4 back into c0
    >-          Repeat loop c1 times
]
                This loop essentially multiples c0 by c1
                and stores the result in c2

<               Move back to c0

>>.             Output value in c2