echo "----------字符串截取----------"
url="c.biancheng.net"
echo ${url: 2: 9} # 从字符串左边开始计数

url="c.biancheng.net"
echo ${url: 2}  #省略 length，截取到字符串末尾

url="c.biancheng.net"
echo ${url: 0-13: 9} # 从右边开始计数

url="c.biancheng.net"
echo ${url: 0-13}  #省略 length，直接截取到字符串末尾

url="http://c.biancheng.net/index.html"
echo ${url#*:} # 从指定字符开始截取

echo ${url#*p:} # 同上
echo ${url#*ttp:} # 同上

url="http://c.biancheng.net/index.html"
echo ${url#http://} # 不忽略内容可以不写*

url="http://c.biancheng.net/index.html"
echo ${url#*/} # 从/开始遇到第一个/就结束，如果希望匹配到最后使用两个#

url="http://c.biancheng.net/index.html"
echo ${url#*/}    #结果为 /c.biancheng.net/index.html
echo ${url##*/}   #结果为 index.html
str="---aa+++aa@@@"
echo ${str#*aa}   #结果为 +++aa@@@
echo ${str##*aa}  #结果为 @@@
