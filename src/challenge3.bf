countdown timer stored in c5
current iteration in c6
>>>>> ++++++++++ [ - < ++++++++++ > ] < c5 = 100

c8 will keep track of fizz
>>> +++               c8 = 3
c9 will keep track of buzz
> +++++               c9 = 5
c13 will keep track of whether fizz or buzz was printed
<<<<                  c5

[                     while c5
  -                     decrement c5
  > +                   increment c6

  >>>>>>> [-]           reset c13

  <<<< -                decrement c9
  < -                   decrement c8

  ====================================================================================================
  Copy c8 to c12
  >>> [-]               reset c11
  > [-]                 reset c12
  <<<<                  c8
  [                     while c8
    -                     decrement c8
    >>> +                 increment c11
    > +                   increment c12
    <<<<                  c8
  ]                     endwhile c8
  >>>                   c11
  [                     while c11
    -                     decrement c11
    <<< +                 increment c8
    >>>                   c11
  ]                     endwhile c11

  Fizz condition
  < [-]+                c10 = 1
  >>                    c12
  [                     if c12
    [-] << [-] >>         c12 = c10 = 0
  ]<<[                  else c10
    [-]                   reset c10
    << +++                c8 = 3
    >>>>> +               increment c13
    
    ============================================
    PRINT FIZZ
    >> +++++++ [ - < ++++++++++ > ] < c14 = 70
    .                     print F
    > +++++++ [ - < +++++ > ] <       c14 = 105
    .                     print i
    > ++++ [ - < ++++ > ] < +         c14 = 122
    ..                    print zz
    [-] > ++++ [ - < ++++++++ > ] <   c14 = 32
    .                     print space
    [-]                               reset c14
    <<<<                  c10
  ]                     endif c10


  ====================================================================================================
  Copy c9 to c12
  > [-]                 reset c11
  > [-]                 resrt c12
  <<<                   c9
  [                     while c9
    -                     decrement c9
    >> +                  increment c11
    > +                   increment c12
    <<<                   c9
  ]                     endwhile c9
  >>                    c11
  [                     while c11
    -                     decrement c11
    << +                  increment c9
    >>                    c11
  ]                     endwhile c11

  Buzz condition
  < [-] +               c10 = 1
  >>                    c12
  [                     if c12
    [-] << [-] >>         c12 = c10 = 0
  ]<<[                  else c10
    [-]                   reset c10
    < +++++               c9 = 5
    >>>> +                increment c13

    ============================================
    PRINT BUZZ
    >> [-] ++++++ [ - < +++++++++++ > ] <     c14 = 66
    .                     print B
    > +++++ [ - < ++++++++++ > ] < +          c14 = 117
    .                     print u
    +++++                                     c14 = 122
    ..                    print zz
    [-]                   reset c14 
    <<<<                  c10
  ]                     endif c10


  ====================================================================================================
  Copy c6 to c1
  <<< [-]            reset c7
  <<<<<< [-]            reset c1
  >>>>>                 c6
  [                     while c6
    -                     decrement c6
    > +                   increment c7
    <<<<<< +              increment c1
    >>>>>                 c6
  ]                     endwhile c6
  >                     c7
  [                     while c7
    -                     decrement c7
    < +                   increment c6
    >                     c7
  ]                     endwhile c7


  ====================================================================================================
  ONLY PRINT THE NUMBER IF HAVEN'T PRINTED FIZZ OR BUZZ YET
  >>> [-]+              c10 = 1
  >>>                   c13
  [                     if c13
    [-] <<< [-] >>>       c13 = c10 = 0
  ]<<<[                 else c10
    <<<<<<<<<             c1

    ====================================================================================================
    PRINT
    Prints the value in c1 in human readable format to stdout

    CONSTRAINT
    c1 between 0 and 99 inclusive

    VARIABLES
          c1    target value
    >[-]  c2    c0/10
    >[-]  c3    c0%10
    >[-]  c4    temp count 10 to 0
    >>>>>
    >[-]  c10   global else branch
    >[-]  c11   global if else temp
    >[-]  c12   global universal temp
    <<<<<<<<<<<
    [                       while c1
      >> [-]                  c3 = 0
      > [-] ++++++++++        c4 = 10

      count 10 down incrementing c3 every loop
      [                       while c4
        <<< -                   decrement c1
        >> +                    increment c3
        > -                     decrement c4
        <<<                     c1
        ___________________________________

        copy c1 to c11
        >>>>>>>>>> [-]          reset c11
        > [-]                   reset c12
        <<<<<<<<<<<             c1
        [                       while c1
          -                       decrement c1
          >>>>>>>>>> +            increment c11
          > +                     increment c12
          <<<<<<<<<<<             c1
        ]                       endwhile c1
        >>>>>>>>>>>             c12
        [                       while c12
          -                       decrement c12
          <<<<<<<<<<< +           increment c1
          >>>>>>>>>>>             c12
        ]                       endwhile c12
        ___________________________________

        if c1 == 0 then make c4 = 0 and hence quit the loop
        << [-]+                 c10 = 1
        >                       c11
        [                       if c11
          [-]<[-]>                c10 = c11 = 0
        ]<[                     else (c10)
          [-]                     c10 = 0
          <<<<<< [-]              c4  = 0
          >>>>>>                  c10
        ]                       endifelse c11 (c10)
        <<<<<<                  c4
      ]                       endwhile c4

      << +                    increment c2
      <                       c1
    ]                       endwhile c1

    > -                     decrement c2
    ___________________________________

    add 48 to c2 and c3 to convert numbers to ASCII
    >>>>>>>>>> [-]          c12 = 0
    ++++++++++ ++++++++++   c12 = 20
    ++++++++++ ++++++++++   c12 = 40
    ++++++++                c12 = 48

    [                       while c12
      -                       decrement c12
      <<<<<<<<<< +            increment c2
      > +                     increment c3
      >>>>>>>>>               c12
    ]                       endwhile c12
    ___________________________________

    print the resulting number
    <<<<<<<<<<              c2
    [                       if c2
      .                       print c2
      [-]                     c2 = 0
    ]                       endif c2

    > .                     print c3
    [-]                     c3 = 0
    ___________________________________
  
    >>>>>>>                 c10
  ]                       endif c10


  print newline
  [-] ++++++++++ .        print \n

  <<<<<                   c5
]                       endwhile c5
