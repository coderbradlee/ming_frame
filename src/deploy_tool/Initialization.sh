#!/bin/bash
#read -p "Please enter the type of the apollo's environment,which you can choose from "production","test" and "development": " EnvironmentType
EnvironmentType=test
if [ $EnvironmentType == production ];then
	#change the B2B and Employee's baseServer.properties that include the MF,WP,PS,Cache,Upload settings
	sed -i "s/^minaServer.*$/minaServer=172.29.0.3/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s/^wpServer.*$/wpServer=172.29.0.2/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s#^cacheServer.*/#cacheServer=http://172.29.0.6:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s#^socketServerUrl.*/#socketServerUrl=ws://172.29.0.10:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s/^minaServer.*$/minaServer=172.29.0.3/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s/^wpServer.*$/wpServer=172.29.0.2/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^referenceCheckServer.*/#referenceCheckServer=http://172.29.0.15:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^permissionCheckServer.*/#permissionCheckServer=http://172.29.0.15:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^cacheServer.*/#cacheServer=http://172.29.0.6:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^socketServerUrl.*/#socketServerUrl=ws://172.29.0.10:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	#change the mysql's ipaddress and password that the servers will connect to!
        #change the Model's db.properties"
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s/^db.password.master.*$/db.password.master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
	#change the MF's db.properties"
	sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
	sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
	sed -i "s/^db.password.master.*$/db.password.master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
	sed -i "s/^db.password.slave.*$/db.password.slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
	#change the PS's db.properties"
	sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
	sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
	sed -i "s/^db.password.master.*$/db.password.master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
	sed -i "s/^db.password.slave.*$/db.password.slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
	#change the WP's db.properties"
	sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
	sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
	sed -i "s/^db.password.master.*$/db.password.master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
	sed -i "s/^db.password.slave.*$/db.password.slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
	#change the apollo-security's db.properties"
	sed -i "s/^db.password.master.*$/db.password.master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
	sed -i "s/^db.password.slave.*$/db.password.slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
	sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
	sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
	#change the b2b's db.properties
	sed -i "s#^url_master.*/#url_master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
	sed -i "s#^url_slave.*/#url_slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
	sed -i "s/^password_master.*$/password_master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
	sed -i "s/^password_slave.*$/password_slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
	#change the employee's db.properties
	sed -i "s#^url_master.*/#url_master=jdbc:mysql://172.29.0.7/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
	sed -i "s#^url_slave.*/#url_slave=jdbc:mysql://172.29.0.8/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
	sed -i "s/^password_master.*$/password_master=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
	sed -i "s/^password_slave.*$/password_slave=renesola.123/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
elif [ $EnvironmentType == test ];then
	#change the B2B and Employee's baseServer.properties that include the MF,WP,PS,Cache,Upload settings
	#sed -i "s/^minaServer.*$/minaServer=172.18.100.207/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
        #sed -i "s/^minaServer.*$/minaServer=172.18.100.207/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/writer.properties
        #sed -i "s/^wpServer.*$/wpServer=172.18.100.228/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/writer.properties
	#sed -i "s#^cacheServer.*/#cacheServer=http://172.18.100.201:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/cacheServer.properties
        sed -i "s#^cacheServer.*#cacheServer=http://172.18.100.85:8088/apollo#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-cache-api/src/main/resources/cacheServer.properties
	sed -i "s#^socketServerUrl.*/#socketServerUrl=ws://172.18.100.72:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
#	sed -i "s/^minaServer.*$/minaServer=172.18.100.207/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
#	sed -i "s/^wpServer.*$/wpServer=172.18.100.228/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
 #      sed -i "s/^minaServer.*$/minaServer=172.18.100.207/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/writer.properties
  #      sed -i "s/^wpServer.*$/wpServer=172.18.100.228/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/writer.properties
#	sed -i "s#^referenceCheckServer.*/#referenceCheckServer=http://172.18.100.223:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
#	sed -i "s#^permissionCheckServer.*/#permissionCheckServer=http://172.18.100.223:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
        sed -i "s#^referenceCheckServer.*/#referenceCheckServer=http://172.18.100.223:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/service.properties
        sed -i "s#^permissionCheckServer.*/#permissionCheckServer=http://172.18.100.223:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/service.properties
