if [[ $a != *[^0-9]* ]]&&[[ $a != 0* ]]
then
echo $a is data
else
echo $a is string
fi

