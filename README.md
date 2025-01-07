# RecursiveParser

A recursive desdent parser that evaluates arithmetic expressions defined by the follwoing context-free grammar described in EBNF:
    command -> expr '\n'   
    expr -> term { + term | - term } 
    term -> power { * power | / power | % power }
    power -> factor [ ^power ]
    factor -> [-] factor1
    factor1 -> ( expr ) | NUMBER
    NUMBER = [0 - 9]+

Sample1:



Sample2: 

    
