% Facts and Rules

food(peanuts).
eats(anil, peanuts).
alive(anil).

alive(X) :- \+ killed(X).

eats(anil, peanuts) :- likes(anil, peanuts).
eats(sunil, peanuts).
killed(sunil).

eats(anil, peanuts) :- eats(sunil, peanuts), \+ killed(sunil).
eats(Y, peanuts) :- eats(X, peanuts), \+ killed(X).

% Queries
% ?- food(peanuts).         % true
% ?- eats(anil, peanuts).   % true
% ?- alive(sunil).          % true
% ?- killed(anil).          % false
