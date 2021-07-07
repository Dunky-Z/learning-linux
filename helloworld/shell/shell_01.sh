echo "----------变量的练习---------"
address="海宁"
echo "${address}"欢迎您!
province="浙江省"
echo "${address}属于${province}"的一个县级市。

echo "----------单双引号的区别----------"
slogan="是界上最好的语言！"

language1="C++"
language2="Java"
echo '${language1} ${slogan}'
echo "${language2} ${slogan}"

echo "----------将命令的输出结果赋值给变量----------"
begin_time=`date`
sleep 1s
finish_time=`date`
echo "Begin time = ${begin_time}"
echo "Finish time = ${finish_time}"

echo "----------传递参数----------"
echo "$1 是世界上最好的语言！"
echo "$2 从入门到入土！"
function func()
{
	
	echo "$3 从入门到放弃！"
	
	echo "$4 从入门到放弃！"
}

func C++ C++  C++ Java
