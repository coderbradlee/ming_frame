#!/usr/bin/python
#coding=utf-8 tag have email function

import re,sys,os,time,datetime
import pexpect
import hashlib
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
prompt = '[$#>]'
ssh_newkey='Are you sure you want to continue connecting'
rsync_prompt='total size.*'
ip_list=["172.18.100.85","0.0.0.2"]
user="root"
password="LetsGo@123!"
local_path="/root/ming_frame/build/release/bin/protobuf_codec_test"
target_path="/root/protobuf_codec_test"
log_path="/root/test_deploy_"
command="md5sum %s" %(target_path)
server_script_exec="sh echo ming_frame"
cur_time = time.strftime('%Y_%m_%d_%H_%M')
log_file_name = log_path + cur_time + ".log"
recipientas_list=["mingming.li@renesola.com"]
 
itheme= '帐号中心生产环境版本更新发布'

for server_ip in ip_list:
    log_file = open(log_file_name, "a")
    child=pexpect.spawn("/usr/bin/rsync -e 'ssh -p 22' -avzcP %s %s@%s:%s" %(local_path, user, server_ip, target_path))
    child.logfile=log_file
     
    index = child.expect([ssh_newkey, 'password: ', pexpect.EOF, pexpect.TIMEOUT])
    if index == 0:
        child.sendline('yes')
        child.expect ('password: ')
        child.sendline(password)
        child.expect(rsync_prompt,timeout=None)
    elif index == 1:
        child.sendline(password)
        child.expect(rsync_prompt,timeout=None)
    elif index == 2:
        print "%s rsync: %s EOF ERROR %s" %('#'*10, server_ip, '#'*10)
    elif index == 3:
        print "%s rsync: %s TIMEOUT ERROR %s" %('#'*10, server_ip, '#'*10)
         
    log_file.close()
    child.close()
     
    time.sleep(5)
     
    log_file = open(log_file_name, "a")
    child=pexpect.spawn("/usr/bin/ssh -p 22 %s@%s" %(user, server_ip))
    child.logfile=log_file
     
    index = child.expect([ssh_newkey, 'password: ', pexpect.EOF, pexpect.TIMEOUT])
    if index == 0:
        child.sendline('yes')
        child.expect ('password: ')
        child.sendline(password)
        child.expect (prompt)
        child.sendline(command)
        child.expect (prompt)
        child.sendline('exit')
    elif index == 1:
        child.sendline(password)
        child.expect (prompt)
        child.sendline(command)
        child.expect (prompt)
        child.sendline('exit')
    elif index == 2:
        print "%s ssh: %s EOF ERROR %s" %('#'*10, server_ip, '#'*10)
    elif index == 3:
        print "%s ssh: %s TIMEOUT ERROR %s" %('#'*10, server_ip, '#'*10)
         
    log_file.close()
    child.close()
     
    os.system("md5sum %s | awk '{print $1}' > /root/upload_file_local.log" %(local_path))
    os.system("grep %s %s | awk '{print $1}' | egrep -v 'md5sum|omadmin' | tail -n 1  > /root/upload_file_remote.log" %(target_path, log_file_name))
         
    for localmd5 in open("/root/upload_file_local.log"):
        local_file_md5 = localmd5
     
    for remotemd5 in open("/root/upload_file_remote.log"):
        target_file_md5 = remotemd5
         
    if target_file_md5 == local_file_md5:
        log_file = open(log_file_name, "a")
        child=pexpect.spawn("/usr/bin/ssh -p 22 %s@%s" %(user, server_ip))
        child.logfile=log_file
         
        index = child.expect(['password: ', pexpect.EOF, pexpect.TIMEOUT])
        if index == 0:
            child.sendline(password)
            child.expect (prompt)
            child.sendline(server_script_exec)
            child.expect (prompt)
            child.sendline('exit')
        elif index == 1: 
            print "%s script exec: %s EOF ERROR %s" %('#'*10, server_ip, '#'*10)
        elif index == 2:
            print "%s script exec: %s TIMEOUT ERROR %s" %('#'*10, server_ip, '#'*10)
        #send_email_succeed(recipientas_list,addresser,itheme,email_server_IP,log_file_name,server_ip,local_file_md5,target_file_md5)
    else:
        print "end"
        #send_email_fail(recipientas_list,addresser,itheme,email_server_IP,log_file_name,server_ip,local_file_md5,target_file_md5)