#	sed -i "s#^cacheServer.*/#cacheServer=http://172.18.100.85:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
#	sed -i "s#^socketServerInternalUrl.*/#socketServerInternalUrl=ws://172.18.100.72:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
 #       sed -i "s#^socketServerPublicUrl.*/#socketServerPublicUrl=ws://172.18.100.72:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
   #change the dao's db.properities
         sed -i "s/^minaServer.*$/minaServer=172.18.100.207/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-dao/src/main/resources/writer.properties
        sed -i "s/^wpServer.*$/wpServer=172.18.100.228/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-dao/src/main/resources/writer.properties
	#change the B2B and Employee's baseServer.properties that include the MF,WP,PS,Cache,Upload settings
	#change the mysql's ipaddress and password that the servers will connect to!
        #change the model's db.properities
        sed -i "s#^db.url.master.*?#db.url.master=jdbc:mysql://172.18.22.202:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties 
        sed -i "s#^db.url.slave.*?#db.url.slave=jdbc:mysql://172.18.22.203:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties 
        sed -i "s/^db.password.master.*$/db.password.master=renes0la.xx/g"  /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renes0la.xx/g"  /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        #change the b2b's db.properties
        sed -i "s#^url_master.*?#url_master=jdbc:mysql://172.18.22.202:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s#^url_slave.*?#url_slave=jdbc:mysql://172.18.22.203:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_master.*$/password_master=renes0la.xx/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_slave.*$/password_slave=renes0la.xx/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s#^wf.msg.queue.accessUrl.*#wf.msg.queue.accessUrl=failover:(tcp://172.18.100.204:61616)?initialReconnectDelay=100#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        #change the employee's db.properties
        sed -i "s#^url_master.*?#url_master=jdbc:mysql://172.18.22.202:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s#^url_slave.*?#url_slave=jdbc:mysql://172.18.22.203:3306/apollo_os?#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_master.*$/password_master=renes0la.xx/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_slave.*$/password_slave=renes0la.xx/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties	
	#change the service's taxScheduleDescription
	#sed -i "s/taxScheduleDescription.*$/taxScheduleDescription=Sales Tax/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-service/src/main/resources/business.properties
elif [ $EnvironmentType == development ];then
	#change the B2B and Employee's baseServer.properties that include the MF,WP,PS,Cache,Upload settings
	sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
        sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/writer.properties
        sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/writer.properties
         sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal-ext-cn/src/main/resources/baseServer.properties
        sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal-ext-cn/src/main/resources/baseServer.properties
        sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal-ext-cn/src/main/resources/writer.properties
        sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal-ext-cn/src/main/resources/writer.properties
	sed -i "s#^cacheServer.*/#cacheServer=http://172.18.100.201:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s#^socketServerUrl.*/#socketServerUrl=ws://172.18.100.202:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/baseServer.properties
	sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
        sed -i "s/^minaServer.*$/minaServer=172.18.100.205/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/writer.properties
        sed -i "s/^wpServer.*$/wpServer=172.18.100.206/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/writer.properties
	sed -i "s#^referenceCheckServer.*/#referenceCheckServer=http://172.18.100.200:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^permissionCheckServer.*/#permissionCheckServer=http://172.18.100.200:8082/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	sed -i "s#^cacheServer.*/#cacheServer=http://172.18.100.201:8088/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	#sed -i "s#^socketServerUrl.*/#socketServerUrl=ws://172.18.100.202:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
        sed -i "s#^socketServerInternalUrl.*/#socketServerInternalUrl=ws://172.18.100.202:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
        sed -i "s#^socketServerPublicUrl.*/#socketServerPublicUrl=ws://172.18.100.202:8080/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/baseServer.properties
	#change the mysql's ipaddress and password that the servers will connect to!
	#change the model's db.properites
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties 
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.18.100.92/#g"  /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s/^db.password.master.*$/db.password.master=renesola/g"  /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola/g"  /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-model/src/main/resources/db.properties
        #change the MF's db.properties"
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
        sed -i "s/^db.password.master.*$/db.password.master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-files/src/main/resources/db.properties
        #change the PS's db.properties"
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
        sed -i "s/^db.password.master.*$/db.password.master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-permission-service/src/main/resources/db.properties
        #change the WP's db.properties"
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
        sed -i "s/^db.password.master.*$/db.password.master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-website-platform/src/main/resources/db.properties
        #change the apollo-security's db.properties"
        sed -i "s/^db.password.master.*$/db.password.master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
        sed -i "s/^db.password.slave.*$/db.password.slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
        sed -i "s#^db.url.master.*/#db.url.master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
        sed -i "s#^db.url.slave.*/#db.url.slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-security/src/main/resources/db.properties
        #change the b2b's db.properties
        sed -i "s#^url_master.*/#url_master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s#^url_slave.*/#url_slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_master.*$/password_master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_slave.*$/password_slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-b2b-portal/src/main/resources/jdbc.properties
        #change the employee's db.properties
        sed -i "s#^url_master.*/#url_master=jdbc:mysql://172.18.100.91/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s#^url_slave.*/#url_slave=jdbc:mysql://172.18.100.92/#g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_master.*$/password_master=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
        sed -i "s/^password_slave.*$/password_slave=renesola/g" /root/overseab2bdeploy/apollo_crm_trunck_v1.1/apollo-master-data-portal/src/main/resources/jdbc.properties
fi
echo "The initialization of the environment has done!"
