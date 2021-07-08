echo "----------数组----------"
nums=(29 100 13 8 91 44)

arr=(20 56 "http://c.biancheng.net/shell/") # 不需要数组内元素类型相同

ages=([3]=24 [5]=19 [10]=12) # 数组长度是3

echo "----------获取数组元素----------"
n=${nums[2]}

echo ${nums[3]}

echo ${nums[*]}
echo ${nums[@]} # 获取数组所有元素

echo "nums数组大小： " ${#nums[*]}
#向数组中添加元素
nums[10]="http://c.biancheng.net/shell/"
echo "nums数组大小： "${#nums[@]}
echo "nums数组大小： "${#nums[10]}
#删除数组元素
unset nums[1]
echo "nums数组大小： "${#nums[*]}


