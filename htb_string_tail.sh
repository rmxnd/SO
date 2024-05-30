#!/bin/bash
# se le variabili sono uguali ( le stringhe), e la lunghezza della variabile 'var' e' > di 113450, allora mostra gli ultimi 20 caratteri di 'var'

var="8dm7KsjU28B7v621Jls"
value="ERmFRMVZ0U2paTlJYTkxDZz09Cg"

for i in {1..40}
do
	var=$(echo $var | base64)

		#<---- If condition here:
if [[ $var == *$value* ]] && [ ${#var} -gt 113450 ]
	then
		echo $var | tail -c 20
		echo "variable lenght of var = ${#var}"
fi
done
