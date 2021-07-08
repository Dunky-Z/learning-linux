echo "----------字符串拼接----------"
name="Shell"
logo="学习记录！"

str1=$name$logo  #中间不能有空格
str2="$name $logo"  #如果被双引号包围，那么中间可以有空格
str3=$name": "$logo  #中间可以出现别的字符串
str4="$name: $logo"  #这样写也可以
str5="${name}Script: ${logo}"  #这个时候需要给变量名加上大括号

echo $str1
echo $str2
echo $str3
echo $str4
echo $str5
