:- [catom].

topla([],0).
topla([H|T],SUM):- topla(T,S), SUM is S + H.


catomic_number(NAME,CATOMIC_NUMBER) :- catom(NAME,_,_,L), topla(L,CATOMIC_NUMBER).


last([A],R):-A=<4 ->R is A; R is A-8.
last([H|T],RES):-last(T,RES).

ion(NAME,CHARGE):- catom(NAME,_,_,L), last(L,CHARGE).


duzelden([H|T],TOT):-catomic_number(N,CATNUM),duzelden([T],Tot_2) , TOT is Tot_2+CATNUM.


molecule(CATOM_LIST,TOTAL_CATOMIC_NUMBER):-duzelden(CATOM_LIST,TOTAL_CATOMIC_NUMBER).