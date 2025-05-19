:- dynamic(plume_color/1).
:- dynamic(size/1).
:- dynamic(eye_color/1).

predict(parrot):-
  plume_color(green),
  size(small),
  eye_color(red).
  
predict(sparrow):-
  plume_color(brown),
  size(small),
  eye_color(black).
  
predict(eagle):-
  plume_color(brown),
  size(large),
  eye_color(black).

reset_facts :-
  retractall(plume_color(_)),
  retractall(eye_color(_)),
  retractall(size(_)).

main :- 
  reset_facts,
  read(PlumeAtom),
  read(SizeAtom),
  read(EyeColorAtom),
  assertz(plume_color(PlumeAtom)),
  assertz(size(SizeAtom)),
  assertz(eye_color(EyeColorAtom)),
  (predict(Bird) -> 
    write('Predicted bird: '), write(Bird), nl;
    write('No match found.'), nl
  ).
  
:- initialization(main).
