
#!/bin/sh

#中企网络：

# 172.29.1.5
# su redis
# redis-server /etc/redis/redis-6380.conf
# redis-server /etc/redis/redis-6381.conf
# redis-server /etc/redis/redis-7382.conf

# 172.29.1.3
# su redis
# redis-server /etc/redis/redis-6382.conf
# redis-server /etc/redis/redis-7380.conf
# redis-server /etc/redis/redis-7381.conf

# redis-trib.rb create --replicas 1 172.29.1.5:6380 172.29.1.5:6381 172.29.1.3:6382 172.29.1.3:7380 172.29.1.3:7381 172.29.1.5:7382
#通过kill master 然后可以调整slave为master

# 172.18.100.85
# su redis
# redis-server /etc/redis/redis-6380.conf
# redis-server /etc/redis/redis-6381.conf
# redis-server /etc/redis/redis-7382.conf

# 172.18.100.87
# su redis
# redis-server /etc/redis/redis-6382.conf
# redis-server /etc/redis/redis-7380.conf
# redis-server /etc/redis/redis-7381.conf

# 172.18.100.85:6380备 172.18.100.85:6381备 172.18.100.87:6382主 172.18.100.87:7380主 172.18.100.87:7381主 172.18.100.85:7382备


#
#
#
#{"+company+"_"+type+"_"+"flow_number}:id
#incr {test1_test_flow_number}:id
#incr {test2_test_flow_number}:id
#incr {test3_test_flow_number}:id
redis-cli -h 172.18.100.85 -p 6380 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 6380 DEL
redis-cli -h 172.18.100.87 -p 7380 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 7380 DEL


redis-cli -h 172.18.100.85 -p 6381 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 6381 DEL
redis-cli -h 172.18.100.87 -p 7381 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 7381 DEL
redis-cli -h 172.18.100.85 -p 7382 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 7382 DEL
redis-cli -h 172.18.100.87 -p 6382 KEYS "{*_test_flow_number}:id" | xargs redis-cli -p 6382 DEL