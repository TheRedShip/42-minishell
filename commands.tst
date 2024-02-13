cat Makefile && rev && wc && rev
echo bonjour && echo salut && echo toi
echo bonjour && (echo salut && echo toi)
(echo salut && echo toi) && echo bonjour
(echo salut && cat -P) && echo bonjour
(cat -P && echo toi) && echo bonjour
cat -P || echo salut
a | b | c
(a | b) | c
a | (b | c)
a && b | c
(a && b) | c
a && (b | c)
(a || b) | c
a || (b | c)
(a | b) | (c | d)
a | b | (c | d)
(a | b) | c | d
(a | b | c) | d
a | (b | c | d)
((a | b) | c) | d
(a | (b | c)) | d
(a | (b | c) | d)
