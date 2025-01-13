# RecursiveParser

A recursive desdent parser that evaluates arithmetic expressions defined by the follwoing context-free grammar described in EBNF: <br>
    command -> expr '\n'   <br>
    expr -> term { + term | - term } <br>
    term -> power { * power | / power | % power } <br>
    power -> factor [ ^power ] <br>
    factor -> [-] factor1 <br>
    factor1 -> ( expr ) | NUMBER <br>
    NUMBER = [0 - 9]+ <br>

<h3>Sample1:</h3>
<strong>Input:</strong> 5 + 6 ∗ 2 ∧ 2 ∧ 2  <br>
<strong>Output:</strong> <br>
    &emsp; 5 &emsp; NUMBER <br>
    &emsp; + &emsp;	PLUS <br>
    &emsp; 6 &emsp;	NUMBER <br>
    &emsp; ∗ &emsp;	MULT <br>
    &emsp; 2 &emsp;	NUMBER <br>
    &emsp; ∧ &emsp;	POWER <br>
    &emsp; 2 &emsp;	NUMBER <br>
    &emsp; ∧ &emsp;	POWER <br>
    &emsp; 2 &emsp;	NUMBER <br>
   &emsp; Result: 101


<h3>Sample2:</h3>
<strong>Input:</strong> 19 % 5 ∗ 10 / ( 2 ∧ 2 ) <br>
<strong>Output:</strong><br>
     &emsp; 19  &emsp;	NUMBER <br>
     &emsp; %  &emsp;	REMAINDER <br>
     &emsp; 5  &emsp;	NUMBER <br>
     &emsp; ∗  &emsp;	MULT <br>
     &emsp; 10  &emsp;	NUMBER <br>
     &emsp; /  &emsp;	DIVIDE <br>
     &emsp; (  &emsp;	LPAREN <br>
     &emsp; 2  &emsp;	NUMBER <br>
     &emsp; ∧  &emsp;	POWER <br>
     &emsp; 2  &emsp;	NUMBER <br>
     &emsp; )  &emsp;	RPAREN <br>
     &emsp; Result: 10

    
