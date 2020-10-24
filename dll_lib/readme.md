# 动态库和静态库链接规则
制作
动态    -c -fpic ->>>> -shared    -o libxxxx.so

静态    -c        ->>>>ar rcs libxxxx.a 

动态库和静态库同时存在会优先调用动态库 
如需要用静态 -static 
#### 拷贝自己制作的共享库到/lib或者/usr/lib
#### 临时设置LD_LIBRARY_PATH:
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径 
#### 永久设置, 把export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径, 设置到∼/.bashrc文件中, 然后在执行下列三种办法之一:
执行. ~/.bashrc使配置文件生效(第一个.后面有一个空格)
执行source ~/.bashrc配置文件生效
退出当前终端, 然后再次登陆也可以使配置文件生效
#### 永久设置,把export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径，设置到/etc/profile文件中
将其添加到 /etc/ld.so.cache文件中
编辑/etc/ld.so.conf文件, 加入库文件所在目录的路径
运行sudo ldconfig -v, 该命令会重建/etc/ld.so.cache文件