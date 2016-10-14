sh /opt/tomcat/bin/shutdown.sh
pid=`ps -ef|grep tomcat|grep -v grep|awk '{print $2}'`
 for Pid in $pid
do
  kill -9 $Pid
done
#sudo fuser -km /opt/tomcat/webapps/apollo-b2b-portal-tem/file
#sudo umount /opt/tomcat/webapps/apollo-b2b-portal-tem/file
sudo umount /opt/tomcat/webapps/apollo-b2b-portal-tem/file
if [ $? -ne 0 ]
then
 sudo fuser -km /opt/tomcat/webapps/apollo-b2b-portal-tem/file
 sudo umount /opt/tomcat/webapps/apollo-b2b-portal-tem/file
fi
cd /opt/tomcat/webapps/
#mv apollo* /tmp
rm -rf apollo-b2b-portal-tem*
mv /home/apollo/apollo-b2b-portal-tem.war ./
sh /opt/tomcat/bin/startup.sh
sed -i "s#/apollo-b2b-portal.*/#/apollo-b2b-portal-tem/#g" /opt/nginx/regulations/nginx.access
sed -i "s#/apollo-b2b-portal.*/#/apollo-b2b-portal-tem/#g" /opt/nginx/conf/vhost/customer.conf
sed -i "s#/opt/tomcat/webapps/apollo-b2b-portal.*;#/opt/tomcat/webapps/apollo-b2b-portal-tem;#g" /opt/nginx/conf/vhost/customer.conf
function checkdir(){
echo "waiting  for the tomcat start.........."
if [  -d /opt/tomcat/webapps/apollo-b2b-portal-tem ] && [ -f /opt/tomcat/webapps/apollo-b2b-portal-tem/WEB-INF/classes/blacklist.properties ];then
  echo "Tomcat started, the project directory and files exist!"
  cd /opt/tomcat/webapps/apollo-b2b-portal-tem
  mkdir attachment
  mkdir file
  sed -i "s#/apollo-b2b-portal.*/#/apollo-b2b-portal-tem/#g" /opt/tomcat/webapps/apollo-b2b-portal-tem/WEB-INF/classes/blacklist.properties
else
  sleep 1
  checkdir
fi
}
checkdir
sudo mount -a
#sudo /opt/nginx/sbin/nginx
#sudo /opt/nginx/sbin/nginx -s reload >/dev/null 2>&1
echo "The deployment has finished!"
