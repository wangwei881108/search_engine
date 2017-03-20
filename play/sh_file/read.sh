FILE=(1.jpg 2.jpg 3.jpg 4.jpg)
for VAR in "${FILE[@]}"
do
if [ -e "$VAR" ]
then
	echo "$VAR found"
else 
	touch "$VAR" 
fi
done
