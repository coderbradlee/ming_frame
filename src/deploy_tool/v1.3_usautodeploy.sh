#!/bin/bash
cd /root/overseab2bdeploy/apollo_oversea_crm_trunck
echo "Now updating the files from svn server!"
svn update
echo "SVN update has done!"
#read -p "Please enter the name of the website you will deploy which are Australia,Brazil,Canada,France,Germany,Global,India,Indonesia,Italy,Japan,Mexico,Panama,Russia,Spain,Thailand,Turkey,UAE,UK,us : " websitename
#export websitename
websitename=us
#read -p "Please enter the server's ipaddress where you will deploy the project in: " ip
ip=172.18.100.76
sh /root/overseab2bdeploy/Initialization_os.sh
#change the service's taxScheduleDescription
sed -i "s/taxScheduleDescription.*$/taxScheduleDescription=Sales and Used Tax/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-service/src/main/resources/business.properties
sed -i "s/currentSiteDomain.*$/currentSiteDomain=172.18.100.76/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/baseServer.properties
sed -i "s/thresholdMax.*$/thresholdMax=2000d/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/business.properties
echo "The environment has initialized successfully!"
sed -i "s/^website.*$/website=$websitename/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/blacklist.properties
sed -i "s/^website.*$/website=United States/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/baseServer.properties
sed -i "s#/apollo-b2b-portal.*/#/apollo-b2b-portal-$websitename/#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/blacklist.properties
sed -i "s#title=RENESOLA.*#title=RENESOLA $websitename#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/i18n.txt
sed -i "s#^channel_led_name.*#channel_led_name=LED#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/i18n.txt
sed -i "s#^channel_led_image.*#channel_led_image=/file/UnitedStates/channel/image/%5EDC7703E9BE5DFE06F637244E55DA8B64B5C277C554EFA59279%5Epimgpsh_fullsize_distr%20copy.jpg#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/i18n.txt
sed -i "s#^channel_led_desc.*#channel_led_desc=Explore our wide selection of energy efficient LED lighting solutions.#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/i18n.txt
sed -i "s/^shippingFeeId/#shippingFeeId/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/business.properties
sed -i "s#^add_fee=Additional.*#add_fee=Additional fees may apply for expedited shipping and/or fixture orders totaling less than $ 2000.#g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/i18n-inquiry.txt 
echo "Now compile the project and package it!"
cd /root/overseab2bdeploy/apollo_oversea_crm_trunck
#mvn clean install
mvn clean install |tee /tmp/mvn.log
grep "BUILD FAILURE" /tmp/mvn.log
if [ $? -eq 0 ];then
	echo "The projects have mvning error,please check the mvn log in /tmp/mvn.log."
	exit 1
else 
 sleep 2
 echo "mvn compile is completed!"
 sed -i "s/thresholdMax.*$/thresholdMax=300d/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/business.properties
sed -i "s/^#shippingFeeId/shippingFeeId/g" /root/overseab2bdeploy/apollo_oversea_crm_trunck/apollo-b2b-portal/src/main/resources/business.properties
 cd apollo-b2b-portal/target
 mv apollo-b2b-portal.war apollo-b2b-portal-$websitename.war
 scp -o StrictHostKeyChecking=no *.war  apollo@$ip:/home/apollo
 sed  "s#apollo-b2b-portal-tem#apollo-b2b-portal-$websitename#g" /root/overseab2bdeploy/SetEnvWar.sh >/root/overseab2bdeploy/finalwardeploy.sh
 ssh apollo@$ip "bash" < /root/overseab2bdeploy/finalwardeploy.sh
fi
